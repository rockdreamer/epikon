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
public slots:
    void onFinished();
private:
    EpikonShipItem * item;
    int numShips;
    EpikonPlanet* m_to;
    EpikonPlayer* m_player;
};

#endif // EPIKONATTACK_H
