#include "epikongame.h"
#include <QList>

EpikonGame::EpikonGame(QObject *parent) :
        QObject(parent)
{
    m_planets=new QList<EpikonPlanet*>();
    m_players=new QList<EpikonPlayer*>();
}

void EpikonGame::addPlayer(EpikonPlayer* player, bool isMe)
{
    m_players->append(player);
    if (isMe){
        m_me = player;
    }
}

void EpikonGame::addPlanet(EpikonPlanet* planet)
{
    m_planets->append(planet);
}
