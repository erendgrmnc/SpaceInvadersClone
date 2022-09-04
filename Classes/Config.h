#pragma once
enum class PhysicsCategory 
{
	None = 0,
	Enemy = (1 << 0),
	Bullet = (1 << 1),
	All = Enemy | Bullet
};

enum BulletDamageTypes 
{
	NormalAttack,
	SuperAttack
};

#define PLAYER_NORMAL_ATTACK 25
#define PLAYER_SUPER_ATTACK 100

#define PLAYER_TAG 01
#define ENEMY_TAG 02
#define PLAYER_BULLET_TAG 04
#define ENEMY_BULLET_TAG 5

#define BLUE_ENEMY_SCORE 60
#define RED_ENEMY_SCORE 25

#define RED_ENEMY_HP 50
#define BLUE_ENEMY_HP 100

#define SUPER_TIME 3