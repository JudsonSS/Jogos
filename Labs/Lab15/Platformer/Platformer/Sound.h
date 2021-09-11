/**********************************************************************************
// Sound (Arquivo de Cabeçalho)
// 
// Criação:     14 Out 2011
// Atualização: 11 Set 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Representa um som no formato WAVE
//
**********************************************************************************/

#ifndef _PROGJOGOS_SOUND_H_
#define _PROGJOGOS_SOUND_H_

// ---------------------------------------------------------------------------------

#include <xaudio2.h>                                    // biblioteca de audio
#include <string>                                       // string de texto
using std::string;

// ---------------------------------------------------------------------------------

class Sound
{
private:
    WAVEFORMATEXTENSIBLE soundFormat;                   // formato do arquivo .wav
    XAUDIO2_BUFFER       soundBuffer;                   // buffer com os dados do som
    IXAudio2SourceVoice* sourceVoice;                   // fonte de áudio

    HRESULT FindChunk(HANDLE hFile, 
                      DWORD fourcc, 
                      DWORD & dwChunkSize, 
                      DWORD & dwChunkDataPosition);     // localiza blocos no arquivo RIFF

    HRESULT ReadChunkData(HANDLE hFile, 
                          void * buffer, 
                          DWORD buffersize, 
                          DWORD bufferoffset);          // lê blocos do arquivo para um buffer

    friend class Audio;

public:
    Sound(string fileName);                              // construtor
    ~Sound();                                            // destrutor
};

// ---------------------------------------------------------------------------------


#endif