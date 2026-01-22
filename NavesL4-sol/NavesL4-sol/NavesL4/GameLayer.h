#pragma once

#include "Layer.h"
#include "Player.h"
#include "Background.h"
#include "EnemyA.h"
#include "EnemyB.h"

#include "Projectile.h"
#include "Text.h"
#include "Audio.h" 
#include <list>

class GameLayer : public Layer
{
public:
	GameLayer(Game* game);
	void init() override;
	void processControls() override;
	void update() override;
	void draw() override;
	void keysToControls(SDL_Event event);

	Audio* audioBackground;
	Text* textPoints;
	Text* textVida;
	int points;
	int newEnemyTime = 0;
	Player* player;
	Player* player1;
	Player* player2; // nuevo jugador
	Text* textVida2; // mostrar vidas del segundo jugador

	Background* background;
	Actor* backgroundPoints;
	list<EnemyPadre*> enemies;
	list<Projectile*> projectiles;
	list<EnemyProjectile*> enemyProjectiles;
	
	bool controlShoot = false;
	int controlMoveY = 0;
	int controlMoveX = 0;
	int controlMoveX2 = 0;
	int controlMoveY2 = 0;
	bool controlShoot2 = false;



};

