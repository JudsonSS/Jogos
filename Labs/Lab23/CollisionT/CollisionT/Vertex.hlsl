/**********************************************************************************
// Vertex (Arquivo de Sombreamento)
//
// Criação:     11 Jul 2007
// Atualização: 13 Ago 2021
// Compilador:  D3DCompiler
//
// Descrição:   Define um vertex shader que apenas multiplica os vértices
//              por uma matriz de transformação e projeção
//
**********************************************************************************/

// matriz de transformação e projeção
cbuffer ConstantBuffer
{
    float4x4 WorldViewProj;
}

// estrutura dos vértices de entrada
struct VertexIn
{
    float3 Pos   : POSITION;
    float4 Color : COLOR;
    float2 Tex   : TEXCOORD;    
};

// estrutura dos vértices de saída
struct VertexOut
{
    float4 Pos   : SV_POSITION;
    float4 Color : COLOR;
    float2 Tex   : TEXCOORD;    
};

// programa principal do vertex shader
VertexOut main( VertexIn vIn )
{
    VertexOut vOut;

    // transforma vértices para coordenadas da tela
    vOut.Pos = mul(float4(vIn.Pos, 1.0f), WorldViewProj);
    
    // mantém as cores inalteradas
    vOut.Color = vIn.Color;

    // mantém as coordenadas da textura inalteradas
    vOut.Tex = vIn.Tex;

    return vOut;
}