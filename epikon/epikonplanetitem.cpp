#include "epikonplanetitem.h"
#include "epikonplanet.h"
#include "epikonplayer.h"
#include <QSvgRenderer>
#include <QBrush>
#include <QPen>

QSvgRenderer* EpikonPlanetItem::neutralRenderer=NULL;

EpikonPlanetItem::EpikonPlanetItem(EpikonPlanet* planet):m_planet(planet)
{
    Q_ASSERT(planet!=NULL);
    m_size=100;
    setPos(planet->x(),planet->y());
    setFlag(QGraphicsItem::ItemIsSelectable,true);

    planet->setItem(this);
    shipsremaining = new QGraphicsSimpleTextItem(QString::number(0),this);
    shipsremaining->setBrush(QBrush(Qt::white));
    rect = new QGraphicsEllipseItem(shipsremaining->boundingRect(),this);
    rect->setBrush(QBrush(Qt::black));
    shipsremaining->setParentItem(rect);
    if (neutralRenderer==NULL){
        neutralRenderer = new QSvgRenderer(QString(":/resources/common/earth-2.svg"));
    }

    if (planet->master()){
        setSharedRenderer(planet->master()->planetRenderer());
    } else {
        setSharedRenderer(neutralRenderer);
    }

    qreal mx = boundingRect().width();
    setScale(m_size/mx);
    rect->setScale(mx/m_size);

    setRemainingShips(planet->remainingShips());
}

void EpikonPlanetItem::setRemainingShips(int i){
    shipsremaining->setText(QString::number(i));
    qreal maxdim=qMax(shipsremaining->boundingRect().width(),shipsremaining->boundingRect().height());
    rect->setRect(shipsremaining->boundingRect().x(),shipsremaining->boundingRect().y(),maxdim,maxdim);
    rect->setPos(m_size/2, m_size/2);
    shipsremaining->setPos(2,0);
}

void EpikonPlanetItem::setMaster(EpikonPlayer* i){
    setSharedRenderer(i->planetRenderer());
    qreal mx = boundingRect().width();
    rect->setPos((m_size-rect->boundingRect().width())/2-3,(m_size-rect->boundingRect().height())/2-3);
    setScale(m_size/mx);

}
