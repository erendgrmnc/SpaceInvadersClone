#pragma once

namespace cocos2d 
{
	class Ref;
};

//Scene Manager Class Definiton. Manages the transitions between scenes.

class SceneManager
{
public:
	static void GoToGameScene(cocos2d::Ref* sender);
	static void GoToMainMenuScene(cocos2d::Ref* sender);
	static void GoToGameOverScene(cocos2d::Ref* sender, int score);
};