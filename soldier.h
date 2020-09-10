#ifndef SOLDER_H
#define SOLDER_H

#include "enemy.h"

class Soldier : public Enemy
{
    Q_OBJECT
public:
    Soldier(int xpos, int ypos, QGraphicsItem *object, CustomScene *sceneP);
    void advance(int phase) override;
private:
    double bulletAngle = 0;
    QTimer *shootTimer;
    QTimer *dodgeTimer;
    int dodgeDirection = 0;
    void spriteChanger() override;
private slots:
    void shoot();
    void dodge();
    void changeDodgeDirection();
};

#endif // SOLDER_H
