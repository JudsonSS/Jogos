/**********************************************************************************
// Sound (Código Fonte)
// 
// Criação:     14 Out 2011
// Atualização: 19 Set 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Representa um som no formato WAVE
//
**********************************************************************************/

#include "Sound.h"

// ---------------------------------------------------------------------------------

#define fourccRIFF 'FFIR'
#define fourccDATA 'atad'
#define fourccFMT  ' tmf'
#define fourccWAVE 'EVAW'

// ---------------------------------------------------------------------------------

Sound::Sound(string fileName, uint nTracks)
{
    // limpa os registros zerando todos os bits
    ZeroMemory(&format, sizeof(format));
    ZeroMemory(&buffer, sizeof(buffer));
    volume = 1.0f;
    frequency = 1.0f;
    tracks = nTracks;
    index = 0;

    // vetor de ponteiros para vozes
    voices = new IXAudio2SourceVoice*[tracks] {nullptr};

    // abre o arquivo de som para leitura
    HANDLE hFile = CreateFile(fileName.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);

    // localiza o bloco 'RIFF' dentro do arquivo de som
    DWORD dwChunkSize;
    DWORD dwChunkPosition;
    FindChunk(hFile, fourccRIFF, dwChunkSize, dwChunkPosition);

    // verifica se o arquivo é do tipo WAVE
    DWORD filetype;
    ReadChunkData(hFile, &filetype, sizeof(DWORD), dwChunkPosition);
    if (filetype != fourccWAVE)
        return;

    // localiza o bloco 'fmt' e copia seu conteúdo para um registro WAVEFORMATEXTENSIBLE
    FindChunk(hFile, fourccFMT, dwChunkSize, dwChunkPosition);
    ReadChunkData(hFile, &format, dwChunkSize, dwChunkPosition);

    // localiza o bloco 'data' e lê seu conteúdo para o registro XAUDIO2_BUFFER
    FindChunk(hFile, fourccDATA, dwChunkSize, dwChunkPosition);
    BYTE * pDataBuffer = new BYTE[dwChunkSize];
    ReadChunkData(hFile, pDataBuffer, dwChunkSize, dwChunkPosition);

    // preenche o registro XAUDIO2_BUFFER
    buffer.AudioBytes = dwChunkSize;        // tamanho do buffer de audio em bytes
    buffer.pAudioData = pDataBuffer;        // os dados (bits) do audio
    buffer.Flags = XAUDIO2_END_OF_STREAM;    // este será o único buffer para a "Source Voice"

    // fecha arquivo
    CloseHandle(hFile);
}

// ---------------------------------------------------------------------------------

Sound::~Sound()
{
    delete [] buffer.pAudioData;    
    delete [] voices;
}

// ---------------------------------------------------------------------------------

HRESULT Sound::FindChunk(HANDLE hFile, DWORD fourcc, DWORD & dwChunkSize, DWORD & dwChunkDataPosition)
{
    HRESULT hr = S_OK;
    if( INVALID_SET_FILE_POINTER == SetFilePointer( hFile, 0, NULL, FILE_BEGIN ) )
        return HRESULT_FROM_WIN32( GetLastError() );

    DWORD dwChunkType;
    DWORD dwChunkDataSize;
    DWORD dwRIFFDataSize = 0;
    DWORD dwFileType;
    DWORD bytesRead = 0;
    DWORD dwOffset = 0;

    while (hr == S_OK)
    {
        DWORD dwRead;
        if( 0 == ReadFile( hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL ) )
            hr = HRESULT_FROM_WIN32( GetLastError() );

        if( 0 == ReadFile( hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL ) )
            hr = HRESULT_FROM_WIN32( GetLastError() );

        switch (dwChunkType)
        {
        case fourccRIFF:
            dwRIFFDataSize = dwChunkDataSize;
            dwChunkDataSize = 4;
            if( 0 == ReadFile( hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL ) )
                hr = HRESULT_FROM_WIN32( GetLastError() );
            break;

        default:
            if( INVALID_SET_FILE_POINTER == SetFilePointer( hFile, dwChunkDataSize, NULL, FILE_CURRENT ) )
            return HRESULT_FROM_WIN32( GetLastError() );            
        }

        dwOffset += sizeof(DWORD) * 2;
        
        if (dwChunkType == fourcc)
        {
            dwChunkSize = dwChunkDataSize;
            dwChunkDataPosition = dwOffset;
            return S_OK;
        }

        dwOffset += dwChunkDataSize;
        
        if (bytesRead >= dwRIFFDataSize) return S_FALSE;

    }

    
    return S_OK;
    
}

// ---------------------------------------------------------------------------------

HRESULT Sound::ReadChunkData(HANDLE hFile, void * buffer, DWORD buffersize, DWORD bufferoffset)
{
    HRESULT hr = S_OK;
    if( INVALID_SET_FILE_POINTER == SetFilePointer( hFile, bufferoffset, NULL, FILE_BEGIN ) )
        return HRESULT_FROM_WIN32( GetLastError() );
    DWORD dwRead;
    if( 0 == ReadFile( hFile, buffer, buffersize, &dwRead, NULL ) )
        hr = HRESULT_FROM_WIN32( GetLastError() );
    return hr;
}

// ---------------------------------------------------------------------------------

