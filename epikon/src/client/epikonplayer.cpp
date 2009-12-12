#include "epikonplayer.h"
#include "epikonplanet.h"
#include <QSvgRenderer>
EpikonPlayer::EpikonPlayer(QObject *parent) :
        QObject(parent),m_name("Anonymous Coward"),m_remainingShips(0),m_remainingPlanets(0)
{
}

void EpikonPlayer::capturedPlanet(EpikonPlanet* planet){
    setRemainingPlanets(remainingPlanets()+1);

}

void EpikonPlayer::setPlanet(const QString& filename){
    m_planetrenderer = new QSvgRenderer(filename);
}

void EpikonPlayer::lostPlanet(EpikonPlanet* planet){
    setRemainingPlanets(remainingPlanets());
    if (remainingShips()<=0 && remainingPlanets()<=0){
        emit lost();
    }
}
void EpikonPlayer::generatedShips(int num){
    setRemainingShips(remainingShips()+num);
}
void EpikonPlayer::lostShips(int num){
    setRemainingShips(remainingShips()-num);
    if (remainingShips()<=0 && remainingPlanets()<=0){
        emit lost();
    }

}
