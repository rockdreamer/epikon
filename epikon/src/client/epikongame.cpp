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

void Game::testGame(){
    EpikonPlanet *pl1, *pl2,*pl3,*pl4;
    EpikonPlayer *p1, *p2;
    p1 = new EpikonPlayer(this);
    p1->setName("Player 1");
    p1->setPlanet(QString(":/resources/common/earth-4.svg"));

    this->addPlayer(p1,true);

    p2 = new EpikonPlayer(this);
    p2->setName("Player 2");
    p2->setPlanet(QString(":/resources/common/earth-3.svg"));
    this->addPlayer(p2);

    pl1 = new EpikonPlanet(10,10,100,100, this);
    pl1->setName("Test Planet 1");
    this->addPlanet(pl1);
    pl1->setMaster(p1);
    pl1->shipsCreated(10);

    pl2 = new EpikonPlanet(10,200,100,100, this);
    pl2->setName("Test Planet 2");
    this->addPlanet(pl2);
    pl2->setMaster(p1);
    pl2->shipsCreated(10);


    pl3 = new EpikonPlanet(300,200,100,100, this);
    pl3->setName("Test Planet 1 2");
    this->addPlanet(pl3);
    pl3->setMaster(p2);
    pl3->shipsCreated(10);

    pl4 = new EpikonPlanet(350,400,100,100, this);
    pl4->setName("Test Planet 2 2");
    this->addPlanet(pl4);
    pl4->setMaster(p2);
    pl4->shipsCreated(10);
}
