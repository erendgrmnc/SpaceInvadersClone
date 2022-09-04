#pragma once
#include "Enemy.h"
//Class definiton for BlueEnemy. Derived from the enemy class. Strongest enemy in the game.
class BlueEnemy: public Enemy
{
public:
	bool init();
	void Reset();
	CREATE_FUNC(BlueEnemy);
};