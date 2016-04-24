#include "player.h"
#include <QGraphicsScene>
#include <QPainter>
#include <QKeyEvent>
#include <QDebug>
#include <QGraphicsView>

Player::Player(QGraphicsItem *parent)
    :QGraphicsItem(parent)
{
    this->setData(0, "Player");
    this->setFlag(ItemIsFocusable);
    movementDirection = stop;
    previousDirection = stop;
}
QRectF Player::boundingRect() const
{
   int adjust = 1;

   return QRectF(-DIAMETR / 2 - adjust, -DIAMETR / 2 - adjust, DIAMETR + adjust, DIAMETR + adjust);
}
void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
           QWidget *widget)
{
    // Not using them
    (void)option;
    (void)widget;

    painter->setBrush(Qt::yellow);
    painter->drawEllipse(boundingRect());
}
void Player::advance(int step)
{
    if (!step)
    {
        checkCrash();
        return;
    }
    move();
}
void Player::keyPressEvent(QKeyEvent * event)
{
    switch (event->key())
    {
    case Qt::Key_Left:
        if (movementDirection != left)
        {
            previousDirection = movementDirection;
            movementDirection = left;
        }
        break;
    case Qt::Key_Right:
        if (movementDirection != right)
        {
            previousDirection = movementDirection;
            movementDirection = right;
        }
        break;
    case Qt::Key_Up:
        if (movementDirection != up)
        {
            previousDirection = movementDirection;
            movementDirection = up;
        }
        break;
    case Qt::Key_Down:
        if (movementDirection != down)
        {
            previousDirection = movementDirection;
            movementDirection = down;
        }
        break;
    };
}
void Player::move()
{
    if (movementDirection != stop)
    {
        switch (movementDirection)
        {
            case left:
                moveBy(-SPEED, 0);
                break;
            case right:
                moveBy(SPEED, 0);
                break;
            case up:
                moveBy(0, -SPEED);
                break;
            case down:
                moveBy(0, SPEED);
                break;
        };
        foreach (QGraphicsView *view, scene()->views()) {
            view->centerOn(this);
        }
    }
}
void Player::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Left:
        if (movementDirection == left)
            movementDirection = previousDirection;
        break;
    case Qt::Key_Right:
        if (movementDirection == right)
            movementDirection = previousDirection;
        break;
    case Qt::Key_Up:
        if (movementDirection == up)
            movementDirection = previousDirection;
        break;
    case Qt::Key_Down:
        if (movementDirection == down)
            movementDirection = previousDirection;
        break;
    };
    previousDirection = stop;
}
void Player::checkCrash()
{
    QList<QGraphicsItem *> items = collidingItems(Qt::IntersectsItemBoundingRect);
    QGraphicsItem *item;
    foreach (item, items)
    {
        if (item->data(0) == "Car")
        {
            emit crashed();
            break;
        }
    }
    items.clear();
}
void Player::setStop()
{

    movementDirection = stop;
}
Player::~Player()
{
}
