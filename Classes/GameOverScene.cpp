#include "GameOverScene.h"
#include "cocos2d.h"
#include "./DataManager.h"
#include "SceneManager.h"
#include "BackgroundManager.h"

namespace
{
	constexpr const char* RETRY_BUTTON_IMG_PATH = "retrybutton.png";
	constexpr const char* HOME_BUTTON_IMG_PATH = "homebutton.png";
	
	constexpr int BACKGROUND_Z_ORDER = -1;

	constexpr const char* SCORE_TEXT_BODY = "Score: ";
	constexpr const char* NEW_HIGH_SCORE_TEXT_BODY = "\n New High Score !";

	constexpr float RETRY_BUTTON_X_POS_RATIO = 0.3f;
	constexpr float RETRY_BUTTON_Y_POS_RATIO = 0.5f;

	constexpr float RETURN_TO_MAIN_MENU_BTN_X_POS_RATIO = 0.7f;
	constexpr float RETURN_TO_MAIN_MENU_BTN_Y_POS_RATIO = 0.5f;

	constexpr float SCORE_LABEL_X_POS_RATIO = 0.5f;
	constexpr float SCORE_LABEL_Y_POS_RATIO = 0.8f;

}

//Create Scene function for creating the game over scene.
cocos2d::Scene* GameOverScene::createScene(int score)
{
	auto scene = GameOverScene::create();
	scene->init(score);
	return scene;
}

void GameOverScene::createRetryButton()
{
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

	std::function<void(Ref* sender)> retryButtonCallBack = CC_CALLBACK_0(SceneManager::GoToGameScene, this);

	retryButton = cocos2d::MenuItemImage::create(RETRY_BUTTON_IMG_PATH, RETRY_BUTTON_IMG_PATH, retryButtonCallBack);
	
	const float retryButtonXPosition = visibleSize.width * RETRY_BUTTON_X_POS_RATIO;
	const float retryButtonYPosition = visibleSize.height * RETRY_BUTTON_Y_POS_RATIO;
	retryButton->setPosition(retryButtonXPosition, retryButtonYPosition);
}

void GameOverScene::createReturnMainMenuButton()
{

	std::function<void(Ref* sender)> returnToMainMenuButtonCallback = CC_CALLBACK_0(SceneManager::GoToMainMenuScene, this);
	returnMainMenuButton = cocos2d::MenuItemImage::create(HOME_BUTTON_IMG_PATH, HOME_BUTTON_IMG_PATH, returnToMainMenuButtonCallback);
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	
	const float returnToMainMenuButtonXPosition = visibleSize.width * RETURN_TO_MAIN_MENU_BTN_X_POS_RATIO;
	const float returnToMainMenuButtonYPosition = visibleSize.height * RETURN_TO_MAIN_MENU_BTN_Y_POS_RATIO;
	
	returnMainMenuButton->setPosition(returnToMainMenuButtonXPosition, returnToMainMenuButtonYPosition);
}

void GameOverScene::createBackground()
{
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	auto bgManager = BackgroundManager::create();
	addChild(bgManager, BACKGROUND_Z_ORDER);
}

void GameOverScene::createScoreTextLabel(int score)
{
	std::string scoreText = SCORE_TEXT_BODY;
	scoreText += std::to_string(score);
	if (DataManager::GetHighScore() < score)
	{
		scoreText += NEW_HIGH_SCORE_TEXT_BODY;
	}

	auto scoreLabel = cocos2d::Label::createWithBMFont("fonts/Arial.fnt", scoreText);
	menuLabel = cocos2d::MenuItemLabel::create(scoreLabel);

	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

	const float scoreTextLabelXPosition = visibleSize.width * SCORE_LABEL_X_POS_RATIO;
	const float scoreTextLabelYPosition = visibleSize.height * SCORE_LABEL_Y_POS_RATIO;
	menuLabel->setPosition(scoreTextLabelXPosition, scoreTextLabelYPosition);
}

void GameOverScene::createMenu()
{
	menu = cocos2d::Menu::create(menuLabel, retryButton, returnMainMenuButton, nullptr);
	menu->setPosition(cocos2d::Point::ZERO);

	addChild(menu);
}

//Initiates the Game over scene components, adds it to main node then returns it(with score parameter for showing the player progress after game is over).
bool GameOverScene::init(int score)
{
	if (!Scene::init())
	{
		return false;
	}
	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

	createBackground();
	createRetryButton();
	createReturnMainMenuButton();
	createScoreTextLabel(score);
	createMenu();

	return true;
}

bool GameOverScene::init()
{
	return true;
}
