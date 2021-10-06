/**********************************************************************************
// Demo (Código Fonte)
//
// Criação:     09 Nov 2011
// Atualização: 30 Set 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Exemplo de uso da classe Controller
//
**********************************************************************************/

#include "Engine.h"
#include "Demo.h"

// ------------------------------------------------------------------------------

void Demo::Init()
{
    // cria gerenciador de controles
    gamepad = new Controller();

    // tenta inicializar um controle do xbox
    xboxOn = gamepad->XboxInitialize(xboxPlayer);
    
    // se falhar, tenta inicializar um controle qualquer
    if (!xboxOn)
        controllerOn = gamepad->Initialize();

    // cria fontes para exibição de texto
    sysFont = new Font("Resources/Tahoma14.png");
    sysFont->Spacing("Resources/Tahoma14.dat");
    gameFont = new Font("Resources/Agency30.png");
    gameFont->Spacing("Resources/Agency30.dat");

    // carrega sprites
    backg = new Sprite("Resources/Background.jpg");
    overlay = new Sprite("Resources/Overlay.png");
    xboxOver = new Sprite("Resources/XboxOverlay.png");
    xbox360 = new Sprite("Resources/Xbox360.png");
    box = new Sprite("Resources/Box.png");

    A = new Sprite("Resources/A.png");
    B = new Sprite("Resources/B.png");
    X = new Sprite("Resources/X.png");
    Y = new Sprite("Resources/Y.png");

    RB = new Sprite("Resources/RB.png");
    LB = new Sprite("Resources/LB.png");
    RT = new Sprite("Resources/RT.png");
    LT = new Sprite("Resources/LT.png");

    Start = new Sprite("Resources/Start.png");
    Back = new Sprite("Resources/Back.png");
    LThumb = new Sprite("Resources/Thumb.png");
    RThumb = new Sprite("Resources/Thumb.png");

    LStick = new Sprite("Resources/Stick.png");
    RStick = new Sprite("Resources/Stick.png");
    DpadU = new Sprite("Resources/DpadU.png");
    DpadD = new Sprite("Resources/DpadD.png");
    DpadL = new Sprite("Resources/DpadL.png");
    DpadR = new Sprite("Resources/DpadR.png");

    P1 = new Sprite("Resources/P1.png");
    P2 = new Sprite("Resources/P2.png");
    P3 = new Sprite("Resources/P3.png");
    P4 = new Sprite("Resources/P4.png");

    // posição inicial da caixa
    boxX = 614;
    boxY = 286;
}

// ------------------------------------------------------------------------------

void Demo::Update()
{
    if (window->KeyDown(VK_ESCAPE))
        window->Close();

    // alterna entre DirectInput e XInput
    if (window->KeyPress(VK_SPACE))
    {
        if (controllerOn)
        {
            xboxOn = gamepad->XboxInitialize(xboxPlayer);
            controllerOn = false;
        }
        else
        {
            xboxOn = false;
            controllerOn = gamepad->Initialize();
        }
    }

    // --------------------------
    // Controle
    // --------------------------
    if (controllerOn)
    {
        // seleciona próximo controle (Page Down)
        if (window->KeyPress(VK_NEXT))
            gamepad->DeviceNext();

        // seleciona controle anterior (Page Up)
        if (window->KeyPress(VK_PRIOR))
            gamepad->DevicePrev();

        gamepad->UpdateState();

        // move caixa com analógicos
        boxX += gamepad->Axis(AxisX) * gameTime;
        boxY += gamepad->Axis(AxisY) * gameTime;
        boxX += gamepad->Axis(AxisRX) * gameTime;
        boxY += gamepad->Axis(AxisRY) * gameTime;
                
        // move caixa com gatilhos
        boxX += -gamepad->Axis(AxisZ) * gameTime;
        boxX += -gamepad->Axis(AxisRZ) * gameTime;

        // move caixa com Dpad
        float delta = 300 * gameTime;
        switch (gamepad->Dpad())
        {
        case 0:
            boxX += 0.0f;          // para cima
            boxY += -delta;        
            break;
        case 4500:
            boxX += delta;         // para cima e direita
            boxY += -delta;
            break;
        case 9000:
            boxX += delta;         // para direita
            boxY += 0.0f;
            break;
        case 13500:
            boxX += delta;         // para baixo e direita
            boxY += delta;    
            break;
        case 18000:
            boxX += 0.0f;          // para baixo
            boxY += delta;
            break;
        case 22500:
            boxX += -delta;        // para baixo e esquerda
            boxY += delta;
            break;
        case 27000:
            boxX += -delta;        // para esquerda
            boxY += 0.0f;
            break;
        case 31500:
            boxX += -delta;        // para esquerda e para cima
            boxY += -delta;
            break;
        }

        // move caixa com os botões dos ombros
        if (gamepad->ButtonDown(4))
        {
            // para esquerda
            boxX += -delta;        
            boxY += 0.0f;
        }
        if (gamepad->ButtonDown(5))
        {
            // para direita
            boxX += delta;
            boxY += 0.0f;
        }

        // restaura posição inicial da caixa com Start ou Back
        if (gamepad->ButtonDown(6) | gamepad->ButtonDown(7))
        {
            boxX = 614;
            boxY = 286;
        }

        // mantém caixa 50x50 dentro das coordenadas (499, 171) a (730, 401)
        if (boxX - 25.0f < 499)
            boxX = 524.0f;
        if (boxX + 25.0f > 730)
            boxX = 705.0f;
        if (boxY - 25.0f < 171)
            boxY = 196.0f;
        if (boxY + 25.0f > 401)
            boxY = 376.0f;
    }
    else
    {
        // --------------------------
        // Controle do Xbox
        // --------------------------
        if (xboxOn)
        {
            // seleciona próximo controle (Page Down)
            if (window->KeyPress(VK_NEXT))
            {
                uint nextPlayer = (xboxPlayer + 1) % 4;
                
                // se controle para próximo jogador está conectado                
                if (gamepad->XboxUpdateState(nextPlayer))
                    xboxPlayer = nextPlayer;
            }
            // seleciona controle anterior (Page Up)
            if (window->KeyPress(VK_PRIOR))
            {
                uint prevPlayer = xboxPlayer == 0 ? 3 : xboxPlayer - 1;

                // se controle para jogador anterior está conectado    
                if (gamepad->XboxUpdateState(prevPlayer))
                    xboxPlayer = prevPlayer;
            }

            // atualiza estado do controle
            gamepad->XboxUpdateState(xboxPlayer);

            if (gamepad->XboxButton(ButtonBack))
            {
                // parada de segurança da vibração
                gamepad->XboxVibrate(xboxPlayer, 0, 0);
            }
            else
            {
                // vibra com os valores dos gatilhos
                gamepad->XboxVibrate(xboxPlayer, gamepad->XboxTrigger(LeftTrigger) * 257, gamepad->XboxTrigger(RightTrigger) * 257);
            }            
        }
    }
} 

// ------------------------------------------------------------------------------

void Demo::Draw()
{
    // desenha pano de fundo
    backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK);

    // --------------------------
    // Controle
    // --------------------------

    // exibe texto com dados do controle conectado
    if (controllerOn)
    {
        // desenha pano de fundo sobreposto
        overlay->Draw(window->CenterX(), window->CenterY(), Layer::LOWER);
        
        // desenha caixa
        box->Draw(boxX, boxY, Layer::MIDDLE);

        // mostra nome do dispositivo
        text.str("");
        text << gamepad->DeviceName()->c_str();
        gameFont->Draw(240, 100, text.str(), Color(0.28f, 0.28f, 0.28f, 1.0f));

        // pega lista de componentes do dispositivo
        list<JoyPart> joyParts = gamepad->DeviceParts();
        float posY = 175.0f;

        int bt = 0;
        int pov = 0;

        // mostra nome e valor de cada componente
        for (const auto & comp : joyParts)
        {
            text.str("");

            if (comp.guid == GUID_XAxis)
                text << comp.name << ": " << gamepad->Axis(AxisX);
            else if (comp.guid == GUID_YAxis)
                text << comp.name << ": " << gamepad->Axis(AxisY);
            else if (comp.guid == GUID_ZAxis)
                text << comp.name << ": " << gamepad->Axis(AxisZ);
            else if (comp.guid == GUID_RxAxis)
                text << comp.name << ": " << gamepad->Axis(AxisRX);
            else if (comp.guid == GUID_RyAxis)
                text << comp.name << ": " << gamepad->Axis(AxisRY);
            else if (comp.guid == GUID_RzAxis)
                text << comp.name << ": " << gamepad->Axis(AxisRZ);
            else if (comp.guid == GUID_Button)
                text << comp.name << ": " << gamepad->ButtonDown(bt++);
            else if (comp.guid == GUID_POV)
                text << comp.name << ": " << gamepad->Dpad(pov++);
            else if (comp.guid == GUID_Slider)
                text << comp.name << ": " << gamepad->Slider(0);
            else if (comp.guid == GUID_Unknown)
                text << "Controller Unknown";
            else if (comp.guid == GUID_Key)
                text << "Controller Key";

            sysFont->Draw(242.0f, posY, text.str(), Color(0.28f, 0.28f, 0.28f, 1.0f));
            posY = posY + 20.0f;
        }
    }
    else
    {
        // --------------------------
        // Controle do Xbox
        // --------------------------

        if (xboxOn)
        {
            // desenha controle do Xbox 360
            xbox360->Draw(window->CenterX(), window->CenterY(), Layer::LOWER);

            // desenha pano de fundo sobreposto
            xboxOver->Draw(window->CenterX(), window->CenterY(), Layer::MIDDLE);

            // desenha indicação do controle ativo
            switch (xboxPlayer)
            {
            case PLAYER1: P1->Draw(window->CenterX(), window->CenterY(), Layer::UPPER); break;
            case PLAYER2: P2->Draw(window->CenterX(), window->CenterY(), Layer::UPPER); break;
            case PLAYER3: P3->Draw(window->CenterX(), window->CenterY(), Layer::UPPER); break;
            case PLAYER4: P4->Draw(window->CenterX(), window->CenterY(), Layer::UPPER); break;
            }

            // desenha valores dos eixos e gatilhos
            text.str("");
            text << gamepad->XboxTrigger(LeftTrigger);
            int length = int(text.tellp());
            gameFont->Draw(220 - (5.0f * length), 148.0f, text.str(), Color(0.25f, 0.25f, 0.25f, 1.0f));

            text.str("");
            text << gamepad->XboxTrigger(RightTrigger);
            length = int(text.tellp());
            gameFont->Draw(775 - (5.0f * length), 148.0f, text.str(), Color(0.25f, 0.25f, 0.25f, 1.0f));

            text.str("");
            text << gamepad->XboxAnalog(ThumbLX);
            length = int(text.tellp());
            gameFont->Draw(125 - (5.0f * length), 425.0f, text.str(), Color(0.25f, 0.25f, 0.25f, 1.0f));

            text.str("");
            text << gamepad->XboxAnalog(ThumbLY);
            length = int(text.tellp());
            gameFont->Draw(218 - (5.0f * length), 489.0f, text.str(), Color(0.25f, 0.25f, 0.25f, 1.0f));

            text.str("");
            text << gamepad->XboxAnalog(ThumbRX);
            length = int(text.tellp());
            gameFont->Draw(868 - (5.0f * length), 425.0f, text.str(), Color(0.28f, 0.28f, 0.28f, 1.0f));

            text.str("");
            text << gamepad->XboxAnalog(ThumbRY);
            length = int(text.tellp());
            gameFont->Draw(775 - (5.0f * length), 489.0f, text.str(), Color(0.25f, 0.25f, 0.25f, 1.0f));

            // desenha indicações de botões pressionados
            if (gamepad->XboxButton(ButtonA))
                A->Draw(642, 305);
            if (gamepad->XboxButton(ButtonB))
                B->Draw(689, 267);
            if (gamepad->XboxButton(ButtonX))
                X->Draw(601, 270);
            if (gamepad->XboxButton(ButtonY))
                Y->Draw(647, 233);
            if (gamepad->XboxButton(RightBumper))
                RB->Draw(646, 171);
            if (gamepad->XboxButton(LeftBumper))
                LB->Draw(315, 171);
            if (gamepad->XboxTrigger(RightTrigger))
                RT->Draw(632, 129);
            if (gamepad->XboxTrigger(LeftTrigger))
                LT->Draw(331, 129);
            if (gamepad->XboxButton(ButtonStart))
                Start->Draw(541, 272);
            if (gamepad->XboxButton(ButtonBack))
                Back->Draw(422, 272);

            // captura valores dos analógicos na faixa de -15 a 15
            float lx = gamepad->XboxAnalog(ThumbLX) / 2184.46f;
            float ly = gamepad->XboxAnalog(ThumbLY) / 2184.46f;
            float rx = gamepad->XboxAnalog(ThumbRX) / 2184.46f;
            float ry = gamepad->XboxAnalog(ThumbRY) / 2184.46f;

            // desenha analógicos de acordo com suas posições
            LStick->Draw(315 + lx, 284 - ly);
            RStick->Draw(556 + rx, 357 - ry);

            // desenha indicações do pressionamento dos analógicos
            if (gamepad->XboxButton(LeftThumb))
                LThumb->Draw(315 + lx, 284 - ly, Layer::UPPER);
            if (gamepad->XboxButton(RightThumb))
                RThumb->Draw(556 + rx, 357 - ry, Layer::UPPER);

            // desenha indicações de pressionamentos do Dpad
            if (gamepad->XboxButton(DpadUp))
                DpadU->Draw(398, 331);
            if (gamepad->XboxButton(DpadDown))
                DpadD->Draw(399, 381);
            if (gamepad->XboxButton(DpadLeft))
                DpadL->Draw(368, 356);
            if (gamepad->XboxButton(DpadRight))
                DpadR->Draw(429, 358);

            // mostra todos os botões do controle com <ENTER>
            if (window->KeyDown(VK_RETURN))
            {
                A->Draw(642, 305);
                B->Draw(689, 267);
                X->Draw(601, 270);
                Y->Draw(647, 233);
                RB->Draw(646, 171);
                LB->Draw(315, 171);
                RT->Draw(632, 129);
                LT->Draw(331, 129);
                Start->Draw(541, 272);
                Back->Draw(422, 272);

                float lx = gamepad->XboxAnalog(ThumbLX) / 2184.46f; 
                float ly = gamepad->XboxAnalog(ThumbLY) / 2184.46f; 
                float rx = gamepad->XboxAnalog(ThumbRX) / 2184.46f; 
                float ry = gamepad->XboxAnalog(ThumbRY) / 2184.46f; 

                LThumb->Draw(315 + lx, 284 - ly, Layer::UPPER);
                RThumb->Draw(556 + rx, 357 - ry, Layer::UPPER);
                DpadU->Draw(398, 331);
                DpadD->Draw(399, 381);
                DpadL->Draw(368, 356);
                DpadR->Draw(429, 358);
            }
        }
        else
        {
            // ---------------------------------
            // Controle Não Compatível com Xbox
            // ---------------------------------

            // desenha controle do Xbox 360
            xbox360->Draw(window->CenterX(), window->CenterY(), Layer::LOWER);

            // desenha mensagem de incompatibilidade 
            gameFont->Draw(360.0f, 480.0f, "Controle compatível não encontrado", Color(0.25f, 0.25f, 0.25f, 1.0f));
        }
    }
} 

// ------------------------------------------------------------------------------

void Demo::Finalize()
{
    // libera sprites
    delete P1;
    delete P2;
    delete P3;
    delete P4;

    delete A;
    delete B;
    delete X;
    delete Y;

    delete RB;
    delete LB;
    delete RT;
    delete LT;

    delete Start;
    delete Back;
    delete LThumb;
    delete RThumb;
    delete LStick;
    delete RStick;

    delete DpadR;
    delete DpadL;
    delete DpadU;
    delete DpadD;

    delete backg;
    delete overlay;
    delete xboxOver;
    delete xbox360;
    delete box;

    // libera fontes
    delete gameFont;
    delete sysFont;
    
    // libera controles
    delete gamepad;
}

// ------------------------------------------------------------------------------
//                                  WinMain                                      
// ------------------------------------------------------------------------------

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, 
                     _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
     Engine * engine = new Engine();

    // configura motor
    engine->window->Mode(WINDOWED);
    engine->window->Size(960, 540);
    engine->window->Color(20, 20, 20);
    engine->window->Title("Controller");
    engine->window->Icon(IDI_ICON);
    engine->window->Cursor(IDC_CURSOR);
    engine->graphics->VSync(true);

    // inicia o jogo
    int status = engine->Start(new Demo());

    delete engine;
    return status;
}

// ----------------------------------------------------------------------------

