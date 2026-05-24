#pragma once

#include <box2d.h>
#include "raylib.h"

#include "Motor.h"

class GarraBase
{
private:

    Motor& motor;   //ref al motor ya creado

    b2Body* clawBody;

    Texture2D clawTexture;

    float cableLength;

public:

    GarraBase(b2World& world,Motor& motor);
    ~GarraBase();

    void Update();
    void Draw();

};