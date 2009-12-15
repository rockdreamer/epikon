#include "epikonnetworkgame.h"
#include "epikonattack.h"
#include "epikonconnection.h"

using namespace Epikon::Client;

NetworkGame::NetworkGame(QObject *parent) :
    Game(parent)
{

}
void NetworkGame::onNetAttack(quint16 fromPlanet, quint16 toPlanet, quint16 player, quint16 numShips, quint16 lag){

EpikonAttack *attack = new EpikonAttack(m_scene,
                                            planets()->at(fromPlanet),planets()->at(toPlanet),
                                            players()->at(player), numShips);
    planets()->at(fromPlanet)->shipsLeft(numShips);
    connect(attack,SIGNAL(finished()),this,SLOT(onAttackFinished()));
    attack->start();
}

void NetworkGame::attack(EpikonPlanet& from, EpikonPlanet& to, EpikonPlayer& player){
    if (from.remainingShips()<=1)
        return;

}
