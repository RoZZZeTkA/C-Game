#ifndef AIDKIT_H
#define AIDKIT_H

#include <QGraphicsPixmapItem>

class AidKit : public QGraphicsPixmapItem, public QObject
{
public:
    AidKit(QPointF initPos);
    int type() const;
    enum {Type = UserType + 9};
    void advance(int phase);
};

#endif // AIDKIT_H
