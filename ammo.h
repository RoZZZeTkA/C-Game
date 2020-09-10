#ifndef AMMO_H
#define AMMO_H

#include <QGraphicsPixmapItem>

class Ammo : public QGraphicsPixmapItem, public QObject
{
public:
    Ammo(QPointF initPos);
    int type() const;
    enum{Type = UserType + 10};
    void advance(int phase);
};

#endif // AMMO_H
