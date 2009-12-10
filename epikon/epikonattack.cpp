#include "epikonattack.h"
#include "epikonplanet.h"
#include "epikonplanetitem.h"
#include "epikonplayer.h"
#include "epikonshipitem.h"
#include "epikongamescene.h"
#include <QPropertyAnimation>
#include <QDebug>

EpikonAttack::EpikonAttack(EpikonGameScene* scene, EpikonPlanet* from,
                           EpikonPlanet* to, EpikonPlayer* player, int numShips, QObject* parent):
    QParallelAnimationGroup(parent), numShips(numShips),m_to(to),m_player(player)
{
    this->numShips=numShips;
    item = new EpikonShipItem(numShips);
    scene->addItem(item);
    QPropertyAnimation* anim;
    anim = new QPropertyAnimation(item,"pos");
    anim->setDuration(1000);
    QPointF pos =from->item()->pos();
    anim->setStartValue(pos);
    pos=to->item()->pos();
    anim->setEndValue(pos);
    anim->setEasingCurve(QEasingCurve::InBack);
    addAnimation(anim);

    connect(anim,SIGNAL(finished()),this,SLOT(onFinished()));
}

void EpikonAttack::onFinished(){
    m_to->shipsLanded(numShips, m_player);
}
