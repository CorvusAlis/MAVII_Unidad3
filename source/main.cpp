#ifndef NDEBUG
#include <vld.h>
#endif

#include "raylib.h"
#include "Constantes.h"
#include <box2d.h>
#include <vector>

#include "Motor.h"

using namespace std;


int main(void)
{
    const int screenWidth = 1000;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Juego de Garra!");
    SetTargetFPS(60);

    //bg
    Color fondo = { 110, 100, 215, 255 };
    Color textoPrincipal = RAYWHITE;
    Color textoSecundario = DARKPURPLE;
    Color sueloColor = Fade(DARKGREEN, 0.7f);

    // Mundo físico - todo se crea DIVIDIENDO el tamaño por scale
    b2Vec2 gravity(0.0f, 9.8f);
    b2World world(gravity);

    // -----------------------------
    // Suelo estático - marca el espacio con el que los elementos interactuan != del suelo visual
    // -----------------------------
    b2BodyDef groundDef;
    groundDef.type = b2_staticBody;
    groundDef.position.Set(
        (screenWidth / 2.0f) / SCALE,
        (screenHeight - 40.0f) / SCALE
    );

    b2PolygonShape groundShape;
    groundShape.SetAsBox(
        (screenWidth / 2.0f) / SCALE,
        20.0f / SCALE
    );

    b2Body* groundBody = world.CreateBody(&groundDef);

    groundBody->CreateFixture(&groundShape, 0.0f);

    Motor motor(world);

    /*
    b2Body = objeto lógico (como una entidad)
    b2Shape = la geometría de esa parte
    b2Fixture = “parte física tangible”
    */

    while (!WindowShouldClose())
    {

        //UPDATE - input+logica
        motor.Update();

        //SIMULACION - fisica
        // Avanzar simulación - sincronizado con el juego a 60fps (definido mas arriba)
        world.Step(1.0f / 60.0f, 8, 3);


        //DRAW - render
        BeginDrawing();
        ClearBackground(fondo);

        // Suelo visual - rectangulo que no tiene fisicas, es solo una imagen
        DrawRectangle(0, screenHeight - 60, screenWidth, 40, sueloColor);
        motor.Draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}