#include "PlayerBullet.h"
#include "Config.h"

namespace
{
	constexpr const char* LASER_SPRITE_PATH = "laser.png";

	constexpr int BULLET_Z_ORDER = 1;

	constexpr float BULLET_PHYSICS_BODY_RATIO = .5f;
	constexpr float BULLET_MOVEMENT_DURATION = 1.f;
}

//Initiates the player bullet node. Creates the components and adds them to main node.
bool PlayerBullet::init()
{

	bulletSprite = cocos2d::Sprite::create(LASER_SPRITE_PATH);
	createBulletPhysicsBody();

	createBulletMovementAction();
	attackPower = PLAYER_NORMAL_ATTACK;
	setTag(PLAYER_BULLET_TAG);
	addChild(bulletSprite, BULLET_Z_ORDER, PLAYER_BULLET_TAG);
	return true;
}

//For setting the action for moving the player bullet when player triggered the fire event.
void PlayerBullet::SetMoveAction()
{
	bulletSprite->stopAllActions();
	createBulletMovementAction();
}

//Creates the PhysicsBody component for bullet.
void PlayerBullet::createBulletPhysicsBody()
{
	const float physicsBodySize = bulletSprite->getContentSize().width * BULLET_PHYSICS_BODY_RATIO;

	auto physicsBody = cocos2d::PhysicsBody::createCircle(physicsBodySize);
	physicsBody->setDynamic(true);
	physicsBody->setCategoryBitmask((int)PhysicsCategory::Bullet);
	physicsBody->setCollisionBitmask((int)PhysicsCategory::None);
	physicsBody->setContactTestBitmask((int)PhysicsCategory::Enemy);
	bulletSprite->setPhysicsBody(physicsBody);
}

//Creates the movement action for bullet.
void PlayerBullet::createBulletMovementAction()
{
	const float bulletMoveDistance = cocos2d::Director::getInstance()->getWinSize().width;
	auto* bulletMoveAction = cocos2d::MoveBy::create(BULLET_MOVEMENT_DURATION, cocos2d::Vec2(0, bulletMoveDistance));
	auto* bulletMoveSequence = cocos2d::Sequence::create(bulletMoveAction,
		nullptr);
	bulletSprite->runAction(bulletMoveSequence);
}