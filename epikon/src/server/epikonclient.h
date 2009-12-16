#ifndef EPIKONSRVCLIENT_H
#define EPIKONSRVCLIENT_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QTcpSocket>

namespace Epikon{
    namespace Protocol {
        class Command;
    }
    namespace Server {
        class Game;
        class Client : public QThread
        {
        Q_OBJECT
        public:
            explicit Client(QObject *parent = 0);
            ~Client();
            void run();

            inline void setSocketDescriptor(int descriptor) {m_descriptor = descriptor;};
        signals:
            void error(const QString& errormsg);
            void socketError(QTcpSocket::SocketError socketError);
            void startGame();
            void joinGame(quint16 gamenum);
            void getGamesList();

        public slots:
 //           void onJoinGame(const Game *game);
  //          void sendGamesList(const QList<Game *> &games);
            void sendCommand(const Epikon::Protocol::Command& cmd);

        private:
            int m_descriptor;
             QMutex mutex;
             QWaitCondition cond;
             bool quit;
            QTcpSocket *tcpSocket;

        };
    }
}

#endif // EPIKONSRVCLIENT_H
