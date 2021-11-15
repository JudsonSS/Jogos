/**********************************************************************************
// Renderer (Código Fonte)
//
// Criação:     11 Mai 2014
// Atualização: 01 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Define um renderizador de grupos de sprites
//
**********************************************************************************/

#include "Renderer.h"
#include "Engine.h"
#include <algorithm>
#include <d3dcompiler.h>

// ---------------------------------------------------------------------------------

Renderer::Renderer()
{
    window         = nullptr;
    graphics       = nullptr;
    inputLayout    = nullptr;
    vertexShader   = nullptr;
    pixelShader    = nullptr;
    rasterState    = nullptr;
    sampler        = nullptr;
    vertexBuffer   = nullptr;
    indexBuffer    = nullptr;
    constantBuffer = nullptr;

    vertexBufferPosition = 0;

    // ----------------------------------------
    // Pixel Ploting
    // ----------------------------------------
    pixelPlotTexture = nullptr;
    pixelPlotView = nullptr;
    ZeroMemory(&pixelPlotSprite, sizeof(pixelPlotSprite));
    videoMemoryPitch = 0;
    videoMemory = nullptr;
    // ----------------------------------------

    storage = new SpriteData[MaxBatchSize];
    storageIndex = 0;
}

// ---------------------------------------------------------------------------------

Renderer::~Renderer()
{
    // libera armazém de sprites
    delete [] storage;

    // ----------------------------------------
    // Pixel Ploting
    // ----------------------------------------

    // libera visualização da textura de plotagem de pixels
    if (pixelPlotView)
    {
        pixelPlotView->Release();
        pixelPlotView = nullptr;
    }

    // libera textura de plotagem de pixels
    if (pixelPlotTexture)
    {
        pixelPlotTexture->Release();
        pixelPlotTexture = nullptr;
    }

    // ----------------------------------------

    if (constantBuffer)
    {
        constantBuffer->Release();
        constantBuffer = nullptr;
    }
    
    if (indexBuffer)
    {
        indexBuffer->Release();
        indexBuffer = nullptr;
    }

    if (vertexBuffer)
    {
        vertexBuffer->Release();
        vertexBuffer = nullptr;
    }

    if (sampler)
    {
        sampler->Release();
        sampler = nullptr;
    }

    if (rasterState)
    {
        rasterState->Release();
        rasterState = nullptr;
    }

    if (pixelShader)
    {
        pixelShader->Release();
        pixelShader = nullptr;
    }

    if (vertexShader)
    {
        vertexShader->Release();
        vertexShader = nullptr;
    }

    if (inputLayout)
    {
        inputLayout->Release();
        inputLayout = nullptr;
    }
}

// -----------------------------------------------------------------------------

void Renderer::BeginPixels()
{
    // trava a textura para plotagem de pixels
    D3D11_MAPPED_SUBRESOURCE mappedTex;
    graphics->context->Map(pixelPlotTexture, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedTex);

    // formato de tela usando 32 bits por pixel
    // ----------------------------------------
    // A memória de vídeo é dividida em blocos de 4 bytes (32 bits por pixel)
    // O pitch é a largura de uma linha da memória de vídeo. O valor do pitch
    // é dado em bytes e portanto será igual a quantidade de pixels * 4 bytes 
    // por pixel. Para obter a quantidade de pixels em cada linha da memória 
    // de vídeo devemos dividir o valor do pitch por 4. É exatamente o que a 
    // operação de deslocamente de bits (>>) está fazendo.

    // define o ponteiro para a memória de vídeo e o pitch da memória
    videoMemoryPitch = mappedTex.RowPitch >> 2;
    videoMemory = (ulong*)mappedTex.pData;

    // limpa a textura para o próximo desenho
    // 0xff000000 = valor 32bits codificado com Alpha transparente
    memset(videoMemory, 0xff000000, mappedTex.RowPitch * int(window->Height()));
}

// -----------------------------------------------------------------------------

void Renderer::Draw(Geometry * shape, ulong color)
{
    switch (shape->Type())
    {
    case POINT_T:
        Draw((Point*)shape, color);
        break;
    case LINE_T:
        Draw((Line*)shape, color);
        break;
    case RECTANGLE_T:
        Draw((Rect*)shape, color);
        break;
    case CIRCLE_T:
        Draw((Circle*)shape, color);
        break;
    case POLYGON_T:
        Draw((Poly*)shape, color);
        break;
    case MIXED_T:
        Draw((Mixed*)shape, color);
        break;
    }
}

// -----------------------------------------------------------------------------

void Renderer::Draw(Point * point, ulong color)
{
    if (point->X() >= Engine::game->viewport.left && point->X() < Engine::game->viewport.right)
        if (point->Y() >= Engine::game->viewport.top && point->Y() < Engine::game->viewport.bottom)
            PlotPixel(int(point->X() - Engine::game->viewport.left), int(point->Y() - Engine::game->viewport.top), color);
}

// -----------------------------------------------------------------------------

void Renderer::Draw(Line * line, ulong color)
{
    int x1 = int(line->Ax());
    int y1 = int(line->Ay());
    int x2 = int(line->Bx());
    int y2 = int(line->By());

    // desenha apenas a parte visível da linha
    if (ClipLine(x1, y1, x2, y2))
        DrawLine(x1, y1, x2, y2, color);
}

// -----------------------------------------------------------------------------

int Renderer::ClipLine(int& x1, int& y1, int& x2, int& y2)
{

    // Clipping Line Algorithm 
    // Implementation by André LaMothe from "Tricks of The Windows Game Programming Gurus", SAMS, 2002

    // this function clips the sent line using the clipping region defined below
    int min_clip_x = int(Engine::game->viewport.left);
    int min_clip_y = int(Engine::game->viewport.top);
    int max_clip_x = int(Engine::game->viewport.right - 1);
    int max_clip_y = int(Engine::game->viewport.bottom - 1);

    // internal clipping codes
    #define CLIP_CODE_C  0x0000
    #define CLIP_CODE_N  0x0008
    #define CLIP_CODE_S  0x0004
    #define CLIP_CODE_E  0x0002
    #define CLIP_CODE_W  0x0001
    
    #define CLIP_CODE_NE 0x000a
    #define CLIP_CODE_SE 0x0006
    #define CLIP_CODE_NW 0x0009 
    #define CLIP_CODE_SW 0x0005

    int xc1 = x1,
        yc1 = y1,
        xc2 = x2,
        yc2 = y2;

    int p1_code = 0,
        p2_code = 0;

    // determine codes for p1 and p2
    if (y1 < min_clip_y)
        p1_code |= CLIP_CODE_N;
    else
        if (y1 > max_clip_y)
            p1_code |= CLIP_CODE_S;

    if (x1 < min_clip_x)
        p1_code |= CLIP_CODE_W;
    else
        if (x1 > max_clip_x)
            p1_code |= CLIP_CODE_E;

    if (y2 < min_clip_y)
        p2_code |= CLIP_CODE_N;
    else
        if (y2 > max_clip_y)
            p2_code |= CLIP_CODE_S;

    if (x2 < min_clip_x)
        p2_code |= CLIP_CODE_W;
    else
        if (x2 > max_clip_x)
            p2_code |= CLIP_CODE_E;

    // try and trivially reject
    if ((p1_code & p2_code))
        return 0;

    // test for totally visible, if so leave points untouched
    if (p1_code == 0 && p2_code == 0)
        return 1;

    // determine end clip point for p1
    switch (p1_code)
    {
    case CLIP_CODE_C: break;

    case CLIP_CODE_N:
    {
        yc1 = min_clip_y;
        xc1 = int(x1 + 0.5 + (min_clip_y - y1) * (x2 - x1) / (y2 - y1));
    } break;
    case CLIP_CODE_S:
    {
        yc1 = max_clip_y;
        xc1 = int(x1 + 0.5 + (max_clip_y - y1) * (x2 - x1) / (y2 - y1));
    } break;

    case CLIP_CODE_W:
    {
        xc1 = min_clip_x;
        yc1 = int(y1 + 0.5 + (min_clip_x - x1) * (y2 - y1) / (x2 - x1));
    } break;

    case CLIP_CODE_E:
    {
        xc1 = max_clip_x;
        yc1 = int(y1 + 0.5 + (max_clip_x - x1) * (y2 - y1) / (x2 - x1));
    } break;

    // these cases are more complex, must compute 2 intersections
    case CLIP_CODE_NE:
    {
        // north hline intersection
        yc1 = min_clip_y;
        xc1 = int(x1 + 0.5 + (min_clip_y - y1) * (x2 - x1) / (y2 - y1));

        // test if intersection is valid, of so then done, else compute next
        if (xc1 < min_clip_x || xc1 > max_clip_x)
        {
            // east vline intersection
            xc1 = max_clip_x;
            yc1 = int(y1 + 0.5 + (max_clip_x - x1) * (y2 - y1) / (x2 - x1));
        } // end if
    } break;

    case CLIP_CODE_SE:
    {
        // south hline intersection
        yc1 = max_clip_y;
        xc1 = int(x1 + 0.5 + (max_clip_y - y1) * (x2 - x1) / (y2 - y1));

        // test if intersection is valid, of so then done, else compute next
        if (xc1 < min_clip_x || xc1 > max_clip_x)
        {
            // east vline intersection
            xc1 = max_clip_x;
            yc1 = int(y1 + 0.5 + (max_clip_x - x1) * (y2 - y1) / (x2 - x1));
        } // end if
    } break;

    case CLIP_CODE_NW:
    {
        // north hline intersection
        yc1 = min_clip_y;
        xc1 = int(x1 + 0.5 + (min_clip_y - y1) * (x2 - x1) / (y2 - y1));

        // test if intersection is valid, of so then done, else compute next
        if (xc1 < min_clip_x || xc1 > max_clip_x)
        {
            xc1 = min_clip_x;
            yc1 = int(y1 + 0.5 + (min_clip_x - x1) * (y2 - y1) / (x2 - x1));
        } // end if
    } break;

    case CLIP_CODE_SW:
    {
        // south hline intersection
        yc1 = max_clip_y;
        xc1 = int(x1 + 0.5 + (max_clip_y - y1) * (x2 - x1) / (y2 - y1));

        // test if intersection is valid, of so then done, else compute next
        if (xc1 < min_clip_x || xc1 > max_clip_x)
        {
            xc1 = min_clip_x;
            yc1 = int(y1 + 0.5 + (min_clip_x - x1) * (y2 - y1) / (x2 - x1));
        } // end if
    } break;

    default:break;
    } // end switch

    // determine clip point for p2
    switch (p2_code)
    {
    case CLIP_CODE_C: break;

    case CLIP_CODE_N:
    {
        yc2 = min_clip_y;
        xc2 = x2 + (min_clip_y - y2) * (x1 - x2) / (y1 - y2);
    } break;

    case CLIP_CODE_S:
    {
        yc2 = max_clip_y;
        xc2 = x2 + (max_clip_y - y2) * (x1 - x2) / (y1 - y2);
    } break;

    case CLIP_CODE_W:
    {
        xc2 = min_clip_x;
        yc2 = y2 + (min_clip_x - x2) * (y1 - y2) / (x1 - x2);
    } break;

    case CLIP_CODE_E:
    {
        xc2 = max_clip_x;
        yc2 = y2 + (max_clip_x - x2) * (y1 - y2) / (x1 - x2);
    } break;

    // these cases are more complex, must compute 2 intersections
    case CLIP_CODE_NE:
    {
        // north hline intersection
        yc2 = min_clip_y;
        xc2 = int(x2 + 0.5 + (min_clip_y - y2) * (x1 - x2) / (y1 - y2));

        // test if intersection is valid, of so then done, else compute next
        if (xc2 < min_clip_x || xc2 > max_clip_x)
        {
            // east vline intersection
            xc2 = max_clip_x;
            yc2 = int(y2 + 0.5 + (max_clip_x - x2) * (y1 - y2) / (x1 - x2));
        } // end if
    } break;

    case CLIP_CODE_SE:
    {
        // south hline intersection
        yc2 = max_clip_y;
        xc2 = int(x2 + 0.5 + (max_clip_y - y2) * (x1 - x2) / (y1 - y2));

        // test if intersection is valid, of so then done, else compute next
        if (xc2 < min_clip_x || xc2 > max_clip_x)
        {
            // east vline intersection
            xc2 = max_clip_x;
            yc2 = int(y2 + 0.5 + (max_clip_x - x2) * (y1 - y2) / (x1 - x2));
        } // end if
    } break;

    case CLIP_CODE_NW:
    {
        // north hline intersection
        yc2 = min_clip_y;
        xc2 = int(x2 + 0.5 + (min_clip_y - y2) * (x1 - x2) / (y1 - y2));

        // test if intersection is valid, of so then done, else compute next
        if (xc2 < min_clip_x || xc2 > max_clip_x)
        {
            xc2 = min_clip_x;
            yc2 = int(y2 + 0.5 + (min_clip_x - x2) * (y1 - y2) / (x1 - x2));
        } // end if

    } break;

    case CLIP_CODE_SW:
    {
        // south hline intersection
        yc2 = max_clip_y;
        xc2 = int(x2 + 0.5 + (max_clip_y - y2) * (x1 - x2) / (y1 - y2));

        // test if intersection is valid, of so then done, else compute next
        if (xc2 < min_clip_x || xc2 > max_clip_x)
        {
            xc2 = min_clip_x;
            yc2 = int(y2 + 0.5 + (min_clip_x - x2) * (y1 - y2) / (x1 - x2));
        } // end if

    } break;

    default:break;

    } // end switch

    // do bounds check
    if ((xc1 < min_clip_x) || (xc1 > max_clip_x) ||
        (yc1 < min_clip_y) || (yc1 > max_clip_y) ||
        (xc2 < min_clip_x) || (xc2 > max_clip_x) ||
        (yc2 < min_clip_y) || (yc2 > max_clip_y))
    {
        return 0;
    }

    // store vars back
    x1 = xc1;
    y1 = yc1;
    x2 = xc2;
    y2 = yc2;

    return 1;
}

// -----------------------------------------------------------------------------

void Renderer::DrawLine(int a1, int b1, int a2, int b2, ulong color)
{
    a1 -= int(Engine::game->viewport.left);
    b1 -= int(Engine::game->viewport.top);
    a2 -= int(Engine::game->viewport.left);
    b2 -= int(Engine::game->viewport.top);

    // Symmetric Double Step Line Algorithm by Xialon Wu
    // It's 3 to 4 times faster than the standard Bressenham's algorithm
    // Implementation by Brian Wyvill from "Graphics Gems", Academic Press, 1990

    int dx, dy, incr1, incr2, D, x, y, xend, c, pixels_left;
    int x1, y1;
    int sign_x, sign_y, step, reverse, i;

    dx = (a2 - a1) * (sign_x = ((a2 - a1) < 0 ? -1 : 1));
    dy = (b2 - b1) * (sign_y = ((b2 - b1) < 0 ? -1 : 1));

    /* decide increment sign by the slope sign */
    if (sign_x == sign_y)
        step = 1;
    else
        step = -1;

    /* chooses axis of greatest movement (make dx) */
    if (dy > dx)
    {
        // operator ^= obtain the bitwise exclusive OR of the first and second operands; 
        // store the result in the object specified by the first operand
        a1 ^= b1; b1 ^= a1; a1 ^= b1;
        a2 ^= b2; b2 ^= a2; a2 ^= b2;
        dx ^= dy; dy ^= dx; dx ^= dy;
        reverse = 1;
    }
    else
        reverse = 0;

    /* note error check for dx==0 should be included here */
    /* start from the smaller coordinate */
    if (a1 > a2)
    {
        x = a2;
        y = b2;
        x1 = a1;
        y1 = b1;
    }
    else
    {
        x = a1;
        y = b1;
        x1 = a2;
        y1 = b2;
    }

    /* Note dx=n implies 0 - n or (dx+1) pixels to be set
    * Go round loop dx/4 times then plot last 0,1,2 or 3 pixels
    *  In fact (dx-1)/4 as 2 pixels are already plotted */
    xend = (dx - 1) / 4;
    pixels_left = (dx - 1) % 4;    /* number of pixels left over at the end */
    PlotLine(x, y, reverse, color);
    if (pixels_left < 0)
        return;    /* plot only one pixel for zero
                * length vectors */
    PlotLine(x1, y1, reverse, color);    /* plot first two points */
    incr2 = 4 * dy - 2 * dx;
    if (incr2 < 0) {    /* slope less than 1/2 */
        c = 2 * dy;
        incr1 = 2 * c;
        D = incr1 - dx;

        for (i = 0; i < xend; i++) {    /* plotting loop */
            ++x;
            --x1;
            if (D < 0) {
                /* pattern 1 forwards */
                PlotLine(x, y, reverse, color);
                PlotLine(++x, y, reverse, color);
                /* pattern 1 backwards */
                PlotLine(x1, y1, reverse, color);
                PlotLine(--x1, y1, reverse, color);
                D += incr1;
            }
            else {
                if (D < c) {
                    /* pattern 2 forwards */
                    PlotLine(x, y, reverse, color);
                    PlotLine(++x, y += step, reverse, color);
                    /* pattern 2 backwards */
                    PlotLine(x1, y1, reverse, color);
                    PlotLine(--x1, y1 -= step, reverse, color);
                }
                else {
                    /* pattern 3 forwards */
                    PlotLine(x, y += step, reverse, color);
                    PlotLine(++x, y, reverse, color);
                    /* pattern 3 backwards */
                    PlotLine(x1, y1 -= step, reverse, color);
                    PlotLine(--x1, y1, reverse, color);
                }
                D += incr2;
            }
        }        /* end for */
        /* plot last pattern */
        if (pixels_left) {
            if (D < 0) {
                PlotLine(++x, y, reverse, color);    /* pattern 1 */
                if (pixels_left > 1)
                    PlotLine(++x, y, reverse, color);
                if (pixels_left > 2)
                    PlotLine(--x1, y1, reverse, color);
            }
            else {
                if (D < c) {
                    PlotLine(++x, y, reverse, color);    /* pattern 2  */
                    if (pixels_left > 1)
                        PlotLine(++x, y += step, reverse, color);
                    if (pixels_left > 2)
                        PlotLine(--x1, y1, reverse, color);
                }
                else {
                    /* pattern 3 */
                    PlotLine(++x, y += step, reverse, color);
                    if (pixels_left > 1)
                        PlotLine(++x, y, reverse, color);
                    if (pixels_left > 2)
                        PlotLine(--x1, y1 -= step, reverse, color);
                }
            }
        }        /* end if pixels_left */
    }
    /* end slope < 1/2 */
    else {            /* slope greater than 1/2 */
        c = 2 * (dy - dx);
        incr1 = 2 * c;
        D = incr1 + dx;
        for (i = 0; i < xend; i++) {
            ++x;
            --x1;
            if (D > 0) {
                /* pattern 4 forwards */
                PlotLine(x, y += step, reverse, color);
                PlotLine(++x, y += step, reverse, color);
                /* pattern 4 backwards */
                PlotLine(x1, y1 -= step, reverse, color);
                PlotLine(--x1, y1 -= step, reverse, color);
                D += incr1;
            }
            else {
                if (D < c) {
                    /* pattern 2 forwards */
                    PlotLine(x, y, reverse, color);
                    PlotLine(++x, y += step, reverse, color);

                    /* pattern 2 backwards */
                    PlotLine(x1, y1, reverse, color);
                    PlotLine(--x1, y1 -= step, reverse, color);
                }
                else {
                    /* pattern 3 forwards */
                    PlotLine(x, y += step, reverse, color);
                    PlotLine(++x, y, reverse, color);
                    /* pattern 3 backwards */
                    PlotLine(x1, y1 -= step, reverse, color);
                    PlotLine(--x1, y1, reverse, color);
                }
                D += incr2;
            }
        }        /* end for */
        /* plot last pattern */
        if (pixels_left) {
            if (D > 0) {
                PlotLine(++x, y += step, reverse, color);    /* pattern 4 */
                if (pixels_left > 1)
                    PlotLine(++x, y += step, reverse, color);
                if (pixels_left > 2)
                    PlotLine(--x1, y1 -= step, reverse, color);
            }
            else {
                if (D < c) {
                    PlotLine(++x, y, reverse, color);    /* pattern 2  */
                    if (pixels_left > 1)
                        PlotLine(++x, y += step, reverse, color);
                    if (pixels_left > 2)
                        PlotLine(--x1, y1, reverse, color);
                }
                else {
                    /* pattern 3 */
                    PlotLine(++x, y += step, reverse, color);
                    if (pixels_left > 1)
                        PlotLine(++x, y, reverse, color);
                    if (pixels_left > 2) {
                        if (D > c) /* step 3 */
                            PlotLine(--x1, y1 -= step, reverse, color);
                        else /* step 2 */
                            PlotLine(--x1, y1, reverse, color);
                    }
                }
            }
        }
    }
}

// -----------------------------------------------------------------------------

void Renderer::Draw(Rect * rect, ulong color)
{
    Line top(rect->Left(), rect->Top(), rect->Right(), rect->Top());
    Line left(rect->Left(), rect->Top() + 1, rect->Left(), rect->Bottom());
    Line right(rect->Right(), rect->Top() + 1, rect->Right(), rect->Bottom());
    Line bottom(rect->Left() + 1, rect->Bottom(), rect->Right() - 1, rect->Bottom());

    Draw(&top, color);
    Draw(&left, color);
    Draw(&right, color);
    Draw(&bottom, color);
}

// -----------------------------------------------------------------------------

void Renderer::Draw(Circle * circ, ulong color)
{
    // Bresenham's circle algorithm

    int xpos = int(circ->CenterX());
    int ypos = int(circ->CenterY());

    int r = int(circ->Radius());

    int p = 3 - (2 * r);
    int x = 0;
    int y = r;

    Point a(xpos, ypos + r); Draw(&a, color);
    Point b(xpos, ypos - r); Draw(&b, color);
    Point c(xpos, ypos + r); Draw(&c, color);
    Point d(xpos, ypos - r); Draw(&d, color);
    Point e(xpos + r, ypos); Draw(&e, color);
    Point f(xpos + r, ypos); Draw(&f, color);
    Point g(xpos - r, ypos); Draw(&g, color);
    Point h(xpos - r, ypos); Draw(&h, color);

    //for(x=1; x <= int(radius/sqrt(2.0f)); x++)
    while (++x < y)
    {
        if (p < 0)
            p = p + (4 * x) + 6;
        else
        {
            p = p + 4 * (x - y) + 10;
            y = y - 1;
        }

        a.MoveTo(float(xpos + x), float(ypos + y)); Draw(&a, color);
        b.MoveTo(float(xpos + x), float(ypos - y)); Draw(&b, color);
        c.MoveTo(float(xpos - x), float(ypos + y)); Draw(&c, color);
        d.MoveTo(float(xpos - x), float(ypos - y)); Draw(&d, color);
        e.MoveTo(float(xpos + y), float(ypos + x)); Draw(&e, color);
        f.MoveTo(float(xpos + y), float(ypos - x)); Draw(&f, color);
        g.MoveTo(float(xpos - y), float(ypos + x)); Draw(&g, color);
        h.MoveTo(float(xpos - y), float(ypos - x)); Draw(&h, color);
    }
}

// -----------------------------------------------------------------------------

void Renderer::Draw(Poly * pol, ulong color)
{
    float x1, y1, x2, y2;
    float x1r, y1r, x2r, y2r;
    float x1s, y1s, x2s, y2s;

    uint i;

    const double PIunder180 = 0.0174532925194444;

    // converte ângulo de rotação para radianos
    float theta = float(pol->Rotation() * PIunder180);

    // loop through and draw a line from vertices 1 to n-1
    for (i = 0; i < pol->vertexCount - 1; ++i)
    {

        // aplica rotação aos pontos
        x1r = float(pol->vertexList[i].X() * cos(theta) - pol->vertexList[i].Y() * sin(theta));
        y1r = float(pol->vertexList[i].X() * sin(theta) + pol->vertexList[i].Y() * cos(theta));
        x2r = float(pol->vertexList[i + 1].X() * cos(theta) - pol->vertexList[i + 1].Y() * sin(theta));
        y2r = float(pol->vertexList[i + 1].X() * sin(theta) + pol->vertexList[i + 1].Y() * cos(theta));

        // aplica escala aos pontos
        x1s = x1r * pol->Scale();
        y1s = y1r * pol->Scale();
        x2s = x2r * pol->Scale();
        y2s = y2r * pol->Scale();

        // transforma coordenadas locais em globais
        x1 = pol->X() + x1s;
        y1 = pol->Y() + y1s;
        x2 = pol->X() + x2s;
        y2 = pol->Y() + y2s;

        // draw a line clipping to viewport
        Line line(x1, y1, x2, y2);
        Draw(&line, color);
    }

    // now close up polygon
    // draw line from first to last vertex
    // aplica rotação aos pontos
    x1r = float(pol->vertexList[0].X() * cos(theta) - pol->vertexList[0].Y() * sin(theta));
    y1r = float(pol->vertexList[0].X() * sin(theta) + pol->vertexList[0].Y() * cos(theta));
    x2r = float(pol->vertexList[i].X() * cos(theta) - pol->vertexList[i].Y() * sin(theta));
    y2r = float(pol->vertexList[i].X() * sin(theta) + pol->vertexList[i].Y() * cos(theta));

    // aplica escala aos pontos
    x1s = x1r * pol->Scale();
    y1s = y1r * pol->Scale();
    x2s = x2r * pol->Scale();
    y2s = y2r * pol->Scale();

    // transforma coordenadas locais em globais
    x1 = pol->X() + x1s;
    y1 = pol->Y() + y1s;
    x2 = pol->X() + x2s;
    y2 = pol->Y() + y2s;

    // draw a line clipping to viewport
    Line line(x1, y1, x2, y2);
    Draw(&line, color);
}

// -----------------------------------------------------------------------------

void Renderer::Draw(Mixed* mul, ulong color)
{
    for (auto i : mul->shapes)
        Draw(i, color);
}

// -----------------------------------------------------------------------------

void Renderer::EndPixels()
{
    // destrava a textura de plotagem de pixels
    graphics->context->Unmap(pixelPlotTexture, 0);

    // adiciona o sprite na lista de desenho
    Draw(pixelPlotSprite);
}

// ---------------------------------------------------------------------------------

bool Renderer::Initialize(Window * window, Graphics * graphics)
{
    this->window = window;
    this->graphics = graphics;

    //-------------------------------
    // Vertex Shader
    //-------------------------------

    // carrega bytecode do vertex shader (HLSL)
    ID3DBlob * vShader = nullptr;
    D3DReadFileToBlob(L"Shaders/Vertex.cso", &vShader);

    // cria o vertex shader
    graphics->device->CreateVertexShader(vShader->GetBufferPointer(), vShader->GetBufferSize(), NULL, &vertexShader);

    //-------------------------------
    // Input Layout
    //-------------------------------

    // descreve o input layout dos vértices
    D3D11_INPUT_ELEMENT_DESC layoutDesc[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,       0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
    };

    // cria o input layout
    graphics->device->CreateInputLayout(layoutDesc, 3, vShader->GetBufferPointer(), vShader->GetBufferSize(), &inputLayout);

    // libera bytecode
    vShader->Release();

    //-------------------------------
    // Pixel Shader
    //-------------------------------

    // carrega bytecode do pixel shader (HLSL)
    ID3DBlob * pShader = nullptr;
    D3DReadFileToBlob(L"Shaders/Pixel.cso", &pShader);

    // cria o vertex shader
    graphics->device->CreatePixelShader(pShader->GetBufferPointer(), pShader->GetBufferSize(), NULL, &pixelShader);

    // libera bytecode
    pShader->Release();

    //-------------------------------
    // Rasterizador
    //-------------------------------

    D3D11_RASTERIZER_DESC rasterDesc;
    ZeroMemory(&rasterDesc, sizeof(rasterDesc));
    rasterDesc.FillMode = D3D11_FILL_SOLID;
    //rasterDesc.FillMode = D3D11_FILL_WIREFRAME;
    rasterDesc.CullMode = D3D11_CULL_NONE;
    rasterDesc.DepthClipEnable = true;

    // cria estado do rasterizador
    graphics->device->CreateRasterizerState(&rasterDesc, &rasterState);

    //-------------------------------
    // Vertex Buffer
    //-------------------------------

    D3D11_BUFFER_DESC vertexBufferDesc = { 0 };
    vertexBufferDesc.ByteWidth = sizeof(Vertex)* MaxBatchSize * VerticesPerSprite;
    vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    graphics->device->CreateBuffer(&vertexBufferDesc, nullptr, &vertexBuffer);

    //-------------------------------
    // Index Buffer
    //-------------------------------

    D3D11_BUFFER_DESC indexBufferDesc = { 0 };
    indexBufferDesc.ByteWidth = sizeof(short)* MaxBatchSize * IndicesPerSprite;
    indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    
    // gera índices para o número máximo de sprites suportados
    vector<short> indices;
    indices.reserve(MaxBatchSize * IndicesPerSprite);
    for (short i = 0; i < MaxBatchSize * VerticesPerSprite; i += VerticesPerSprite)
    {
        indices.push_back(i);
        indices.push_back(i + 1);
        indices.push_back(i + 2);

        indices.push_back(i + 1);
        indices.push_back(i + 3);
        indices.push_back(i + 2);
    }

    D3D11_SUBRESOURCE_DATA indexData = { 0 };
    indexData.pSysMem = &indices.front();

    if FAILED(graphics->device->CreateBuffer(&indexBufferDesc, &indexData, &indexBuffer))
        return false;

    //-------------------------------
    // Constant Buffer
    //-------------------------------

    D3D11_BUFFER_DESC constBufferDesc = { 0 };
    constBufferDesc.ByteWidth = sizeof(XMMATRIX);
    constBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    constBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    constBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    // calcula a matriz de transformação
    float xScale = (graphics->viewport.Width  > 0) ? 2.0f / graphics->viewport.Width : 0.0f;
    float yScale = (graphics->viewport.Height > 0) ? 2.0f / graphics->viewport.Height : 0.0f;
    
    // transforma para coordenadas da tela
    XMMATRIX transformMatrix 
    (
        xScale,  0,      0,      0,
        0,      -yScale, 0,      0,
        0,       0,      1,      0,
       -1,       1,      0,      1
    );

    D3D11_SUBRESOURCE_DATA constantData = { 0 };
    XMMATRIX worldViewProj =  XMMatrixTranspose(transformMatrix);
    constantData.pSysMem = &worldViewProj;

    graphics->device->CreateBuffer(&constBufferDesc, &constantData, &constantBuffer);

    //-------------------------------
    // Texture Sampler
    //-------------------------------

    D3D11_SAMPLER_DESC samplerDesc;
    ZeroMemory(&samplerDesc, sizeof(samplerDesc));
    samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;
    samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.MipLODBias = 0.0f;
    samplerDesc.MaxAnisotropy = (graphics->device->GetFeatureLevel() > D3D_FEATURE_LEVEL_9_1) ? 16 : 2;
    samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    samplerDesc.BorderColor[0] = 0.0f;
    samplerDesc.BorderColor[1] = 0.0f;
    samplerDesc.BorderColor[2] = 0.0f;
    samplerDesc.BorderColor[3] = 0.0f;
    samplerDesc.MinLOD = 0;
    samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

    // cria o amostrador da textura
    graphics->device->CreateSamplerState(&samplerDesc, &sampler);

    //-------------------------------
    // Configura Direct3D Pipeline
    //-------------------------------

    uint vertexStride = sizeof(Vertex);
    uint vertexOffset = 0;
    graphics->context->IASetVertexBuffers(0, 1, &vertexBuffer, &vertexStride, &vertexOffset);
    graphics->context->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R16_UINT, 0);
    graphics->context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    graphics->context->IASetInputLayout(inputLayout);
    graphics->context->VSSetShader(vertexShader, NULL, 0);
    graphics->context->VSSetConstantBuffers(0, 1, &constantBuffer);
    graphics->context->PSSetShader(pixelShader, NULL, 0);
    graphics->context->PSSetSamplers(0, 1, &sampler);
    graphics->context->RSSetState(rasterState);

    // ---------------------------------------------
    // Textura de Plotagem de Pixels
    // ---------------------------------------------

    // descreve uma textura a ser preenchida manualmente
    D3D11_TEXTURE2D_DESC desc;
    ZeroMemory(&desc, sizeof(desc));

    desc.Width = int(window->Width());              // largura da textura
    desc.Height = int(window->Height());            // altura da textura
    desc.MipLevels = 1;                             // usa apenas um nível
    desc.ArraySize = 1;                             // cria apenas uma textura
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;       // formato RGBA de 32 bits
    desc.SampleDesc.Count = 1;                      // uma amostra por pixel (sem antialiasing)
    desc.Usage = D3D11_USAGE_DYNAMIC;               // alocada em RAM para acesso rápido via CPU
    desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;    // será acessada por um shader
    desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;   // CPU pode escrever na textura

    // cria textura a ser preenchida com pixels
    if FAILED(graphics->device->CreateTexture2D(&desc, nullptr, &pixelPlotTexture))
        return false;

    // configura visualização para a textura de pixels
    D3D11_SHADER_RESOURCE_VIEW_DESC pixelPlotDesc;
    ZeroMemory(&pixelPlotDesc, sizeof(pixelPlotDesc));

    pixelPlotDesc.Format = desc.Format;
    pixelPlotDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    pixelPlotDesc.Texture2D.MipLevels = desc.MipLevels;
    pixelPlotDesc.Texture2D.MostDetailedMip = desc.MipLevels - 1;

    // cria uma visualização para a textura de pixels
    if FAILED(graphics->device->CreateShaderResourceView((ID3D11Resource*)pixelPlotTexture, &pixelPlotDesc, &pixelPlotView))
        return false;

    // ---------------------------------------------
    // Sprite 
    // ---------------------------------------------

    pixelPlotSprite.x = window->CenterX();
    pixelPlotSprite.y = window->CenterY();
    pixelPlotSprite.scale = 1.0f;
    pixelPlotSprite.depth = 0.01f;
    pixelPlotSprite.rotation = 0.0f;
    pixelPlotSprite.width = uint(window->Width());
    pixelPlotSprite.height = uint(window->Height());
    pixelPlotSprite.texture = pixelPlotView;
    pixelPlotSprite.texCoord.x = 0.0f;
    pixelPlotSprite.texCoord.y = 0.0f;
    pixelPlotSprite.texSize.x = 1.0f;
    pixelPlotSprite.texSize.y = 1.0f;
    pixelPlotSprite.color = Color(1.0f, 1.0f, 1.0f, 1.0f);

    // inicialização bem sucedida
    return true;
}

// ---------------------------------------------------------------------------------

void Renderer::RenderBatch(ID3D11ShaderResourceView * texture, SpriteData ** sprites, uint count)
{
    // desenhe usando a seguinte textura
    graphics->context->PSSetShaderResources(0, 1, &texture);

    while (count > 0)
    {
        // quantos sprites vamos desenhar
        uint batchSize = count;

        // quantos sprites cabem no vertex buffer
        uint remainingSpace = MaxBatchSize - vertexBufferPosition;

        // quantidade de sprite é maior do que o espaço disponível
        if (batchSize > remainingSpace)
        {
            // se o tamanho disponível é muito pequeno
            if (remainingSpace < MinBatchSize)
            {
                // volte ao ínicio do buffer
                vertexBufferPosition = 0;
                batchSize = (count < MaxBatchSize) ? count : MaxBatchSize;
            }
            else
            {
                // restrinja a quantidade de sprites pelo espaço sobrando
                batchSize = remainingSpace;
            }
        }

        // trava o vertex buffer para escrita
        D3D11_MAP mapType = (vertexBufferPosition == 0) ? D3D11_MAP_WRITE_DISCARD : D3D11_MAP_WRITE_NO_OVERWRITE;
        D3D11_MAPPED_SUBRESOURCE mappedBuffer;
        graphics->context->Map(vertexBuffer, 0, mapType, 0, &mappedBuffer);

        // se posiciona dentro do vertex buffer
        Vertex * vertices = (Vertex*)mappedBuffer.pData + size_t(vertexBufferPosition) * VerticesPerSprite;

        // gera posições dos vértices de cada sprite que será desenhado nesse lote
        for (uint i = 0; i < batchSize; ++i)
        {        
            // pega tamanho da textura
            XMVECTOR size = XMVectorMergeXY(XMLoadInt(&sprites[i]->width), XMLoadInt(&sprites[i]->height));
            XMVECTOR textureSize = XMConvertVectorUIntToFloat(size, 0);
            XMVECTOR inverseTextureSize = XMVectorReciprocal(textureSize);

            // organiza informações do sprite
            XMFLOAT2 positionxy(sprites[i]->x, sprites[i]->y);
            float scale = sprites[i]->scale;
            XMFLOAT2 center(sprites[i]->width * sprites[i]->texSize.x / 2.0f, sprites[i]->height * sprites[i]->texSize.y / 2.0f);
            float rotation = sprites[i]->rotation;
            float layerDepth = sprites[i]->depth;

            // carrega informações do sprite em registros SIMD
            XMVECTOR source = XMVectorSet(sprites[i]->texCoord.x, sprites[i]->texCoord.y, sprites[i]->texSize.x, sprites[i]->texSize.y);
            XMVECTOR destination = XMVectorPermute<0, 1, 4, 4>(XMLoadFloat2(&positionxy), XMLoadFloat(&scale));
            XMVECTOR color = XMVectorSet(sprites[i]->color.r, sprites[i]->color.g, sprites[i]->color.b, sprites[i]->color.a);
            XMVECTOR originRotationDepth = XMVectorSet(center.x, center.y, rotation, layerDepth);

            // extrai os tamanhos de origem e destino em vetores separados
            XMVECTOR sourceSize = XMVectorSwizzle<2, 3, 2, 3>(source);
            XMVECTOR destinationSize = XMVectorSwizzle<2, 3, 2, 3>(destination);

            // altera a escala do offset de origem pelo tamanho da fonte, tomando cuidado para evitar overflow se a região fonte for zero
            XMVECTOR isZeroMask = XMVectorEqual(sourceSize, XMVectorZero());
            XMVECTOR nonZeroSourceSize = XMVectorSelect(sourceSize, g_XMEpsilon, isZeroMask);

            XMVECTOR origin = XMVectorDivide(originRotationDepth, nonZeroSourceSize);

            // converte a região fonte de texels para o formato de coordenadas de textura mod-1
            origin *= inverseTextureSize;

            // se o tamanho de destino é relativo a região fonte, converte-o para pixels
            destinationSize *= textureSize;

            // calcula uma matriz de rotação 2x2
            XMVECTOR rotationMatrix1;
            XMVECTOR rotationMatrix2;

            if (rotation != 0)
            {
                float sin, cos;

                XMScalarSinCos(&sin, &cos, rotation);

                XMVECTOR sinV = XMLoadFloat(&sin);
                XMVECTOR cosV = XMLoadFloat(&cos);

                rotationMatrix1 = XMVectorMergeXY(cosV, sinV);
                rotationMatrix2 = XMVectorMergeXY(-sinV, cosV);
            }
            else
            {
                rotationMatrix1 = g_XMIdentityR0;
                rotationMatrix2 = g_XMIdentityR1;
            }

            // os quatro vértices do sprite são calculados a partir de transformações dessas posições unitárias
            static XMVECTORF32 cornerOffsets[VerticesPerSprite] =
            {
                { 0, 0 },
                { 1, 0 },
                { 0, 1 },
                { 1, 1 },
            };

            int mirrorBits = 0;

            // gere os quatro vértices 
            for (int i = 0; i < VerticesPerSprite; ++i)
            {
                // calcula posição
                XMVECTOR cornerOffset = (cornerOffsets[i] - origin) * destinationSize;

                // aplica matriz de rotação 2x2
                XMVECTOR position1 = XMVectorMultiplyAdd(XMVectorSplatX(cornerOffset), rotationMatrix1, destination);
                XMVECTOR position2 = XMVectorMultiplyAdd(XMVectorSplatY(cornerOffset), rotationMatrix2, position1);

                // insere componente z = depth
                XMVECTOR position = XMVectorPermute<0, 1, 7, 6>(position2, originRotationDepth);

                // Escreve posição como um Float4, mesmo sendo VertexPositionColor::position um XMFLOAT3.
                // Isso é mais rápido e inofensivo porque estamos apenas invalidando o primeiro elemento
                // do campo cor, que será imediatamente sobrescrito com seu valor correto.
                XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&vertices[i].pos), position);

                // insere a cor
                XMStoreFloat4(&vertices[i].color, color);

                // computa e escreve as coordenadas da textura
                XMVECTOR textureCoordinate = XMVectorMultiplyAdd(cornerOffsets[i ^ mirrorBits], sourceSize, source);

                XMStoreFloat2(&vertices[i].tex, textureCoordinate);
            }

            vertices += VerticesPerSprite;
        }

        // destrava o vertex buffer
        graphics->context->Unmap(vertexBuffer, 0);

        // desenha sprites 
        uint startIndex = (uint)vertexBufferPosition * IndicesPerSprite;
        uint indexCount = (uint)batchSize * IndicesPerSprite;
        graphics->context->DrawIndexed(indexCount, startIndex, 0);

        // avança a posição no vertex buffer
        vertexBufferPosition += batchSize;

        // avança a posição no vetor de sprites
        sprites += batchSize;

        // foram desenhados batchSize sprites nessa passagem
        count -= batchSize;
    }
}

// ---------------------------------------------------------------------------------

void Renderer::Render()
{
    // ordena sprites por profundidade:
    // necessário para o correto funcionamento 
    // da mistura (blending) entre as texturas dos sprites
    sort(spriteVector.begin(), spriteVector.end(), 
        [](SpriteData * a, SpriteData * b) -> bool 
        { return a->depth > b->depth; }    );

    // quantidades de sprites a serem renderizados
    uint spriteVectorSize = uint(spriteVector.size());

    if (spriteVectorSize == 0)
        return;

    ID3D11ShaderResourceView* batchTexture = nullptr;
    uint batchStart = 0;

    // junta sprites adjacentes que compartilham a mesma textura
    for (uint pos = 0; pos < spriteVectorSize; ++pos)
    {
        ID3D11ShaderResourceView * texture = spriteVector[pos]->texture;

        if (texture != batchTexture)
        {
            if (pos > batchStart)
            {
                RenderBatch(batchTexture, &spriteVector[batchStart], pos - batchStart);
            }

            batchTexture = texture;
            batchStart = pos;
        }
    }

    // desenha o grupo final de sprites
    RenderBatch(batchTexture, &spriteVector[batchStart], spriteVectorSize - batchStart);

    // limpa a lista de desenho (atualizada a cada frame)
    spriteVector.clear();
    storageIndex = 0;
}

// ---------------------------------------------------------------------------------

void Renderer::Draw(SpriteData & sprite)
{
    if (storageIndex < MaxBatchSize)
{
        storage[storageIndex] = sprite;
        spriteVector.push_back(&storage[storageIndex]);
        ++storageIndex;
    }
}

// ---------------------------------------------------------------------------------