#ifndef EPIKONCONNECTION_H
#define EPIKONCONNECTION_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QTcpSocket>

namespace Epikon {
    namespace Client {
        class Connection : public QThread
        {
        Q_OBJECT
        public:
            explicit Connection(QObject *parent = 0);
            ~Connection();
            void run();
        signals:
            void error(const QString& errormsg);
            void socketError(QTcpSocket::SocketError socketError);
        public slots:
            void connectToHost(const QString& hostname, quint16 port);
        private:
            QTcpSocket *tcpSocket;
            QString hostName;
            quint16 port;
            QMutex mutex;
            QWaitCondition cond;
            bool quit;
        };
    }
}

#endif // EPIKONCONNECTION_H
