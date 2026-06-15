#pragma once

#include "raylib.h"
#include <box2d.h>

class Esfera
{
private:

    b2Body* body;

    float radius;

    Color color;

    int puntos;

public:

    Esfera(b2World& world,float x, float y, float radius, Color color, int puntos);
    ~Esfera();

    b2Body* GetBody() const;
    int GetPuntos() const;

    void Draw();
};