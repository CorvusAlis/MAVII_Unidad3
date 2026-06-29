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

    //TODO: sacar esto de aca. Crear una clase menos generica (premios o algo asi) solo para las esferas y cajas (y cualquier otro premio)
    //incluso podria crear una clase que englobe garra, moto, zonaentrega y cosas que no tengan puntaje, no se borren, etc
    //por ahora queda para cumplir con la interfaz de la clase GameObject generica
    int GetPuntos() const override;
};