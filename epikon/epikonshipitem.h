#ifndef EPIKONSHIPITEM_H
#define EPIKONSHIPITEM_H

#include <QObject>
#include <QGraphicsSvgItem>

class EpikonPlayer;
class QGraphicsSimpleTextItem;

class EpikonShipItem : public QGraphicsSvgItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)

public:
    EpikonShipItem(int numships);
    void setMaster(EpikonPlayer* player);
    void setPos(QPointF pos){QGraphicsSvgItem::setPos(pos);};
private:
        QGraphicsSimpleTextItem *ships;
        static QSvgRenderer* neutralRenderer;
        qreal m_svgsize;

};

#endif // EPIKONSHIPITEM_H
