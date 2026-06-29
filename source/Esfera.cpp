#include "Esfera.h"
#include "Constantes.h"

using namespace std;

Esfera::Esfera(b2World& world, const string& rutaTextura, float x, float y, float radius, Color color, int puntos)
    : radius(radius),
    color(color),
    puntos(puntos)
{
    esferaTexture = LoadTexture(rutaTextura.c_str());

    b2BodyDef def;

    def.type = b2_dynamicBody;
    def.position.Set(
        x / SCALE,
        y / SCALE
    );

    body = world.CreateBody(&def);

    b2CircleShape shape;
    shape.m_radius = radius / SCALE;    //aca uso radio por que es una esfera, a diferencia de la caja que usa alto y ancho

    b2FixtureDef fixture;

    fixture.shape = &shape;
    fixture.density = 0.4f;
    fixture.friction = 0.2f;
    fixture.restitution = 0.2f;

    body->CreateFixture(&fixture);

    //MUY IMPORTANTE es lo que al final sirve para detectar que los objetos hacen contacto, devuelve el objeto que se reconoce en GameContactListener
    body->GetUserData().pointer = reinterpret_cast<uintptr_t>(this);
}

Esfera::~Esfera()
{
    if (body)
    {
        body->GetWorld()->DestroyBody(body);
        body = nullptr;
    }
}

void Esfera::Draw()
{
    b2Vec2 pos = body->GetPosition();

    DrawCircleV(
        {
            pos.x * SCALE,
            pos.y * SCALE
        },
        radius,
        color
    );

    //para debug
    if (DEBUG_MODE)
    {
        DrawCircleLines(
            (int)(pos.x * SCALE),
            (int)(pos.y * SCALE),
            radius,
            BLACK
        );

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

b2Body* Esfera::GetBody() const
{
    return body;
}

int Esfera::GetPuntos() const
{
    return puntos;
}

GameObjectType Esfera::GetType() const
{
    return GameObjectType::Esfera;
}