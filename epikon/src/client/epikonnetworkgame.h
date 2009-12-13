#ifndef EPIKONNETWORKGAME_H
#define EPIKONNETWORKGAME_H

#include "epikongame.h"

namespace Epikon{
    namespace Client {
        class NetworkGame : public Game
        {
        Q_OBJECT
        public:
            explicit NetworkGame(QObject *parent = 0);

        signals:

        public slots:

        };

    }
}

#endif // EPIKONNETWORKGAME_H
