#include "Brazo.h"
#include "Constantes.h"

BrazoGarra::BrazoGarra(b2World& world, b2Body* garraBaseBody, bool ladoIzquierdo)
{
    izquierdo = ladoIzquierdo;
    brazoTexture = LoadTexture("assets/brazo_cm.png");

    velocidadMotor = 2.0f;
    torqueMotor = 40.0f;

    if (izquierdo)
    {
        anguloMinimo = -50 * DEG2RAD;   //pasaje a grados
        anguloMaximo = 15 * DEG2RAD;
    }
    else
    {
        anguloMinimo = -15 * DEG2RAD;
        anguloMaximo = 50 * DEG2RAD;
    }

    b2Vec2 basePos = garraBaseBody->GetPosition();

    float offsetX;

    if (izquierdo) {
        offsetX = -0.7f;
    }
    else {
        offsetX = 0.7f;
    }

    //body
    b2BodyDef brazoDef;

    brazoDef.type = b2_dynamicBody;   //DINAMICO
    brazoDef.position.Set(basePos.x + offsetX, basePos.y + 0.2f);

    brazoBody = world.CreateBody(&brazoDef);

    b2PolygonShape brazoShape;
    brazoShape.SetAsBox(0.15f,0.7f);


    b2FixtureDef brazoFixture;
    brazoFixture.shape = &brazoShape;
    brazoFixture.density = 1.0f;
    brazoFixture.friction = 0.7f;   //para que pueda "agarrar" cosas
    brazoFixture.restitution = 0.1f;

    //fixture
    brazoBody->CreateFixture(&brazoFixture);

    //revouteJoint
    b2RevoluteJointDef jointDef;

    //anchor - punto de bisagra
    b2Vec2 anchor;
    anchor.Set(basePos.x + offsetX, basePos.y);

    //iinit joint entre garraBase y brazo
    jointDef.Initialize(garraBaseBody,brazoBody,anchor);
    jointDef.enableLimit = true;
    jointDef.lowerAngle = anguloMinimo;
    jointDef.upperAngle = anguloMaximo;

    //motor
    jointDef.enableMotor = true;
    jointDef.motorSpeed = 0.0f;
    jointDef.maxMotorTorque = torqueMotor;

    //creacion de joint
    revoluteJoint = (b2RevoluteJoint*) world.CreateJoint(&jointDef);
}

BrazoGarra::~BrazoGarra()
{
    UnloadTexture(brazoTexture);
}

