#include "Motor.h"
#include "Constantes.h"

Motor::Motor(b2World& world)
{
    railTexture = LoadTexture("assets/rail_cm.png");
    motorTexture = LoadTexture("assets/motor_cm.png");

    float railX = 500.0f / SCALE;
    float railY = 80.0f / SCALE;

    //rail (STATIC BODY)

    b2BodyDef railDef;
    railDef.type = b2_staticBody;
    railDef.position.Set(railX, railY);

    railBody = world.CreateBody(&railDef);

    b2PolygonShape railShape;

    //el fixture NO necesita coincidir visualmente con el sprite
    railShape.SetAsBox(5.0f, 0.2f);
    railBody->CreateFixture(&railShape, 0.0f);

    //motor (DYNAMIC BODY)

    b2BodyDef motorDef;
    motorDef.type = b2_dynamicBody;

    motorDef.position.Set(
        railX,
        railY
    );

    motorDef.fixedRotation = true;  //para que no rote ni vibre de manera rara

    motorBody = world.CreateBody(&motorDef);

    b2PolygonShape motorShape;

    motorShape.SetAsBox(
       15.0f,
        0.4f
    );

    b2FixtureDef motorFixture;

    motorFixture.shape = &motorShape;
    motorFixture.density = 1.0f;
    motorFixture.friction = 0.3f;

    motorBody->CreateFixture(&motorFixture);

    //definicion del pismatico joint

    b2PrismaticJointDef jointDef;

    jointDef.Initialize(
        railBody,
        motorBody,
        motorBody->GetWorldCenter(),
        b2Vec2(1.0f, 0.0f)
    );

    //limites para el movimiento del motor

    jointDef.enableLimit = true;
    jointDef.lowerTranslation = -14.0f;
    jointDef.upperTranslation = 14.0f;

    jointDef.enableMotor = true;
    jointDef.maxMotorForce = 1000.0f;
    jointDef.motorSpeed = 0.0f;

    //creacion de prismatic joint

    prismaticJoint = (b2PrismaticJoint*)
        world.CreateJoint(&jointDef);
}

Motor::~Motor()
{
    UnloadTexture(railTexture);
    UnloadTexture(motorTexture);
}

void Motor::Update()
{
    if (IsKeyDown(KEY_A))
    {
        prismaticJoint->SetMotorSpeed(-5.0f);
    }
    else if (IsKeyDown(KEY_D))
    {
        prismaticJoint->SetMotorSpeed(5.0f);
    }
    else
    {
        prismaticJoint->SetMotorSpeed(0.0f);
    }
}

void Motor::Draw()
{
    //rail

    b2Vec2 railPos = railBody->GetPosition();

    float railX = railPos.x * SCALE;
    float railY = railPos.y * SCALE;

    //uso todo el sprite desde 0,0 esquina superior izqueirda
    Rectangle railSource = {
        0,
        0,
        (float)railTexture.width,
        (float)railTexture.height
    };

    //tamaño final del renderizado
    Rectangle railDest = {
        railX,
        railY,
        900.0f,
        //(float)railTexture.width,
        (float)railTexture.height
    };

    Vector2 railOrigin = {
        //railTexture.width / 2.0f,
        900.0f / 2,
        railTexture.height / 2.0f
    };

    DrawTexturePro(
        railTexture,
        railSource,
        railDest,
        railOrigin,
        0.0f,
        WHITE
    );

    //motor

    b2Vec2 motorPos = motorBody->GetPosition();

    float motorX = motorPos.x * SCALE;
    float motorY = motorPos.y * SCALE;

    float motorAngle = motorBody->GetAngle() * RAD2DEG;

    Rectangle motorSource = {
        0,
        0,
        (float)motorTexture.width,
        (float)motorTexture.height
    };

    Rectangle motorDest = {
        motorX,
        motorY,
        (float)motorTexture.width,
        (float)motorTexture.height
    };

    Vector2 motorOrigin = {
        motorTexture.width / 2.0f,
        motorTexture.height / 2.0f
    };

    DrawTexturePro(
        motorTexture,
        motorSource,
        motorDest,
        motorOrigin,
        motorAngle,
        WHITE
    );
}

b2Body* Motor::GetBody() const
{
    return motorBody;
}