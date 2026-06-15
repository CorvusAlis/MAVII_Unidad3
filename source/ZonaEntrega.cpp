#include "ZonaEntrega.h"
#include "Caja.h"

ZonaEntrega::ZonaEntrega(
    float x,
    float y,
    float width,
    float height)
{
    area = { x, y, width, height };
}

bool ZonaEntrega::Contiene(b2Body* body)
{
    b2Vec2 pos = body->GetPosition();

    //veo cuando el centro de la caja colisione con el area de la zona
    Vector2 punto =
    {
        pos.x * SCALE,
        pos.y * SCALE
    };

    return CheckCollisionPointRec(
        punto,
        area
    );
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