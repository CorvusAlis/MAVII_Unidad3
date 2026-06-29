#pragma once

#include "raylib.h"
#include <box2d.h>
#include <string>
#include <vector>
#include "GameObject.h"

using namespace std;

class Esfera : public GameObject
{
private:

    b2Body* body;
    float radius;
    Color color;
    Texture2D esferaTexture;

    int puntos;

public:

    Esfera(b2World& world, const string& rutaTextura, float x, float y, float radius, Color color, int puntos);
    ~Esfera();

    void Draw();

    b2Body* GetBody() const;
    int GetPuntos() const override;
    GameObjectType GetType() const override;
};