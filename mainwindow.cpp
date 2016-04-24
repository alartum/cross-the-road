#include "mainwindow.h"
#include <QPainter>
#include <QTimer>
#include <QTime>

MainWindow::MainWindow(QObject *parent) :
    QGraphicsScene(parent)
{
//    setItemIndexMethod(QGraphicsScene::NoIndex);
    setBspTreeDepth(5);
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
    view = new MyView (this);
    timer = new QTimer(this);
    view->setRenderHint(QPainter::Antialiasing);
    level = new RoadGroup (ROADS_AMOUNT, RoadGroup::random);
    this->addItem(level);
    view->setSceneRect(level->mapRectToScene(level->boundingRect()));
    connect (timer, SIGNAL(timeout()),
                           this, SLOT(advance()));
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    level->getPlayer()->grabKeyboard();
    view->centerOn(level->getPlayer());
    connect(level, SIGNAL(levelFinished(bool)), this, SLOT (showMenu(bool)));
    connect(view, SIGNAL(restartNeeded()), this, SLOT(restart()));
}
void MainWindow::show()
{
    view->show();
}
void MainWindow::start()
{
    timer->start(UPDATE_FREQUENCY);
}
void MainWindow::stop()
{
    timer->stop();
}
MainWindow::~MainWindow()
{
    delete view;
    delete timer;
    delete level;
}
void MainWindow::restart()
{
    setForegroundBrush(Qt::NoBrush);
    view->hideInGameMenu();
    disconnect(level, SIGNAL(levelFinished(bool)), this, SLOT (showMenu(bool)));
    removeItem(level);
    delete level;
    level = new RoadGroup (ROADS_AMOUNT, RoadGroup::random);
    this->addItem(level);
    connect(level, SIGNAL(levelFinished(bool)), this, SLOT (showMenu(bool)));
    level->getPlayer()->grabKeyboard();
    view->centerOn(level->getPlayer());
    start();
}
void MainWindow::showMenu(bool success)
{
    stop();
    setForegroundBrush(QColor(0, 0, 0, 80));
    view->showInGameMenu(success);
}
