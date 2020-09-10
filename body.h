#ifndef BODY_H
#define BODY_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QTimer>
#include <math.h>
#include "bullet.h"
#include <QDebug>

class Body : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    virtual void advance(int phase) = 0;
    virtual int type() const = 0;
protected:
    double angle = 0;
    int healthPoints = 200;
    QTimer *checkTimer;
public slots:
    virtual void itemCheck() = 0;
    virtual void shoot() = 0;
};


#endif // BODY_H
