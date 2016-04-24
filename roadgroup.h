#ifndef ROADGROUP_H
#define ROADGROUP_H

#include <QGraphicsItem>
#include <QObject>
#include <QVector>
#include "road.h"
#include "player.h"

class RoadGroup : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    enum Generation {interchangable, random, left, right};
    explicit RoadGroup(int roadsCount = 1, Generation generationType = interchangable, QGraphicsItem *parent = 0);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    Player* getPlayer();
    ~RoadGroup();
protected:
    void advance(int step);
private:
    int roadsCount;
    QVector<Road *> roads;
    Generation generationType;
    Player *player;
    static const int AREA_WIDTH = 2 * Player::DIAMETR;
    QRectF *border;
    QLineF *finish;

    void checkFinish();
    void checkBorder();
signals:
    void playerAtFinish();
    void levelFinished (bool success);
private slots:
    void levelFailed();
};

#endif // ROADGROUP_H
