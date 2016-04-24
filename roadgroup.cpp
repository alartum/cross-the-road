#include "roadgroup.h"
#include <QTime>
#include <QPainter>
#include <QBrush>
#include <QGraphicsScene>

RoadGroup::RoadGroup(int roadsCount, Generation generationType, QGraphicsItem *parent) :
    QGraphicsItem(parent)
{
    player = new Player (this);
    this->roadsCount = roadsCount;
    this->generationType = generationType;
    for (int i = 0; i < roadsCount; i ++)
    {
        Road *road;
        switch (generationType)
        {
        case interchangable:
            if (i % 2)
                road = new Road(Road::left, 2, true, this);
            else
                road = new Road(Road::right, 2, true, this);
            break;
        case random:
            if (qrand() % 2)
                road = new Road(Road::right, 2, true, this);
            else
                road = new Road(Road::left, 2, true, this);
            break;
        case left:
            road = new Road(Road::left, 2, true, this);
            break;
        case right:
            road = new Road(Road::right, 2, true, this);
            break;
        }
        roads.append (road);
        road->setPos(0, Road::WIDTH * (roadsCount - i) - Road::WIDTH / 2);
        road->stackBefore(player);
        road->randomizeSpeed();
    }
    player->setPos(0, Road::WIDTH * roadsCount + AREA_WIDTH / 2 + 5);
    setData(0, "RoadGroup");
    finish = new QLineF (-Road::LENGHT / 2, -AREA_WIDTH / 3 , Road::LENGHT / 2, -AREA_WIDTH / 2);
    border = new QRectF (-Road::LENGHT / 2, -AREA_WIDTH, Road::LENGHT, Road::WIDTH * roadsCount + 2 * AREA_WIDTH);
    connect(player, SIGNAL(crashed()), this, SLOT(levelFailed()));
}
void RoadGroup::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                      QWidget *widget)
{
    painter->setBrush(Qt::NoBrush);
    painter->setBrush(Qt::darkGreen);
    painter->drawRect(-Road::LENGHT / 2, - AREA_WIDTH, Road::LENGHT, AREA_WIDTH);
    painter->drawRect(-Road::LENGHT / 2, Road::WIDTH * roadsCount, Road::LENGHT, AREA_WIDTH);
}
QRectF RoadGroup::boundingRect() const
{
    int adjust = 0;
    return QRectF (-Road::LENGHT / 2 - adjust, -adjust - AREA_WIDTH,
                   Road::LENGHT + adjust, Road::WIDTH * roadsCount + adjust + 2 * AREA_WIDTH);
}
void RoadGroup::advance(int step)
{
    if (!step)
        return;
    checkBorder();
    checkFinish();
}
Player* RoadGroup::getPlayer()
{
    return this->player;
}
void RoadGroup::levelFailed()
{
    emit levelFinished(false);
}
RoadGroup::~RoadGroup()
{
    qDeleteAll (roads);
    roads.clear();
    delete player;
}
void RoadGroup::checkFinish()
{
    if (player->y() < -AREA_WIDTH / 3)
        emit levelFinished(true);
}
void RoadGroup::checkBorder()
{
    if (player->x() < boundingRect().left() + Player::DIAMETR / 2)
    {
        player->setPos(boundingRect().left() + Player::DIAMETR / 2, player->y());
        player->setStop();
    }
    if (player->x() > boundingRect().right() - Player::DIAMETR / 2)
    {
        player->setPos(boundingRect().right() - Player::DIAMETR / 2, player->y());
        player->setStop();
    }
    if (player->y() > boundingRect().bottom() - Player::DIAMETR / 2)
    {
        player->setPos(player->x(), boundingRect().bottom() - Player::DIAMETR / 2);
        player->setStop();
    }
    if (player->y() < boundingRect().top() + Player::DIAMETR / 2)
    {
        player->setPos(player->x(), boundingRect().top() + Player::DIAMETR / 2);
        player->setStop();
    }
}
