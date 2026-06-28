#include "GameContactListener.h"

void GameContactListener::BeginContact(
    b2Contact* contact)
{
    b2Fixture* fixtureA =
        contact->GetFixtureA();

    b2Fixture* fixtureB =
        contact->GetFixtureB();

    b2Body* bodyA =
        fixtureA->GetBody();

    b2Body* bodyB =
        fixtureB->GetBody();
}