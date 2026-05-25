#ifndef NDEBUG
#include <vld.h>
#endif

#include "raylib.h"
#include "Constantes.h"
#include <box2d.h>
#include <vector>

#include "Motor.h"
#include "GarraBase.h"
#include "Caja.h"

using namespace std;


int main(void)
{
    const int screenWidth = 1000;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Juego de Garra!");
    SetTargetFPS(60);

    Texture2D background = LoadTexture("assets/fondo_cm.png");

    //Mundo físico - todo se crea DIVIDIENDO el tamaño por scale
    b2Vec2 gravity(0.0f, 9.8f);
    b2World world(gravity);

    //Suelo estático - marca el espacio con el que los elementos interactuan != del suelo visual
    b2BodyDef groundDef;
    groundDef.type = b2_staticBody;
    groundDef.position.Set(
        (screenWidth / 2.0f) / SCALE,
        (screenHeight - 70.0f) / SCALE
    );

    b2PolygonShape groundShape;
    groundShape.SetAsBox(
        (screenWidth / 2.0f) / SCALE,
        20.0f / SCALE
    );

    b2Body* groundBody = world.CreateBody(&groundDef);

    groundBody->CreateFixture(&groundShape, 0.0f);

    Motor motor(world);
    GarraBase garraBase(world, motor);

    vector<Caja*> cajas;

    #pragma region cajas
        cajas.push_back(
            new Caja(
                world,
                350, 450,
                40, 40,
                RED,
                0.0f
            )
        );

        cajas.push_back(
            new Caja(
                world,
                450, 450,
                40, 40,
                BLUE,
                0.0f
            )
        );

        cajas.push_back(
            new Caja(
                world,
                550, 450,
                40, 40,
                GREEN,
                0.0f
            )
        );

        cajas.push_back(
            new Caja(
                world,
                280, 450,
                40, 40,
                ORANGE,
                -10.0f
            )
        );

        cajas.push_back(
            new Caja(
                world,
                340, 470,
                50, 50,
                PURPLE,
                15.0f
            )
        );

        cajas.push_back(
            new Caja(
                world,
                410, 455,
                35, 35,
                GOLD,
                -20.0f
            )
        );

        cajas.push_back(
            new Caja(
                world,
                480, 490,
                60, 40,
                PINK,
                8.0f
            )
        );

        cajas.push_back(
            new Caja(
                world,
                560, 460,
                45, 45,
                SKYBLUE,
                -5.0f
            )
        );

        cajas.push_back(
            new Caja(
                world,
                630, 500,
                40, 60,
                LIME,
                25.0f
            )
        );

        cajas.push_back(
            new Caja(
                world,
                700, 450,
                55, 35,
                MAROON,
                -12.0f
            )
        );

        cajas.push_back(
            new Caja(
                world,
                770, 480,
                40, 40,
                DARKBLUE,
                18.0f
            )
        );
#pragma endregion

    while (!WindowShouldClose())
    {

        //UPDATE - input+logica
        motor.Update();
        garraBase.Update(); //se hacen los updates de los brazos

        //SIMULACION - fisica
        // Avanzar simulación - sincronizado con el juego a 60fps (definido mas arriba)
        world.Step(1.0f / 60.0f, 8, 3);


        //DRAW - render
        BeginDrawing();
        ClearBackground(BLACK);
        #pragma region background
        Rectangle source = {
            0,
            0,
            (float)background.width,
            (float)background.height
        };

        Rectangle dest = {
            0,
            0,
            (float)screenWidth,
            (float)screenHeight
        };

        DrawTexturePro(
            background,
            source,
            dest,
            { 0,0 },
            0.0f,
            WHITE
        );
#pragma endregion

        for (auto caja : cajas)
        {
            caja->Draw();
        }

        motor.Draw();
        garraBase.Draw();   //se hacen los draw de los brazos

        EndDrawing();
    }

    UnloadTexture(background);
    for (auto caja : cajas)
    {
        delete caja;
    }
    CloseWindow();

    return 0;
}