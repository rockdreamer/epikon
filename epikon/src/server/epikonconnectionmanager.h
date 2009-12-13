#ifndef EPIKONCONNECTIONMANAGER_H
#define EPIKONCONNECTIONMANAGER_H

#include <QByteArray>
#include <QSet>

namespace Epikon{
    namespace Server {
        class Client;
        class EpikonConnectionManager
        {
        public:
            explicit inline EpikonConnectionManager(){};

            static EpikonConnectionManager *instance();
            bool canAddConnection() const;
            void addConnection(Client *connection);
            void removeConnection(Client *connection);
            int maxConnections() const;

        private:
            QSet<Client *> connections;

        };

    }
}

#endif // EPIKONCONNECTIONMANAGER_H
