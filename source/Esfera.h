#pragma once

#include "raylib.h"
#include <box2d.h>
#include "GameObject.h"

class Esfera : public GameObject
{
private:

    b2Body* body;

    float radius;

    Color color;

    int puntos;

public:

    Esfera(b2World& world,float x, float y, float radius, Color color, int puntos);
    ~Esfera();

    void Draw();

    b2Body* GetBody() const;
    int GetPuntos() const;
    GameObjectType GetType() const override;
};