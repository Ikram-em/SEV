#pragma once

#include "Actor.h"
#include "Projectile.h" 
#include "Audio.h"
#include <string>

class Player : public Actor
{
public:
    Player(float x, float y, Game* game);

    Projectile* shoot();
    void update() override;
    void moveX(float axis);
    void moveY(float axis);

    Audio* audioShoot;
    int shootCadence = 30;
    int shootTime = 0;
    int vidas = 3;  // empieza con 3 vidas
    void recibirImpacto(); // decrementa vida

    void setShipType(int type);

private:
    float moveSpeed = 3.0f; // velocidad de movimiento, cambia según la nave
    int shipType = 1;       // tipo de nave actual
};
