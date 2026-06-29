#include "GameManager.h"
#include "Constantes.h"

GameManager::GameManager()
{
    background = LoadTexture("assets/fondo_cm.png");

    world = new b2World(b2Vec2(0.0f, 9.8f));

    world->SetContactListener(&contactListener);

    CreateBoundaries();

    motor = new Motor(*world);
    garraBase = new GarraBase(*world, *motor);
    CreatePremios();

    zonaEntrega = new ZonaEntrega(
        *world,
        800.0f,   // posx
        400.0f,   // posy
        85.0f,   // ancho
        100.0f    // alto
    );

    scoreTotal = 0;
    tiempoRestante = 60.0f;

    gameOver = false;
}

GameManager::~GameManager()
{
    for (auto caja : cajas)
    {
        delete caja;
    }

    for (auto esfera : esferas)
    {
        delete esfera;
    }

    delete garraBase;
    delete motor;
    delete zonaEntrega;
    delete world;

    UnloadTexture(background);
}

void GameManager::Update()
{
    if (gameOver)
    {
        if (IsKeyPressed(KEY_R))
        {
            ResetGame();
        }

        return;
    }

    tiempoRestante -= GetFrameTime();

    if (tiempoRestante <= 0.0f)
    {
        tiempoRestante = 0.0f;
        gameOver = true;
        return;
    }

    motor->Update();
    garraBase->Update();

    //primero actualizo la fisica, luego veo si algun objeto entro en la zona
    world->Step(1.0f / 60.0f, 8, 3);

    CheckDeliveries(); //retomo el uso de CheckDeliveries pero con la logica del contactListener
}

void GameManager::Draw()
{
    BeginDrawing();

    //fondo
    ClearBackground(BLACK);

    DibujarFondo();

    DibujarUI();

    //dibujo zona entrega
    zonaEntrega->Draw();

    //dibujo premios
    for (auto caja : cajas)
    {
        caja->Draw();
    }

    for (auto esfera : esferas)
    {
        esfera->Draw();
    }

    motor->Draw();
    garraBase->Draw();

    if (gameOver)
    {
        DibujarUIGameOver();
    }

    EndDrawing();
}

void GameManager::CreatePremios()
{
    cajas.push_back(
        new Caja(
            *world,
            "assets/gema1.png",
            350, 450,
            50, 50,
            GREEN,
            0,
            100
        )
    );

    cajas.push_back(
        new Caja(
            *world,
            "assets/gema3.png",
            500, 450,
            40, 40,
            BLUE,
            0,
            250
        )
    );

    cajas.push_back(
        new Caja(
            *world,
            "assets/gema3.png",
            560, 450,
            40, 40,
            BLUE,
            0,
            250
        )
    );

    cajas.push_back(
        new Caja(
            *world,
            "assets/gema2.png",
            650, 450,
            30, 30,
            RED,
            0,
            500
        )
    );

    esferas.push_back(
        new Esfera(
            *world,
            "assets/gema4.png",
            520,
            450,
            15,
            GOLD,
            1000
        )
    );
}

void GameManager::CheckDeliveries()
{
    if (contactListener.premioEntregado == nullptr)
        return;

    GameObject* premio = contactListener.premioEntregado;
    GameObjectType tipo = premio->GetType();

    scoreTotal += premio->GetPuntos();

    //borrado del objeto que entro en la zona de entrega
    //CAJAS
    if (tipo == GameObjectType::Caja)
    {
        for (auto it = cajas.begin(); it != cajas.end(); ++it)
        {
            if (*it == premio)
            {
                world->DestroyBody((*it)->GetBody());
                delete* it;
                cajas.erase(it);

                break;
            }
        }
    }

    //ESFERAS
    else if (tipo == GameObjectType::Esfera)
    {
        for (auto it = esferas.begin(); it != esferas.end(); ++it)
        {
            if (*it == premio)
            {
                world->DestroyBody((*it)->GetBody());
                delete* it;
                esferas.erase(it);

                break;
            }
        }
    }

    //dejo el puntero a null para otro evento
    contactListener.premioEntregado = nullptr;
}

void GameManager::CreateBoundaries() {
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

    //pared izqueirda
    b2BodyDef leftWallDef;
    leftWallDef.type = b2_staticBody;

    leftWallDef.position.Set(
        50.0f / SCALE,
        (SCREENHEIGHT / 2.0f) / SCALE
    );

    b2Body* leftWall =
        world->CreateBody(&leftWallDef);

    b2PolygonShape leftWallShape;

    leftWallShape.SetAsBox(
        WALL_THICKNESS / SCALE,
        (SCREENHEIGHT / 2.0f) / SCALE
    );

    leftWall->CreateFixture(
        &leftWallShape,
        0.0f
    );

    //pared derecha
    b2BodyDef rightWallDef;
    rightWallDef.type = b2_staticBody;

    rightWallDef.position.Set(
        (SCREENWIDTH - 50.0f)/ SCALE,
        (SCREENHEIGHT / 2.0f) / SCALE
    );

    b2Body* rightWall =
        world->CreateBody(&rightWallDef);

    b2PolygonShape rightWallShape;

    rightWallShape.SetAsBox(
        WALL_THICKNESS / SCALE,
        (SCREENHEIGHT / 2.0f) / SCALE
    );

    rightWall->CreateFixture(
        &rightWallShape,
        0.0f
    );
}

//reseteo toda la escena y creo de nuevo
void GameManager::ResetGame()
{
    scoreTotal = 0;

    tiempoRestante = 60.0f;

    gameOver = false; //reseteo bool de gameover NO OLVIDAR

    //borrar cajas
    for (auto caja : cajas)
    {
        delete caja;
    }

    cajas.clear();

    //borrar esferas
    for (auto esfera : esferas)
    {
        delete esfera;
    }

    esferas.clear();

    //recrear premios
    CreatePremios();
}

void GameManager::DibujarFondo() {
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
}

void GameManager::DibujarUI(){
    //timer
    DrawText(
        TextFormat("TIEMPO: %d", (int)tiempoRestante),
        425,
        15,
        30,
        WHITE
    );

    //puntos
    DrawText(
        TextFormat("PUNTOS: %d", scoreTotal),
        50,
        15,
        30,
        WHITE
    );
}

void GameManager::DibujarUIGameOver() {
    DrawRectangle(
        0,
        0,
        SCREENWIDTH,
        SCREENHEIGHT,
        Fade(BLACK, 0.7f)
    );

    DrawText(
        "TIEMPO AGOTADO",
        SCREENWIDTH / 2 - 180,
        SCREENHEIGHT / 2 - 60,
        40,
        RED
    );

    DrawText(
        TextFormat("PUNTAJE FINAL: %d", scoreTotal),
        SCREENWIDTH / 2 - 180,
        SCREENHEIGHT / 2,
        30,
        GOLD
    );

    DrawText(
        "Presione R para reiniciar",
        SCREENWIDTH / 2 - 170,
        SCREENHEIGHT / 2 + 60,
        25,
        WHITE
    );
}