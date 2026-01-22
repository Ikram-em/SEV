// EnemyProjectile.cpp
#include "EnemyProjectile.h"

EnemyProjectile::EnemyProjectile(float x, float y, Game* game)
    : Actor("res/disparo_jugador.png", x, y, 12, 12, game) {
    vx = -5; // velocidad hacia la izquierda
}

void EnemyProjectile::update() {
    x += vx; // movimiento horizontal
}
