#include "myview.h"

MyView::MyView(QGraphicsScene *scene, QWidget *parent) :
    QGraphicsView(scene, parent)
{
    inGameMenu = new Menu (this);
    connect(inGameMenu, SIGNAL(restartPressed()), this, SLOT(restartPressed()));
    inGameMenu->hide();
}
void MyView::resizeEvent(QResizeEvent * event)
{
    // Not using this
    (void)event;

    this->fitInView(this->sceneRect(), Qt::KeepAspectRatioByExpanding);
    this->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
}
void MyView::wheelEvent(QWheelEvent *event)
{
    // Just do nothing
    // Not using this
    (void)event;
}
MyView::~MyView()
{
}
void MyView::restartPressed()
{
    emit restartNeeded();
}
void MyView::showInGameMenu(bool success)
{
    inGameMenu->move((width() - inGameMenu->width()) / 2, (height() - inGameMenu->height()) / 2);
    inGameMenu->changeMessage(success);
    inGameMenu->show();
}
void MyView::hideInGameMenu()
{
    inGameMenu->hide();
}
