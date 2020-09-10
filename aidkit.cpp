#include "aidkit.h"

AidKit::AidKit(QPointF initPos)
{
    setPos(initPos);
    setPixmap(QPixmap(":/images/aidKit.png"));
}

int AidKit::type() const
{
    return Type;
}

void AidKit::advance(int phase)
{
    if(!phase)
    {
        if(this->x() < 0)
            this->deleteLater();
        if(this->y() < 0)
            this->deleteLater();
    }
}
