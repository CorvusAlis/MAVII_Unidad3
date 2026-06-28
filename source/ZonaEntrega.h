#pragma once

#include "raylib.h"
#include "Caja.h"

class ZonaEntrega
{
private:

    Rectangle area;

    b2Body* body; //ahora tiene un cuerpo que va a ser el sensor

public:

    ZonaEntrega(b2World& world, float x, float y, float width, float height);
    ~ZonaEntrega();

    //ya no uso metodo Contiene, uso isSensor
    //bool Contiene(b2Body* body);    //para  que reciba cualquier tipo de cuerpo, no solo cajas

    void Draw();

    b2Body* GetBody() const;
};