/**********************************************************************************
// Audio (Código Fonte)
// 
// Criação:     14 Out 2011
// Atualização: 25 Out 2021
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

    // inicializa o Component Object Model (COM) para a XAudio2
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
    for (const auto & [id, sound] : soundTable)
    {
        // destroi todas as vozes criadas para este som
        for (uint k = 0; k < sound->tracks; ++k)
            sound->voices[k]->DestroyVoice();

        // libera o som
        delete sound;
    }

    // destroi voz mestre
    if (masterVoice) masterVoice->DestroyVoice();

    // libera instância de XAudio2
    if (audioEngine) audioEngine->Release(); 

    // libera o Component Object Model (COM)
    CoUninitialize();
}

// ---------------------------------------------------------------------------------

void Audio::Add(uint id, string filename, uint nVoices)
{
    // cria novo som
    Sound * sound = new Sound(filename, nVoices);

    // cria o número de vozes requisitadas para o som
    for (uint i = 0; i < nVoices; ++i)
        audioEngine->CreateSourceVoice(&sound->voices[i], (WAVEFORMATEX*)&sound->format);

    // insere novo som na coleção
    soundTable[id] = sound;
}

// ---------------------------------------------------------------------------------

void Audio::Play(uint id, bool repeat)
{ 
    // recupera som da tabela
    Sound * selected = soundTable[id];

    // toca áudio em loop ou apenas uma vez
    if (repeat)
        selected->buffer.LoopCount = XAUDIO2_LOOP_INFINITE;
    else
        selected->buffer.LoopCount = 0;

    // limpa voz corrente e inicia reprodução do som
    selected->voices[selected->index]->Stop();
    selected->voices[selected->index]->FlushSourceBuffers();
    selected->voices[selected->index]->SetVolume(selected->volume);
    selected->voices[selected->index]->SubmitSourceBuffer(&selected->buffer);
    selected->voices[selected->index]->Start();

    // seleciona nova trilha para reprodução do próximo som
    selected->index = (selected->index + 1) % selected->tracks;
}

// ---------------------------------------------------------------------------------

void Audio::Stop(uint id)
{
    // recupera som da tabela
    Sound * selected = soundTable[id];

    // encerra todas as trilhas desse som
    for (uint i = 0; i < selected->tracks; ++i)
        selected->voices[i]->Stop();
}

// ---------------------------------------------------------------------------------

void Audio::Volume(uint id, float level)
{
    // verifica se o nível está dentro dos limites
    if (level < 0)
        level = 0;

    if (level > XAUDIO2_MAX_VOLUME_LEVEL)
        level = XAUDIO2_MAX_VOLUME_LEVEL;

    // recupera som da tabela
    Sound * selected = soundTable[id];

    // ajusta o volume
    selected->volume = level;
    selected->voices[selected->index]->SetVolume(level);
}

// ---------------------------------------------------------------------------------

void Audio::Frequency(uint id, float level)
{
    // verifica se o nível está dentro dos limites
    if (level < XAUDIO2_MIN_FREQ_RATIO)
        level = XAUDIO2_MIN_FREQ_RATIO;

    // recupera som da tabela
    Sound * selected = soundTable[id];

    // ajusta a frequencia
    selected->frequency = level;
    selected->voices[selected->index]->SetFrequencyRatio(level);
}

// ---------------------------------------------------------------------------------

