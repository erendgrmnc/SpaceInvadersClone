#pragma once
#include "Enemy.h"
//Class definition for RedEnemy class. Derived from enemy class. Weakest enemy in the game
class RedEnemy: public Enemy
{
public:
	bool init();
	void Reset();
	CREATE_FUNC(RedEnemy);
};