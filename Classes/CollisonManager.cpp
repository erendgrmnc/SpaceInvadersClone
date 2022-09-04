#include "CollisonManager.h"

CollisionManager::CollisionManager()
{
}

bool CollisionManager::onContactBegan(PhysicsContact& contact)
{
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();

    nodeA->removeFromParent();
    nodeB->removeFromParent();
    return true;
}
