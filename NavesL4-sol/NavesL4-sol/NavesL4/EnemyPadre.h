
#pragma once
#include "Actor.h"
#include "Animation.h"
#include "EnemyProjectile.h"

class EnemyPadre : public Actor {
public:
    EnemyPadre(string filename, float x, float y, int width, int height, Game* game);

    virtual void update() = 0;
    virtual void draw() override = 0;

    Animation* animation = nullptr;
    int shootCounter = 0; 
    virtual EnemyProjectile* shoot();
};
