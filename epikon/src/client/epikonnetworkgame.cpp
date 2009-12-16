#include "epikonnetworkgame.h"
#include "epikonattack.h"
#include "epikonconnection.h"
#include "server/epikonprotocolcommand.h"

using namespace Epikon::Client;
using namespace Epikon::Protocol;

NetworkGame::NetworkGame(Connection *connection, QObject *parent) :
    Game(parent), m_connection(connection)
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
    Attack attack;
    attack.setFromPlanet(from.id());
    attack.setToPlanet(to.id());
    attack.setToPlayer(player.id());
    m_connection->sendCommand(attack);
}
