#include "Enemy.h"
//Initiates the enemy.
bool Enemy::init()
{
	return true;
}

// returns the enemy health.
int Enemy::GetHealth()
{
	return health;
}
//For handling damage enemy event.
bool Enemy::TakeDamage(int damage)
{
	bool isEnemyDied = false;
	health -= damage;
	if (health <= 0)
	{
		isEnemyDied = true;
	}
	return isEnemyDied;
}
//For handling enemy Move event.
void Enemy::Move(cocos2d::Vec2 moveDistance, float dt)
{
	Forward(moveDistance);
}
//Moves the enemy according to parameter Vector.
void Enemy::Forward(cocos2d::Vec2 moveDistance)
{
	setPosition(getPosition() + moveDistance);
}
//Returns the enemy type.
EnemyTypes Enemy::GetType()
{
	return type;
}
//Returns the sprite component of enemy.
cocos2d::Sprite* Enemy::getEnemySprite()
{
	return enemySprite;
}
//Reset method for reseting the enemy instance.
void Enemy::Reset()
{
	health = 0;
	enemySprite->stopAllActions();
}
//Return the score to be added after destroying enemy instance.
int Enemy::GetScore()
{
	return this->score;
}
