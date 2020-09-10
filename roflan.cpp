#include "roflan.h"

static const double Pi = 3.14159265358979323846264338327950288419717;
static double TwoPi = 2 * Pi;

static qreal normalizeAngle(qreal angle)
{
    while (angle < 0)
        angle += TwoPi;
    while (angle > TwoPi)
        angle -= TwoPi;
    return angle;
}

Roflan::Roflan(double sceneWidth, double sceneHieght)
{
    setPixmap(QPixmap(":/images/gg0.png"));
    setPos((sceneWidth-pixmap().width())/2 , (sceneHieght-pixmap().height())/2);
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
    target = QPointF(sceneWidth/2, 0);
    setTransformOriginPoint(pixmap().width()/2, pixmap().height()/2);
    checkTimer = new QTimer;
    connect(this->checkTimer, &QTimer::timeout, this, &Roflan::itemCheck);
    checkTimer->start(1000/60);
    immunityTimer = new QTimer;
    immunityTimer->setSingleShot(true);
    shootCooldownTimer = new QTimer;
    shootCooldownTimer->setSingleShot(true);
    spriteTimer = new QTimer;
    connect(this->spriteTimer, &QTimer::timeout, this, &Roflan::spriteChanger);
    spriteTimer->start(200);

    zombiePlayer = new QMediaPlayer(this);
    zombiePlaylist = new QMediaPlaylist(zombiePlayer);
    zombiePlayer->setPlaylist(zombiePlaylist);
    zombiePlaylist->setPlaybackMode(QMediaPlaylist::Random);
    zombiePlaylist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
    zombiePlaylist->addMedia(QUrl("qrc:/sounds/munch1.mp3"));
    zombiePlaylist->addMedia(QUrl("qrc:/sounds/munch2.mp3"));
    zombiePlaylist->addMedia(QUrl("qrc:/sounds/munch3.mp3"));
    zombiePlaylist->addMedia(QUrl("qrc:/sounds/munch4.mp3"));

    weaponPlayer = new QMediaPlayer(this);
    weaponPlaylist = new QMediaPlaylist(weaponPlayer);
    weaponPlayer->setPlaylist(weaponPlaylist);
    weaponPlaylist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
    weaponPlaylist->addMedia(QUrl("qrc:/sounds/pickUpAK.mp3"));
    weaponPlaylist->addMedia(QUrl("qrc:/sounds/pickUpPistol.mp3"));

    shootPlayer = new QMediaPlayer(this);
    shootPlaylist = new QMediaPlaylist(shootPlayer);
    shootPlayer->setPlaylist(shootPlaylist);
    shootPlaylist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
    shootPlaylist->addMedia(QUrl("qrc:/sounds/akShot.mp3"));
    shootPlaylist->addMedia(QUrl("qrc:/sounds/pistolShot.mp3"));

    ggPlayer = new QMediaPlayer(this);
    ggPlaylist = new QMediaPlaylist(ggPlayer);
    ggPlayer->setPlaylist(ggPlaylist);
    ggPlaylist->setPlaybackMode(QMediaPlaylist::Random);
    ggPlaylist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
    ggPlaylist->addMedia(QUrl("qrc:/sounds/hurt1.mp3"));
    ggPlaylist->addMedia(QUrl("qrc:/sounds/hurt2.mp3"));
    ggPlaylist->addMedia(QUrl("qrc:/sounds/hurt3.mp3"));
}

void Roflan::advance(int phase)
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

        if(healthPoints <= 0)
        {
            setPixmap(QPixmap(":/images/ggDead.png"));
        }
    }
    else
    {
        if(healthPoints > 0)
        {
            moveBy(xspeed+xspeed1, yspeed+yspeed1);
            QLineF lineToTarget(QPointF(25, 25), mapFromScene(target));
            qreal angleToTarget = ::acos(lineToTarget.dx() / lineToTarget.length());
            if (lineToTarget.dy() < 0)
                angleToTarget = TwoPi - angleToTarget;
            angleToTarget = normalizeAngle((Pi - angleToTarget) + Pi / 2);
            if (angleToTarget >= 0 && angleToTarget < Pi)
                setRotation(angle = (rotation() - angleToTarget * 180 /Pi));
            else if (angleToTarget <= TwoPi && angleToTarget > Pi)
                setRotation(angle = (rotation() + (angleToTarget - TwoPi )* (-180) /Pi));
        }
    }
}

int Roflan::type() const
{
    return Type;
}

int Roflan::getHealth()
{
    return healthPoints;
}

int Roflan::getWeaponNumber()
{
    return weaponNumber;
}

int Roflan::getAmmo()
{
    if(weaponNumber == 1)
        return akAmmo;
    else if(weaponNumber == 2)
        return 1;
    else
        return 0;

}

void Roflan::spriteChanger()
{
    if(healthPoints > 0)
    {
        if(weaponNumber == 0)
        {
            if(yspeed+yspeed1 || xspeed+xspeed1)
            {
                switch (spriteNumber%3)
                {
                    case 0:
                    setPixmap(QPixmap(":/images/gg1.png"));
                    break;
                    case 1:
                    setPixmap(QPixmap(":/images/gg0.png"));
                    break;
                    case 2:
                    setPixmap(QPixmap(":/images/gg2.png"));
                    break;
                }
                spriteNumber++;
            }
            else
            {
                setPixmap(QPixmap(":/images/gg0.png"));
                spriteNumber = 0;
            }
        }
        if(weaponNumber == 1)
        {
            if(yspeed+yspeed1 || xspeed+xspeed1)
            {
                switch (spriteNumber%3)
                {
                    case 0:
                    setPixmap(QPixmap(":/images/ggAk1.png"));
                    break;
                    case 1:
                    setPixmap(QPixmap(":/images/ggAk0.png"));
                    break;
                    case 2:
                    setPixmap(QPixmap(":/images/ggAk2.png"));
                    break;
                }
                spriteNumber++;
            }
            else
            {
                setPixmap(QPixmap(":/images/ggAk0.png"));
                spriteNumber = 0;
            }
        }
        if(weaponNumber == 2)
        {
            if(yspeed+yspeed1 || xspeed+xspeed1)
            {
                switch (spriteNumber%3)
                {
                    case 0:
                    setPixmap(QPixmap(":/images/ggPistol1.png"));
                    break;
                    case 1:
                    setPixmap(QPixmap(":/images/ggPistol0.png"));
                    break;
                    case 2:
                    setPixmap(QPixmap(":/images/ggPistol2.png"));
                    break;
                }
                spriteNumber++;
            }
            else
            {
                setPixmap(QPixmap(":/images/ggPistol0.png"));
                spriteNumber = 0;
            }
        }
    }
}

void Roflan::slotTarget(QPointF point)
{
    if(healthPoints > 0)
    {
        target = point;
        QLineF lineToTarget(QPointF(25, 25), mapFromScene(target));
        qreal angleToTarget = ::acos(lineToTarget.dx() / lineToTarget.length());
        if (lineToTarget.dy() < 0)
            angleToTarget = TwoPi - angleToTarget;
        angleToTarget = normalizeAngle((Pi - angleToTarget) + Pi / 2);
        if (angleToTarget >= 0 && angleToTarget < Pi) {
            setRotation(angle = (rotation() - angleToTarget * 180 /Pi));
        } else if (angleToTarget <= TwoPi && angleToTarget > Pi) {
            setRotation(angle = (rotation() + (angleToTarget - TwoPi )* (-180) /Pi));
        }
    }
}

void Roflan::itemCheck()
{
    if(healthPoints > 0)
    {
        foreach (QGraphicsItem* item, collidingItems())
        {
            if(item->type() == PriWeapon::Type)
            {
                ak = true;
                weaponNumber = 1;
                akAmmo += 60;
                item->setData(0, true);
                signalWeaponChanged();
                weaponPlaylist->setCurrentIndex(0);
                weaponPlayer->play();
                signalAmmo();
            }
            if(item->type() == SecWeapon::Type)
            {
                pistol = true;
                weaponNumber = 2;
                item->setData(0, true);
                signalWeaponChanged();
                weaponPlaylist->setCurrentIndex(1);
                weaponPlayer->play();
                signalAmmo();
            }
            if(item->type() == EnemyBullet::Type && !immunityTimer->isActive() && healthPoints > 0)
            {
                healthPoints-=20;
                ggPlayer->play();
                immunityTimer->start(2000);
                signalHealth();
                item->setPos(-100, -100);
            }
            if(item->type() == Zombie::Type && !immunityTimer->isActive() && healthPoints > 0)
            {
                healthPoints-=15;
                ggPlayer->play();
                immunityTimer->start(2000);
                zombiePlayer->play();
                signalHealth();
            }
            if(item->type() == AidKit::Type && healthPoints < 100)
            {
                healthPoints+=25;
                if(healthPoints > 100)
                    healthPoints = 100;
                signalHealth();
                weaponPlaylist->setCurrentIndex(1);
                weaponPlayer->play();
                item->setPos(-100, 0);
            }
            if(item->type() == Ammo::Type)
            {
                akAmmo+=30;
                weaponPlaylist->setCurrentIndex(1);
                weaponPlayer->play();
                item->setPos(-100, 0);
                if(ak)
                    signalAmmo();
            }
        }
    }
}

void Roflan::shoot()
{
    if(!shootCooldownTimer->isActive() && weaponNumber!=0 && getAmmo() && healthPoints > 0)
    {
        if(weaponNumber == 1)
        {
            shootPlaylist->setCurrentIndex(0);
            shootCooldownTimer->start(1000/6);
            akAmmo--;
            signalAmmo();
        }
        if(weaponNumber == 2)
        {
            shootPlaylist->setCurrentIndex(1);
            shootCooldownTimer->start(1000/3);
        }
        scene()->addItem(new FriendlyBullet(mapToScene(QPointF(12.5, 0)), angle, this));
        //shootPlayer->stop();
        shootPlayer->play();
    }
}

void Roflan::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
        case Qt::Key_W:
        yspeed = -5;
        break;
        case Qt::Key_A:
        xspeed = -5;
        break;
        case Qt::Key_S:
        yspeed1 = 5;
        break;
        case Qt::Key_D:
        xspeed1 = 5;
        break;
        case Qt::Key_1:
        {
            if(ak && healthPoints > 0)
            {
            weaponNumber = 1;
            signalWeaponChanged();
            signalAmmo();
            setTransformOriginPoint(pixmap().width()/2, pixmap().height()/2+20);
            //setPixmap(QPixmap(":/images/ak47.png"));
            }
        }
        break;
        case Qt::Key_2:
        {
            if(pistol && healthPoints > 0)
            {
            weaponNumber = 2;
            signalWeaponChanged();
            signalAmmo();
            setTransformOriginPoint(pixmap().width()/2, pixmap().height()/2+10);
            //setPixmap(QPixmap(":/images/pistol.png"));
            }
        }
        break;
        default:
        break;
    }
}

void Roflan::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key())
    {
        case Qt::Key_W:
        yspeed = 0;
        break;
        case Qt::Key_A:
        xspeed = 0;
        break;
        case Qt::Key_S:
        yspeed1 = 0;
        break;
        case Qt::Key_D:
        xspeed1 = 0;
        break;
        default:
        break;
    }
}
