#pragma once

#include "EnemyPadre.h"

class EnemyB : public EnemyPadre {
public:
    EnemyB(float x, float y, Game* game);

    void update() override; 
    void draw() override;   

private:

    float angle=0;     
   
};
