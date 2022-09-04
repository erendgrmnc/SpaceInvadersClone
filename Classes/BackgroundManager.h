#pragma once
#include "cocos/2d/CCNode.h"
#include "cocos/platform/CCPlatformMacros.h"

namespace cocos2d 
{
	class Size;
	class Sprite;
	class ParallaxNode;
	class Vec2;
}

//Background Manager Class. For managing background of screens.
class BackgroundManager : public cocos2d::Node
{
public:
	cocos2d::ParallaxNode* GetBgNode();
	CREATE_FUNC(BackgroundManager);

private:
	bool init();
	
	cocos2d::Point dustSpeed;
	cocos2d::Point bgSpeed;
	cocos2d::ParallaxNode* _backgroundNode;
	cocos2d::Sprite* _spacedust1;
	cocos2d::Sprite* _spacedust2;
	cocos2d::Sprite* _planetsunrise;
	cocos2d::Sprite* _galaxy;
	cocos2d::Sprite* _spacialanomaly;
	cocos2d::Sprite* _spacialanomaly2;
	
	void InitializeBgSpeedVals(cocos2d::Vec2 dustSpeed, cocos2d::Vec2 bgSpeed);
	void createFirstSpaceDust();
	void createSecondSpaceDust();
	void createPlanetSunrise();
	void createGalaxy();
	void createFirstSpacialAnomaly();
	void createSecondSpacialAnomaly();
};
