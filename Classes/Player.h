#pragma once
#include "cocos2d.h"

//Player Class Definition. Managing the player object in program.
class Player :public cocos2d::Node
{
public:
	bool init();
	bool GetIsPlayerMoving();
	
	int GetKillCount();

	void update(float dt);
	void SetPlayerSprite(cocos2d::Sprite* sprite);
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void OnMouseDown(cocos2d::EventMouse* event, cocos2d::Size screenSize);
	void MovePlayer(cocos2d::Size screenSize);
	void SetIsFireable(bool isFireable);
	void IncreaseKillCount();
	void Shoot();
	void EnableSuperAttack();
	void DisableSuperAttack();
	void InitiateSuperAttack();
	void ResetKillCount();

	cocos2d::Sprite* GetPlayerSprite();

	CREATE_FUNC(Player);

	static void ResetPlayerInstance();

	static Player* GetInstance();
private:	
	bool isPlayerInput;
	bool isFireable;

	char* spriteName;
	
	int xMovement;
	int yMovement;
	int killCount;
	
	cocos2d::Sprite* playerSprite;

	cocos2d::DelayTime* fireDelay;
	
	static Player* player;

	void createPlayerSprite();
	void createPlayerPhsyicsBody();
	void createPlayerControlEvents();
};