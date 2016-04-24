#ifndef ROAD_H
#define ROAD_H
#include "car.h"
#include <QGraphicsItem>
#include <QQueue>
#include <QList>
#include <QPointF>

class Road : public QGraphicsItem
{
    friend class Car;
public:
    enum Direction {right, left};
    Road(Direction trafficDirection = right, int trafficSpeed = 2, bool generateCars = true, QGraphicsItem *parent = 0);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    void addCar ();
    void addCar (Car *car);
    void setGenerateCars (bool generateCars);
    void randomizeSpeed();
    static int getLength();
    static int getWidth();
    ~Road();
protected:
    void advance(int step);
private:
    friend class Player;
    friend class RoadGroup;
    QQueue<Car *> traffic;
    static const int MAX_SPEED = 5;
    static const int MIN_SPEED = 2;
    qreal trafficSpeed;
    Direction trafficDirection;
    static const int LENGHT = 600;
    static const int WIDTH = Car::WIDTH + 20;
    static const int MIN_DISTANCE = 30;
    static const int MAX_DISTANCE = LENGHT / 2;
    int nextDistance;
    QPointF *start;
    bool generateCars;

    void moveTraffic();
    void generateDistance();
    void updateDistance();
};

#endif // ROAD_H
