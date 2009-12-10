#include "epikonshipitem.h"
#include "epikonplayer.h"
#include <QGraphicsSimpleTextItem>
#include <QGraphicsEllipseItem>
#include <QSvgRenderer>
#include <QBrush>
#include <QPen>
#include <QDebug>

QSvgRenderer* EpikonShipItem::neutralRenderer=NULL;

EpikonShipItem::EpikonShipItem(int numships):
     QGraphicsSvgItem()
{
    if (neutralRenderer==NULL){
        neutralRenderer = new QSvgRenderer(QString(":/resources/common/rocket.svg"));
    }
    setSharedRenderer(neutralRenderer);
    m_svgsize = neutralRenderer->defaultSize().width();
    QGraphicsSimpleTextItem *txt = new QGraphicsSimpleTextItem(QString::number(numships));
    QGraphicsEllipseItem* rect = new QGraphicsEllipseItem(txt->boundingRect(),this);
    rect->setBrush(QBrush(Qt::darkBlue));
    rect->setPen(QPen(Qt::black));
    txt->setParentItem(rect);
    txt->setPen(QPen(Qt::yellow));
    rect->setPos(40,70);
    qreal inner=5;
    qreal maxdim=qMax(txt->boundingRect().width(),txt->boundingRect().height());
    rect->setRect(0,0,maxdim+inner,maxdim+inner);
    txt->setPos((maxdim-txt->boundingRect().width()+inner)/2,(maxdim-txt->boundingRect().height()+inner)/2);
}

void EpikonShipItem::setMaster(EpikonPlayer* i){
}
