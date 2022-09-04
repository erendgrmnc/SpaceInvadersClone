#pragma once
#include "cocos/2d/CCScene.h"

namespace cocos2d 
{
	class Sprite;
	class MenuItemImage;
	class MenuItemLabel;
	class Menu;
}

class BackgroundManager;
class SceneManager;

//Main Menu class definition. Derived from Scene class. Manages the Main Menu Scene.
class MainMenu : public cocos2d::Scene
{
public:
	static Scene* createScene();
	bool init();

	CREATE_FUNC(MainMenu);
private:
	cocos2d::Sprite* background = nullptr;
	cocos2d::MenuItemImage* playButton = nullptr;
	cocos2d::MenuItemLabel* highScoreLabel = nullptr;
	cocos2d::MenuItemLabel* menuLabel = nullptr;
	cocos2d::Menu* mainMenu = nullptr;

	void createBackground();
	void createPlayButton();
	void createHighScroeLabel();
	void createMenuLabel();
	void createMenu();

};