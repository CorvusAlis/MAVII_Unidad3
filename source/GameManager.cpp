#include "GameManager.h"
#include "Constantes.h"

GameManager::GameManager()
{
    background = LoadTexture("assets/fondo_cm.png");

    world = new b2World(
        b2Vec2(0.0f, 9.8f)  //gravedad del mundo
    );
   
    CreateGround();

    motor = new Motor(*world);

    garraBase = new GarraBase(*world, *motor);

    CreateCajas();
}

void GameManager::Update()
{
    motor->Update();

    garraBase->Update();

    world->Step(1.0f / 60.0f,8, 3);
}

void GameManager::Draw()
{
    BeginDrawing();

    ClearBackground(BLACK);

    //fondo
    Rectangle source = {
        0,
        0,
        (float)background.width,
        (float)background.height
    };

    Rectangle dest = {
        0,
        0,
        1000,
        600
    };

    DrawTexturePro(
        background,
        source,
        dest,
        { 0,0 },
        0.0f,
        WHITE
    );

    //dibujo cajas
    for (auto caja : cajas)
    {
        caja->Draw();
    }

    motor->Draw();

    garraBase->Draw();

    EndDrawing();
}

GameManager::~GameManager()
{
    for (auto caja : cajas)
    {
        delete caja;
    }

    delete garraBase;
    delete motor;

    delete world;

    UnloadTexture(background);
}

void GameManager::CreateCajas()
{
    cajas.push_back(
        new Caja(
            *world,
            350, 450,
            40, 40,
            RED,
            0.0f
        )
    );

    cajas.push_back(
        new Caja(
            *world,
            450, 450,
            40, 40,
            BLUE,
            0.0f
        )
    );

    cajas.push_back(
        new Caja(
            *world,
            550, 450,
            40, 40,
            GREEN,
            0.0f
        )
    );

    cajas.push_back(
        new Caja(
            *world,
            280, 450,
            40, 40,
            ORANGE,
            -10.0f
        )
    );

    cajas.push_back(
        new Caja(
            *world,
            340, 470,
            50, 50,
            PURPLE,
            15.0f
        )
    );

    cajas.push_back(
        new Caja(
            *world,
            410, 455,
            35, 35,
            GOLD,
            -20.0f
        )
    );

    cajas.push_back(
        new Caja(
            *world,
            480, 490,
            60, 40,
            PINK,
            8.0f
        )
    );

    cajas.push_back(
        new Caja(
            *world,
            560, 460,
            45, 45,
            SKYBLUE,
            -5.0f
        )
    );

    cajas.push_back(
        new Caja(
            *world,
            630, 500,
            40, 60,
            LIME,
            25.0f
        )
    );

    cajas.push_back(
        new Caja(
            *world,
            700, 450,
            55, 35,
            MAROON,
            -12.0f
        )
    );

    cajas.push_back(
        new Caja(
            *world,
            770, 480,
            40, 40,
            DARKBLUE,
            18.0f
        )
    );
}

void GameManager::CreateGround() {
    //Suelo estático - marca el espacio con el que los elementos interactuan != del suelo visual
    b2BodyDef groundDef;
    groundDef.type = b2_staticBody;
    groundDef.position.Set(
        (SCREENWIDTH / 2.0f) / SCALE,
        (SCREENHEIGHT - 70.0f) / SCALE
    );

    b2PolygonShape groundShape;
    groundShape.SetAsBox(
        (SCREENWIDTH / 2.0f) / SCALE,
        20.0f / SCALE
    );

    groundBody= world->CreateBody(&groundDef);

    groundBody->CreateFixture(&groundShape, 0.0f);
}