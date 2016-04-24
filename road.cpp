#include "road.h"
#include <QPainter>
#include <QTime>
#include <QGraphicsScene>

Road::Road(Direction trafficDirection, int trafficSpeed, bool generateCars, QGraphicsItem *parent)
    : QGraphicsItem (parent)
{
    this->generateCars = generateCars;
    this->trafficDirection = trafficDirection;
    this->trafficSpeed = trafficSpeed;
    if (trafficDirection == right)
    {
        start = new QPointF (-(LENGHT + Car::getLength()) / 2, 0);
    }
    else
    {
        start = new QPointF ((LENGHT + Car::getLength()) / 2, 0);
    }
    this->nextDistance = 0;
    this->setData(0, "Road");
    setCacheMode(QGraphicsItem::ItemCoordinateCache);
}
QRectF Road::boundingRect() const
{
    qreal adjust = 0.5;
    return QRectF (-LENGHT / 2 - adjust, -WIDTH / 2 - adjust,
                   LENGHT + adjust, WIDTH + adjust);
}
void Road::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
           QWidget *widget)
{
    painter->setBrush(Qt::darkGray);
    QPen *pen = new QPen;
    painter->drawRect(-LENGHT / 2, -WIDTH / 2, LENGHT, WIDTH);
    pen->setColor(Qt::white);
    pen->setWidth(3);
    pen->setStyle(Qt::SolidLine);
    painter->setPen(*pen);
    painter->drawLine(-LENGHT / 2, -WIDTH / 2, LENGHT / 2, -WIDTH / 2);
    painter->drawLine(-LENGHT / 2, WIDTH / 2, LENGHT / 2, WIDTH / 2);
    delete pen;
}
void Road::advance(int step)
{
    if (!step)
        return;
    if (generateCars)
        addCar();
    updateDistance();
    moveTraffic();
}
void Road::addCar()
{
    if (nextDistance <= 0)
    {
        Car *car;
        if (trafficDirection == right)
            car = new Car(Car::right, trafficSpeed, this);
        else
            car = new Car(Car::left, trafficSpeed, this);
        traffic.enqueue(car);
        car->setPos(*start);
        generateDistance();
    }
}
Road::~Road ()
{
    qDeleteAll (traffic);
    traffic.clear();
    delete start;
}
void Road::moveTraffic()
{
    if (traffic.isEmpty())
        return;
    else
        if (traffic.head()->distanceDone > Car::LENGTH + Road::LENGHT)
        {
            scene()->removeItem(traffic.head());
            delete traffic.dequeue();
        }
}
void Road::generateDistance()
{
    nextDistance = MIN_DISTANCE + qrand() % (MAX_DISTANCE - MIN_DISTANCE) + Car::LENGTH;
}
int Road::getLength()
{
    return LENGHT;
}
int Road::getWidth()
{
    return WIDTH;
}
void Road::setGenerateCars(bool generateCars)
{
    this->generateCars = generateCars;
}
void Road::randomizeSpeed()
{
    trafficSpeed = MIN_SPEED + qrand() % (MAX_SPEED - MIN_SPEED);
}
void Road::updateDistance()
{
    nextDistance -= trafficSpeed;
}
