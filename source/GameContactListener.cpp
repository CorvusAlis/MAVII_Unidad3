#include "GameContactListener.h"

#include "GameObject.h"
#include "GameObjectType.h"

void GameContactListener::BeginContact(b2Contact* contact)
{
    //recupero los fixture y body de los dos objetos que hacen contacto
    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();

    b2Body* bodyA = fixtureA->GetBody();
    b2Body* bodyB = fixtureB->GetBody();

    //obtengo puntero al objeto real que contacta con userData
    GameObject* objA = reinterpret_cast<GameObject*>(bodyA->GetUserData().pointer);
    GameObject* objB = reinterpret_cast<GameObject*>(bodyB->GetUserData().pointer);

    if (!objA || !objB)
    {
        return;
    }

    //obtengo el tipo de objeto (caja/esfera/zona)
    GameObjectType typeA = objA->GetType();
    GameObjectType typeB = objB->GetType();

    //devuelvo siempre el objeto entero (caja o esfera) para recuperar tipo, puntos, o lo que necesite del objeto
    //uso GameObject directamente y recupero el tipo de objeto
    if (typeA == GameObjectType::ZonaEntrega &&
        typeB != GameObjectType::ZonaEntrega)
    {
        premioEntregado = objB;
        return;
    }

    if (typeB == GameObjectType::ZonaEntrega &&
        typeA != GameObjectType::ZonaEntrega)
    {
        premioEntregado = objA;
        return;
    }
}