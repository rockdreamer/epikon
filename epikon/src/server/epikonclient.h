#ifndef EPIKONSRVCLIENT_H
#define EPIKONSRVCLIENT_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QTcpSocket>
#include "protocol/protocol.h"

namespace Epikon{
    namespace Server {
        class Game;
        class Client : public Epikon::Protocol::Protocol
        {
        Q_OBJECT
        public:
            explicit Client(int descriptor, QObject *parent = 0);
            ~Client();

        signals:
            void startGame();
            void joinGame(quint16 gamenum);
            void getGamesList();

        public slots:
            virtual void onConnected();

        private:

        };
    }
}

#endif // EPIKONSRVCLIENT_H
