#pragma once
#include "cocos2d.h"

class Enemy;
class RedEnemy;
class BlueEnemy;

//EnemySpawner Class. For Managing the enemy instances on the scene and enemy object pools.
class EnemySpawner
{
public:
	static bool init(cocos2d::Node* enemyLayer);
	static void Reset();
	static Enemy* SpawnEnemy(int type);
	static cocos2d::Vector<Enemy*>* GetEnemyRow(int enemyCount);
	static Enemy* CreateOrGet(int type);
	static cocos2d::Vector<Enemy*> enemiesInScene;
	static void Erase(int enemyIndex);
	static cocos2d::Vector<Enemy*> showCaseEnemies;
	static Enemy* GetEnemy(cocos2d::Node* enemy);
	static int GetEnemyRowCount();
	static void SetEnemyRowCount(int value);
	static int GetEnemyIndex(Enemy* enemy);
	static void Erase(Enemy* enemy);
	static bool GetIsEnemyErasing();

	//enemy vectors
	static cocos2d::Vector<RedEnemy*> redEnemies;
	static cocos2d::Vector<BlueEnemy*> blueEnemies;

protected:
	static bool _inited;
	static cocos2d::Node* _enemyLayer;
private:
	static bool isEnemyErasing;
	static int enemyRowCount;

};