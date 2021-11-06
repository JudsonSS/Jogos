/**********************************************************************************
// Timer (Arquivo de Cabeçalho)
// 
// Criação:     02 Abr 2011
// Atualização: 18 Out 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Usa um contador de alta precisão para medir o tempo.
//
**********************************************************************************/

#ifndef _PROGJOGOS_TIMER_H_
#define _PROGJOGOS_TIMER_H_

// -------------------------------------------------------------------------------

#include <windows.h>                            // contador de alta precisão
#include "Types.h"                              // tipos específicos do motor

// -------------------------------------------------------------------------------

class Timer
{
private:
    LARGE_INTEGER start, end;                   // valores de início e fim do contador
    LARGE_INTEGER freq;                         // freqüência do contador
    bool stoped;                                // estado da contagem
    
public:
    Timer();                                    // constructor

    void  Start();                              // inicia/retoma contagem do tempo
    void  Stop();                               // pára contagem do tempo
    float Reset();                              // reinicia contagem e retorna tempo transcorrido
    float Elapsed();                            // retorna tempo transcorrido em segundos    
    bool  Elapsed(float time);                  // testa se transcorreu o tempo em segundos

    llong Stamp();                              // retorna valor atual do contador
    float Elapsed(llong stamp);                 // retorna tempo transcorrido desde a marca
    bool  Elapsed(llong stamp, float time);     // testa se transcorreu o tempo desde a marca
}; 

// -------------------------------------------------------------------------------

// Funções Inline

inline bool Timer::Elapsed(float time)
{ return (Elapsed() >= time ? true : false); }

inline bool Timer::Elapsed(llong stamp, float time)
{ return (Elapsed(stamp) >= time ? true : false); }

// -------------------------------------------------------------------------------

#endif