#ifndef ROFLAN_H
#define ROFLAN_H

#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QTimer>
#include "weapon.h"
#include "bullet.h"
#include "zombie.h"
#include <math.h>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include "rock.h"
#include "ammo.h"
#include "aidkit.h"

class Roflan : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Roflan(double sceneWidth, double sceneHeight);
    void advance(int phase);
    int type() const;
    enum {Type = UserType + 1};
    int getHealth();
    int getWeaponNumber();
    int getAmmo();
private:
    int xspeed = 0;
    int yspeed = 0;
    int xspeed1 = 0;
    int yspeed1 = 0;
    QPointF target;
    double angle = 0;
    int weaponNumber = 0;
    bool pistol = false;
    bool ak = false;
    int healthPoints = 100;
    int akAmmo = 0;
    QTimer *checkTimer;
    QTimer *shootCooldownTimer;
    QTimer *immunityTimer;
    QMediaPlayer * zombiePlayer;
    QMediaPlaylist * zombiePlaylist;
    QMediaPlayer * weaponPlayer;
    QMediaPlaylist * weaponPlaylist;
    QMediaPlayer * shootPlayer;
    QMediaPlaylist * shootPlaylist;
    QMediaPlayer * ggPlayer;
    QMediaPlaylist * ggPlaylist;
    QTimer *spriteTimer;
    void spriteChanger();
    int spriteNumber = 0;
signals:
    void signalWeaponChanged();
    void signalHealth();
    void signalAmmo();
public slots:
    void slotTarget(QPointF point);
    void itemCheck();
    void shoot();
protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
};

#endif // ROFLAN_H
