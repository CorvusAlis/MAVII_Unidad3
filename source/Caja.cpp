#include "Caja.h"
#include "Constantes.h"
#include "GameObjectType.h"

using namespace std;

//constructor
Caja::Caja(b2World& world, const string& rutaTextura, float x, float y, float w, float h, Color c, float angleDeg, int puntos)
    : width(w), height(h), color(c), puntos(puntos)
{
    cajaTexture = LoadTexture(rutaTextura.c_str());

    b2BodyDef def;
    def.type = b2_dynamicBody;
    def.position.Set(x / SCALE, y / SCALE);

    def.angle = angleDeg * DEG2RAD; //pasar angulos a radianes (usado por Box2D)

    b2PolygonShape shape;
    shape.SetAsBox((w / 2.0f) / SCALE, (h / 2.0f) / SCALE);

    body = world.CreateBody(&def);

    b2FixtureDef fixture;
    fixture.shape = &shape;
    fixture.density = 0.5f; //menos peso
    fixture.friction = 1.2f;    //mas friccion
    fixture.restitution = 0.0f;

    body->CreateFixture(&fixture);

    //agrego un tag/etiqueta al body del objeto
    body->GetUserData().pointer =reinterpret_cast<uintptr_t>(this);
}

Caja::~Caja()
{
    if (body)
    {
        body->GetWorld()->DestroyBody(body);
        body = nullptr;
    }
}

void Caja::Draw()
{
    b2Vec2 pos = body->GetPosition();
    float angle = body->GetAngle() * RAD2DEG;

    Rectangle rect = {  //ahora esta bien con el centro del rectangulo
        pos.x * SCALE,
        pos.y * SCALE,
        width,
        height
    };

    Vector2 origin = { width / 2.0f, height / 2.0f };

    DrawRectanglePro(rect, origin, angle, color);

    //debug
    if (DEBUG_MODE)
    {
        b2Fixture* fixture = body->GetFixtureList();

        if (fixture)
        {
            b2PolygonShape* poly =
                (b2PolygonShape*)fixture->GetShape();

            Vector2 points[b2_maxPolygonVertices];

            for (int i = 0; i < poly->m_count; i++)
            {
                b2Vec2 worldPoint =
                    body->GetWorldPoint(poly->m_vertices[i]);

                points[i] = {
                    worldPoint.x * SCALE,
                    worldPoint.y * SCALE
                };
            }

            for (int i = 0; i < poly->m_count; i++)
            {
                int next = (i + 1) % poly->m_count;

                DrawLineEx(
                    points[i],
                    points[next],
                    2.0f,
                    BLACK
                );
            }
        }

        DrawCircleV(
            {
                pos.x * SCALE,
                pos.y * SCALE
            },
            4,
            YELLOW
        );
    }
}

b2Body* Caja::GetBody() const
{
    return body;
}

int Caja::GetPuntos() const
{
    return puntos;
}

GameObjectType Caja::GetType() const
{
    return GameObjectType::Caja;
}