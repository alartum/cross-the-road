#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsItem>
#include "road.h"

class Player : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    Player(QGraphicsItem *parent = 0);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    void move();
    void setStop();
    ~Player();
protected:
    void advance(int step);
    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent *event);
private:
    friend class RoadGroup;
    static const qreal SPEED = Road::MAX_SPEED / 1.5;
    enum Direction {up, down, left, right, stop};
    Direction movementDirection;
    Direction previousDirection;
    void checkCrash();
    static const int DIAMETR = 25;
signals:
    void crashed();
};

#endif // PLAYER_H
