/**********************************************************************************
// Renderer (Código Fonte)
//
// Criação:     11 Mai 2014
// Atualização: 13 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Define um renderizador de sprites
//
**********************************************************************************/

#include "Renderer.h"
#include <algorithm>
#include <d3dcompiler.h>
#include <DirectXMath.h>
using namespace DirectX;

// ---------------------------------------------------------------------------------

struct Vertex
{
    XMFLOAT3 pos;
    XMFLOAT4 color;
    XMFLOAT2 tex;
};

// ---------------------------------------------------------------------------------

Renderer::Renderer()
{
    inputLayout    = nullptr;
    vertexShader   = nullptr;
    pixelShader    = nullptr;
    rasterState    = nullptr;
    sampler        = nullptr;
    vertexBuffer   = nullptr;
    indexBuffer    = nullptr;
    constantBuffer = nullptr;

    vertexBufferPosition = 0;
}

// ---------------------------------------------------------------------------------

Renderer::~Renderer()
{
    if (constantBuffer)
    {
        constantBuffer->Release();
        constantBuffer = nullptr;
    }
    
    if (indexBuffer)
    {
        indexBuffer->Release();
        indexBuffer = nullptr;
    }

    if (vertexBuffer)
    {
        vertexBuffer->Release();
        vertexBuffer = nullptr;
    }

    if (sampler)
    {
        sampler->Release();
        sampler = nullptr;
    }

    if (rasterState)
    {
        rasterState->Release();
        rasterState = nullptr;
    }

    if (pixelShader)
    {
        pixelShader->Release();
        pixelShader = nullptr;
    }

    if (vertexShader)
    {
        vertexShader->Release();
        vertexShader = nullptr;
    }

    if (inputLayout)
    {
        inputLayout->Release();
        inputLayout = nullptr;
    }
}

// ---------------------------------------------------------------------------------

bool Renderer::Initialize(Window * window, Graphics * graphics)
{
    //-------------------------------
    // Vertex Shader
    //-------------------------------

    // carrega bytecode do vertex shader (HLSL)
    ID3DBlob * vShader = nullptr;
    if FAILED(D3DReadFileToBlob(L"Shaders/Vertex.cso", &vShader))
        return false;

    // cria o vertex shader
    if FAILED(graphics->device->CreateVertexShader(vShader->GetBufferPointer(), vShader->GetBufferSize(), NULL, &vertexShader))
        return false;

    //-------------------------------
    // Input Layout
    //-------------------------------

    // descreve o input layout dos vértices
    D3D11_INPUT_ELEMENT_DESC layoutDesc[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,       0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
    };

    // cria o input layout
    if FAILED(graphics->device->CreateInputLayout(layoutDesc, 3, vShader->GetBufferPointer(), vShader->GetBufferSize(), &inputLayout))
        return false;

    // libera bytecode
    vShader->Release();

    //-------------------------------
    // Pixel Shader
    //-------------------------------

    // carrega bytecode do pixel shader (HLSL)
    ID3DBlob * pShader = nullptr;
    if FAILED(D3DReadFileToBlob(L"Shaders/Pixel.cso", &pShader))
        return false;

    // cria o pixel shader
    if FAILED(graphics->device->CreatePixelShader(pShader->GetBufferPointer(), pShader->GetBufferSize(), NULL, &pixelShader))
        return false;

    // libera bytecode
    pShader->Release();

    //-------------------------------
    // Rasterizador
    //-------------------------------

    D3D11_RASTERIZER_DESC rasterDesc = {};
    rasterDesc.FillMode = D3D11_FILL_SOLID;
    //rasterDesc.FillMode = D3D11_FILL_WIREFRAME;
    rasterDesc.CullMode = D3D11_CULL_NONE;
    rasterDesc.DepthClipEnable = true;

    // cria estado do rasterizador
    if FAILED(graphics->device->CreateRasterizerState(&rasterDesc, &rasterState))
        return false;

    //-------------------------------
    // Vertex Buffer
    //-------------------------------

    D3D11_BUFFER_DESC vertexBufferDesc = {};
    vertexBufferDesc.ByteWidth = sizeof(Vertex) * VerticesPerSprite * MaxBatchSize;
    vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    if FAILED(graphics->device->CreateBuffer(&vertexBufferDesc, nullptr, &vertexBuffer))
        return false;

    //-------------------------------
    // Index Buffer
    //-------------------------------

    D3D11_BUFFER_DESC indexBufferDesc = { 0 };
    indexBufferDesc.ByteWidth = sizeof(short) * IndicesPerSprite * MaxBatchSize;
    indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    
    // gera índices para o número máximo de sprites suportados
    vector<short> indices;
    indices.reserve(MaxBatchSize * IndicesPerSprite);
    for (short i = 0; i < MaxBatchSize * VerticesPerSprite; i += VerticesPerSprite)
    {
        indices.push_back(i);
        indices.push_back(i + 1);
        indices.push_back(i + 2);

        indices.push_back(i + 1);
        indices.push_back(i + 3);
        indices.push_back(i + 2);
    }

    D3D11_SUBRESOURCE_DATA indexData = { 0 };
    indexData.pSysMem = &indices.front();

    if FAILED(graphics->device->CreateBuffer(&indexBufferDesc, &indexData, &indexBuffer))
        return false;

    //-------------------------------
    // Constant Buffer
    //-------------------------------

    D3D11_BUFFER_DESC constBufferDesc = { 0 };
    constBufferDesc.ByteWidth = sizeof(XMMATRIX);
    constBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    constBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    constBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    // calcula a matriz de transformação
    float xScale = (graphics->viewport.Width  > 0) ? 2.0f / graphics->viewport.Width : 0.0f;
    float yScale = (graphics->viewport.Height > 0) ? 2.0f / graphics->viewport.Height : 0.0f;
    
    // transforma para coordenadas da tela
    XMMATRIX transformMatrix 
    (
        xScale, 0,      0,     0,
        0,     -yScale, 0,     0,
        0,      0,      1,     0,
       -1,      1,      0,     1
    );

    D3D11_SUBRESOURCE_DATA constantData = { 0 };
    XMMATRIX worldViewProj =  XMMatrixTranspose(transformMatrix);
    constantData.pSysMem = &worldViewProj;

    if FAILED(graphics->device->CreateBuffer(&constBufferDesc, &constantData, &constantBuffer))
        return false;

    //-------------------------------
    // Texture Sampler
    //-------------------------------

    D3D11_SAMPLER_DESC samplerDesc = {};
    samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.MipLODBias = 0.0f;
    samplerDesc.MaxAnisotropy = (graphics->device->GetFeatureLevel() > D3D_FEATURE_LEVEL_9_1) ? 16 : 2;
    samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    samplerDesc.BorderColor[0] = 0.0f;
    samplerDesc.BorderColor[1] = 0.0f;
    samplerDesc.BorderColor[2] = 0.0f;
    samplerDesc.BorderColor[3] = 0.0f;
    samplerDesc.MinLOD = 0;
    samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

    // cria o amostrador da textura
    if FAILED(graphics->device->CreateSamplerState(&samplerDesc, &sampler))
        return false;

    //-------------------------------
    // Configura Pipeline Direct3D 
    //-------------------------------

    uint vertexStride = sizeof(Vertex);
    uint vertexOffset = 0;
    graphics->context->IASetVertexBuffers(0, 1, &vertexBuffer, &vertexStride, &vertexOffset);
    graphics->context->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R16_UINT, 0);
    graphics->context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    graphics->context->IASetInputLayout(inputLayout);
    graphics->context->VSSetShader(vertexShader, NULL, 0);
    graphics->context->VSSetConstantBuffers(0, 1, &constantBuffer);
    graphics->context->PSSetShader(pixelShader, NULL, 0);
    graphics->context->PSSetSamplers(0, 1, &sampler);
    graphics->context->RSSetState(rasterState);

    // inicialização bem sucedida
    return true;
}

// ---------------------------------------------------------------------------------

void Renderer::RenderBatch(ID3D11ShaderResourceView * texture, SpriteData ** sprites, uint cont)
{
    // desenhe usando a seguinte textura
    Graphics::context->PSSetShaderResources(0, 1, &texture);

    while (cont > 0)
    {
        // quantos sprites vamos desenhar
        uint batchSize = cont;

        // quantos sprites cabem no vertex buffer
        uint remainingSpace = MaxBatchSize - vertexBufferPosition;

        // quantidade de sprite é maior do que o espaço disponível
        if (batchSize > remainingSpace)
        {
            // se o tamanho disponível é muito pequeno
            if (remainingSpace < MinBatchSize)
            {
                // volte ao ínicio do buffer
                vertexBufferPosition = 0;
                batchSize = (cont < MaxBatchSize) ? cont : MaxBatchSize;
            }
            else
            {
                // restrinja a quantidade de sprites pelo espaço sobrando
                batchSize = remainingSpace;
            }
        }

        // trava o vertex buffer para escrita
        D3D11_MAP mapType = (vertexBufferPosition == 0) ? D3D11_MAP_WRITE_DISCARD : D3D11_MAP_WRITE_NO_OVERWRITE;
        D3D11_MAPPED_SUBRESOURCE mappedBuffer;
        Graphics::context->Map(vertexBuffer, 0, mapType, 0, &mappedBuffer);

        // se posiciona dentro do vertex buffer
        Vertex * vertices = (Vertex*)mappedBuffer.pData + vertexBufferPosition * VerticesPerSprite;

        // gera posições dos vértices de cada sprite que será desenhado nesse lote
        for (uint i = 0; i < batchSize; ++i)
        {        
            // pega tamanho da textura
            XMVECTOR size = XMVectorMergeXY(XMLoadInt(&sprites[i]->width), XMLoadInt(&sprites[i]->height));
            XMVECTOR textureSize = XMConvertVectorUIntToFloat(size, 0);
            XMVECTOR inverseTextureSize = XMVectorReciprocal(textureSize);

            // organiza informações do sprite
            XMFLOAT2 positionxy(sprites[i]->x, sprites[i]->y);
            float scale = sprites[i]->scale;
            XMFLOAT2 center(0.0f, 0.0f);
            float rotation = sprites[i]->rotation;
            float layerDepth = sprites[i]->depth;

            // carrega informações do sprite em registros SIMD
            XMVECTOR source = XMVectorSet(0, 0, 1, 1);
            XMVECTOR destination = XMVectorPermute<0, 1, 4, 4>(XMLoadFloat2(&positionxy), XMLoadFloat(&scale));
            XMVECTOR color = XMVectorSet(1, 1, 1, 1);
            XMVECTOR originRotationDepth = XMVectorSet(center.x, center.y, rotation, layerDepth);

            // extrai os tamanhos de origem e destino em vetores separados
            XMVECTOR sourceSize = XMVectorSwizzle<2, 3, 2, 3>(source);
            XMVECTOR destinationSize = XMVectorSwizzle<2, 3, 2, 3>(destination);

            // altera a escala do offset de origem pelo tamanho da fonte, tomando cuidado para evitar overflow se a região fonte for zero
            XMVECTOR isZeroMask = XMVectorEqual(sourceSize, XMVectorZero());
            XMVECTOR nonZeroSourceSize = XMVectorSelect(sourceSize, g_XMEpsilon, isZeroMask);

            XMVECTOR origin = XMVectorDivide(originRotationDepth, nonZeroSourceSize);

            // converte a região fonte de texels para o formato de coordenadas de textura mod-1
            origin *= inverseTextureSize;

            // se o tamanho de destino é relativo a região fonte, converte-o para pixels
            destinationSize *= textureSize;

            // calcula uma matriz de rotação 2x2
            XMVECTOR rotationMatrix1;
            XMVECTOR rotationMatrix2;

            if (rotation != 0)
            {
                float sin, cos;

                XMScalarSinCos(&sin, &cos, rotation);

                XMVECTOR sinV = XMLoadFloat(&sin);
                XMVECTOR cosV = XMLoadFloat(&cos);

                rotationMatrix1 = XMVectorMergeXY(cosV, sinV);
                rotationMatrix2 = XMVectorMergeXY(-sinV, cosV);
            }
            else
            {
                rotationMatrix1 = g_XMIdentityR0;
                rotationMatrix2 = g_XMIdentityR1;
            }

            // os quatro vértices do sprite são calculados a partir de transformações dessas posições unitárias
            static XMVECTORF32 cornerOffsets[VerticesPerSprite] =
            {
                { 0, 0 },
                { 1, 0 },
                { 0, 1 },
                { 1, 1 },
            };

            int mirrorBits = 0;

            // gere os quatro vértices 
            for (int i = 0; i < VerticesPerSprite; ++i)
            {
                // calcula posição
                XMVECTOR cornerOffset = (cornerOffsets[i] - origin) * destinationSize;

                // aplica matriz de rotação 2x2
                XMVECTOR position1 = XMVectorMultiplyAdd(XMVectorSplatX(cornerOffset), rotationMatrix1, destination);
                XMVECTOR position2 = XMVectorMultiplyAdd(XMVectorSplatY(cornerOffset), rotationMatrix2, position1);

                // insere componente z = depth
                XMVECTOR position = XMVectorPermute<0, 1, 7, 6>(position2, originRotationDepth);

                // Escreve posição como um Float4, mesmo sendo VertexPositionColor::position um XMFLOAT3.
                // Isso é mais rápido e inofensivo porque estamos apenas invalidando o primeiro elemento
                // do campo cor, que será imediatamente sobrescrito com seu valor correto.
                XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&vertices[i].pos), position);

                // insere a cor
                XMStoreFloat4(&vertices[i].color, color);

                // computa e escreve as coordenadas da textura
                XMVECTOR textureCoordinate = XMVectorMultiplyAdd(cornerOffsets[i ^ mirrorBits], sourceSize, source);

                XMStoreFloat2(&vertices[i].tex, textureCoordinate);
            }

            vertices += VerticesPerSprite;
        }

        // destrava o vertex buffer
        Graphics::context->Unmap(vertexBuffer, 0);

        // desenha sprites 
        uint startIndex = (uint)vertexBufferPosition * IndicesPerSprite;
        uint indexCount = (uint)batchSize * IndicesPerSprite;
        Graphics::context->DrawIndexed(indexCount, startIndex, 0);

        // avança a posição no vertex buffer
        vertexBufferPosition += batchSize;

        // avança a posição no vetor de sprites
        sprites += batchSize;

        // foram desenhados batchSize sprites nessa passagem
        cont -= batchSize;
    }
}

// ---------------------------------------------------------------------------------

void Renderer::Render()
{
    // ordena sprites por profundidade
    sort(spriteVector.begin(), spriteVector.end(), 
        [](SpriteData * a, SpriteData * b) -> bool 
        { return a->depth > b->depth; } );

    // quantidades de sprites a serem renderizados
    uint spriteVectorSize = uint(spriteVector.size());

    if (spriteVectorSize == 0)
        return;

    ID3D11ShaderResourceView* batchTexture = nullptr;
    uint batchStart = 0;

    // junta sprites adjacentes que compartilham a mesma textura
    for (uint pos = 0; pos < spriteVectorSize; ++pos)
    {
        ID3D11ShaderResourceView * texture = spriteVector[pos]->texture;

        if (texture != batchTexture)
        {
            if (pos > batchStart)
            {
                RenderBatch(batchTexture, &spriteVector[batchStart], pos - batchStart);
            }

            batchTexture = texture;
            batchStart = pos;
        }
    }

    // desenha o grupo final de sprites
    RenderBatch(batchTexture, &spriteVector[batchStart], spriteVectorSize - batchStart);

    // limpa a lista de desenho (atualizada a cada frame)
    spriteVector.clear();
}

// ---------------------------------------------------------------------------------

void Renderer::Draw(SpriteData * sprite)
{
    spriteVector.push_back(sprite);
}

// ---------------------------------------------------------------------------------