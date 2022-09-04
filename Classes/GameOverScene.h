#pragma once
#include "cocos/2d/CCScene.h"
#include "cocos/platform/CCPlatformMacros.h"

namespace cocos2d
{
	class MenuItemImage;
	class MenuItemLabel;
	class Menu;
}

//Class definition for GameOverScene. Manages the game over scene.
class GameOverScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene(int score);
	bool init(int score);
	bool init();
	CREATE_FUNC(GameOverScene, int);
private:

	cocos2d::MenuItemImage* scoreLabel;
	cocos2d::MenuItemImage* retryButton;
	cocos2d::MenuItemImage* returnMainMenuButton;
	cocos2d::MenuItemLabel* menuLabel;
	cocos2d::Menu* menu;

	void createRetryButton();
	void createReturnMainMenuButton();
	void createBackground();
	void createScoreTextLabel(int score);
	void createMenu();
};
