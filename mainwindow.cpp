#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    sceneGame = new CustomScene();
    sceneGame->shootTimer = new QTimer(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::enemySpawner()
{
    srand(static_cast<unsigned int>(time(nullptr)));
    switch(int who = rand()%4)
    {
        case 0:
        if(who%3)
            sceneGame->addItem(new Soldier(100, 100, gg, sceneGame));
        else
            sceneGame->addItem(new Zombie(100, 100, gg, sceneGame));
        break;
        case 1:
        if(who%3)
            sceneGame->addItem(new Soldier(sceneGame->width()-100, 100, gg, sceneGame));
        else
            sceneGame->addItem(new Zombie(sceneGame->width()-100, 100, gg, sceneGame));
        break;
        case 2:
        if(who%3)
            sceneGame->addItem(new Soldier(100, sceneGame->height()-100, gg, sceneGame));
        else
            sceneGame->addItem(new Zombie(100, sceneGame->height()-100, gg, sceneGame));
        break;
        case 3:
        if(who%3)
            sceneGame->addItem(new Soldier(sceneGame->width()-100, sceneGame->height()-100, gg, sceneGame));
        else
            sceneGame->addItem(new Zombie(sceneGame->width()-100, sceneGame->height()-100, gg, sceneGame));
        break;
        default:
        break;
    }
}

void MainWindow::currentScore()
{
    ui->scoreLabel->setNum(++scoreCounter);
    if(scoreCounter == 5)
        sceneGame->addItem(new PriWeapon(500,200));
}

void MainWindow::currentHealth()
{
    ui->healthLabel->setNum(gg->getHealth());
}

void MainWindow::currentWeapon()
{
    switch(gg->getWeaponNumber())
    {
        case 1:
        ui->weaponLabel->setPixmap(QPixmap(":/images/ak47White.png"));
        break;
        case 2:
        ui->weaponLabel->setPixmap(QPixmap(":/images/pistolWhite.png"));
        break;
    }
}

void MainWindow::currentAmmo()
{
    if(gg->getWeaponNumber() == 2)
        ui->ammoLabel->setText("∞");
    else
        ui->ammoLabel->setNum(gg->getAmmo());
}

void MainWindow::on_pushButton_clicked()
{
    ui->pushButton->hide();
    ui->pushButton_2->hide();



    ui->graphicsView->setScene(sceneGame);
    sceneGame->setSceneRect(0, 0, ui->graphicsView->width(), ui->graphicsView->height());
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    sceneGame->setStickyFocus(true);
    ui->graphicsView->setMouseTracking(true);
    ui->graphicsView->setBackgroundBrush(QImage(":/images/bg1.png"));
    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground);

    sceneGame->addItem(new SecWeapon(700,200));

    sceneGame->addItem(gg = new Roflan(sceneGame->width()+200, sceneGame->height()-100));
    connect(sceneGame, &CustomScene::signalTargetCoordinate, gg, &Roflan::slotTarget);
    connect(sceneGame->shootTimer, &QTimer::timeout, gg, &Roflan::shoot);
    connect(gg, &Roflan::signalWeaponChanged, this, &MainWindow::currentWeapon);

    animationTimer = new QTimer(this);
    connect(animationTimer, &QTimer::timeout, sceneGame, &CustomScene::advance);
    animationTimer->start(1000/60);

    spawnTimer = new QTimer(this);
    connect(spawnTimer, &QTimer::timeout, this, &MainWindow::enemySpawner);
    spawnTimer->start(4000);

    connect(sceneGame, &CustomScene::signaScorePlus, this, &MainWindow::currentScore);
    ui->scoreLabel->setNum(scoreCounter);

    connect(gg, &Roflan::signalHealth, this, &MainWindow::currentHealth);
    ui->healthLabel->setNum(gg->getHealth());

    connect(gg, &Roflan::signalAmmo, this, &MainWindow::currentAmmo);
    ui->ammoLabel->setText("");



    sceneGame->addItem(new AidKit(QPointF(150, 150)));
    sceneGame->addItem(new Ammo(QPointF(150, 300)));

    sceneGame->addItem(new Rock(-40, -100, 2000, 50));
    sceneGame->addItem(new Rock(-40, sceneGame->height()+50, 2000, 50));
    sceneGame->addItem(new Rock(-100, -10, 50, 1100));
    sceneGame->addItem(new Rock(sceneGame->width()+50, -10, 50, 1100));

    sceneGame->addItem(new Rock(966, 200, 150, 50));
    sceneGame->addItem(new Rock(250, 200, 150, 50));
    sceneGame->addItem(new Rock(966, 450, 150, 50));
    sceneGame->addItem(new Rock(250, 450, 150, 50));
    sceneGame->addItem(new Rock(658, 284, 50, 150));
}

void MainWindow::on_pushButton_2_clicked()
{
    QApplication::quit();
}

