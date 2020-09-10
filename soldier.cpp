#include "soldier.h"

static const double Pi = 3.14159265358979323846264338327950288419717;
static double TwoPi = 2.0 * Pi;

static qreal normalizeAngle(qreal angle)
{
    while (angle < 0)
        angle += TwoPi;
    while (angle > TwoPi)
        angle -= TwoPi;
    return angle;
}

Soldier::Soldier(int xpos, int ypos, QGraphicsItem *object, CustomScene *sceneP)
{
    setPixmap(QPixmap(":/images/soldier5.png"));
    setPos(xpos-pixmap().width()/2, ypos-pixmap().height()/2);
    healthPoints = 100;
    target = object;
    parentScene = sceneP;
    //setTransformOriginPoint(pixmap().width()/2, pixmap().height()/2);
    shootTimer = new QTimer;
    connect(this->shootTimer, &QTimer::timeout, this, &Soldier::shoot);
    //shootTimer->start(700);
    dodgeTimer = new QTimer;
    connect(this->dodgeTimer, &QTimer::timeout, this, &Soldier::dodge);
    dodgeTimer->start(1000/60);
    randTimer = new QTimer;
    connect(this->randTimer, &QTimer::timeout, this, &Soldier::changeDodgeDirection);
    connect(this->randTimer, &QTimer::timeout, this, &Soldier::changeMoveDirection);
    randTimer->start(2500);
    checkTimer = new QTimer;
    connect(this->checkTimer, &QTimer::timeout, this, &Soldier::itemCheck);
    checkTimer->start(1000/60);
    spriteTimer = new QTimer;
    connect(this->spriteTimer, &QTimer::timeout, this, &Soldier::spriteChanger);
    spriteTimer->start(200);
    connect(this, &Soldier::signalDeath, parentScene, &CustomScene::deleteSoldier);
}

void Soldier::advance(int phase)
{
    if(!phase)
    {
        if(this->x() < 0)
            this->setX(0);
        if(this->x() > scene()->width()-pixmap().width())
            this->setX(scene()->width()-pixmap().width());
        if(this->y() < 0)
            this->setY(0);
        if(this->y() > scene()->height()-pixmap().height())
            this->setY(scene()->height()-pixmap().height());
        //           ПРОВЕРЯЕТ ОБЪЕКТЫ МЕЖДУ СОЛДЕРОМ И РОФЛАНОМ
        QList<QGraphicsItem *> lineToRoflan = scene()->items(QPolygonF() << mapToScene(0, 0) << mapToScene(50, 0)
                                << mapToScene(mapFromItem(target, 0, 0)) << mapToScene(mapFromItem(target, 25, 0)));
        foreach (QGraphicsItem *item, lineToRoflan)
        {
            if (item->type()  == Rock::Type)
            {
                seeRoflan = false;
                //yspeed = 0;
                shootTimer->stop();
            }
        }

        if(healthPoints <= 0)
        {
            signalDeath(this);
            this->deleteLater();
        }
    }
    else
    {
        if(seeRoflan)
        {
            QLineF lineToTarget(QPointF(25, 25), mapFromItem(target, 25, 25));
            qreal angleToTarget = ::acos(lineToTarget.dx() / lineToTarget.length());
            if (lineToTarget.dy() < 0)
                    angleToTarget = TwoPi - angleToTarget;
            angleToTarget = normalizeAngle((Pi - angleToTarget) + Pi / 2);
            if (angleToTarget > 0 && angleToTarget < Pi)
            {

                   if(angleToTarget > Pi / 5)
                       angle = -15;
                   else if(angleToTarget > Pi / 10)
                       angle = -5;
                   else
                       angle = -1;
            }
            else if (angleToTarget <= TwoPi && angleToTarget > (Pi))
            {
                   if(angleToTarget < (Pi / 5))
                       angle = 15;
                   else if(angleToTarget < (Pi / 10))
                       angle = 5;
                   else
                       angle = 1;
             }
             else if(angleToTarget == 0.0)
                   angle = 0;

            if(angleToTarget > Pi/18 && angleToTarget < TwoPi-(Pi/18))
                setRotation(bulletAngle = rotation() + angle);

            if(lineToTarget.length() > 800)
                yspeed = -3;
            else
                yspeed = 0;

            setPos(mapToScene(0, yspeed));

            if(!shootTimer->isActive())
                shootTimer->start(1800);
        }
        if(!seeRoflan)
        {
            if(moveDirection == 0)
            {
                srand(static_cast<unsigned int>(time(nullptr)));
                switch(rand()%2)
                {
                    case 0:
                    angle = 20;
                    break;
                    case 1:
                    angle = -20;
                    break;
                }
            }
            QList<QGraphicsItem *> zone = scene()->items(QPolygonF() << mapToScene(0, 0) << mapToScene(50, 0) << mapToScene(0, -300) << mapToScene(50, -300));
            foreach (QGraphicsItem *item, zone)
            {
                if(item->type() == Rock::Type)
                {
                    angle = 5;
                    canRotate = true;
                }
            }
            if(canRotate)
            {
                setRotation(rotation() + angle);
                canRotate = false;
            }
            yspeed = -3;
            setPos(mapToScene(0, yspeed));
            seeRoflan = true;
        }
    }
}

void Soldier::spriteChanger()
{
    if(yspeed)
    {
        switch (spriteNumber%4)
        {
            case 0:
            setPixmap(QPixmap(":/images/soldier1.png"));
            break;
            case 1:
            setPixmap(QPixmap(":/images/soldier2.png"));
            break;
            case 2:
            setPixmap(QPixmap(":/images/soldier3.png"));
            break;
            case 3:
            setPixmap(QPixmap(":/images/soldier4.png"));
            break;
        }
        spriteNumber++;
    }
    else
    {
        setPixmap(QPixmap(":/images/soldier5.png"));
        spriteNumber = 0;
    }

}

void Soldier::shoot()
{
    scene()->addItem(new EnemyBullet(mapToScene(QPointF(12.5, 0)), bulletAngle, this));
}

void Soldier::dodge()
{
    QList<QGraphicsItem *> lineToTarget = scene()->items(QPolygonF() << mapToScene(0, 0) << mapToScene(50, 0) << mapToScene(0, -400) << mapToScene(50, -400));
    foreach (QGraphicsItem *item, lineToTarget)
    {
        if(item->type() == FriendlyBullet::Type)
        {
            switch(dodgeDirection)
            {
                case 0:
                setPos(mapToScene(-5, 0));
                break;
                case 1:
                setPos(mapToScene(5, 0));
                break;
            }
        }
    }
}

void Soldier::changeDodgeDirection()
{
    dodgeDirection = rand()%2;
}
