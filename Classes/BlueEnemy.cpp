#include "BlueEnemy.h"

namespace {
	constexpr const char* BLUE_ENEMY_SPRITE_PATH = "blueenemy.png";
}

//Initiates the blue enemy object.
bool BlueEnemy::init()
{
	enemySprite = cocos2d::Sprite::create(BLUE_ENEMY_SPRITE_PATH);
	enemySprite->setFlippedY(true);

	auto physicsBody = cocos2d::PhysicsBody::createBox(cocos2d::Size(enemySprite->getContentSize().width, enemySprite->getContentSize().height), cocos2d::PhysicsMaterial(0.1f, 1.0f, 0.0f));
	physicsBody->setDynamic(true);
	physicsBody->setCategoryBitmask((int)PhysicsCategory::Enemy);
	physicsBody->setCollisionBitmask((int)PhysicsCategory::None);
	physicsBody->setContactTestBitmask((int)PhysicsCategory::Bullet);

	setPhysicsBody(physicsBody);

	health = BLUE_ENEMY_HP;
	score = BLUE_ENEMY_SCORE;

	type = EnemyTypes::_BlueEnemy;
	setTag(ENEMY_TAG);
	addChild(enemySprite, 2);
	return true;
}

void BlueEnemy::Reset()
{
	health = BLUE_ENEMY_HP;
}

