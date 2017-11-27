#ifndef EPIKONPLANET_H
#define EPIKONPLANET_H

#include <QObject>
#include <QRect>

class EpikonPlayer;
class EpikonPlanetItem;
class EpikonPlanet : public QObject, public QRect
{
Q_OBJECT
Q_PROPERTY(int remainingShips READ remainingShips WRITE setRemainingShips)
Q_PROPERTY(QString name READ name WRITE setName)

public:
    explicit EpikonPlanet(QObject *parent = 0);
    explicit EpikonPlanet ( const QPoint & topLeft, const QPoint & bottomRight,QObject *parent = 0 );
    explicit EpikonPlanet ( const QPoint & topLeft, const QSize & size,QObject *parent = 0 );
    explicit EpikonPlanet ( int x, int y, int width, int height,QObject *parent = 0 );

    quint16 id(){return m_id;};
    void setId(quint16 id){m_id=id;};

    QString name() {return m_name;};
    void setName(const QString& in) {m_name=in;};

    int remainingShips() {return m_remainingShips;};
    void setRemainingShips(int in) {m_remainingShips=in;};

    EpikonPlayer* master() {return m_master;};
    void setMaster(EpikonPlayer* in) {m_master=in;};

    EpikonPlanetItem* item() {return m_item;};
    void setItem(EpikonPlanetItem* item) {m_item=item;};
signals:

public slots:
    void shipsLanded(int numShips, EpikonPlayer* fromplayer);
    void shipsCreated(int numShips);
    void shipsLeft(int numShips);

private:
    QString m_name;
    int m_remainingShips;
    quint16 m_id;
    EpikonPlayer *m_master;
    EpikonPlanetItem *m_item;
};

#endif // EPIKONPLANET_H
