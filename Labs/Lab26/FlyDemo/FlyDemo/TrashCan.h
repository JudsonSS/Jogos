/**********************************************************************************
// TrashCan (Arquivo de Cabeçalho)
//
// Criação:     06 Ago 2019
// Atualização: 05 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Lixeira
//
**********************************************************************************/

#ifndef _FLYDEMO_TRASHCAN_H_
#define _FLYDEMO_TRASHCAN_H_

// ---------------------------------------------------------------------------------

#include "Object.h"
#include "Image.h"
#include "Sprite.h"
#include "Types.h"        

// ---------------------------------------------------------------------------------

class TrashCan : public Object
{
private:
    const int maxFlies = 50;            // número máximo de moscas
    Image * flyImg;                     // imagem da mosca
    Sprite * cover;                     // tampa da lata de lixo
    Sprite * message;                   // mensagem de conscientização
    Sprite * warning;                   // indicativo de atenção
    float rFactor;                      // fator de rotação
    bool openCover;                     // estado da lixeira
    

public:
    TrashCan();                         // construtor
    ~TrashCan();                        // destrutor

    void OnCollision(Object* obj);      // resolução de colisão
    void Update();                      // atualização
    void Draw();                        // desenho
};

// ---------------------------------------------------------------------------------

#endif
