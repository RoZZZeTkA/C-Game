#include "rock.h"

Rock::Rock(double xpos, double ypos, int width_p, int height_p)
{
    width = width_p;
    height = height_p;
    if(width == 50 && height == 50)
        setPixmap(QPixmap(":/images/wall.png"));
    if(width == 150 && height == 50)
        setPixmap(QPixmap(":/images/wall3g.png"));
    if(width == 50 && height == 150)
        setPixmap(QPixmap(":/images/wall3v.png"));
    if(width == 2000 && height == 50)
        setPixmap(QPixmap(":/images/2000.png"));
    if(width == 50 && height == 1100)
        setPixmap(QPixmap(":/images/1100.png"));
    setPos(xpos, ypos);
}

int Rock::type() const
{
    return Type;
}

void Rock::advance(int phase)
{
    if(!phase)
    {
        QList<QGraphicsItem *> leftSide = scene()->items(QPolygonF() << mapToScene(-25, height-10) << mapToScene(-25, 10) << mapToScene(-24, 10) << mapToScene(-24, height-10));
        foreach (QGraphicsItem *item, leftSide)
        {
            if (item  == this || item->type() == Rock::type())
                continue;
            else
                foreach(QGraphicsItem *item1, collidingItems())
                    if(item == item1)
                        item->setPos(this->x()-50, item->y());
        }
        QList<QGraphicsItem *> rightSide = scene()->items(QPolygonF() << mapToScene(width+24, height-10) << mapToScene(width+24, 10) << mapToScene(width+25, 10) << mapToScene(width+25, height-10));
        foreach (QGraphicsItem *item, rightSide)
        {
            if (item  == this || item->type() == Rock::type())
                continue;
            else
                foreach(QGraphicsItem *item1, collidingItems())
                    if(item == item1)
                        item->setPos(this->x()+pixmap().width(), item->y());
        }
        QList<QGraphicsItem *> topSide = scene()->items(QPolygonF() << mapToScene(10, -24) << mapToScene(10, -25) << mapToScene(width-10, -25) << mapToScene(width-10, -24));
        foreach (QGraphicsItem *item, topSide)
        {
            if (item  == this || item->type() == Rock::type())
                continue;
            else
                foreach(QGraphicsItem *item1, collidingItems())
                    if(item == item1)
                        item->setPos(item->x(), this->y()-50);
        }
        QList<QGraphicsItem *> lowSide = scene()->items(QPolygonF() << mapToScene(10, height+25) << mapToScene(10, height+24) << mapToScene(width-10, height+24) << mapToScene(width-10, height+25));
        foreach (QGraphicsItem *item, lowSide)
        {
            if (item  == this || item->type() == Rock::type())
                continue;
            else
                foreach(QGraphicsItem *item1, collidingItems())
                    if(item == item1)
                        item->setPos(item->x(), this->y()+pixmap().height());
        }
    }
}
