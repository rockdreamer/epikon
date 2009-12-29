#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QTcpSocket>
#include "command.h"

namespace Epikon {
    namespace Protocol {

        class Command;
        class Protocol : public QThread
        {
            Q_OBJECT
        public:
            explicit Protocol(QObject *parent = 0);
            explicit Protocol(int socketDescriptor, QObject *parent = 0);
            explicit Protocol(const QString &hostname, quint16 port, QObject *parent = 0);
            ~Protocol();
            void run();

        signals:
            void error(const QString& errormsg);
            void hello(const Hello & command);
            void attack(const Attack & command);
            void connected();
            void closed();

        public slots:
            void sendCommand(const Command& cmd);
            void handleSocketError();
            virtual void onConnected(){};

        private slots:
            void readCommand();
        private:
            int m_descriptor;
            QString m_hostname;
            quint16 m_port;
            QMutex mutex;
            QWaitCondition cond;
            bool waitingLength;
            QTcpSocket *m_sockptr;
            quint16 blockSize;
            CommandType cmdtype;
        };

    } // namespace Protocol
} // namespace Epikon

#endif // PROTOCOL_H
