#pragma once

#include <box2d.h>

class GameContactListener: public b2ContactListener //hereda de b2contactlistener
{
public:

    //le paso contact, la colision o contacto de dos cuerpos
    void BeginContact(b2Contact* contact) override; //reemplazo con implementacion propia de BegiContact para mi juego pero Box2D ejecuta la funcion
};