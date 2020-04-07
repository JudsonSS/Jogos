/**********************************************************************************
// Graphics (Arquivo de Cabeçalho)
// 
// Criação:		06 Abr 2011
// Atualização:	24 Mai 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Graphics é uma classe que faz uso das funções do Direct3D para 
//              acessar o hardware de aceleração gráfica da placa de vídeo.
//
**********************************************************************************/

#ifndef _DESENVJOGOS_GRAPHICS_H_
#define _DESENVJOGOS_GRAPHICS_H_

// --------------------------------------------------------------------------------
// Inclusões

#include <dxgi.h>			// infraestrutura gráfica do DirectX
#include <d3d11.h>			// principais funções do Direct3D
#include "Window.h"			// cria e configura uma janela do Windows
#include "Types.h"			// tipos específicos da engine

// --------------------------------------------------------------------------------

class Graphics
{
private:
	static ID3D11Device        * d3dDev;					// dispositivo gráfico
	static ID3D11DeviceContext * d3dDevContext;				// contexto do dispositivo gráfico
	D3D_FEATURE_LEVEL			 featureLevel;				// versão D3D suportada pelo hardware
	IDXGISwapChain             * swapChain;					// swap chain 			
	ID3D11RenderTargetView     * renderTargetView;			// render target view do backbuffer
	ID3D11BlendState           * blendState;				// configuração da mistura de cores
	ID3D11Texture2D            * depthStencilBuffer;		// buffer de profundidade e estampa
	ID3D11DepthStencilView     * depthStencilView;			// depth-stencil view
	static D3D11_VIEWPORT		 viewport;					// viewport
	float						 bgColor[4];				// cor de fundo do backbuffer
	uint						 antialiasing;				// número de amostras para antialiasing
	uint						 quality;					// nível de qualidade das amostras
	bool						 vSync;						// vertical sync 

public:
	Graphics();												// constructor
	~Graphics();											// destructor

	static ID3D11Device * Device();							// retorna dispositivo Direct3D
	static ID3D11DeviceContext * Context();					// retorna o contexto do dispositivo D3D
	static D3D11_VIEWPORT Viewport();						// retorna a viewport utilizada

	void Antialiasing(uint samples);						// ajusta o número de amostras para antialiasing
	void VSync(bool state);									// liga/desliga vertical sync
	void Clear();											// limpa o backbuffer com a cor de fundo
	bool Present();											// apresenta desenho na tela
	bool Initialize(Window * window);						// inicializa o Direct3D
	
};

// --------------------------------------------------------------------------------
// Métodos Inline

// retorna dispositivo Direct3D
inline ID3D11Device * Graphics::Device()
{ return d3dDev; }

// retorna o contexto do dispositivo D3D
inline ID3D11DeviceContext * Graphics::Context()
{ return d3dDevContext; }

// retorna a viewport utilizada
inline D3D11_VIEWPORT Graphics::Viewport()
{	return viewport; }

// liga/desliga vertical sync
inline void Graphics::VSync(bool state)
{ vSync = state; }

// limpa o bacbuffer para o próximo quadro
inline void Graphics::Clear()
{ 	d3dDevContext->ClearRenderTargetView(renderTargetView, bgColor); 
	d3dDevContext->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0); }

// apresenta desenho na tela (troca backbuffer com frontbuffer)
inline bool Graphics::Present()
{ return SUCCEEDED(swapChain->Present(vSync, NULL)); }

// --------------------------------------------------------------------------------

#endif