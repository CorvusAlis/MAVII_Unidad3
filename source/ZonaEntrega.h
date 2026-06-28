#pragma once

#include "raylib.h"
#include <box2d.h>
#include "GameObject.h"
#include "GameObjectType.h"

class ZonaEntrega : public GameObject
{
private:

    Rectangle area;

    b2Body* body; //ahora tiene un cuerpo que va a ser el sensor

public:

    ZonaEntrega(b2World& world, float x, float y, float width, float height);
    ~ZonaEntrega() override;

    //ya no uso metodo Contiene, uso isSensor - ya no incluyo Caja por que no me fijo que "tiene" la zona
    //bool Contiene(b2Body* body);    //para  que reciba cualquier tipo de cuerpo, no solo cajas

    void Draw();

    b2Body* GetBody() const override;
    GameObjectType GetType() const override;
};