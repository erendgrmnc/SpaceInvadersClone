#include "MainMenu.h"
#include "DataManager.h"
#include "cocos/2d/CCLabel.h"
#include "cocos/2d/CCMenu.h"
#include "cocos/2d/CCMenuItem.h"
#include "cocos/base/CCDirector.h"
#include "cocos/2d/CCSprite.h"
#include "SceneManager.h"

namespace {
	constexpr const char* PLAY_BUTTON_SPRITE_PATH = "playbutton.png";
	constexpr const char* BACKGROUND_SPRITE_PATH = "Backgrounds/spaceBg.jpg";
	constexpr const char* HEADER_TEXT = "Space Invaders Clone";
	constexpr const char* HIGH_SCORE_TEXT = "High Score: ";
	constexpr const char* FONT_TYPE = "fonts/Arial.fnt";

	constexpr int BACKGROUND_NODE_Z_ORDER = -1;
	constexpr int HEADER_FONT_RATIO = 12;

	constexpr float BACKGROUND_X_POS_RATIO = 0.5f;
	constexpr float BACKGROUND_Y_POS_RATIO = 0.5f;

	constexpr float PLAY_BUTTON_X_POS_RATIO = 0.5f;
	constexpr float PLAY_BUTTON_Y_POS_RATIO = 0.5f;

	constexpr float HIGH_SCORE_MENU_LABEL_Y_POS_RATIO = 0.66f;
	constexpr float HIGH_SCORE_MENU_LABEL_X_POS_RATIO = 0.5f;

	constexpr float MENU_LABEL_X_POS_RATIO = 0.5f;
	constexpr float MENU_LABEL_Y_POS_RATIO = 0.8f;

}

//Creates the main menu scene then returns it.
cocos2d::Scene* MainMenu::createScene()
{
	DataManager::ReadHighScore();
	auto scene = MainMenu::create();
	return scene;
}
//Initiates the Main Menu scene.
bool MainMenu::init()
{
	if (!Scene::init())
	{
		return false;
	}

	createBackground();
	createPlayButton();
	createHighScroeLabel();
	createMenuLabel();
	createMenu();

	return true;
}

void MainMenu::createBackground()
{
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	background = cocos2d::Sprite::create(BACKGROUND_SPRITE_PATH);
	background->setPosition(visibleSize.width * BACKGROUND_X_POS_RATIO, visibleSize.height * BACKGROUND_Y_POS_RATIO);
	addChild(background, BACKGROUND_NODE_Z_ORDER);
}

void MainMenu::createPlayButton()
{
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

	auto playBtnCallback = CC_CALLBACK_0(SceneManager::GoToGameScene, this);
	playButton = cocos2d::MenuItemImage::create(PLAY_BUTTON_SPRITE_PATH, PLAY_BUTTON_SPRITE_PATH, playBtnCallback);

	const float playButtonXPosition = visibleSize.width * PLAY_BUTTON_X_POS_RATIO;
	const float playButtonYPosition = visibleSize.height * PLAY_BUTTON_Y_POS_RATIO;

	playButton->setPosition(playButtonXPosition, playButtonYPosition);
}

void MainMenu::createHighScroeLabel()
{
	std::string highScoreText(HIGH_SCORE_TEXT);
	highScoreText += std::to_string(DataManager::GetHighScore());
	auto scoreLabel = cocos2d::Label::createWithBMFont(FONT_TYPE, highScoreText);
	highScoreLabel = cocos2d::MenuItemLabel::create(scoreLabel);

	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	const float highScoreMenuLabelXPosition = visibleSize.width * HIGH_SCORE_MENU_LABEL_X_POS_RATIO;
	const float highScoreMenuYPosition = visibleSize.height * HIGH_SCORE_MENU_LABEL_Y_POS_RATIO;

	highScoreLabel->setPosition(highScoreMenuLabelXPosition, highScoreMenuYPosition);
}

void MainMenu::createMenuLabel()
{
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

	auto header = cocos2d::Label::createWithBMFont(FONT_TYPE, HEADER_TEXT);
	const float headerFontSize = visibleSize.height / HEADER_FONT_RATIO;
	header->setBMFontSize(headerFontSize);

	const float menuHeaderXPosition = visibleSize.width * MENU_LABEL_X_POS_RATIO;
	const float menuHeaderYPosition = visibleSize.height * MENU_LABEL_Y_POS_RATIO;

	menuLabel = cocos2d::MenuItemLabel::create(header);
	menuLabel->setPosition(menuHeaderXPosition, menuHeaderYPosition);
}

void MainMenu::createMenu()
{
	mainMenu = cocos2d::Menu::create(menuLabel, highScoreLabel, playButton, nullptr);
	mainMenu->setPosition(cocos2d::Point::ZERO);

	addChild(mainMenu);
}
