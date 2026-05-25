#include "Brazo.h"
#include "Constantes.h"

BrazoGarra::BrazoGarra(b2World& world, b2Body* garraBaseBody, bool ladoIzquierdo)
{
    izquierdo = ladoIzquierdo;
    brazoTexture = LoadTexture("assets/brazo_cm.png");

    velocidadMotor = 2.0f;
    torqueMotor = 100.0f;

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
        offsetX = -1.0f;
    }
    else {
        offsetX = 1.0f;
    }

    //body
    b2BodyDef brazoDef;

    brazoDef.type = b2_dynamicBody;   //DINAMICO
    brazoDef.position.Set(basePos.x + offsetX, basePos.y + 1.60f);

    brazoBody = world.CreateBody(&brazoDef);

    b2PolygonShape brazoShape;
    brazoShape.SetAsBox(0.06f,0.45f);


    b2FixtureDef brazoFixture;
    brazoFixture.shape = &brazoShape;
    brazoFixture.density = 1.0f;
    brazoFixture.friction = 2.0f;   //para que pueda "agarrar" cosas
    brazoFixture.restitution = 0.0f;

    //fixture
    brazoBody->CreateFixture(&brazoFixture);

    //revouteJoint
    b2RevoluteJointDef jointDef;

    //anchor - punto de bisagra
    b2Vec2 anchor;
    anchor.Set(basePos.x + offsetX, basePos.y + 0.65f);

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

void BrazoGarra::Update(bool cerrarGarra)
{
    float speed = velocidadMotor;

    //invierte el lado al que cierra el brazo
    if (!cerrarGarra)
    {
        speed *= -1.0f;
    }

    if (izquierdo)
    {
        speed *= -1.0f;
    }

    revoluteJoint->SetMotorSpeed(speed);
}

void BrazoGarra::Draw()
{
    //pos body brazo
    b2Vec2 pos = brazoBody->GetPosition();
    float x = pos.x * SCALE;
    float y = pos.y * SCALE;
    float angle = brazoBody->GetAngle() * RAD2DEG;

    Rectangle source = {0,0, (float)brazoTexture.width, (float)brazoTexture.height};
    Rectangle dest = {x, y, (float)brazoTexture.width, (float)brazoTexture.height};

    Vector2 origin = {brazoTexture.width / 2.0f, 24.0f}; //para que el brazo rote desde la punta superior

    //flip orizontal para brazo derecho si quiero usar otro tipo de brazo
    if (!izquierdo)
    {
        source.width *= -1.0f;
    }

    DrawTexturePro(
        brazoTexture,
        source,
        dest,
        origin,
        angle,
        WHITE
    );

    //debug
    if (DEBUG_MODE) {
        DrawCircleV(
            { x, y },
            4.0f,
            RED
        );

        b2Vec2 anchor = revoluteJoint->GetAnchorA();

        DrawCircleV(
            {
                anchor.x * SCALE,
                anchor.y * SCALE
            },
            5.0f,
            BLUE
        );
    }

}