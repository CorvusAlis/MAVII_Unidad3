#pragma once

#include <box2d.h>
#include "raylib.h"

class Motor
{
private:

    Texture2D railTexture;
    Texture2D motorTexture;

    b2Body* railBody;   //estatico
    b2Body* motorBody;  //dinamico

    b2PrismaticJoint* prismaticJoint;   //joint entre el rail fijo y el motor que se mueve horizontal sobre el

public:

    Motor(b2World& world);
    ~Motor();

    void Update();
    void Draw();

    b2Body* GetBody() const;

};