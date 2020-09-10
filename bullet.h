#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include "rock.h"

class Bullet : public QObject, public QGraphicsPixmapItem
{
public:
    void advance(int phase);
protected:
    int yspeed;
    QGraphicsItem* shooter;
};

class FriendlyBullet : public Bullet
{
public:
    FriendlyBullet(QPointF initPos, double angle, QGraphicsItem *shooterP);
    int type() const;
    enum {Type = UserType + 6};
};

class EnemyBullet : public Bullet
{
public:
    EnemyBullet(QPointF initPos, double angle, QGraphicsItem *shooterP);
    int type() const;
    enum {Type = UserType + 7};
};

#endif // BULLET_H
