#pragma once

#include "cocos2d.h"

enum BulletDamageTypes;
//UI Manager Class Definition. Manages the UI of the scene.

class UIManager : public cocos2d::Node
{
public:
	static UIManager* getInstance();

	bool init(cocos2d::Node* _gameLayer);
	void SetScoreLabelText(std::string text);
	void SetPowerLabelText(BulletDamageTypes bulletDamageType);

	UIManager(UIManager& other) = delete;
	void operator=(const UIManager&) = delete;
private:
	UIManager();

	static UIManager* instance;

	cocos2d::Label* scoreLabel;
	cocos2d::Label* powerLabel;
	cocos2d::Node* gameLayer;

	void createPowerLabel();
	void createScoreLabel();
};