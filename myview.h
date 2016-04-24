#ifndef MYVIEW_H
#define MYVIEW_H

#include <QGraphicsView>
#include "player.h"
#include "menu.h"

class MyView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit MyView(QGraphicsScene * scene, QWidget * parent = 0);
    ~MyView();
    void showInGameMenu(bool success);
    void hideInGameMenu();
protected:
    void resizeEvent(QResizeEvent * event);
    void wheelEvent(QWheelEvent *event);
private:
    Menu *inGameMenu;
signals:
    void restartNeeded();
private slots:
    void restartPressed();
};

#endif // MYVIEW_H
