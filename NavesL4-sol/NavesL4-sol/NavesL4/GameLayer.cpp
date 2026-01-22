#pragma once
#include "GameLayer.h"
#include "EnemyPadre.h"
#include "EnemyProjectile.h"
#include "Player.h"
#include "EnemyA.h"
#include "EnemyB.h"


GameLayer::GameLayer(Game* game)
    : Layer(game) {
    init();
}

void GameLayer::init() {
    audioBackground = new Audio("res/musica_ambiente.mp3", true);
    audioBackground->play();

    points = 0;
    textPoints = new Text("0", WIDTH * 0.92, HEIGHT * 0.04, game);

    // --- Jugadores ---
    player1 = new Player(50, 70, game);
    textVida = new Text(std::to_string(player1->vidas), 50, 20, game);

    player2 = new Player(50, 200, game); // posición inicial jugador 2
    textVida2 = new Text(std::to_string(player2->vidas), 700, 20, game);

    background = new Background("res/fondo.png", WIDTH * 0.5, HEIGHT * 0.5, -1, game);
    backgroundPoints = new Actor("res/icono_puntos.png", WIDTH * 0.85, HEIGHT * 0.05, 24, 24, game);

    enemies.clear();
    projectiles.clear();

    enemies.push_back(new EnemyA(300, 50, game));
    enemies.push_back(new EnemyB(300, 200, game));

    // Inicializar controles jugador 2
    controlMoveX2 = 0;
    controlMoveY2 = 0;
    controlShoot2 = false;
}

void GameLayer::processControls() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        keysToControls(event);
    }

    // --- Movimiento y disparo Jugador 1 ---
    player1->moveX(controlMoveX);
    player1->moveY(controlMoveY);
    if (controlShoot) {
        Projectile* p1 = player1->shoot();
        if (p1) projectiles.push_back(p1);
    }

    // --- Movimiento y disparo Jugador 2 ---
    player2->moveX(controlMoveX2);
    player2->moveY(controlMoveY2);
    if (controlShoot2) {
        Projectile* p2 = player2->shoot();
        if (p2) projectiles.push_back(p2);
    }
}

void GameLayer::update() {
    background->update();
    player1->update();
    player2->update();

    // --- Actualizar enemigos ---
    for (auto const& enemy : enemies) {
        enemy->update();
        enemy->shootCounter++;
        if (enemy->shootCounter % 100 == 0) {
            EnemyProjectile* p = enemy->shoot();
            if (p) enemyProjectiles.push_back(p);
        }
    }

    // --- Actualizar proyectiles ---
    for (auto it = projectiles.begin(); it != projectiles.end();) {
        Projectile* p = *it;
        p->update();
        if (!p->isInRender()) {
            delete p;
            it = projectiles.erase(it);
        }
        else ++it;
    }

    // --- Colisiones enemigos - proyectiles ---
    for (auto itEnemy = enemies.begin(); itEnemy != enemies.end();) {
        EnemyPadre* enemy = *itEnemy;
        bool enemyHit = false;
        for (auto itProj = projectiles.begin(); itProj != projectiles.end();) {
            Projectile* proj = *itProj;
            if (enemy->isOverlap(proj)) {
                enemyHit = true;
                delete proj;
                itProj = projectiles.erase(itProj);
                points++;
                if (textPoints) textPoints->content = std::to_string(points);
            }
            else ++itProj;
        }
        if (enemyHit) {
            delete enemy;
            itEnemy = enemies.erase(itEnemy);
        }
        else ++itEnemy;
    }

    // --- Colisiones enemigos - jugadores ---
    for (auto it = enemyProjectiles.begin(); it != enemyProjectiles.end();) {
        EnemyProjectile* eProj = *it;
        eProj->update();

        bool hit = false;
        if (player1->isOverlap(eProj)) {
            player1->recibirImpacto();
            if (textVida) textVida->content = std::to_string(player1->vidas);
            hit = true;
        }
        else if (player2->isOverlap(eProj)) {
            player2->recibirImpacto();
            if (textVida2) textVida2->content = std::to_string(player2->vidas);
            hit = true;
        }

        if (hit || !eProj->isInRender()) {
            delete eProj;
            it = enemyProjectiles.erase(it);
        }
        else ++it;
    }

    // --- Generar nuevos enemigos ---
    newEnemyTime--;
    if (newEnemyTime <= 0) {
        int rX = rand() % WIDTH;   // posición X aleatoria
        int rY = rand() % HEIGHT;  // posición Y aleatoria

        EnemyPadre* newEnemy = nullptr;

        if (rand() % 2 == 0) {
            newEnemy = new EnemyA(rX, rY, game);
        }
        else {
            newEnemy = new EnemyB(rX, rY, game);
        }

        if (newEnemy) {
            enemies.push_back(newEnemy);
        }

        newEnemyTime = 135; 
    }

}

void GameLayer::draw() {
    background->draw();

    for (auto const& projectile : projectiles) projectile->draw();

    player1->draw();
    player2->draw();

    for (auto const& enemy : enemies) enemy->draw();
    for (auto const& eProj : enemyProjectiles) eProj->draw();

    backgroundPoints->draw();
    textPoints->draw();
    if (textVida) textVida->draw();
    if (textVida2) textVida2->draw();

    SDL_RenderPresent(game->renderer);
}

void GameLayer::keysToControls(SDL_Event event) {
    int code = event.key.keysym.sym;

    if (event.type == SDL_KEYDOWN) {
        switch (code) {
            // --- Jugador 1 ---
        case SDLK_1: player1->setShipType(1); break;
        case SDLK_2: player1->setShipType(2); break;
        case SDLK_w: controlMoveY = -1; break;
        case SDLK_s: controlMoveY = 1; break;
        case SDLK_a: controlMoveX = -1; break;
        case SDLK_d: controlMoveX = 1; break;
        case SDLK_SPACE: controlShoot = true; break;

            // --- Jugador 2 ---
        case SDLK_UP: controlMoveY2 = -1; break;
        case SDLK_DOWN: controlMoveY2 = 1; break;
        case SDLK_LEFT: controlMoveX2 = -1; break;
        case SDLK_RIGHT: controlMoveX2 = 1; break;
        case SDLK_RETURN: controlShoot2 = true; break;

        case SDLK_ESCAPE: game->loopActive = false; break;
        }
    }

    if (event.type == SDL_KEYUP) {
        switch (code) {
            // --- Jugador 1 ---
        case SDLK_w: if (controlMoveY == -1) controlMoveY = 0; break;
        case SDLK_s: if (controlMoveY == 1) controlMoveY = 0; break;
        case SDLK_a: if (controlMoveX == -1) controlMoveX = 0; break;
        case SDLK_d: if (controlMoveX == 1) controlMoveX = 0; break;
        case SDLK_SPACE: controlShoot = false; break;

            // --- Jugador 2 ---
        case SDLK_UP: if (controlMoveY2 == -1) controlMoveY2 = 0; break;
        case SDLK_DOWN: if (controlMoveY2 == 1) controlMoveY2 = 0; break;
        case SDLK_LEFT: if (controlMoveX2 == -1) controlMoveX2 = 0; break;
        case SDLK_RIGHT: if (controlMoveX2 == 1) controlMoveX2 = 0; break;
        case SDLK_RETURN: controlShoot2 = false; break;
        }
    }
}
