#include "./cocos/base/CCRef.h"
#include "cocos/base/CCDirector.h"
#include "cocos/2d/CCTransition.h"
#include "SceneManager.h"
#include "GameScene.h"
#include "GameOverScene.h"
#include "MainMenu.h"
//Replaces the current scene with game scene.
void SceneManager::GoToGameScene(cocos2d::Ref* sender)
{
	GameScene::ResetGameScene();
	cocos2d::Director::getInstance()->replaceScene(GameScene::createScene());
}
//Replaces the current scene with game over scene.
void SceneManager::GoToGameOverScene(cocos2d::Ref* sender, int score)
{
	auto gameOverScene = GameOverScene::createScene(score);
	cocos2d::Director::getInstance()->replaceScene(gameOverScene);
}
////Replaces the current scene with main menu scene.
void SceneManager::GoToMainMenuScene(cocos2d::Ref* sender)
{
	auto mainMenuScene = MainMenu::createScene();
	cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(1, mainMenuScene));
}
