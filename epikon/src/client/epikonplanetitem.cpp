#include "epikonplanetitem.h"
#include "epikonplanet.h"
#include "epikonplayer.h"
#include <QSvgRenderer>
#include <QBrush>
#include <QPen>
#include <QDebug>
QSvgRenderer* EpikonPlanetItem::neutralRenderer=NULL;

EpikonPlanetItem::EpikonPlanetItem(EpikonPlanet* planet):m_planet(planet)
{
    Q_ASSERT(planet!=NULL);
    m_size=planet->size().width();
    qDebug() << "EpikonPlanetItem " << this << " m_size="<<m_size;
    setPos(planet->x(),planet->y());
    setFlag(QGraphicsItem::ItemIsSelectable,true);

    planet->setItem(this);
    shipsremaining = new QGraphicsSimpleTextItem(QString::number(0),this);
    shipsremaining->setBrush(QBrush(Qt::white));
    rect = new QGraphicsEllipseItem(shipsremaining->boundingRect(),this);
    rect->setBrush(QBrush(Qt::black));
    rect->setPen(QPen(Qt::white));
    shipsremaining->setParentItem(rect);
    if (neutralRenderer==NULL){
        neutralRenderer = new QSvgRenderer(QString(":/resources/common/earth-2.svg"));
    }

    if (planet->master()){
        setSharedRenderer(planet->master()->planetRenderer());
        m_svgsize = planet->master()->planetRenderer()->defaultSize().width();
    } else {
        setSharedRenderer(neutralRenderer);
        m_svgsize = neutralRenderer->defaultSize().width();
    }

    qDebug() << "EpikonPlanetItem " << this << " svg width="<<m_svgsize << " scaling by " << m_size/m_svgsize;
    shipsremaining->setText(QString::number(0));
    qreal maxdim=qMax(shipsremaining->boundingRect().width(),shipsremaining->boundingRect().height());
    rect->setPos((m_svgsize-rect->rect().width())/2, (m_svgsize-rect->rect().height())/2);
    setScale(m_size/m_svgsize);
    rect->setScale(m_svgsize/m_size);

    setRemainingShips(planet->remainingShips());
}

void EpikonPlanetItem::setRemainingShips(int i){
    qreal inner=5;
    shipsremaining->setText(QString::number(i));
    qreal maxdim=qMax(shipsremaining->boundingRect().width(),shipsremaining->boundingRect().height());
    rect->setRect(0,0,maxdim+inner,maxdim+inner);
    shipsremaining->setPos((maxdim-shipsremaining->boundingRect().width()+inner)/2,(maxdim-shipsremaining->boundingRect().height()+inner)/2);
}

void EpikonPlanetItem::setMaster(EpikonPlayer* i){
    QSvgRenderer *m_renderer;
    if (i != NULL){
        m_renderer=i->planetRenderer();
    } else {
        m_renderer = neutralRenderer;
   }
    setSharedRenderer(m_renderer);
    m_svgsize = m_renderer->defaultSize().width();
    setScale(m_size/m_svgsize);
    rect->setPos((m_svgsize-shipsremaining->boundingRect().width())/2, (m_svgsize-shipsremaining->boundingRect().height())/2);
    rect->setScale(m_svgsize/m_size);
}
