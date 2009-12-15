#ifndef EPIKONNETWORKGAME_H
#define EPIKONNETWORKGAME_H

#include "epikongame.h"

namespace Epikon{
    namespace Client {
        class Connection;
        class NetworkGame : public Game
        {
        Q_OBJECT
        public:
            explicit NetworkGame(QObject *parent = 0);

        signals:

        public slots:
            void attack(EpikonPlanet& from, EpikonPlanet& to, EpikonPlayer& player);
            void onNetAttack(quint16 fromPlanet, quint16 toPlanet, quint16 player, quint16 numShips, quint16 lag);
        protected:
            Epikon::Client::Connection* m_connection;
        };

    }
}

#endif // EPIKONNETWORKGAME_H
