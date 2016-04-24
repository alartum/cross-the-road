#include "car.h"

#include <QPainter>

Car::Car(Direction movement, qreal speed, QGraphicsItem *parent) :
    QGraphicsItem (parent),
    color(qrand() % 256, qrand() % 256, qrand() % 256)
{
    this->speed = speed;
    this->setData(0, "Car");
    this->movement = movement;
    distanceDone = 0;
}
void Car::setColor(QColor color)
{
    this->color = color;
}
QColor Car::getColor()
{
    return this->color;
}
void Car::setSpeed(qreal speed)
{
    this->speed = speed;
}
qreal Car::getSpeed()
{
    return this->speed;
}
QRectF Car::boundingRect() const
{
    qreal adjust = 3;
    return QRectF(-LENGTH / 2 - adjust, -WIDTH / 2 - adjust,
        LENGTH + adjust, WIDTH + adjust);
}
void Car::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
           QWidget *widget)
{
    painter->setBrush(color.darker(300));
    painter->drawRect(-LENGTH / 2 - 1, -WIDTH / 2 - 1, LENGTH + 1, WIDTH + 1);
    painter->setBrush(color);
    painter->drawRect(-LENGTH / 2, -WIDTH / 2, LENGTH, WIDTH);
    painter->setBrush(color.darker(150));
    painter->drawRect(-LENGTH / 3 - 2, -WIDTH / 3 - 2, LENGTH * 2 / 3 - 10, WIDTH * 2 / 3 + 4);
    painter->setBrush(QBrush(QColor (173, 216, 230, 200)));
    painter->drawRect(LENGTH / 4 - 4, -WIDTH / 3 - 2, LENGTH / 6, WIDTH * 2 / 3 + 4);
    if (movement == left)
        setRotation(-180);
}
void Car::advance(int step)
{
    if (!step)
        return;
    move();
}
int Car::getLength()
{
    return LENGTH;
}
int Car::getWidth()
{
    return WIDTH;
}
void Car::move()
{
    if (movement == right)
        moveBy(speed, 0);
    else
        moveBy(-speed, 0);
    distanceDone += speed;
}
Car::~Car()
{
}
