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
        class Client : public QThread
        {
        Q_OBJECT
        public:
            explicit Client(int descriptor, QObject *parent = 0);
            ~Client();
            void run();

        signals:
            void startGame();
            void joinGame(quint16 gamenum);
            void getGamesList();

        public slots:
            virtual void onConnected();

        private:
            int m_descriptor;
        };
    }
}

#endif // EPIKONSRVCLIENT_H
