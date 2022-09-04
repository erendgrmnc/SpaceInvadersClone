#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H
#include "cocos2d.h"
using namespace cocos2d;

enum moveMode {
	Default,
	Turn
};

enum class PhysicsCategory {
	None = 0,
	Monster = (1 << 0),
	Projectile = (1 << 1),
	All = Monster | Projectile
};


class CollisionManager
{
public:
	CollisionManager();
	bool onContactBegan(PhysicsContact& contact);

private:

};

#endif