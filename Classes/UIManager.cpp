#include "cocos2d.h"
#include "Config.h"
#include "UIManager.h"

namespace
{
	constexpr const char* LABEL_FONT = "fonts/Arial.fnt";
	constexpr const char* NORMAL_ATTACK_TEXT = "NORMAL";
	constexpr const char* SUPER_ATTACK_TEXT = "SUPER";

	const int SCORE_LABEL_INIT_VALUE = 0;

	constexpr float POWER_LABEL_X_POS_RATIO = .92f;
	constexpr float POWER_LABEL_Y_POS_RATIO = .1f;

	constexpr float SCORE_LABEL_X_POS_RATIO = .94f;
	constexpr float SCORE_LABEL_Y_POS_RATIO = .96f;

	constexpr int LABEL_Z_ORDER = 3;
}

UIManager* UIManager::instance = nullptr;

UIManager::UIManager()
{
	gameLayer = nullptr;
	powerLabel = nullptr;
	scoreLabel = nullptr;
}


UIManager* UIManager::getInstance()
{
	if (instance == nullptr)
	{
		instance = new UIManager();
	}
	return instance;
}

//Initiates the UI Element Node. Creates the components and attachs it to the referanced game layer.
bool UIManager::init(Node* _gameLayer)
{
	gameLayer = _gameLayer;
	createPowerLabel();
	createScoreLabel();

	return true;
}
//Sets the score labels text.
void UIManager::SetScoreLabelText(std::string text)
{
	scoreLabel->setString(text);
}
//Sets the power labels text by given parameter 'text'.
void UIManager::SetPowerLabelText(BulletDamageTypes bulletDamageType)
{
	if (bulletDamageType == BulletDamageTypes::SuperAttack)
	{
		powerLabel->setString(SUPER_ATTACK_TEXT);
	}
	else
	{
		powerLabel->setString(NORMAL_ATTACK_TEXT);
	}
}

void UIManager::createPowerLabel()
{
	std::string powerLabelText = NORMAL_ATTACK_TEXT;
	powerLabel = cocos2d::Label::createWithBMFont(LABEL_FONT, powerLabelText);

	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getWinSize();
	const float powerLabelXPosition = visibleSize.width * POWER_LABEL_X_POS_RATIO;
	const float powerLabelYPosition = visibleSize.height * POWER_LABEL_Y_POS_RATIO;
	powerLabel->setPosition(powerLabelXPosition, powerLabelYPosition);

	gameLayer->addChild(powerLabel, LABEL_Z_ORDER);
}

void UIManager::createScoreLabel()
{
	std::string scoreText = std::to_string(SCORE_LABEL_INIT_VALUE);
	scoreLabel = cocos2d::Label::createWithBMFont(LABEL_FONT, scoreText);

	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getWinSize();
	const float scoreLabelXPosition = visibleSize.width * SCORE_LABEL_X_POS_RATIO;
	const float scoreLabelYPosition = visibleSize.height * SCORE_LABEL_Y_POS_RATIO;
	scoreLabel->setPosition(scoreLabelXPosition, scoreLabelYPosition);

	gameLayer->addChild(scoreLabel, LABEL_Z_ORDER);
}
