#include "Player.h"

Player::Player(float x, float y, Game* game)
    : Actor("res/jugador.png", x, y, 50, 57, game) {
    audioShoot = new Audio("res/efecto_disparo.wav", false);
    vidas = 3; // inicializamos vidas
    // Inicializamos velocidad a 0
    vx = 0;
    vy = 0;
}

void Player::recibirImpacto() {
    if (vidas > 0) vidas--;
}

void Player::update() {
    if (shootTime > 0) {
        shootTime--;
    }

    x = x + vx;
    y = y + vy;
}

void Player::moveX(float axis) {
    vx = axis * moveSpeed; // usa moveSpeed según la nave
}

void Player::moveY(float axis) {
    vy = axis * moveSpeed; // usa moveSpeed según la nave
}

void Player::setShipType(int type) {
    shipType = type;

    if (type == 1) {
        texture = game->getTexture("res/jugador.png");
        fileWidth = 50; fileHeight = 57;
        width = 50; height = 57;
        moveSpeed = 3.0f;
        shootCadence = 30;
    }
    else if (type == 2) {
        texture = game->getTexture("res/nave.png");
        fileWidth = 48; fileHeight = 52;
        width = 48; height = 52;
        moveSpeed = 5.0f;
        shootCadence = 15;
    }
}

Projectile* Player::shoot() {
    if (shootTime == 0) {
        audioShoot->play();
        shootTime = shootCadence;
        return new Projectile(x, y, game);
    }
    else {
        return NULL;
    }
}
