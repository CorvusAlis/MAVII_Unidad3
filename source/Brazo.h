#pragma once

#include <box2d.h>
#include "raylib.h"

class BrazoGarra
{
private:

    b2Body* brazoBody;
    b2RevoluteJoint* revoluteJoint; //garraBase-brazo
    Texture2D brazoTexture;

    float anguloMinimo; //pasar de radianes a grados
    float anguloMaximo;
    float velocidadMotor;
    float torqueMotor;  //"fuerza" de cierre de la garra

    bool izquierdo;

public:

    BrazoGarra(b2World& world, b2Body* garraBaseBody, bool ladoIzquierdo);

    ~BrazoGarra();

    void Update(bool cerrarGarra);
    void Draw();
};