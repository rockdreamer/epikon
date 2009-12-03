#ifndef EPIKONPLANETITEM_H
#define EPIKONPLANETITEM_H

#include <QGraphicsSvgItem>

class EpikonPlanet;
class EpikonPlayer;
class QGraphicsSimpleTextItem;
class QSvgRenderer;
class QGraphicsRectItem;
class QGraphicsEllipseItem;

class EpikonPlanetItem : public QGraphicsSvgItem
{
public:
    EpikonPlanetItem(EpikonPlanet* planet);
    void setRemainingShips(int i);
    void setMaster(EpikonPlayer* player);
    EpikonPlanet* planet(){return m_planet;}
private:
    EpikonPlanet* m_planet;
    QGraphicsSimpleTextItem *shipsremaining;
    static QSvgRenderer* neutralRenderer;
    QGraphicsEllipseItem *rect;
    qreal m_size;
};

#endif // EPIKONPLANETITEM_H
