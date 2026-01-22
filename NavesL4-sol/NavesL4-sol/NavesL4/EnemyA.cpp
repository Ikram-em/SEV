#include "EnemyA.h"

// Constructor
EnemyA::EnemyA(float x, float y, Game* game)
    : EnemyPadre("res/enemigo.png", x, y, 36, 40, game) {

    animation = new Animation("res/enemigo_movimiento.png", width, height,
		108, 40, 6, 3, game);
    vx = -1; 
}

void EnemyA::update() {
    x += vx;
    shootCounter++;
}

void EnemyA::draw() {
    animation->draw(x, y);
}
