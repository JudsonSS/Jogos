/**********************************************************************************
// Audio (Código Fonte)
// 
// Criação:     14 Out 2011
// Atualização: 11 Set 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Classe para reproduzir áudio
//
**********************************************************************************/

#include "Audio.h"
#include "Sound.h"

// ---------------------------------------------------------------------------------

Audio::Audio()
{
    audioEngine = nullptr;
    masterVoice = nullptr;

    // XAudio2 usa a biblioteca COM
    if (SUCCEEDED(CoInitializeEx(NULL, COINIT_MULTITHREADED)))
    {
        // cria uma instância da engine XAudio2
        if (SUCCEEDED(XAudio2Create(&audioEngine, 0, XAUDIO2_DEFAULT_PROCESSOR)))
        {
            // cria o dispositivo principal de saída de audio
            audioEngine->CreateMasteringVoice(&masterVoice);
        }
    }
}

// ---------------------------------------------------------------------------------

Audio::~Audio()
{
    // deleta todos os sons da coleção
    for (const auto & [id, sound] : sounds)
    {
        sound->sourceVoice->DestroyVoice();
        delete sound;
    }

    // destroi voz mestre
    if (masterVoice) masterVoice->DestroyVoice();

    // libera instância de XAudio2
    if (audioEngine) audioEngine->Release();

    // XAudio2 usa a biblioteca COM
    CoUninitialize();
}

// ---------------------------------------------------------------------------------

void Audio::Add(uint id, string filename)
{
    // cria novo som
    Sound * sound = new Sound(filename);
    
    // cria uma SourceVoice para o som
    audioEngine->CreateSourceVoice(&sound->sourceVoice, (WAVEFORMATEX*) &sound->soundFormat);    

    // insere novo som na coleção
    sounds[id] = sound;
}

// ---------------------------------------------------------------------------------

void Audio::Play(uint id)
{ 
    Sound * selected = sounds[id];

    selected->sourceVoice->Stop();
    selected->sourceVoice->FlushSourceBuffers();
    selected->sourceVoice->SubmitSourceBuffer(&selected->soundBuffer);
    selected->sourceVoice->Start();
}

// ---------------------------------------------------------------------------------

