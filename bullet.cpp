#include "bullet.h"

void Bullet::advance(int phase)
{
    if(!phase)
    {
        if(this->x() < 0)
            this->deleteLater();
        if(this->x() > scene()->width())
            this->deleteLater();
        if(this->y() < 0)
            this->deleteLater();
        if(this->y() > scene()->height())
            this->deleteLater();

        foreach (QGraphicsItem* item, collidingItems())
        {
            if(item->type() == Rock::Type)
            {
                setPos(-100, -100);
            }
        }
    }
    else
    {
        setPos(mapToParent(0, yspeed));
    }
}

FriendlyBullet::FriendlyBullet(QPointF initPos, double angle, QGraphicsItem *shooterP)
{
    yspeed = -10;
    setPixmap(QPixmap(":/images/bulletFriendly.png"));
    setPos(initPos);
    setRotation(angle);
    shooter = shooterP;
}

int FriendlyBullet::type() const
{
    return Type;
}

EnemyBullet::EnemyBullet(QPointF initPos, double angle, QGraphicsItem *shooterP)
{
    yspeed = -8;
    setPixmap(QPixmap(":/images/bulletEnemy.png"));
    setPos(initPos);
    setRotation(angle);
    shooter = shooterP;
}

int EnemyBullet::type() const
{
    return Type;
}
