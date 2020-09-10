#include "enemy.h"

void Enemy::itemCheck()
{
    foreach (QGraphicsItem* item, collidingItems())
    {
        if(item->type() == FriendlyBullet::Type)
        {
            healthPoints-=20;
            item->setPos(-100,-100);
        }
    }
}

void Enemy::changeMoveDirection()
{
    moveDirection = rand()%2;
    canRotate = true;
}
