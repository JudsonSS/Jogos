/**********************************************************************************
// Graphics (Código Fonte)
// 
// Criação:		06 Abr 2011
// Atualização:	24 Mai 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Graphics é uma classe que faz uso das funções do Direct3D para 
//              acessar o hardware de aceleração gráfica da placa de vídeo.
//
**********************************************************************************/

#include "Graphics.h"

// -------------------------------------------------------------------------------
// Inicialização de membros estáticos da classe

ID3D11Device * Graphics::d3dDev = nullptr;					// dispositivo gráfico
ID3D11DeviceContext * Graphics::d3dDevContext = nullptr;	// contexto do dispositivo gráfico 
D3D11_VIEWPORT	Graphics::viewport = { 0 };					// viewport

// ------------------------------------------------------------------------------

Graphics::Graphics() 
{
	// inicializa variáveis membro
	swapChain			= nullptr;					// ponteiro para swap chain 
	renderTargetView	= nullptr;					// render target view
	blendState          = nullptr;					// mistura de cores
	depthStencilView    = nullptr;					// depth stencil view
	depthStencilBuffer  = nullptr;					// buffer de profundidade
	featureLevel        = D3D_FEATURE_LEVEL_11_0;	// versão do Direct3D
	
	bgColor[0]			= 0.0f;						// componente Red
	bgColor[1]			= 0.0f;						// componente Green
	bgColor[2]			= 0.0f;						// componente Blue
	bgColor[3]			= 0.0f;						// componente Alpha (sólido)

	antialiasing		= 1;						// número de amostras para antialiasing
	quality				= 0;						// nível de qualidade das amostras
	vSync               = false;					// vertical sync desligado

	// define flags de depuração quando compilador estiver no modo Debug
	uint createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	// cria objeto para acessar dispositivo gráfico
	D3D11CreateDevice(
		NULL,								// adaptador de vídeo (NULL = adaptador padrão)
		D3D_DRIVER_TYPE_HARDWARE,			// tipo de driver D3D (Hardware, Reference ou Software)
		NULL,								// ponteiro para rasterizador em software
		createDeviceFlags,					// modo de depuração ou modo normal
		NULL,								// featureLevels do Direct3D (NULL = maior suportada)
		0,									// tamanho do vetor featureLevels
		D3D11_SDK_VERSION,                  // versão do SDK do Direct3D
		&d3dDev,							// guarda o dispositivo D3D criado
		&featureLevel,						// versão do Direct3D utilizada
		&d3dDevContext);					// contexto do dispositivo D3D
}

// ------------------------------------------------------------------------------

Graphics::~Graphics()
{
	// libera depth stencil view
	if (depthStencilView)
	{
		depthStencilView->Release();
		depthStencilView = nullptr;
	}

	// libera buffer de profundidade
	if (depthStencilBuffer)
	{
		depthStencilBuffer->Release();
		depthStencilBuffer = nullptr;
	}

	// libera blend state
	if (blendState)
	{
		blendState->Release();
		blendState = nullptr;
	}

	// libera render-target
	if (renderTargetView)
	{
		renderTargetView->Release();
		renderTargetView = nullptr;
	}

	// libera swap chain
	if (swapChain)
	{
		// Direct3D é incapaz de fechar quando em tela cheia
		swapChain->SetFullscreenState(false, NULL);
		swapChain->Release();
		swapChain = nullptr;
	}

	// libera contexto do dispositivo gráfico
	if (d3dDevContext)
	{
		// restaura ao estado original
		d3dDevContext->ClearState();
		d3dDevContext->Release();
		d3dDevContext = nullptr;
	}

	// libera dispositivo gráfico
	if (d3dDev)
	{
		d3dDev->Release();
		d3dDev = nullptr;
	}
}

// -----------------------------------------------------------------------------

// ajusta o número de amostras para antialiasing
void Graphics::Antialiasing(uint samples)
{ 
	antialiasing = (samples > D3D11_MAX_MULTISAMPLE_SAMPLE_COUNT ? D3D11_MAX_MULTISAMPLE_SAMPLE_COUNT : samples);

	uint maxQuality = 0;
	d3dDev->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, samples, &maxQuality);
	
	if (maxQuality != 0)
		quality = maxQuality-1;
	else
	{
		antialiasing = 1;
		quality = 0;
	}
}

// -----------------------------------------------------------------------------

bool Graphics::Initialize(Window * window)
{
	// ajusta a cor de fundo do backbuffer
	// para a mesma cor de fundo da janela
	COLORREF color = window->Color();

	bgColor[0] = GetRValue(color)/255.0f;						// componente Red
	bgColor[1] = GetGValue(color)/255.0f;						// componente Green
	bgColor[2] = GetBValue(color)/255.0f;						// componente Blue
	bgColor[3] = 1.0f;											// componente Alpha (sólido)

	// -------------------------------
	// Captura interfaces DXGI
	// -------------------------------

	// pega um ponteiro para o dispositivo Direct3D
	IDXGIDevice * dxgiDevice = nullptr;
	if FAILED(d3dDev->QueryInterface(__uuidof(IDXGIDevice), (void**) &dxgiDevice))
		return false;

	// pega adaptador controlado pelo dispositivo Direct3D (d3dDev)
	IDXGIAdapter * dxgiAdapter = nullptr;
	if FAILED(dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**) &dxgiAdapter))
		return false;

	// pega um ponteiro para a DXGIFactory do adaptador
	IDXGIFactory * dxgiFactory = nullptr;
	if FAILED(dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**) &dxgiFactory))
		return false;

	// -------------------------------
	// Enumera Modos de Vídeo 
	// -------------------------------
	
	// enumerar os modos de vídeo garante a realização de um pageflip (mudança de apontador) 
	// no lugar de um bitblit (cópia de bits) quando se está em modo tela cheia

	// enumera apenas a primeira saída do adaptador (ligada ao monitor padrão)
	IDXGIOutput * dxgiOutput = nullptr;
	dxgiAdapter->EnumOutputs(0, &dxgiOutput);

	// pega o número de modos de vídeo suportados pelo monitor no formato DXGI_FORMAT_R8G8B8A8_UNORM
	uint numModes = 0;
	dxgiOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_SCALING, &numModes, NULL);
	
	// cria uma lista dos modos de vídeo suportados por essa combinação de placa de vídeo e monitor
	DXGI_MODE_DESC * displayModeList = new DXGI_MODE_DESC[numModes];
	dxgiOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_SCALING, &numModes, displayModeList);
	
	// pega as dimensões da tela
	uint screenWidth  = GetSystemMetrics(SM_CXSCREEN);
	uint screenHeight = GetSystemMetrics(SM_CYSCREEN);

	// numerador e denominador da taxa de atualização do vídeo
	uint num = 60;
	uint den = 1;

	// atualiza numerador e denominador com os valores de um modo de vídeo compatível com as dimensões da tela
	for (uint i = 0; i < numModes; ++i)
	{
		if (displayModeList[i].Width == screenWidth && displayModeList[i].Height == screenHeight)
		{
			num = displayModeList[i].RefreshRate.Numerator;
			den = displayModeList[i].RefreshRate.Denominator;
		}
	}

	// -------------------------------
	// Cria uma Swap Chain 
	// -------------------------------

	// descrição de uma swap chain
	DXGI_SWAP_CHAIN_DESC swapDesc = {0};
	swapDesc.BufferDesc.Width = uint(window->Width());			// largura do backbuffer
	swapDesc.BufferDesc.Height = uint(window->Height());		// altura do backbuffer
	swapDesc.BufferDesc.RefreshRate.Numerator = num;			// taxa de atualização em hertz 
	swapDesc.BufferDesc.RefreshRate.Denominator = den;			// numerador é um inteiro e não um racional
	swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	// formato de cores RGBA 8 bits
	swapDesc.SampleDesc.Count = antialiasing;					// amostras por pixel (antialiasing)
	swapDesc.SampleDesc.Quality = quality;						// nível de qualidade da imagem
	swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;		// utilize superfície como RENDER TARGET
	swapDesc.BufferCount = 1;									// número de backbuffers
	swapDesc.OutputWindow = window->Id();						// identificador da janela
	swapDesc.Windowed = (window->Mode() == WINDOWED);			// modo janela ou tela cheia
	swapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;				// descarta superfície após apresentação
	swapDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;	// usa tamanho do backbuffer para tela cheia

	// cria uma swap chain
	if FAILED(dxgiFactory->CreateSwapChain(d3dDev, &swapDesc, &swapChain))
		return false;

	// impede a DXGI de monitorar ALT-ENTER e alternar entre windowed/fullscreen
	if FAILED(dxgiFactory->MakeWindowAssociation(window->Id(), DXGI_MWA_NO_ALT_ENTER))
		return false;

	// -------------------------------
	// Cria uma Render Target View
	// -------------------------------

	// pega a superfície backbuffer de uma swapchain
	ID3D11Texture2D * backBuffer = nullptr;
	if FAILED(swapChain->GetBuffer(0, __uuidof(backBuffer), (void**)(&backBuffer)))
		return false;

	// cria uma render-target view do backbuffer
	if FAILED(d3dDev->CreateRenderTargetView(backBuffer, NULL, &renderTargetView))
		return false;

	// -------------------------------
	// Cria um Depth/Stencil Buffer
	// -------------------------------

	// descrição do buffer de profundidade 
	D3D11_TEXTURE2D_DESC depthStencilDesc = {0};

	// configura o buffer de profundidade
	depthStencilDesc.Width = uint(window->Width());				// largura da textura
	depthStencilDesc.Height = uint(window->Height());			// altura da textura 
	depthStencilDesc.MipLevels = 1;								// número de níveis mip
	depthStencilDesc.ArraySize = 1;								// o número de texturas no vetor
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;	// formato dos texels (24 bits)
	depthStencilDesc.SampleDesc.Count = antialiasing;			// amostras por pixel (antialiasing)
	depthStencilDesc.SampleDesc.Quality = quality;				// nível de qualidade da imagem
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;				// uso da textura (apenas GPU)
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;		// associa textura ao pipeline D3D
	depthStencilDesc.CPUAccessFlags = 0;						// acesso da CPU a textura (nenhum)
	depthStencilDesc.MiscFlags = 0;								// flag opcional

	// usa textura como buffer de profundidade
	if FAILED(d3dDev->CreateTexture2D(&depthStencilDesc, NULL, &depthStencilBuffer))
		return false;

	// cria uma depth/stencil view para o backbuffer
	if FAILED(d3dDev->CreateDepthStencilView(depthStencilBuffer, NULL, &depthStencilView))
		return false;
	
	// -------------------------------
	// Output/Viewport/Rasterizer
	// -------------------------------

	// liga uma render-target ao estágio output-merger
	d3dDevContext->OMSetRenderTargets(1, &renderTargetView, depthStencilView);

	// configura uma viewport
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = float(window->Width());
	viewport.Height = float(window->Height());
    viewport.MinDepth = 0.0f;
    viewport.MaxDepth = 1.0f;

	// liga a viewport ao estágio de rasterização
    d3dDevContext->RSSetViewports(1, &viewport); 

	// ---------------------------------------------
	// Blend State
	// ---------------------------------------------

	// Equação de mistura de cores (blending):
	// finalColor = SrcColor * SrcBlend <OP> DestColor * DestBlend

	// Combinando superfícies transparentes (Alpha Blending)
	// finalColor = SrcColor * ScrAlpha + DestColor * (1-SrcAlpha)

	D3D11_BLEND_DESC blendDesc = { 0 };
	blendDesc.AlphaToCoverageEnable = false;								// destaca a silhueta dos sprites
	blendDesc.IndependentBlendEnable = false;								// usa mesma mistura para todos os render targets
	blendDesc.RenderTarget[0].BlendEnable = true;							// habilita o blending
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;				// fator de mistura da fonte 
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;		// destino da mistura RGB é o alpha invertido 
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;					// operação de adição na mistura de cores
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;				// fonte da mistura Alpha é o alpha do pixel shader
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;			// destino da mistura Alpha é o alpha invertido
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;			// operação de adição na mistura de cores
	blendDesc.RenderTarget[0].RenderTargetWriteMask = 0x0F;					// componentes de cada pixel que podem ser sobrescritos

	// cria a blend state
	if FAILED(d3dDev->CreateBlendState(&blendDesc, &blendState))
		return false;

	// liga a blend state ao estágio Output-Merger
	d3dDevContext->OMSetBlendState(blendState, nullptr, 0xffffffff);

	// -------------------------------
	// Libera interfaces DXGI
	// -------------------------------

	dxgiDevice->Release();
	dxgiAdapter->Release();
	dxgiFactory->Release();
	dxgiOutput->Release();
	backBuffer->Release();

	// inicialização bem sucedida
	return true;
}

// -----------------------------------------------------------------------------
