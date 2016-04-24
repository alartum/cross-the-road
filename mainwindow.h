#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include "roadgroup.h"
#include "myview.h"

class MainWindow : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit MainWindow(QObject *parent = 0);
    ~MainWindow();
    void show();
    void start();
    MyView *view;
private:
    QTimer *timer;
    RoadGroup *level;
    static const int UPDATE_FREQUENCY = 33;
    static const int ROADS_AMOUNT = 5;
private slots:
    void stop();
    void showMenu (bool success);
    void restart();
};

#endif // MAINWINDOW_H
