#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "enemy.h"

class Zombie : public Enemy
{
    Q_OBJECT
public:
    Zombie(int xpos, int ypos, QGraphicsItem *object, CustomScene *sceneP);
    void advance(int phase) override;
    int type() const override;
    enum {Type = UserType + 8};
private:
    void spriteChanger() override;
};
#endif // ZOMBIE_H
