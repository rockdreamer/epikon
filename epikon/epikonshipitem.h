#ifndef EPIKONSHIPITEM_H
#define EPIKONSHIPITEM_H

#include <QObject>
#include <QGraphicsEllipseItem>

class EpikonPlayer;
class QGraphicsSimpleTextItem;

class EpikonShipItem : public QObject, public QGraphicsEllipseItem 
{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)

public:
    EpikonShipItem(int numships);
    void setMaster(EpikonPlayer* player);
    void setPos(QPointF pos){QGraphicsEllipseItem::setPos(pos);};
private:
        QGraphicsSimpleTextItem *ships;
};

#endif // EPIKONSHIPITEM_H
