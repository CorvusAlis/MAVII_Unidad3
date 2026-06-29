#pragma once

#include "raylib.h"
#include <box2d.h>
#include <vector>

#include "Motor.h"
#include "GarraBase.h"
#include "Caja.h"
#include "Esfera.h"
#include "ZonaEntrega.h"
#include "GameContactListener.h"

using namespace std;

class GameManager
{
private:

    Texture2D background;

    b2World* world;
    b2Body* groundBody;
    GameContactListener contactListener;

    Motor* motor;
    GarraBase* garraBase;
    ZonaEntrega* zonaEntrega;

    vector<Caja*> cajas;
    vector<Esfera*> esferas;

    int scoreTotal;
    float tiempoRestante;

    bool gameOver;

public:

    GameManager();
    ~GameManager();

    void Update();
    void Draw();

    void DibujarFondo();
    void DibujarUI();
    void DibujarUIGameOver();

    void CheckDeliveries();

    void CreateBoundaries();
    void CreatePremios();

    void ResetGame();
};