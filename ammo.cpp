#include "ammo.h"

Ammo::Ammo(QPointF initPos)
{
    setPos(initPos);
    setPixmap(QPixmap(":/images/ammo.png"));
}

int Ammo::type() const
{
    return Type;
}

void Ammo::advance(int phase)
{
    if(!phase)
    {
        if(this->x() < 0)
            this->deleteLater();
        if(this->y() < 0)
            this->deleteLater();
    }
}
