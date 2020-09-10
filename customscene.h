#ifndef CUSTOMSCENE_H
#define CUSTOMSCENE_H


#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QTimer>
#include <QMediaPlayer>
#include <QMediaPlaylist>

class CustomScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit CustomScene(QObject *parent = nullptr);
    QTimer *shootTimer;
    void deleteZombie(QGraphicsItem *zombie);
    void deleteSoldier(QGraphicsItem *soldier);
signals:
    void signalTargetCoordinate(QPointF point);
    void signaScorePlus();
    void signalPress();
    void signalRelease();
private:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    QMediaPlayer * zombiePlayer;
    QMediaPlaylist * zombiePlaylist;
    QMediaPlayer * soldierPlayer;
    QMediaPlaylist * soldierPlaylist;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // CUSTOMSCENE_H
