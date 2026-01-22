#include "EnemyPadre.h"

EnemyPadre::EnemyPadre(string filename, float x, float y, int width, int height, Game* game)
    : Actor(filename, x, y, width, height, game) {
    vx = -1;
    shootCounter = 0;
}

EnemyProjectile* EnemyPadre::shoot() {
    return new EnemyProjectile(x - width / 2, y, game);
}

// Este es el update que debes añadir
void EnemyPadre::update() {
    // Movemos al enemigo horizontalmente
    x += vx;
    shootCounter++;
}