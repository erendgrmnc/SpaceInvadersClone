#pragma once
#include "cocos2d.h"

//Enumeration For Bullet Types.
enum BulletTypes {
    _PlayerBullet,
    _EnemyBullet
};
//Class definition of Bullet. Parent class for bullets. Manages the common properties and methods for bullets.
class Bullet : public cocos2d::Node
{
public:
    bool init();
    int GetAttackPower();
    int GetType();
    void SetAttackPower(int attackPower);
    virtual void Reset();
    cocos2d::Sprite* GetBulletSprite();
    CREATE_FUNC(Bullet);
protected:
    int attackPower;
    int type;
    cocos2d::Sprite* bulletSprite;
 
    virtual void Move(cocos2d::Vec2 moveDistance, float dt);
    virtual void Forward(cocos2d::Vec2 moveDistance);
};
