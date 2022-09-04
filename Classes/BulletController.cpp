#include "BulletController.h"
#include "Config.h"

cocos2d::Node* BulletController::_bulletLayer = nullptr;
bool BulletController::inited = false;
bool BulletController::isSuperAttack = false;
cocos2d::Vector<Bullet*> BulletController::bulletsInScene;
cocos2d::Vector<PlayerBullet*> BulletController::playerBullets;

//Resets the fields of Bullet Controller instance.
void BulletController::reset() 
{
	inited = false;
	_bulletLayer = nullptr;
	bulletsInScene.clear();
	playerBullets.clear();
}
//Initiates the Bullet Controller.
bool BulletController::init(cocos2d::Node* bulletLayer)
{
	if (bulletLayer)
	{
		_bulletLayer = bulletLayer;
		inited = true;
		return true;
	}
	return false;
}
//Spawns type of given parameter in given location.
Bullet* BulletController::SpawnBullet(int type, cocos2d::Vec2 pos)
{
	CC_ASSERT(_bulletLayer);
	Bullet* bullet = nullptr;
	switch (type)
	{
	case BulletTypes::_PlayerBullet:
		bullet = CreateOrGetBullet(BulletTypes::_PlayerBullet);
		//If Player is in super attack mode, set bullet attackPower to super attack Value.
		if (isSuperAttack)
		{
			bullet->SetAttackPower(PLAYER_SUPER_ATTACK);
		}
		bullet->retain();
		break;
	case BulletTypes::_EnemyBullet:
		bullet = Bullet::create();
		break;
	}
	if (bullet)
	{
		bulletsInScene.pushBack(bullet);
		_bulletLayer->addChild(bullet, 1, PLAYER_BULLET_TAG);
		bullet->setPosition(pos);
		return bullet;
	}
	return nullptr;
}
//Creates or gets an instance of type from pool according to the parameter.
Bullet* BulletController::CreateOrGetBullet(int type)
{
	Bullet* bullet = nullptr;
	switch (type)
	{
	case BulletTypes::_PlayerBullet:
		if (!playerBullets.empty())
		{
			bullet = playerBullets.back();
			playerBullets.popBack();
			BulletController::SetAttackPowerOfBullet(bullet);

		}
		else
		{
			bullet = PlayerBullet::create();
			bullet->retain();
		}
		//TO DO: After implementing enemy shooting system, case if type EnemyBullet.
	default:
		break;
	}
	return bullet;
}
//Erases the given bullet from bulletsInScene Vector.
void BulletController::Erase(Bullet* bullet)
{
	auto bulletToOperate = GetBullet(bullet);
	int type = bullet->GetType();
	switch (type)
	{
	case BulletTypes::_PlayerBullet:
		playerBullets.pushBack(static_cast<PlayerBullet*>(bullet));
	case BulletTypes::_EnemyBullet:
		//TO DO: After Implementing enemy shooting system, case for returning enemy bullet to enemyBullet pool.
	default:
		break;
	}
	bulletsInScene.erase(BulletController::GetBulletIndex(bullet));
	bullet->removeFromParentAndCleanup(false);
	_bulletLayer->removeChild(bullet);
	bullet->Reset();

}
//Returns the bullet instance given by parameter from bulletsInScene vector. 
Bullet* BulletController::GetBullet(cocos2d::Node* bullet)
{
	Bullet* bulletToReturn = nullptr;
	if (bullet)
	{
		for (int i = 0; i < bulletsInScene.size(); i++)
		{
			bulletToReturn = bulletsInScene.at(i);
			if (bullet == bulletToReturn)
			{
				break;
			}
		}
	}
	return bulletToReturn;
}
//Returns the index of bullet from bulletsInScene vector.
int BulletController::GetBulletIndex(cocos2d::Node* bullet)
{
	int indexToReturn = 0;
	if (bullet)
	{
		for (int i = 0; i < bulletsInScene.size(); i++)
		{
			indexToReturn = i;
			if (bullet == bulletsInScene.at(i))
			{
				break;
			}
		}
	}

	return indexToReturn;
}
//Sets the attack power of given bullet.
void BulletController::SetAttackPowerOfBullet(Bullet* bullet)
{
	switch (bullet->GetType())
	{
	case BulletTypes::_PlayerBullet:
		if (BulletController::isSuperAttack)
		{
			bullet->SetAttackPower(PLAYER_SUPER_ATTACK);
		}
		else
		{
			bullet->SetAttackPower(PLAYER_NORMAL_ATTACK);
		}
	default:
		break;
	}

}
