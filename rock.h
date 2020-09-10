#ifndef ROCK_H
#define ROCK_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>
#include <QGraphicsScene>

class Rock : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Rock(double xpos, double ypos, int width_p, int height_p);
    int type() const;
    enum {Type = UserType + 5};
    void advance(int phase);
private:
    int width = 0;
    int height = 0;
};

#endif // ROCK_H
