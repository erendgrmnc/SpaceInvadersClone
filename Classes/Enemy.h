#pragma once
#include "cocos2d.h"
#include "Config.h"

//Enumeration for enemy types.
enum  EnemyTypes
{
	_RedEnemy,
	_BlueEnemy
};
//Class definiton for Enemy. Parent class for all enemy instances. Manages common enemy properties and methods.
class Enemy: public cocos2d::Node
{
public:
	virtual bool init();
	virtual bool TakeDamage(int damage);
	virtual int GetHealth();
	int GetScore();
	EnemyTypes GetType();
	cocos2d::Sprite* getEnemySprite();
	virtual void Move(cocos2d::Vec2 moveDistance, float dt);
	virtual void Forward(cocos2d::Vec2 moveDistance);
	virtual void Reset();
protected:
	int health;
	int score;
	EnemyTypes type;
	cocos2d::Sprite* enemySprite;
private:
};