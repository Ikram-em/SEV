#include "EnemyB.h"
#include <cmath>

// Constructor
EnemyB::EnemyB(float x, float y, Game* game)
    : EnemyPadre("res/marciano.png", x, y, 40, 40, game) {

    animation = new Animation("res/marciano.png", width, height,
        120, 42, 4, 3, game);
    vx = -2; 
}

void EnemyB::update() {
    x += -2.0f;    // avanza a la izquierda
    angle += 0.2f; // se usa como temporizador del parpadeo
    shootCounter++;
}

void EnemyB::draw() {
    // se dibuja solo cuando sin(angle) > 0 →esto lo hice para el efecto parpadeo :)
    if (sin(angle) > 0) {
        animation->draw(x, y);
    }
}
