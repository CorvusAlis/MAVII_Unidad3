#include "ZonaEntrega.h"
#include "Caja.h"

ZonaEntrega::ZonaEntrega(
    b2World& world,
    float x,
    float y,
    float width,
    float height)
{
    area = { x, y, width, height };

    //creo un cuerpo para la zona de entrega
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;

    bodyDef.position.Set(
        (x + width / 2.0f) / SCALE,
        (y + height / 2.0f) / SCALE
    );

    body = world.CreateBody(&bodyDef);

    b2PolygonShape shape;

    shape.SetAsBox(
        (width / 2.0f) / SCALE,
        (height / 2.0f) / SCALE
    );

    b2FixtureDef fixture;

    fixture.shape = &shape;

    //va a actuar como sensor
    fixture.isSensor = true;

    body->CreateFixture(&fixture);
}

ZonaEntrega::~ZonaEntrega() {

}

void ZonaEntrega::Draw()
{
    DrawRectangleRec(
        area,
        Fade(DARKPURPLE, 0.5f)
    );

    DrawRectangleLinesEx(
        area,
        2,
        DARKPURPLE
    );
}

b2Body* ZonaEntrega::GetBody() const
{
    return body;
}

GameObjectType ZonaEntrega::GetType() const
{
    return GameObjectType::ZonaEntrega;
}