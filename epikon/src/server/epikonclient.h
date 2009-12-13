#ifndef EPIKONSRVCLIENT_H
#define EPIKONSRVCLIENT_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QTcpSocket>

namespace Epikon{
    namespace Server {
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

        public slots:

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
