#pragma once
#include "Bullet.h"
#include "PlayerBullet.h"

//Bullet Controller Class Definition. Manages the bullet events like spawning and pooling the bullet instances.
class BulletController
{
public:
    static void reset();
    static bool init(cocos2d::Node* bulletLayer);
    static Bullet* SpawnBullet(int type, cocos2d::Vec2 pos);
    static Bullet* CreateOrGetBullet(int type);
    static cocos2d::Vector<Bullet*> bulletsInScene;
    static cocos2d::Vector<PlayerBullet*> playerBullets;
    //TO DO: After implementing enemy shooting system, vector for object pool of enemy bullets.
    //static Vector<PlayerBullet*> enemyBullets;
    static void Erase(Bullet* b);
    static Bullet* GetBullet(cocos2d::Node* bullet);
    static int GetBulletIndex(cocos2d::Node* bullet);
    static bool isSuperAttack;
    static void SetAttackPowerOfBullet(Bullet* bullet);
protected:
    static bool inited;
    static cocos2d::Node* _bulletLayer;
};