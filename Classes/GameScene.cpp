/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "GameScene.h"
#include "ui/CocosGUI.h"
#include "GameOverScene.h"
#include "UIManager.h"
#include "Enemy.h"
#include "BulletController.h"
#include "Player.h"
#include "EnemySpawner.h"
#include "BackgroundManager.h"
#include "DataManager.h"
#include "SceneManager.h"
#include "cocos/physics/CCPhysicsContact.h"

cocos2d::Scene* GameScene::gameScene = nullptr;

//Update function for game scene. Called in every frame. Controls the events like parallaxing efect, enemy spawning, score text changing exc.
void GameScene::update(float dt) {
	if (!isGameOvered)
	{
		cocos2d::Point backgroundScrollVert = cocos2d::Vec2(0, -1000);
		bgManager->GetBgNode()->setPosition(bgManager->GetBgNode()->getPosition() + (backgroundScrollVert * dt));
		if (bgManager->GetBgNode()->getPosition().y < -20 * cocos2d::Director::getInstance()->getWinSize().height)
		{
			bgManager->GetBgNode()->setPosition(cocos2d::Vec2(cocos2d::Director::getInstance()->getWinSize().width, 20 * cocos2d::Director::getInstance()->getWinSize().height));
		}

		Player::GetInstance()->update(dt);

		int enemyCount = EnemySpawner::enemiesInScene.size();

		if (enemyRowTimer >= 8 && !EnemySpawner::GetIsEnemyErasing())
		{
			enemyRowTimer = 0;

			EnemySpawner::GetEnemyRow(6);

		}

		std::string scoreText = std::to_string(score);
		UIManager::getInstance()->SetScoreLabelText(scoreText);

		for (int enemyIndex = 0; enemyIndex < EnemySpawner::enemiesInScene.size(); enemyIndex++)
		{
			auto enemy = EnemySpawner::enemiesInScene.at(enemyIndex);
			switch (enemy->GetType())
			{
			default:
				enemy->Move(cocos2d::Vec2(0,-0.5), dt);
				break;
			}

			if (enemy->getEnemySprite() && enemy->getPosition().y <= enemy->getEnemySprite()->getContentSize().height / 2)
			{
				GameOver();
				
			}
		}

		if (!BulletController::isSuperAttack && Player::GetInstance()->GetKillCount() != 0 && Player::GetInstance()->GetKillCount() % 5 == 0)
		{
			Player::GetInstance()->InitiateSuperAttack();
		}

		for (int bulletIndex = 0; bulletIndex < BulletController::bulletsInScene.size(); bulletIndex++)
		{
			if (BulletController::bulletsInScene.at(bulletIndex)->GetBulletSprite()->getPosition().y > cocos2d::Director::getInstance()->getVisibleSize().height || BulletController::bulletsInScene.at(bulletIndex)->GetBulletSprite()->getPosition().y < 0)
			{
				BulletController::Erase(BulletController::bulletsInScene.at(bulletIndex));
			}
		}

		enemyRowTimer += dt;


	}

}
//Called when two physicbody collided. This method handles the collison of objects.
bool GameScene::onContactBegin(cocos2d::PhysicsContact& contact)
{
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();

	int bulletDamage = 0;
	Enemy* enemy = nullptr;
	Bullet* bullet = nullptr;
	bool isEnemyDied = false;

	switch (nodeB->getTag())
	{
	case ENEMY_TAG:
		enemy = EnemySpawner::GetEnemy(nodeB);
		switch (nodeA->getTag())
		{
		case PLAYER_BULLET_TAG:
			bullet = BulletController::GetBullet(nodeA);

			if (bullet && enemy)
			{
				bulletDamage = bullet->GetAttackPower();
				BulletController::Erase(bullet);
				isEnemyDied = enemy->TakeDamage(bulletDamage);

				if (isEnemyDied)
				{
					EnemySpawner::Erase(enemy);
					Player::GetInstance()->IncreaseKillCount();
					this->score += enemy->GetScore();
				}
			}
			break;
		case PLAYER_TAG:
			GameOver();
		default:
			break;
		}
		break;
	case PLAYER_BULLET_TAG:
		bullet = BulletController::GetBullet(nodeB);

		switch (nodeA->getTag())
		{
		case ENEMY_TAG:
			enemy = EnemySpawner::GetEnemy(nodeA);
			if (bullet && enemy)
			{
				bulletDamage = bullet->GetAttackPower();
				isEnemyDied = enemy->TakeDamage(bullet->GetAttackPower());
				cocos2d::log("Enemy hit !");
				BulletController::Erase(bullet);
				if (isEnemyDied)
				{
					EnemySpawner::Erase(enemy);
					Player::GetInstance()->IncreaseKillCount();
					this->score += enemy->GetScore();
				}
			}
		default:
			break;
		}
	case PLAYER_TAG:
		switch (nodeB->getTag())
		{
		case ENEMY_TAG:
			GameOver();
		default:
			break;
		}
	default:
		break;
	}

	return true;
}

//Initiates the game over sequence.
void GameScene::GameOver()
{

	isGameOvered = true;
	
	EnemySpawner::Reset();
	BulletController::reset();
	//SHOW GAME OVER SCENE
	DataManager::WriteHighScore(score);
	SceneManager::GoToGameOverScene(this, this->score);

}
//For getting the instance of gamescene. Creates it if it's not initialized.
cocos2d::Scene* GameScene::createScene()
{
	if (gameScene != NULL)
	{
		return gameScene;
	}
	gameScene = GameScene::create();
	gameScene->initWithPhysics();
	gameScene->getPhysicsWorld()->setGravity(cocos2d::Vec2(0, 0));
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	return gameScene;
}
//Method for reseting the gameScene instance.
void GameScene::ResetGameScene()
{
	if (gameScene != NULL)
	{
		gameScene = nullptr;
	}
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	this->isGameOvered = false;
	this->score = 0;
	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();


	bgManager = BackgroundManager::create();
	addChild(bgManager, -1);

	//To Do: Audio Engine is not working because of MSVCR110.dll error. Installing package of the c++ redustrable 2012 not solved the problem. 
	//auto audioEngine = AudioEngine::create();
	//AudioEngine::play2d("lumbee_heights.mp3");

	UIManager::getInstance()->init(this);
	EnemySpawner::init(this);
	BulletController::init(this);
	
	Player::ResetPlayerInstance();
	
	this->addChild(Player::GetInstance());

	auto contactListener = cocos2d::EventListenerPhysicsContact::create();

	contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	EnemySpawner::GetEnemyRow(6);
	this->scheduleUpdate();

	return true;
}






