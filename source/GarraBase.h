#pragma once

#include <box2d.h>
#include "raylib.h"

#include "Motor.h"
#include "Brazo.h"

class GarraBase
{
private:

    Motor& motor;   //ref al motor ya creado

    BrazoGarra* brazoIzq;    //brazos de la garra
    BrazoGarra* brazoDer;

    b2Body* clawBody;

    Texture2D clawTexture;

    float cableLength;

public:

    GarraBase(b2World& world,Motor& motor);
    ~GarraBase();

    void Update();
    void Draw();

};