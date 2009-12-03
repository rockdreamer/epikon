#include "epikonshipitem.h"
#include "epikonplayer.h"
#include <QGraphicsSimpleTextItem>

EpikonShipItem::EpikonShipItem(int numships):
      QObject(),QGraphicsEllipseItem()
{
    setRect(0,0,5,5);
    QGraphicsSimpleTextItem *txt = new QGraphicsSimpleTextItem(QString::number(numships),this);
}

void EpikonShipItem::setMaster(EpikonPlayer* i){
}
