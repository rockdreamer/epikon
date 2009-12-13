#include "epikongame.h"
#include <QList>
#include "epikongamescene.h"
#include "epikonattack.h"

using namespace Epikon::Client;
Game::Game(QObject *parent) :
        QObject(parent)
{
    m_planets=new QList<EpikonPlanet*>();
    m_players=new QList<EpikonPlayer*>();
}

void Game::addPlayer(EpikonPlayer* player, bool isMe)
{
    m_players->append(player);
    if (isMe){
        m_me = player;
    }
}

void Game::addPlanet(EpikonPlanet* planet)
{
    m_planets->append(planet);
}

void Game::attack(EpikonPlanet& from, EpikonPlanet& to, EpikonPlayer& player){
    if (from.remainingShips()<=1)
        return;
    EpikonGameScene * scene = qobject_cast<EpikonGameScene *>(sender());
    EpikonAttack *attack = new EpikonAttack(scene,
                                                &from,&to,
                                                &player, from.remainingShips()/2);
        from.shipsLeft(from.remainingShips()/2);
        connect(attack,SIGNAL(finished()),this,SLOT(onAttackFinished()));
        attack->start();

}

void Game::onAttackFinished(){
    EpikonAttack *attack = qobject_cast<EpikonAttack *>(sender());
    attack->toPlanet()->shipsLanded(attack->numShips(), attack->fromPlayer());
    attack->deleteLater();
}

