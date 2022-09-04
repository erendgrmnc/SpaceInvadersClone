#pragma once

#include "Bullet.h";

//PlayerBullet class definition. Derived from the bullet class. Projectiles of player's ship.
class PlayerBullet : public Bullet
{
public:
    bool init();
    void SetMoveAction();
    CREATE_FUNC(PlayerBullet);
private:
    void createBulletPhysicsBody();
    void createBulletMovementAction();
};
