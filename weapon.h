#ifndef WEAPON_H
#define WEAPON_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Weapon : public QGraphicsPixmapItem
{
public:
    void advance(int phase);
};

class PriWeapon : public Weapon
{
public:
    PriWeapon(int xpos, int ypos);
    int type() const;
    enum {Type = UserType + 3};
};

class SecWeapon : public Weapon
{
public:
    SecWeapon(int xpos, int ypos);
    int type() const;
    enum {Type = UserType + 4};
};

#endif // WEAPON_H
