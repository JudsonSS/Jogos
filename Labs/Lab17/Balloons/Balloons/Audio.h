/**********************************************************************************
// Audio (Arquivo de Cabeçalho)
// 
// Criação:     14 Out 2011
// Atualização: 19 Set 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Classe para reproduzir áudio
//
**********************************************************************************/

#ifndef _PROGJOGOS_AUDIO_H_
#define _PROGJOGOS_AUDIO_H_

// ---------------------------------------------------------------------------------

#include "Sound.h"                                          // guarda o som no formato WAVE
#include "Types.h"                                          // tipos específicos da engine
#include <XAudio2.h>                                        // XAudio2 API
#include <unordered_map>                                    // tabela de dispersão
#include <string>                                           // tipo string da STL
using std::unordered_map;
using std::string;

// ---------------------------------------------------------------------------------

class Audio
{
private:
    IXAudio2* audioEngine;                                  // sistema de áudio (engine)
    IXAudio2MasteringVoice* masterVoice;                    // dispositivo principal de áudio
    unordered_map<uint, Sound*> soundTable;                 // coleção de sons

public:
    Audio();                                                // construtor
    ~Audio();                                               // destrutor

    void Add(uint id, string filename, uint nVoices = 1);   // adiciona arquivo a coleção de sons
    void Play(uint id, bool repeat = false);                // inicia a reprodução do som
    void Stop(uint id);                                     // para a reprodução do som
    void Volume(uint id, float level);                      // ajusta volume do som
    void Frequency(uint id, float level);                   // ajusta a frequência do som
}; 

// ---------------------------------------------------------------------------------

#endif