/**********************************************************************************
// Graphics (Código Fonte)
// 
// Criação:     06 Abr 2011
// Atualização: 27 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Graphics é uma classe que faz uso das funções do Direct3D para 
//              acessar o hardware de aceleração gráfica da placa de vídeo.
//
**********************************************************************************/

#include "Graphics.h"

// -------------------------------------------------------------------------------
// Inicialização de membros estáticos da classe

ID3D11Device * Graphics::device = nullptr;            // dispositivo gráfico
ID3D11DeviceContext * Graphics::context = nullptr;    // contexto do dispositivo gráfico 
D3D11_VIEWPORT Graphics::viewport = {};               // viewport

// ------------------------------------------------------------------------------

Graphics::Graphics() 
{
    // inicializa variáveis membro
    swapChain           = nullptr;                    // ponteiro para swap chain 
    renderTargetView    = nullptr;                    // render target view
    blendState          = nullptr;                    // mistura de cores
    featureLevel        = D3D_FEATURE_LEVEL_11_0;     // versão do Direct3D
    
    bgColor[0]          = 0.0f;                       // Red
    bgColor[1]          = 0.0f;                       // Green
    bgColor[2]          = 0.0f;                       // Blue
    bgColor[3]          = 0.0f;                       // Alpha (0 = transparente)

    vSync               = false;                      // vertical sync desligado
}

// ------------------------------------------------------------------------------

Graphics::~Graphics()
{
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
    if (context)
    {
        // restaura ao estado original
        context->ClearState();
        context->Release();
        context = nullptr;
    }

    // libera dispositivo gráfico
    if (device)
    {
        device->Release();
        device = nullptr;
    }
}

// -----------------------------------------------------------------------------

bool Graphics::Initialize(Window * window)
{
    // -------------------------------
    // Dispositivo Direct3D
    // -------------------------------

    uint createDeviceFlags = 0;

#ifdef _DEBUG
    // exibe mensagens de erro do Direct3D em modo de depuração
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    // cria objeto para acessar dispositivo Direct3D
    if FAILED(
        D3D11CreateDevice(
            NULL,                           // adaptador de vídeo (NULL = adaptador padrão)
            D3D_DRIVER_TYPE_HARDWARE,       // tipo de driver D3D (Hardware, Reference ou Software)
            NULL,                           // ponteiro para rasterizador em software
            createDeviceFlags,              // modo de depuração ou modo normal
            NULL,                           // featureLevels do Direct3D (NULL = maior suportada)
            0,                              // tamanho do vetor featureLevels
            D3D11_SDK_VERSION,              // versão do SDK do Direct3D
            &device,                        // guarda o dispositivo D3D criado
            &featureLevel,                  // versão do Direct3D utilizada
            &context))                      // contexto do dispositivo D3D
        return false;

    // -------------------------------
    // Cor de Fundo do Direct3D
    // -------------------------------
    
    // ajusta a cor de fundo do backbuffer
    // para a mesma cor de fundo da janela
    COLORREF color = window->Color();

    bgColor[0] = GetRValue(color)/255.0f;     // Red
    bgColor[1] = GetGValue(color)/255.0f;     // Green
    bgColor[2] = GetBValue(color)/255.0f;     // Blue
    bgColor[3] = 1.0f;                        // Alpha (1 = cor sólida)

    // -------------------------------
    // Interfaces DXGI
    // -------------------------------

    // cria objeto para a infraestrutura gráfica
    IDXGIDevice * dxgiDevice = nullptr;
    if FAILED(device->QueryInterface(__uuidof(IDXGIDevice), (void**) &dxgiDevice))
        return false;

    // cria objeto para adaptador de vídeo (placa gráfica)
    IDXGIAdapter * dxgiAdapter = nullptr;
    if FAILED(dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**) &dxgiAdapter))
        return false;

    // cria objeto para a fábrica DXGI
    IDXGIFactory * dxgiFactory = nullptr;
    if FAILED(dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**) &dxgiFactory))
        return false;

    // -------------------------------
    // Swap Chain 
    // -------------------------------

    // descrição de uma swap chain
    DXGI_SWAP_CHAIN_DESC swapDesc = {0};
    swapDesc.BufferDesc.Width = uint(window->Width());          // largura do backbuffer
    swapDesc.BufferDesc.Height = uint(window->Height());        // altura do backbuffer
    swapDesc.BufferDesc.RefreshRate.Numerator = 60;             // taxa de atualização em hertz 
    swapDesc.BufferDesc.RefreshRate.Denominator = 1;            // numerador é um inteiro e não um racional
    swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;    // formato de cores RGBA 8 bits
    swapDesc.SampleDesc.Count = 1;                              // amostras por pixel (antialiasing)
    swapDesc.SampleDesc.Quality = 0;                            // nível de qualidade da imagem
    swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;     // utilize superfície como RENDER-TARGET
    swapDesc.BufferCount = 2;                                   // número de buffers (front + back)
    swapDesc.OutputWindow = window->Id();                       // identificador da janela
    swapDesc.Windowed = (window->Mode() != FULLSCREEN);         // modo janela ou tela cheia
    swapDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;        // descarta superfície após apresentação
    swapDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;    // muda a resolução do monitor em tela cheia

    // cria uma swap chain
    if FAILED(dxgiFactory->CreateSwapChain(device, &swapDesc, &swapChain))
        return false;

    // impede a DXGI de monitorar ALT-ENTER e alternar entre windowed/fullscreen
    if FAILED(dxgiFactory->MakeWindowAssociation(window->Id(), DXGI_MWA_NO_ALT_ENTER))
        return false;

    // -------------------------------
    // Render Target
    // -------------------------------

    // pega a superfície backbuffer de uma swapchain
    ID3D11Texture2D * backBuffer = nullptr;
    if FAILED(swapChain->GetBuffer(0, __uuidof(backBuffer), (void**)(&backBuffer)))
        return false;

    // cria uma render-target view do backbuffer
    if FAILED(device->CreateRenderTargetView(backBuffer, NULL, &renderTargetView))
        return false;

    // liga uma render-target ao estágio output-merger
    context->OMSetRenderTargets(1, &renderTargetView, nullptr);
    
    // -------------------------------
    // Viewport / Rasterizer
    // -------------------------------

    // configura uma viewport
    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
    viewport.Width    = float(window->Width());
    viewport.Height   = float(window->Height());
    viewport.MinDepth = 0.0f;
    viewport.MaxDepth = 1.0f;

    // liga a viewport ao estágio de rasterização
    context->RSSetViewports(1, &viewport); 

    // ---------------------------------------------
    // Blend State
    // ---------------------------------------------

    // Equação de mistura de cores (blending):
    // finalColor = SrcColor * SrcBlend <OP> DestColor * DestBlend

    // Combinando superfícies transparentes (Alpha Blending)
    // finalColor = SrcColor * ScrAlpha + DestColor * (1-SrcAlpha)

    D3D11_BLEND_DESC blendDesc = { };
    blendDesc.AlphaToCoverageEnable = false;                                // destaca a silhueta dos sprites
    blendDesc.IndependentBlendEnable = false;                               // usa mesma mistura para todos os render targets
    blendDesc.RenderTarget[0].BlendEnable = true;                           // habilita o blending
    blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;             // fator de mistura da fonte 
    blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;        // destino da mistura RGB é o alpha invertido 
    blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;                 // operação de adição na mistura de cores
    blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_SRC_ALPHA;        // fonte da mistura Alpha é o alpha do pixel shader
    blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;   // destino da mistura Alpha é o alpha invertido
    blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;            // operação de adição na mistura de cores
    blendDesc.RenderTarget[0].RenderTargetWriteMask = 0x0F;                 // componentes de cada pixel que podem ser sobrescritos

    // cria a blend state
    if FAILED(device->CreateBlendState(&blendDesc, &blendState))
        return false;

    // liga a blend state ao estágio Output-Merger
    context->OMSetBlendState(blendState, nullptr, 0xffffffff);

    // -------------------------------
    // Libera interfaces DXGI
    // -------------------------------

    dxgiDevice->Release();
    dxgiAdapter->Release();
    dxgiFactory->Release();
    backBuffer->Release();

    // inicialização bem sucedida
    return true;
}

// -----------------------------------------------------------------------------
