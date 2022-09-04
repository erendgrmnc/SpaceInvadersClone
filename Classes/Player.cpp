#include "Player.h"
#include "UIManager.h"
#include "Bullet.h"
#include "BulletController.h"
#include "Config.h"

namespace
{
	constexpr const char* SPACE_SHIP_SPRITE_PATH = "SpaceShip.png";
	
	constexpr int PLAYER_Z_ORDER = 0;

	constexpr const float SPACE_SHIP_PHYSICS_RATIO = .5f;
	
	constexpr const float PLAYER_X_POS_RATIO = .5f;
	constexpr const float PLAYER_Y_POS_RATIO = .1f;
}

//Static instance for player object. Player needs to be singleton for handling events.
Player* Player::player = nullptr;

//Initiating the player object. Components created and added to the main node.
bool Player::init()
{
	isPlayerInput = false;
	xMovement = 0;
	yMovement = 0;
	isFireable = true;
	killCount = 0;

	createPlayerSprite();
	createPlayerPhsyicsBody();
	createPlayerControlEvents();

	return true;
}

//Sets the variable is Fireable.
void Player::SetIsFireable(bool isFireable)
{
	if (!isFireable)
	{
		cocos2d::log("Dolduruluyor...");
	}
	else
	{
		cocos2d::log("Hazır !");
	}
	isFireable = isFireable;
}
//Returns the kill count variable for deciding the activation of Super Mode.
int Player::GetKillCount()
{
	return killCount;
}
//Incerasing the kill count when player destroyed an enemy ship.(NOT IN SUPER MODE!)
void Player::IncreaseKillCount()
{
	if (!BulletController::isSuperAttack)
	{
		killCount += 1;
	}
}

//For handling the player shoot event. Instantiates a player bullet when player triggered the shoot control.
void Player::Shoot()
{
	BulletController::SpawnBullet(BulletTypes::_PlayerBullet, playerSprite->getPosition());
}

//For activating the super mode.
void Player::EnableSuperAttack()
{
	BulletController::isSuperAttack = true;
	UIManager::getInstance()->SetPowerLabelText(BulletDamageTypes::SuperAttack);
}

//For disabling the super mode.
void Player::DisableSuperAttack()
{
	BulletController::isSuperAttack = false;
	Player::GetInstance()->ResetKillCount();
	UIManager::getInstance()->SetPowerLabelText(BulletDamageTypes::NormalAttack);
}
//Triggers the action for super attack mode.
void Player::InitiateSuperAttack()
{
	runAction(cocos2d::Sequence::create(cocos2d::CallFunc::create(CC_CALLBACK_0(Player::EnableSuperAttack, this)), cocos2d::DelayTime::create(SUPER_TIME), cocos2d::CallFunc::create(CC_CALLBACK_0(Player::DisableSuperAttack, this)), NULL));
}
//Resets the kill count for Super Mode.
void Player::ResetKillCount()
{
	killCount = 0;
}
//Method for reseting the Player Instance
void Player::ResetPlayerInstance()
{
	player = nullptr;
}
//Returns the player instance. Creates the instance if it's not initiated.
Player* Player::GetInstance()
{
	if (!player || player->GetPlayerSprite() == NULL)
	{
		player = Player::create();

	}

	return player;
}
void Player::createPlayerSprite()
{
	playerSprite = cocos2d::Sprite::create(SPACE_SHIP_SPRITE_PATH);
	addChild(playerSprite, PLAYER_Z_ORDER, PLAYER_TAG);
}
void Player::createPlayerPhsyicsBody()
{
	const float spaceShipPhsyicsBodySize = playerSprite->getContentSize().width * SPACE_SHIP_PHYSICS_RATIO;
	auto physicsBody = cocos2d::PhysicsBody::createCircle(spaceShipPhsyicsBodySize);
	physicsBody->setDynamic(true);
	physicsBody->setCategoryBitmask((int)PhysicsCategory::Bullet);
	physicsBody->setCollisionBitmask((int)PhysicsCategory::None);
	physicsBody->setContactTestBitmask((int)PhysicsCategory::Enemy);
	playerSprite->setPhysicsBody(physicsBody);
}
void Player::createPlayerControlEvents()
{
	playerSprite->setPosition(cocos2d::Vec2(cocos2d::Director::getInstance()->getWinSize().width / 2, cocos2d::Director::getInstance()->getWinSize().height * 0.1));
	auto keyboardListener = cocos2d::EventListenerKeyboard::create();
	auto mouseListener = cocos2d::EventListenerMouse::create();

	keyboardListener->onKeyPressed = CC_CALLBACK_2(Player::onKeyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(Player::onKeyReleased, this);

	mouseListener->onMouseDown = CC_CALLBACK_1(Player::OnMouseDown, this, cocos2d::Director::getInstance()->getWinSize());

	cocos2d::Node::_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
	cocos2d::Node::_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
}
//Return the player sprite object.
cocos2d::Sprite* Player::GetPlayerSprite() {
	return playerSprite;
}
//Sets the player sprite by given parameter
void Player::SetPlayerSprite(cocos2d::Sprite* sprite) {
	playerSprite = sprite;
}
//Event handler when player pressed a key from keyboard.
void Player::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	isPlayerInput = true;
	cocos2d::log("Key with keycode %d pressed", keyCode);

	std::string _logtext = "Player" + std::to_string(this->playerSprite->getPosition().x);
	cocos2d::log(_logtext.c_str());
	switch (keyCode)
	{
	case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	case cocos2d::EventKeyboard::KeyCode::KEY_A:
		xMovement--;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
	case cocos2d::EventKeyboard::KeyCode::KEY_D:
		xMovement++;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
	case cocos2d::EventKeyboard::KeyCode::KEY_W:
		//yMovement++; Y Movement is disabled due to original space invaders game.
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
	case cocos2d::EventKeyboard::KeyCode::KEY_S:
		//yMovement--; Y Movement is disabled due to original space invaders game.
		break;
	}
}

//Event handler when player released a key from keyboard.
void Player::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	this->isPlayerInput = false;
	log("Key with keycode %d pressed", keyCode);
	switch (keyCode)
	{
	case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	case cocos2d::EventKeyboard::KeyCode::KEY_A:
		xMovement++;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
	case cocos2d::EventKeyboard::KeyCode::KEY_D:
		xMovement--;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
	case cocos2d::EventKeyboard::KeyCode::KEY_W:
		//yMovement--; Y Movement is disabled due to original space invaders game.
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
	case cocos2d::EventKeyboard::KeyCode::KEY_S:
		//yMovement++; Y Movement is disabled due to original space invaders game.
		break;
	}
}
//Event handler for moving the player when there is an input from the player.
void Player::MovePlayer(cocos2d::Size screenSize) {

	float newPosX = playerSprite->getPositionX() + (xMovement * 10.f);
	float newPosY = playerSprite->getPositionY() + (yMovement * 10.f);
	if (newPosX >= screenSize.width || newPosX <= 0)
	{
		cocos2d::log("Ekrandan Disari cikamazsin");
	}
	else
	{
		playerSprite->setPosition(newPosX, newPosY);
	}
}
//Returns the variable for player movement status.
bool Player::GetIsPlayerMoving()
{
	return isPlayerInput;
}
//Update function for player.
void Player::update(float dt)
{
	if (player)
	{
		MovePlayer(cocos2d::Director::getInstance()->getWinSize());
	}

}
//Event handler when player preesed the mouse button.
void Player::OnMouseDown(cocos2d::EventMouse* event, cocos2d::Size screenSize) {
	if (isFireable)
	{
		if (event->getMouseButton() == cocos2d::EventMouse::MouseButton::BUTTON_LEFT) {
			//TO DO: For creating a reload mechanism.
			if (BulletController::bulletsInScene.size() >= 10) {
				this->runAction(cocos2d::Sequence::create(cocos2d::CallFunc::create(CC_CALLBACK_0(Player::SetIsFireable, this, false)), cocos2d::DelayTime::create(2), cocos2d::CallFunc::create(CC_CALLBACK_0(Player::SetIsFireable, this, true)), NULL));
			}
			Shoot();
		}
	}
}