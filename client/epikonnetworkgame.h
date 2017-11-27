#ifndef EPIKONNETWORKGAME_H
#define EPIKONNETWORKGAME_H

#include "epikongame.h"

namespace Epikon{
    namespace Protocol{
        class Protocol;
    }
    namespace Client {
        class Connection;
        class NetworkGame : public Game
        {
        Q_OBJECT
        public:
            explicit NetworkGame(Epikon::Protocol::Protocol * connection, QObject *parent = 0);

        signals:

        public slots:
            void attack(EpikonPlanet& from, EpikonPlanet& to, EpikonPlayer& player);
            void onNetAttack(quint16 fromPlanet, quint16 toPlanet, quint16 player, quint16 numShips, quint16 lag);
        protected:
            Epikon::Protocol::Protocol* m_connection;
        };

    }
}

#endif // EPIKONNETWORKGAME_H
