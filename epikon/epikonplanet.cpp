#include "epikonplanet.h"
#include "epikonplanetitem.h"
#include "epikonplayer.h"
#include <QDebug>

EpikonPlanet::EpikonPlanet(QObject *parent):
    QObject(parent),m_item(0)
{
}

EpikonPlanet::EpikonPlanet ( const QPoint & topLeft, const QPoint & bottomRight,QObject *parent) :
QObject(parent),QRect(topLeft,bottomRight),m_name("Anonymous Planet"),m_remainingShips(0),m_master(0),m_item(0)
{
}

EpikonPlanet::EpikonPlanet ( const QPoint & topLeft, const QSize & size,QObject *parent) :
        QObject(parent),QRect(topLeft,size),m_name("Anonymous Planet"),m_remainingShips(0),m_master(0),m_item(0)
{
}

EpikonPlanet::EpikonPlanet ( int x, int y, int width, int height,QObject *parent ) :
        QObject(parent),QRect(x,y,width,height),m_name("Anonymous Planet"),m_remainingShips(0),m_master(0),m_item(0)
{
}

void EpikonPlanet::shipsCreated(int numShips){
    if (m_master!=NULL){
        m_master->generatedShips(numShips);
    }
    m_remainingShips=m_remainingShips+numShips;
    if (m_item)m_item->setRemainingShips(m_remainingShips);
}

void EpikonPlanet::shipsLeft(int numShips){
    m_remainingShips=m_remainingShips-numShips;
    if (m_item)m_item->setRemainingShips(m_remainingShips);
    qDebug() << "Planet " << m_name << ": " << numShips << " are leaving " << m_remainingShips << " left";
}

void EpikonPlanet::shipsLanded(int numShips, EpikonPlayer* fromplayer){
    qDebug() << "Planet " << m_name << ": " << numShips << " landed from player " << fromplayer->name();

    if (m_master == fromplayer){
        //reinforcements arrived
        m_remainingShips = m_remainingShips+numShips;
        m_item->setRemainingShips(m_remainingShips);
        qDebug() << "Planet " << m_name << " now has " << m_remainingShips;
        return;
    }

    if (m_remainingShips>numShips){
        // We didn't lose the planet but we all got hurt, war can be like that..
        fromplayer->lostShips(numShips);
        if (m_master!=NULL){
            m_master->lostShips(numShips);
        }
        m_remainingShips = m_remainingShips-numShips;
        qDebug() << "Planet " << m_name << " lost some, now has " << m_remainingShips;
    } else {
        // we lost the planet
        fromplayer->lostShips(m_remainingShips);
        if (m_master!=NULL){
            m_master->lostPlanet(this);
            m_master->lostShips(m_remainingShips);
            qDebug() << "Planet " << m_name << " was lost";
        }

        m_remainingShips = numShips-m_remainingShips;
        if (m_remainingShips>0){
            // He won
            m_master= fromplayer;
            m_master->capturedPlanet(this);
            m_item->setMaster(m_master);
            qDebug() << "Planet " << m_name << " now belongs to " << m_master->name() << " " << m_remainingShips << " ships remain";
        } else {
            m_master=NULL;
            m_item->setMaster(m_master);
            qDebug() << "Planet " << m_name << " is neutral";
        }

    }
    m_item->setRemainingShips(m_remainingShips);
}
