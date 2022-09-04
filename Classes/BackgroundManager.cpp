#include "BackgroundManager.h"
#include "cocos/math/Vec2.h",
#include "cocos/math/CCGeometry.h"
#include "cocos/2d/CCParallaxNode.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

namespace
{
	constexpr const char* SPACE_DUST_SPRITE_PATH = "Backgrounds/bg_front_spacedust.png";
	constexpr const char* PLANET_SUNRISE_SPRITE_PATH = "Backgrounds/bg_planetsunrise.png";
	constexpr const char* GALAXY_SPRITE_PATH = "Backgrounds/bg_galaxy.png";
	constexpr const char* FIRST_SPACIAL_ANOMALY_SPRITE_PATH = "Backgrounds/bg_spacialanomaly.png";
	constexpr const char* SECOND_SPACIAL_ANOMALY_SPRITE_PATH = "Backgrounds/bg_spacialanomaly2.png";

	constexpr int FIRST_SPACE_DUST_Z_ORDER = 0;
	constexpr int SECOND_SPACE_DUST_Z_ORDER = 0;
	constexpr int PLANET_SUNRISE_Z_ORDER = -1;
	constexpr int GALAXY_Z_ORDER = -1;
	constexpr int FIRST_SPACIAL_ANOMALY_Z_ORDER = -1;
	constexpr int SECOND_SPACIAL_ANOMALY_Z_ORDER = -1;

	constexpr float DUST_SPEED_X_MOVEMENT_INIT_VAL = .1f;
	constexpr float DUST_SPEED_Y_MOVEMENT_INIT_VAL = .1f;
	constexpr float BG_SPEED_X_MOVEMENT_INIT_VAL = .05f;
	constexpr float BG_SPEED_Y_MOVEMENT_INIT_VAL = .05f;

	constexpr float FIRST_SPACE_DUST_X_POS_RATIO = 0.f;
	constexpr float FIRST_SPACE_DUST_Y_POS_RATIO = 0.5f;
	constexpr float SECOND_SPACE_DUST_X_POS_RATIO = 1.f;
	constexpr float SECOND_SPACE_DUST_Y_POS_RATIO = .5f;
	constexpr float GALAXY_X_POS_RATIO = 0.f;
	constexpr float GALAXY_Y_POS_RATIO = .7f;
	constexpr float PLANET_SUNRISE_X_POS_RATIO = .5f;
	constexpr float PLANET_SUNRISE_Y_POS_RATIO = .0f;
	constexpr float FIRST_SPACE_ANOMALY_X_POS_RATIO = .8f;
	constexpr float FIRST_SPACE_ANOMALY_Y_POS_RATIO = .3f;
	constexpr float SECOND_SPACE_ANOMALY_X_POS_RATIO = 1.2f;
	constexpr float SECOND_SPACE_ANOMALY_Y_POS_RATIO = .9f;
}

void BackgroundManager::InitializeBgSpeedVals(cocos2d::Vec2 dustSpeed = cocos2d::Vec2(DUST_SPEED_X_MOVEMENT_INIT_VAL, DUST_SPEED_Y_MOVEMENT_INIT_VAL), cocos2d::Vec2 bgSpeed = cocos2d::Vec2(BG_SPEED_X_MOVEMENT_INIT_VAL, BG_SPEED_Y_MOVEMENT_INIT_VAL)) {
	this->dustSpeed = dustSpeed;
	this->bgSpeed = bgSpeed;
}

void BackgroundManager::createFirstSpaceDust()
{
	_spacedust1 = cocos2d::Sprite::create(SPACE_DUST_SPRITE_PATH);
	cocos2d::Size& visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	const float firstSpaceDustXPosition = FIRST_SPACE_DUST_X_POS_RATIO;
	const float firstSpaceDustYPosition = visibleSize.height * FIRST_SPACE_DUST_Y_POS_RATIO;
	const cocos2d::Vec2& firstSpaceDustPositionVec = cocos2d::Vec2(firstSpaceDustXPosition, firstSpaceDustYPosition);
	_backgroundNode->addChild(_spacedust1, FIRST_SPACE_DUST_Z_ORDER, dustSpeed, firstSpaceDustPositionVec);
}

void BackgroundManager::createSecondSpaceDust()
{
	_spacedust2 = cocos2d::Sprite::create(SPACE_DUST_SPRITE_PATH);

	cocos2d::Size& visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	const float secondSpaceDustXPosition = _spacedust1->getContentSize().width * SECOND_SPACE_DUST_X_POS_RATIO;
	const float secondSpaceDustYPosition = visibleSize.height * SECOND_SPACE_DUST_Y_POS_RATIO;
	const cocos2d::Vec2& secondSpaceDustPositionVec = cocos2d::Vec2(secondSpaceDustXPosition, secondSpaceDustYPosition);
	_backgroundNode->addChild(_spacedust2, SECOND_SPACE_DUST_Z_ORDER, dustSpeed, secondSpaceDustPositionVec);
}

void BackgroundManager::createPlanetSunrise()
{
	_planetsunrise = cocos2d::Sprite::create(PLANET_SUNRISE_SPRITE_PATH);

	cocos2d::Size& visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	const float planetSunriseXPosition = visibleSize.width * PLANET_SUNRISE_X_POS_RATIO;
	const float planetSunriseYPosition = visibleSize.height * PLANET_SUNRISE_Y_POS_RATIO;
	const cocos2d::Vec2& planetSunrisePosVec = cocos2d::Vec2(planetSunriseXPosition, planetSunriseYPosition);
	_backgroundNode->addChild(_planetsunrise, PLANET_SUNRISE_Z_ORDER, bgSpeed, planetSunrisePosVec);
}

void BackgroundManager::createGalaxy()
{
	_galaxy = cocos2d::Sprite::create(GALAXY_SPRITE_PATH);

	cocos2d::Size& visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	const float galaxyXPosition = GALAXY_X_POS_RATIO;
	const float galaxyYPosition = visibleSize.height * GALAXY_Y_POS_RATIO;
	const cocos2d::Vec2& galaxyPositionVec = cocos2d::Vec2(galaxyXPosition, galaxyYPosition);
	_backgroundNode->addChild(_galaxy, GALAXY_Z_ORDER, bgSpeed, galaxyPositionVec);
}

void BackgroundManager::createFirstSpacialAnomaly()
{
	_spacialanomaly = cocos2d::Sprite::create(FIRST_SPACIAL_ANOMALY_SPRITE_PATH);

	cocos2d::Size& visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	const float firstSpacialAnomalyXPosition = visibleSize.width * FIRST_SPACE_ANOMALY_X_POS_RATIO;
	const float firstSpacialAnomalyYPosition = visibleSize.height * FIRST_SPACE_ANOMALY_Y_POS_RATIO;
	const cocos2d::Vec2& firstSpacialAnomalyPosVec = cocos2d::Vec2(firstSpacialAnomalyXPosition, firstSpacialAnomalyYPosition);
	_backgroundNode->addChild(_spacialanomaly, FIRST_SPACIAL_ANOMALY_Z_ORDER, bgSpeed, firstSpacialAnomalyPosVec);
}

void BackgroundManager::createSecondSpacialAnomaly()
{
	_spacialanomaly2 = cocos2d::Sprite::create(SECOND_SPACIAL_ANOMALY_SPRITE_PATH);

	cocos2d::Size& visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	const float secondSpacialAnomalyXPosition = visibleSize.width * SECOND_SPACE_ANOMALY_X_POS_RATIO;
	const float secondSpacialAnomalyYPosition = visibleSize.height * SECOND_SPACE_ANOMALY_Y_POS_RATIO;
	const cocos2d::Vec2& secondSpacialAnomalyPosVec = cocos2d::Vec2(secondSpacialAnomalyXPosition, secondSpacialAnomalyYPosition);
	_backgroundNode->addChild(_spacialanomaly2, SECOND_SPACIAL_ANOMALY_Z_ORDER, bgSpeed, secondSpacialAnomalyPosVec);
}

bool BackgroundManager::init() {

	_backgroundNode = cocos2d::ParallaxNode::create();
	InitializeBgSpeedVals();	


	createFirstSpaceDust();
	createSecondSpaceDust();
	createPlanetSunrise();
	createGalaxy();
	createFirstSpacialAnomaly();
	createSecondSpacialAnomaly();

	addChild(_backgroundNode);

	return true;
}

cocos2d::ParallaxNode* BackgroundManager::GetBgNode() {
	return _backgroundNode;
}