#pragma once

#include <box2d.h>
#include "raylib.h"

#include "Motor.h"
#include "Brazo.h"

class GarraBase
{
private:

    Motor& motor;   //ref al motor ya creado

    BrazoGarra* brazoIzq = nullptr;    //brazos de la garra
    BrazoGarra* brazoDer = nullptr;

    b2Body* clawBody;

    Texture2D clawTexture;

    float cableLength;
    float cableSpeed;   //para bajar y subir el cable attacheado a la garra
    float minCableLength;
    float maxCableLength;

public:

    GarraBase(b2World& world,Motor& motor);
    ~GarraBase();

    void Update();
    void Draw();

};