#pragma once
//clase generica de objeto del juego - es clase padre para el resto de los objetos
//no tiene implementacion (.cpp) con los = 0 indico que la implementacion de la funcion esta en la clase hijo
//pide devolver el body y el tipo del objeto

#pragma once

#include <box2d.h>
#include "GameObjectType.h"

class GameObject
{
public:

    virtual ~GameObject() = default;

    virtual b2Body* GetBody() const = 0;

    virtual GameObjectType GetType() const = 0;
};