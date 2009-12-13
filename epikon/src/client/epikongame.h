#ifndef EPIKONGAME_H
#define EPIKONGAME_H

#include <QObject>
#include <QtContainerFwd>

#include "epikonplanet.h"
#include "epikonplayer.h"

namespace Epikon{
    namespace Client{
        class Game : public QObject
        {
        Q_OBJECT
        public:
            explicit Game(QObject *parent = 0);
            void addPlayer(EpikonPlayer* player,bool isMe=false);
            void addPlanet(EpikonPlanet* planet);
            EpikonPlayer* me(){return m_me;};
            QList<EpikonPlayer*> *players(){return m_players;};
            QList<EpikonPlanet*> *planets(){return m_planets;};

        public slots:
            void attack(EpikonPlanet& from, EpikonPlanet& to, EpikonPlayer& player);
            void onAttackFinished();
        private:
            QList<EpikonPlayer*> *m_players;
            QList<EpikonPlanet*> *m_planets;
            EpikonPlayer* m_me;
        };

    }
}

#endif // EPIKONGAME_H
