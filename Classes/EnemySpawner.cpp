#include "EnemySpawner.h"
#include "BlueEnemy.h"
#include "RedEnemy.h"

int EnemySpawner::enemyRowCount = 0;
bool EnemySpawner::isEnemyErasing = false;
bool EnemySpawner::_inited = false;
cocos2d::Node* EnemySpawner::_enemyLayer = nullptr;
cocos2d::Vector<Enemy*> EnemySpawner::enemiesInScene;
cocos2d::Vector<Enemy*> EnemySpawner::showCaseEnemies;
cocos2d::Vector<RedEnemy*> EnemySpawner::redEnemies;
cocos2d::Vector<BlueEnemy*> EnemySpawner::blueEnemies;


//Reset function of Enemy Spawner class.
void EnemySpawner::Reset()
{
	_inited = false;
	_enemyLayer = nullptr;
	enemiesInScene.clear();
}
//Init function of Enemy Spawner class.
bool EnemySpawner::init(cocos2d::Node* enemyLayer)
{
	_enemyLayer = enemyLayer;
	_inited = true;
	return true;
}

//Returns an enemy of given type. Calls CreateOrGet function to create new enemy object or get from related pool.
Enemy* EnemySpawner::SpawnEnemy(int type)
{
	CC_ASSERT(_enemyLayer);
	Enemy* enemy = CreateOrGet(type);
	if (enemy)
	{
		enemy->getEnemySprite()->setVisible(true);
		enemiesInScene.pushBack(enemy);
		_enemyLayer->addChild(enemy);
		return enemy;

	}
	return nullptr;
}
//Spawns 'enemyCount' enemies and add them in one row. Returns the created row.
cocos2d::Vector<Enemy*>* EnemySpawner::GetEnemyRow(int enemyCount)
{
	cocos2d::Vector<Enemy*>* enemyRow = new cocos2d::Vector<Enemy*>();
	int lastPosition = 0;
	for (int i = 0; i < enemyCount; i++)
	{
		CC_ASSERT(_enemyLayer);
		Enemy* enemy = nullptr;
		bool isSpawnable = (rand() % 2) == 1;
		if (isSpawnable)
		{
			enemy = EnemySpawner::SpawnEnemy(rand() % 2);

			if (enemyRow->size() == 0)
			{
				lastPosition += enemy->getEnemySprite()->getContentSize().width;
			}

			if (lastPosition <= cocos2d::Director::getInstance()->getVisibleSize().width)
			{
				enemy->setPosition(cocos2d::Vec2(lastPosition, cocos2d::Director::getInstance()->getWinSize().height));
				lastPosition += enemy->getEnemySprite()->getContentSize().width;
			}
			enemyRow->pushBack(enemy);
		}
		else
		{
			if (enemyRow->size() != 0)
			{
				lastPosition += enemiesInScene.at(enemiesInScene.size() - 1)->getEnemySprite()->getContentSize().width + 1;
			}
		}
	}
	return enemyRow;
}
//Creates a new enemy or gets from related object pool of type give in parameter. Then returns it.
Enemy* EnemySpawner::CreateOrGet(int type)
{
	Enemy* enemy = nullptr;
	switch (type)
	{
	case EnemyTypes::_RedEnemy:
		if (!redEnemies.empty())
		{
			enemy = redEnemies.back();
			redEnemies.popBack();
		}
		else
		{
			enemy = RedEnemy::create();
			enemy->retain();
		}
		break;
	case EnemyTypes::_BlueEnemy:
		if (!blueEnemies.empty())
		{
			enemy = blueEnemies.back();
			blueEnemies.popBack();
		}
		else
		{
			enemy = BlueEnemy::create();

		}
		break;
	}
	enemy->retain();
	return enemy;
}
//Erases the enemy in index from the enemies(In Scene) vector.
void EnemySpawner::Erase(int enemyIndex)
{
	auto enemy = enemiesInScene.at(enemyIndex);
	int type = enemy->GetType();
	switch (type)
	{
	case EnemyTypes::_RedEnemy:
		redEnemies.pushBack(static_cast<RedEnemy*>(enemy));
		break;
	case EnemyTypes::_BlueEnemy:
		blueEnemies.pushBack(static_cast<BlueEnemy*>(enemy));
		break;
	}
	isEnemyErasing = true;
	enemiesInScene.erase(enemyIndex);
	isEnemyErasing = false;
	enemy->removeFromParentAndCleanup(false);
	enemy->getEnemySprite()->setPosition(cocos2d::Director::getInstance()->getWinSize().width, cocos2d::Director::getInstance()->getWinSize().height);
	enemy->Reset();
}
//Returns the enemy object referance from enemies vector.
Enemy* EnemySpawner::GetEnemy(cocos2d::Node* enemy)
{
	Enemy* enemyToReturn = nullptr;
	if (enemy)
	{
		for (int i = 0; i < enemiesInScene.size(); i++)
		{
			enemyToReturn = enemiesInScene.at(i);
			if (enemyToReturn == enemy)
			{
				break;
			}
		}
	}
	return enemyToReturn;
}
//Get Current Created Enemy Row Count.
int EnemySpawner::GetEnemyRowCount()
{
	return enemyRowCount;
}
//Set Current Created Enemy Row Count.
void EnemySpawner::SetEnemyRowCount(int value)
{
	enemyRowCount += value;
}
//Returns the index of from enemiesInScene vector by given parameter object.  
int EnemySpawner::GetEnemyIndex(Enemy* enemy)
{
	int indexToReturn = -1;
	for (int enemyIter = 0; enemyIter < enemiesInScene.size(); enemyIter++)
	{
		if (enemiesInScene.at(enemyIter) == enemy)
		{
			indexToReturn = enemyIter;
		}
	}
	return indexToReturn;
}
//Erases the given object referance from enemiesInScene vector.
void EnemySpawner::Erase(Enemy* enemy)
{
	int type = enemy->GetType();
	switch (type)
	{
	case EnemyTypes::_RedEnemy:
		redEnemies.pushBack(static_cast<RedEnemy*>(enemy));
		break;
	case EnemyTypes::_BlueEnemy:
		blueEnemies.pushBack(static_cast<BlueEnemy*>(enemy));
		break;
	}
	isEnemyErasing = true;
	enemiesInScene.eraseObject(enemy, true);
	isEnemyErasing = false;
	enemy->removeFromParentAndCleanup(false);
	_enemyLayer->removeChild(enemy);
	enemy->Reset();
}
//Returns the status variable of currently is enemy is being erased from enemiesInScene vector. 
bool EnemySpawner::GetIsEnemyErasing()
{
	return isEnemyErasing;
}
