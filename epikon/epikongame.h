#ifndef EPIKONGAME_H
#define EPIKONGAME_H

#include <QObject>
#include <QtContainerFwd>

#include "epikonplanet.h"
#include "epikonplayer.h"

class EpikonGame : public QObject
{
Q_OBJECT
public:
    explicit EpikonGame(QObject *parent = 0);
    void addPlayer(EpikonPlayer* player,bool isMe=false);
    void addPlanet(EpikonPlanet* planet);
    EpikonPlayer* me(){return m_me;};
    QList<EpikonPlayer*> *players(){return m_players;};
    QList<EpikonPlanet*> *planets(){return m_planets;};
private:
    QList<EpikonPlayer*> *m_players;
    QList<EpikonPlanet*> *m_planets;
    EpikonPlayer* m_me;
};

#endif // EPIKONGAME_H
