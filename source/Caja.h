#pragma once
#include "raylib.h"
#include <box2d.h>
#include <string>
#include <vector>
#include "GameObject.h"

//para usar la constante definida en main
extern const float SCALE;

using namespace std;
class Caja : public GameObject
{
private:
    b2Body* body;
    float width;
    float height;
    Color color;

    int puntos;

public:
    Caja(b2World& world, float x, float y, float w, float h, Color c, float angleDeg, int puntos);
    ~Caja();

    void Draw();

    b2Body* GetBody() const;
    int GetPuntos() const;
    GameObjectType GetType() const override;
};