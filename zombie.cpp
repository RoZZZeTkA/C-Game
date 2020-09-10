#include "zombie.h"

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

Zombie::Zombie(int xpos, int ypos, QGraphicsItem *object, CustomScene *sceneP)
{
    setPixmap(QPixmap(":/images/zombie1.png"));
    setPos(xpos-pixmap().width()/2, ypos-pixmap().height()/2);
    healthPoints = 110;
    target = object;
    parentScene = sceneP;
    //setTransformOriginPoint(pixmap().width()/2, pixmap().height()/2);
    spriteTimer = new QTimer;
    connect(this->spriteTimer, &QTimer::timeout, this, &Zombie::spriteChanger);
    spriteTimer->start(200);
    checkTimer = new QTimer;
    connect(this->checkTimer, &QTimer::timeout, this, &Zombie::itemCheck);
    checkTimer->start(1000/60);
    randTimer = new QTimer;
    connect(this->randTimer, &QTimer::timeout, this, &Zombie::changeMoveDirection);
    randTimer->start(2500);
    connect(this, &Zombie::signalDeath, parentScene, &CustomScene::deleteZombie);
}

void Zombie::advance(int phase)
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

        QList<QGraphicsItem *> lineToRoflan = scene()->items(QPolygonF() << mapToScene(0, 0) << mapToScene(50, 0)
                                << mapToScene(mapFromItem(target, 0, 0)) << mapToScene(mapFromItem(target, 25, 0)));
        foreach (QGraphicsItem *item, lineToRoflan)
        {
            if (item->type()  == Rock::Type)
            {
                seeRoflan = false;
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
            if (angleToTarget > 0 && angleToTarget < Pi )
                    angle = -5;
            else if (angleToTarget <= TwoPi && angleToTarget > (Pi))
                    angle = 5;
            else if(angleToTarget == 0.0)
                    angle = 0;
            if(angleToTarget > Pi/18 && angleToTarget < TwoPi-(Pi/18) && lineToTarget.length() > 40)
                setRotation(rotation() + angle);
            if(lineToTarget.length() > 40)
                yspeed = -5;
            else
                yspeed = 0;
            setPos(mapToScene(0, yspeed));
        }
        if(!seeRoflan)
        {
            QList<QGraphicsItem *> zone = scene()->items(QPolygonF() << mapToScene(0, 0) << mapToScene(50, 0) << mapToScene(0, -300) << mapToScene(50, -300));
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
            //setPos(mapToScene(-2, -2));
        }
    }
}

void Zombie::spriteChanger()
{
    if(yspeed)
    {
        switch (spriteNumber%4)
        {
            case 0:
            setPixmap(QPixmap(":/images/zombie1.png"));
            break;
            case 1:
            setPixmap(QPixmap(":/images/zombie2.png"));
            break;
            case 2:
            setPixmap(QPixmap(":/images/zombie3.png"));
            break;
            case 3:
            setPixmap(QPixmap(":/images/zombie4.png"));
            break;
        }
        spriteNumber++;
    }
    else
    {
        setPixmap(QPixmap(":/images/zombie5.png"));
        spriteNumber = 0;
    }

}

int Zombie::type() const
{
    return Type;
}
