#include "Bullet.h"
#include "Config.h"

//Initiates the bullet.
bool Bullet::init()
{
	return true;
}
//Handler for moving the bullet.
void Bullet::Move(cocos2d::Vec2 moveDistance, float dt)
{
	Forward(moveDistance);
}
//Moves bullet according to the given parameter.
void Bullet::Forward(cocos2d::Vec2 moveDistance)
{
	setPosition(getPosition() + moveDistance);
}
//Method for reseting the bullet events.
void Bullet::Reset()
{
	bulletSprite->setPosition(cocos2d::Vec2(1, 1));
	bulletSprite->stopAllActions();

	const float screenWidth = cocos2d::Director::getInstance()->getWinSize().width;
	const float movementDuration = 1.f;
	auto* bulletMovementSequence = cocos2d::Sequence::create(cocos2d::MoveBy::create(movementDuration, cocos2d::Vec2(0, screenWidth)),
		nullptr);

	bulletSprite->runAction(bulletMovementSequence);
}
//Returns the attack power of bullet.
int Bullet::GetAttackPower()
{
	return attackPower;
}
//Sets the attack power of bullet.
void Bullet::SetAttackPower(int attackPower)
{
	this->attackPower = attackPower;
}
//Returns the type of bullet.
int Bullet::GetType()
{
	return type;
}
//Return the bullet's sprite.
cocos2d::Sprite* Bullet::GetBulletSprite()
{
	return bulletSprite;
}
