#pragma once

#include "EnemyPadre.h"

class EnemyA : public EnemyPadre {
public:
    EnemyA(float x, float y, Game* game);

    void update() override; 
    void draw() override;  
};
