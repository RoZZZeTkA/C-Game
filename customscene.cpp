#include "customscene.h"
#include "roflan.h"

CustomScene::CustomScene(QObject *parent) :
    QGraphicsScene()
{
    Q_UNUSED(parent);
    zombiePlaylist = new QMediaPlaylist(zombiePlayer);
    zombiePlaylist->setPlaybackMode(QMediaPlaylist::Random);
    zombiePlaylist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
    zombiePlaylist->addMedia(QUrl("qrc:/sounds/zombieDies.mp3"));
    soldierPlaylist = new QMediaPlaylist(zombiePlayer);
    soldierPlaylist->setPlaybackMode(QMediaPlaylist::Random);
    soldierPlaylist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
    soldierPlaylist->addMedia(QUrl("qrc:/sounds/soldierDies.mp3"));
}

void CustomScene::deleteZombie(QGraphicsItem *zombie)
{
    zombiePlayer = new QMediaPlayer(this);
    zombiePlayer->setPlaylist(zombiePlaylist);
    zombiePlayer->play();
    signaScorePlus();
    srand(static_cast<unsigned int>(time(nullptr)));
    if(rand()%7 == 3)
        this->addItem(new AidKit(QPointF(zombie->x(), zombie->y())));
}

void CustomScene::deleteSoldier(QGraphicsItem *soldier)
{
    soldierPlayer = new QMediaPlayer(this);
    soldierPlayer->setPlaylist(soldierPlaylist);
    soldierPlayer->play();
    signaScorePlus();
    srand(static_cast<unsigned int>(time(nullptr)));
    if(rand()%7 == 0)
        this->addItem(new Ammo(QPointF(soldier->x(), soldier->y())));
}

void CustomScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    signalTargetCoordinate(event->scenePos());
}

void CustomScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    shootTimer->start(1000/60);
}

void CustomScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    shootTimer->stop();
}
