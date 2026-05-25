#ifndef NDEBUG
#include <vld.h>
#endif

#include "raylib.h"
#include <box2d.h>
#include <vector>

#include "GameManager.h"
#include "Constantes.h"

using namespace std;


int main(void)
{
    InitWindow(SCREENWIDTH, SCREENHEIGHT, "Juego de Garra!");
    SetTargetFPS(60);

    GameManager game;

    while (!WindowShouldClose())
    {
        //UPDATE
        game.Update();

        //DRAW - render
        game.Draw();
    }
    CloseWindow();

    return 0;
}