// EnemyProjectile.h
#pragma once
#include "Actor.h"
#include "Game.h"


class EnemyProjectile : public Actor {
public:
    EnemyProjectile(float x, float y, Game* game);

    void update() override;
};
