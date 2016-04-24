#ifndef CAR_H
#define CAR_H
#include <QDebug>
#include <QGraphicsItem>

class Car : public QGraphicsItem
{
public:
    enum Direction {left, right};
    explicit Car(Direction movement = right, qreal speed = 0, QGraphicsItem *parent = 0);
    void setColor (QColor color);
    void setSpeed (qreal speed);
    QColor getColor ();
    qreal getSpeed ();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    static int getLength();
    static int getWidth();
    ~Car();
protected:
    void advance(int step);
private:
    friend class Road;
    qreal speed;
    QColor color;
    static const int LENGTH = 100;
    static const int WIDTH = 50;
    Direction movement;
    qreal distanceDone;

    void move();
};

#endif // CAR_H
