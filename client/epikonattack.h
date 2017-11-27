#ifndef EPIKONATTACK_H
#define EPIKONATTACK_H

#include <QParallelAnimationGroup>
#include <QObject>

class EpikonPlanet;
class EpikonPlayer;
class EpikonShipItem;
class EpikonGameScene;

class EpikonAttack : public QParallelAnimationGroup
{
    Q_OBJECT
public:
    EpikonAttack(EpikonGameScene* scene, EpikonPlanet* from,
                 EpikonPlanet* to, EpikonPlayer* player, int numShips, QObject* parent= 0);
    int numShips(){return m_numships;};
    EpikonPlanet *toPlanet() {return m_to;};
    EpikonPlayer *fromPlayer() {return m_player;};
public slots:

private:
    EpikonShipItem * item;
    int m_numships;
    EpikonPlanet* m_to;
    EpikonPlayer* m_player;
};

#endif // EPIKONATTACK_H
