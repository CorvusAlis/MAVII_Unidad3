#pragma once

#include "raylib.h"
#include <box2d.h>
#include <vector>

#include "Motor.h"
#include "GarraBase.h"
#include "Caja.h"

class GameManager
{
private:

    Texture2D background;

    b2World* world;

    b2Body* groundBody;

    Motor* motor;
    GarraBase* garraBase;

    std::vector<Caja*> cajas;

public:

    GameManager();
    ~GameManager();

    void Update();
    void Draw();

private:

    void CreateGround();
    void CreateCajas();
};