#include "epikonattack.h"
#include "epikonplanet.h"
#include "epikonplanetitem.h"
#include "epikonplayer.h"
#include "epikonshipitem.h"
#include "epikongamescene.h"
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QDebug>
#include <cmath>
EpikonAttack::EpikonAttack(EpikonGameScene* scene, EpikonPlanet* from,
                           EpikonPlanet* to, EpikonPlayer* player, int numShips, QObject* parent):
    QParallelAnimationGroup(parent), m_numships(numShips),m_to(to),m_player(player)
{
    int speed=4;
    int duration = sqrt(pow(to->x()-from->x(),2)+pow(to->y()-from->y(),2))*speed;
    item = new EpikonShipItem(m_numships);
    scene->addItem(item);
    QPropertyAnimation* anim;
    anim = new QPropertyAnimation(item,"pos");
    anim->setDuration(duration);
    QPointF pos =from->item()->pos();
    anim->setStartValue(pos);
    pos=to->item()->pos();
    anim->setEndValue(pos);
    anim->setEasingCurve(QEasingCurve::InBack);
    addAnimation(anim);

    QSequentialAnimationGroup *scalegroup = new QSequentialAnimationGroup(this);
    anim = new QPropertyAnimation(item,"scale");
    anim->setDuration((4*duration)/10);
    anim->setStartValue(0);
    anim->setEndValue(1);
//    anim->setEasingCurve(QEasingCurve::OutCubic);
    scalegroup->addAnimation(anim);
    anim = new QPropertyAnimation(item,"scale");
    anim->setDuration((6*duration)/10);
    anim->setStartValue(1);
    anim->setEndValue(0);
    anim->setEasingCurve(QEasingCurve::InQuart);
    scalegroup->addAnimation(anim);

    addAnimation(scalegroup);
}

