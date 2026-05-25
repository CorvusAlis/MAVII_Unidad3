#include "GarraBase.h"
#include "Constantes.h"

GarraBase::GarraBase(b2World& world,Motor& motor)
    : motor(motor)
{
    clawTexture = LoadTexture("assets/garra_superior_cm.png");

    cableLength = 120.0f;

    b2Vec2 motorPos = motor.GetBody()->GetPosition();

    //body

    b2BodyDef clawDef;

    clawDef.type = b2_kinematicBody;    //cambiar a dynamic
    clawDef.position.Set(motorPos.x, motorPos.y + (cableLength / SCALE));
    clawDef.fixedRotation = true;

    clawBody = world.CreateBody(&clawDef);

    b2PolygonShape clawShape;

    clawShape.SetAsBox(0.9f,0.45f);

    //fixture base

    b2FixtureDef clawFixture;

    clawFixture.shape = &clawShape;
    clawFixture.density = 1.0f;
    clawFixture.friction = 0.4f;
    clawFixture.restitution = 0.1f;

    clawBody->CreateFixture(&clawFixture);

    //creacion de brazos izq y der

    brazoIzq = new BrazoGarra(
        world,
        clawBody,
        true    //es izquierdo
    );

    brazoDer = new BrazoGarra(
        world,
        clawBody,
        false
    );

}

GarraBase::~GarraBase() {
    UnloadTexture(clawTexture);
}

void GarraBase::Update()
{
    b2Vec2 motorPos = motor.GetBody()->GetPosition();

    b2Vec2 targetPos;

    targetPos.Set(motorPos.x,motorPos.y + (cableLength / SCALE));

    clawBody->SetTransform(targetPos,0.0f);    //actualizar para joints con brazos moviles
}

void GarraBase::Draw()
{
    //pos motor
    b2Vec2 motorPos = motor.GetBody()->GetPosition();
    float motorX = motorPos.x * SCALE;
    float motorY = motorPos.y * SCALE;

    //pos garra
    b2Vec2 clawPos =clawBody->GetPosition();
    float clawX = clawPos.x * SCALE;
    float clawY = clawPos.y * SCALE;

    //angulo garra
    float clawAngle = clawBody->GetAngle() * RAD2DEG;

    //cable
    DrawLineEx(
        {
            motorX,
            motorY + 20
        },
        {
            clawX,
            clawY - 20
        },
        4.0f,
        DARKGRAY
    );

    //garra
    Rectangle source = {
        0,
        0,
        (float)clawTexture.width,
        (float)clawTexture.height
    };

    Rectangle dest = {
        clawX,
        clawY,
        (float)clawTexture.width,
        (float)clawTexture.height
    };

    Vector2 origin = {
        clawTexture.width / 2.0f,
        clawTexture.height / 2.0f
    };

    DrawTexturePro(
        clawTexture,
        source,
        dest,
        origin,
        clawAngle,
        WHITE
    );
    
    if(DEBUG_MODE){
        //centro garra
        DrawCircleV({clawX,clawY},5.0f,RED);

        //anchors
        DrawCircleV({motorX,motorY + 20},4.0f,BLUE);
        DrawCircleV({clawX,clawY - 20},4.0f,GREEN);

        //collider
        DrawRectangleLines(clawX - 27,clawY - 13,54,26,ORANGE);
    }
}