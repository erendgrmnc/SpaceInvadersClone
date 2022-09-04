#include "RedEnemy.h"
//Initiates the Red Enemy Node. Creates the componenets of enemy and attaches it to the main node.
bool RedEnemy::init()
{
	this->enemySprite = cocos2d::Sprite::create("redenemy.png");
	this->enemySprite->setFlippedY(true);
	auto physicsBody = cocos2d::PhysicsBody::createBox(cocos2d::Size(enemySprite->getContentSize().width, enemySprite->getContentSize().height), cocos2d::PhysicsMaterial(0.1f, 1.0f, 0.0f));
	physicsBody->setDynamic(true);
	physicsBody->setCategoryBitmask((int)PhysicsCategory::Enemy);
	physicsBody->setCollisionBitmask((int)PhysicsCategory::None);
	physicsBody->setContactTestBitmask((int)PhysicsCategory::Bullet);

	this->setPhysicsBody(physicsBody);

	this->health = RED_ENEMY_HP;
	this->score = RED_ENEMY_SCORE;
	this->type = EnemyTypes::_RedEnemy;
	this->setTag(ENEMY_TAG);
	this->addChild(enemySprite, 2, ENEMY_TAG);
	return true;
}

void RedEnemy::Reset() {
	this->health = RED_ENEMY_HP;
}


