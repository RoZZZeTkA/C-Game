#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "customscene.h"
#include "roflan.h"
#include "weapon.h"
#include "bullet.h"
#include "rock.h"
#include "zombie.h"
#include "soldier.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    CustomScene *sceneGame;
    Roflan *gg;
    QTimer *animationTimer;
    QTimer *spawnTimer;
    int scoreCounter = 0;
    void currentScore();
    void currentHealth();
    void currentWeapon();
    void currentAmmo();
    void enemySpawner();
};

#endif // MAINWINDOW_H
