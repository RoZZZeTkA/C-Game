#include "weapon.h"

void Weapon::advance(int phase)
{
    Q_UNUSED(phase)
    if(data(0).toBool())
        delete this;
}

PriWeapon::PriWeapon(int xpos, int ypos)
{
    setPixmap(QPixmap(":/images/ak47.png"));
    setPos(xpos, ypos);
}

int PriWeapon::type() const
{
    return Type;
}

SecWeapon::SecWeapon(int xpos, int ypos)
{
    setPixmap(QPixmap(":/images/pistol.png"));
    setPos(xpos, ypos);
}

int SecWeapon::type() const
{
    return Type;
}
