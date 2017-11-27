#ifndef EPIKONSERVER_H
#define EPIKONSERVER_H

#include <QTcpServer>


namespace Epikon {
    namespace Server {
        class Client;
        class Game;
        class Player;
        class Server : public QTcpServer
        {
        Q_OBJECT
        public:
            explicit inline Server(QObject *parent = 0):QTcpServer(parent),m_maxconnections(100){
                connect(this,SIGNAL(newClient(Client*)), this, SLOT(addClient(Client*)));
            };
            static Server *instance();

            void removeClient(Client *client);
            bool canAddClient() const;
            quint16 maxClients() const {return m_maxconnections; };
            void setMaxClients(quint16 m){m_maxconnections=m;};

        public slots:
            void addClient(Client *client);
            void removeClient();

        protected:
            void incomingConnection(int socketDescriptor);

        private slots:

        private:
            QList<Client *> clients;
            QList<Game *> games;
            quint16 m_maxconnections;

        signals:
            void newClient(Client * client);

        public slots:

        };

    }
}

#endif // EPIKONSERVER_H
