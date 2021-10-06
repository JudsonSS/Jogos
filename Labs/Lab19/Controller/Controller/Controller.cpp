/**********************************************************************************
// Controller (Código Fonte)
// 
// Criação:     09 Nov 2011
// Atualização: 05 Out 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Faz a leitura de controles
//
**********************************************************************************/

// ---------------------------------------------------------------------------------

#include "Controller.h"
#include "Engine.h"
#include <cmath>

// ---------------------------------------------------------------------------------

Controller::Controller()
{
    dInput = nullptr;
    joyDev = nullptr;

    ZeroMemory(&joyState, sizeof(joyState));
    ZeroMemory(&joyCtrl, sizeof(joyCtrl));
    ZeroMemory(&xboxState, sizeof(XINPUT_STATE));
    ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));

    // cria o objeto direct input
    DirectInput8Create(
        GetModuleHandle(NULL),       // identificador da janela
        DIRECTINPUT_VERSION,         // versão do direct input
        IID_IDirectInput8,           // identificador da interface
        (void **) &dInput,           // objeto direct input
        NULL);                       // sempre nulo

    // busca por dispositivos conectados usando a função callback EnumerateControllers
    dInput->EnumDevices(
        DI8DEVCLASS_GAMECTRL,        // procure apenas controladores de jogos
        EnumerateControllers,        // função de enumeração
        &controllers,                // endereço da lista de controles
        DIEDFL_ATTACHEDONLY);        // apenas dispositivos conectados

    // seleciona o primeiro controle encontrado
    selected = controllers.begin();
}

// ---------------------------------------------------------------------------------

Controller::~Controller()
{
    // libera o dispositivo
    if (joyDev)
        joyDev->Unacquire();

    // apaga o dispositivo
    if (joyDev)
        joyDev->Release();

    // apaga o objeto direct input
    if (dInput)
        dInput->Release();
}

// ---------------------------------------------------------------------------------

bool Controller::Initialize()
{
    // retorna falha se o direct input não foi inicializado
    if (!dInput)
        return false;

    // retorna falha se não existir controles conectados
    if (controllers.empty())
        return false;

    // libera o dispositivo criado em inicializações anteriores
    if (joyDev)
    {
        joyDev->Unacquire();
        joyDev->Release();
    }    

    // cria um novo dispositivo para o controle selecionado
    if (FAILED(dInput->CreateDevice(selected->guid, &joyDev, NULL)))
        return false;

    // seleciona o nível de cooperação para o controle
    if (FAILED(joyDev->SetCooperativeLevel(Engine::window->Id(), DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)))
        return false;

    // seleciona o formato de dados
    if (FAILED(joyDev->SetDataFormat(&c_dfDIJoystick)))
        return false;

    // enumera as partes (botões e eixos) do controle selecionado
    parts.clear();
    if(FAILED(joyDev->EnumObjects(EnumControllerParts, &parts, DIDFT_ALL)))
        return false;
    
    // ajusta a faixa de movimento e a zona morta dos eixos
    DIPROPRANGE axisRange; 
    DIPROPDWORD deadZone;

    for (const auto & p : parts)
    {
        // se é um eixo
        if (p.type & DIDFT_AXIS)
        {
            // define faixa do eixo
            axisRange.diph.dwSize       = sizeof(DIPROPRANGE); 
            axisRange.diph.dwHeaderSize = sizeof(DIPROPHEADER); 
            axisRange.diph.dwHow        = DIPH_BYID; 
            axisRange.diph.dwObj        = p.type;
            axisRange.lMin              = -1000; 
            axisRange.lMax              = +1000; 
    
            // aplica a faixa no eixo
            if (FAILED(joyDev->SetProperty(DIPROP_RANGE, &axisRange.diph))) 
                return false;

            // define a zona morta
            deadZone.diph.dwSize       = sizeof(DIPROPDWORD);
            deadZone.diph.dwHeaderSize = sizeof(DIPROPHEADER);
            deadZone.diph.dwHow        = DIPH_BYID;
            deadZone.diph.dwObj        = p.type;
            deadZone.dwData            = 2000;  

            // aplica a zona morta no eixo
            if (FAILED(joyDev->SetProperty(DIPROP_DEADZONE, &deadZone.diph)))
                return false;
        }
    }

    // requisita acesso ao controle
    if(FAILED(joyDev->Acquire()))
        return false;

    // inicialização bem sucedida
    return true;
}

// ---------------------------------------------------------------------------------

bool Controller::XboxInitialize(int ctrl)
{
    // características do controle
    XINPUT_CAPABILITIES caps;
    ZeroMemory(&caps, sizeof(XINPUT_CAPABILITIES));
    
    // pega as características do controle
    XInputGetCapabilities(ctrl, XINPUT_FLAG_GAMEPAD, &caps);

    // retorna falha se não for um controle compatível
    if (caps.SubType == XINPUT_DEVSUBTYPE_UNKNOWN)
        return false;

    // inicialização bem sucedida
    return true;
}

// ---------------------------------------------------------------------------------

bool Controller::UpdateState()
{
    
    // Poll() deve ser usado antes de ler o estado do controle
    // porque alguns drivers de dispositivos não atualizam seu estado
    // interno automaticamente

    // atualiza o estado interno do controle
    if (FAILED(joyDev->Poll()))
        return false;

    // lê o estado do controle
    HRESULT result = joyDev->GetDeviceState(sizeof(DIJOYSTATE), (LPVOID) &joyState); 

    // se aconteceu alguma falha na leitura
    if(FAILED (result))
    {
        if (result == DIERR_NOTACQUIRED || result == DIERR_INPUTLOST)
        {
            // libera o dispositivo
            joyDev->Unacquire();

            // tenta re-capturar o dispositivo
            joyDev->Acquire();

            // repete a leitura
            joyDev->GetDeviceState(sizeof(DIJOYSTATE), (LPVOID)& joyState);
        }
        else
        {
            return false;
        }    
    }
    
    // leitura bem sucedida
    return true;
}

// ---------------------------------------------------------------------------------

bool Controller::XboxUpdateState(int ctrl)
{
    // se o resultado não é zero significa que a leitura falhou
    if (XInputGetState(ctrl, &xboxState))
        return false;

    // leitura bem sucedida
    return true;
}

// ---------------------------------------------------------------------------------

bool Controller::ButtonPress(int button)
{
    if (joyCtrl[button])
    {
        if (ButtonDown(button))
        {
            joyCtrl[button] = false;
            return true;
        }
    } 
    else if (ButtonUp(button))
    {
        joyCtrl[button] = true;
    }

    return false;
}

// ---------------------------------------------------------------------------------

long Controller::Axis(int axis)
{ 
    switch (axis)
    {
    case AxisX:
        return joyState.lX; 
    case AxisY:
        return joyState.lY; 
    case AxisZ:
        return joyState.lZ;
    case AxisRX:
        return joyState.lRx; 
    case AxisRY:
        return joyState.lRy; 
    case AxisRZ:
        return joyState.lRz;

    default:
        return 0;
    }    
}

// ---------------------------------------------------------------------------------

long Controller::Slider(int slider)
{
    return joyState.rglSlider[slider];
}

// ---------------------------------------------------------------------------------

long Controller::Dpad(int pov)
{
    return joyState.rgdwPOV[pov];
}

// ---------------------------------------------------------------------------------

bool Controller::DeviceNext()
{
    // passa para o próximo controle da lista
    ++selected;

    // seleção circular na lista de controles
    if (selected == controllers.end())
        selected = controllers.begin();        

    // inicializa controle selecionado
    if (Initialize())
        return true;
    else
        return false;
}

// ---------------------------------------------------------------------------------

bool Controller::DevicePrev()
{
    // seleção circular na lista de controles
    if (selected == controllers.begin())
        selected = controllers.end();

    // passa para o controle anterior
    --selected;
    
    // inicializa controle selecionado
    if (Initialize())
        return true;
    else
        return false;
}

// ---------------------------------------------------------------------------------

BOOL CALLBACK EnumerateControllers(LPCDIDEVICEINSTANCE lpDDi, LPVOID data)
{
    // registro que guarda nome e GUID do controle
    JoyInfo joy;

    // copia identificador do controle
    joy.guid = lpDDi->guidInstance;

    // copia nome do controle
    joy.name = lpDDi->tszInstanceName;

    // adiciona controle na lista
    ((list<JoyInfo>*) data)->push_back(joy);

    // continua enumeração até o fim
    return DIENUM_CONTINUE;
}

// ---------------------------------------------------------------------------------

BOOL CALLBACK EnumControllerParts(LPCDIDEVICEOBJECTINSTANCE lpDIdoi, LPVOID data)
{
    // registro que guarda nome, identificador e tipo de cada parte do controle
    // (botões, eixos, dpads e sliders)
    JoyPart part;

    // copia o identificador, tipo e nome
    part.guid = lpDIdoi->guidType;
    part.type = lpDIdoi->dwType;
    part.name = lpDIdoi->tszName;
    
    // se é uma parte de tipo conhecido, insere-a na lista de partes do controle
    if (lpDIdoi->guidType != GUID_Unknown)
        ((list<JoyPart>*) data)->push_back(part);

    // continua enumeração até o fim
    return DIENUM_CONTINUE;
}

// ---------------------------------------------------------------------------------

int Controller::XboxButton(int button)
{
    switch (button)
    {
    case DpadUp: return (xboxState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP); break;
    case DpadDown: return (xboxState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN); break;
    case DpadLeft: return (xboxState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT); break;
    case DpadRight: return (xboxState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT); break;
    case ButtonStart: return (xboxState.Gamepad.wButtons & XINPUT_GAMEPAD_START); break;
    case ButtonBack: return (xboxState.Gamepad.wButtons & XINPUT_GAMEPAD_BACK); break;
    case LeftThumb: return (xboxState.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB); break;
    case RightThumb: return (xboxState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB); break;
    case LeftBumper: return (xboxState.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER); break;
    case RightBumper: return (xboxState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER); break;
    case ButtonA: return (xboxState.Gamepad.wButtons & XINPUT_GAMEPAD_A); break;
    case ButtonB: return (xboxState.Gamepad.wButtons & XINPUT_GAMEPAD_B); break;
    case ButtonX: return (xboxState.Gamepad.wButtons & XINPUT_GAMEPAD_X); break;
    case ButtonY: return (xboxState.Gamepad.wButtons & XINPUT_GAMEPAD_Y); break;
    }

    return false;
}

// ---------------------------------------------------------------------------------

int  Controller::XboxTrigger(int trigger)
{
    // valor dos gatilhos vai de 0 a 255
    switch (trigger)
    {
    case LeftTrigger: return xboxState.Gamepad.bLeftTrigger; break;
    case RightTrigger: return xboxState.Gamepad.bRightTrigger; break;
    }

    return 0;
}

// ---------------------------------------------------------------------------------

int  Controller::XboxAnalog(int stick)
{
    // valor das alavancas vai de -32768 a 32767
    switch (stick)
    {
    case ThumbLX:
        if (abs(xboxState.Gamepad.sThumbLX) > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
            return xboxState.Gamepad.sThumbLX;
        break;
    case ThumbLY:
        if (abs(xboxState.Gamepad.sThumbLY) > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
            return xboxState.Gamepad.sThumbLY;
        break;
    case ThumbRX:
        if (abs(xboxState.Gamepad.sThumbRX) > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
            return xboxState.Gamepad.sThumbRX;
        break;
    case ThumbRY:
        if (abs(xboxState.Gamepad.sThumbRY) > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
            return xboxState.Gamepad.sThumbRY;
        break;
    }

    return 0;
}

// ---------------------------------------------------------------------------------

void Controller::XboxVibrate(int ctrl, int left, int right)
{
    vibration.wLeftMotorSpeed = left;
    vibration.wRightMotorSpeed = right;
    XInputSetState(ctrl, &vibration);
}

// ---------------------------------------------------------------------------------