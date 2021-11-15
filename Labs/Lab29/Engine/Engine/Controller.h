/**********************************************************************************
// Controller (Arquivo de Cabeçalho)
// 
// Criação:     09 Nov 2011
// Atualização: 15 Out 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Faz a leitura de controles
//
**********************************************************************************/

#ifndef _PROGJOGOS_CONTROLLER_H_
#define _PROGJOGOS_CONTROLLER_H_

#ifdef ENGINE_EXPORTS
#define DLL __declspec( dllexport ) 
#else
#define DLL __declspec( dllimport )
#endif

// ---------------------------------------------------------------------------------

#define INITGUID                                // inclusão dos GUIDs do DirectX
#define DIRECTINPUT_VERSION 0x0800              // usa versão 8 do DirectInput

// ---------------------------------------------------------------------------------

#include "Types.h"                              // tipos específicos da engine
#include <dinput.h>                             // direct input
#include <xinput.h>                             // xinput
#include <list>                                 // listas da STL
#include <string>                               // strings da STL
using std::list;                                // usando listas sem std::
using std::string;                              // usando strings sem std::

// ---------------------------------------------------------------------------------

// eixos e botões do controle do Xbox
enum XboxCtrl
{
    DpadUp, DpadDown, DpadLeft, DpadRight,      // Dpad
    ButtonStart, ButtonBack,                    // Botões de menu
    LeftThumb, RightThumb,                      // Botões dos analógicos
    LeftBumper, RightBumper,                    // Botões LB e RB
    ButtonA, ButtonB, ButtonX, ButtonY,         // Botões A, B, X e Y
    LeftTrigger, RightTrigger,                  // Gatilhos LT e RT (faixa entre 0 e 255)
    ThumbLX, ThumbLY, ThumbRX, ThumbRY          // Eixos dos analógicos (faixa entre -32768 e 32767)
};

// número do jogador no controle do Xbox
enum XboxPlayer
{
    PLAYER1,
    PLAYER2,
    PLAYER3,
    PLAYER4
};

// eixos do controle 
enum JoyAxis 
{
    AxisX,                                      // Eixo X
    AxisY,                                      // Eixo Y
    AxisZ,                                      // Eixo Z
    AxisRX,                                     // Eixo RX
    AxisRY,                                     // Eixo RY
    AxisRZ                                      // Eixo RZ
};

// informações do controle 
struct JoyInfo 
{
    GUID   guid;                                // identificador global único
    string name;                                // nome do controle
};

// partes do controle 
struct JoyPart 
{
    GUID   guid;                                // identificador global único
    DWORD  type;                                // tipo da parte
    string name;                                // nome da parte
};

// ---------------------------------------------------------------------------------

class DLL Controller
{
private:
    LPDIRECTINPUT8 dInput;                      // objeto direct input
    LPDIRECTINPUTDEVICE8 joyDev;                // dispositivo do controle
    DIJOYSTATE joyState;                        // estado do controle
    XINPUT_STATE xboxState;                     // estado do controle do Xbox
    XINPUT_VIBRATION vibration;                 // vibração do controle do Xbox
    bool joyCtrl[32];                           // estado de liberação de botões

    list<JoyPart> parts;                        // lista de botões e eixos para o controle selecionado
    list<JoyInfo> controllers;                  // lista dos dispositivos de controle    
    list<JoyInfo>::const_iterator selected;     // aponta para o controle selecionado

public:
    Controller();                               // construtor
    ~Controller();                              // destrutor

    bool Initialize();                          // inicializa controle
    bool XboxInitialize(int ctrl = 0);          // inicializa controle do Xbox
    
    bool UpdateState();                         // atualiza estado do controle
    bool XboxUpdateState(int ctrl = 0);         // atualiza estado do controle do Xbox
    
    bool ButtonDown(int button);                // verifica se um botão do controle está pressionado
    bool ButtonUp(int button);                  // verifica se um botão do controle está liberado
    bool ButtonPress(int button);               // registra novo pressionamento somente após liberação
    long Axis(int axis);                        // retorna o movimento de um eixo do controle
    long Slider(int slider);                    // retorna movimento do slider
    long Dpad(int pov = 0);                     // retorna o movimento do D-pad

    bool DeviceNext();                          // seleciona o próximo controle da lista
    bool DevicePrev();                          // seleciona o controle anterior da lista
    const string * DeviceName();                // retorna o nome do controle selecionado
    list<JoyPart> & DeviceParts();              // retorna lista de botões e eixos do controle

    int XboxButton(int button);                 // retorna estado do botão do controle do Xbox
    int XboxTrigger(int trigger);               // retorna valor dos gatilhos do contole do Xbox
    int XboxAnalog(int stick);                  // retorna valor dos direcionais do controle do Xbox
    void XboxVibrate(int ctrl = 0,              // faz o controle do xbox vibrar
        int left = 65535, 
        int right = 65535);                    
};

// -------------------------------------------------------------------------------
// funções membro inline

// verifica se o botão do controle está pressionado
inline bool Controller::ButtonDown(int button)
{ return joyState.rgbButtons[button] && 0x80; }

// verifica se o botão do controle está pressionado
inline bool Controller::ButtonUp(int button)
{ return !(joyState.rgbButtons[button] && 0x80); }

// retorna o nome do controle selecionado
inline const string * Controller::DeviceName() 
{ return &(*selected).name; }

// retorna lista de botões e eixos do controle 
inline list<JoyPart> & Controller::DeviceParts() 
{ return parts;}

// ---------------------------------------------------------------------------------

// função callback que enumera os controles
BOOL CALLBACK EnumerateControllers(LPCDIDEVICEINSTANCE lpDDi, LPVOID data);

// função callback que enumera os botões e eixos do controle
BOOL CALLBACK EnumControllerParts(LPCDIDEVICEOBJECTINSTANCE lpDIdoi, LPVOID data);

// ---------------------------------------------------------------------------------

#endif