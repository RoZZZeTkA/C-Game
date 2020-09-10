#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QTimer>
#include "bullet.h"
#include "customscene.h"
#include "math.h"

class Enemy : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    virtual void advance(int phase) = 0;
protected:
    qreal angle = 0;
    QGraphicsItem *target;
    QTimer *randTimer;
    int moveDirection = 0;
    int healthPoints;
    bool canRotate = false;
    QTimer *checkTimer;
    QTimer *spriteTimer;
    virtual void spriteChanger() = 0;
    int spriteNumber = 0;
    int yspeed = 0;
    CustomScene *parentScene;
    bool seeRoflan = true;
signals:
    void signalDeath(QGraphicsItem *item);
protected slots:
    void itemCheck();
    void changeMoveDirection();
};

#endif // ENEMY_H
