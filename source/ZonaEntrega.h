#pragma once

#include "raylib.h"
#include "Caja.h"

class ZonaEntrega
{
private:

    Rectangle area;

public:

    ZonaEntrega(float x, float y, float width, float height);

    bool Contiene(b2Body* body);    //para  que reciba cualquier tipo de cuerpo, no solo cajas

    void Draw();
};