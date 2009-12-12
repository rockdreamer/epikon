#include "epikongamescene.h"
#include "epikongame.h"
#include "epikonplanet.h"
#include "epikonplanetitem.h"
#include "epikonattack.h"


EpikonGameScene::EpikonGameScene(QObject *parent) :
    QGraphicsScene(parent),m_game(0)
{
    connect(this,SIGNAL(selectionChanged()),this,SLOT(onSelectionChange()));
}

void EpikonGameScene::setGame(EpikonGame *game)
{
    m_game=game;
    clear();
    drawInitialScene();
}

void EpikonGameScene::drawInitialScene(){
    QList<EpikonPlanet*> *planets = m_game->planets();
    for (int i = 0; i < planets->size(); ++i) {
         EpikonPlanet* p = planets->at(i);
         EpikonPlanetItem *e = new EpikonPlanetItem(p);
         addItem(e);
     }
}

void EpikonGameScene::onSelectionChange(){
    currentSelection= selectedItems();
    // nothing was selected
    if (currentSelection.size()==0){
        previousSelection=currentSelection;
        return;
    }
    // many planets were selected, we memorize this
    if (currentSelection.size()>1){
        previousSelection=currentSelection;
        return;
    }
    // Brace for impact, we have an attack
    EpikonPlanetItem* from;
    EpikonPlanetItem* to = (EpikonPlanetItem*)currentSelection.at(0);
    for (int i=0;i<previousSelection.size();i++){
        from = (EpikonPlanetItem*)previousSelection.at(i);
        EpikonAttack *attack = new EpikonAttack(this,
                                                from->planet(),to->planet(),
                                                m_game->me(),from->planet()->remainingShips()/2);
        from->planet()->shipsLeft(from->planet()->remainingShips()/2);
        attack->start();
    }
    previousSelection=currentSelection;
}
