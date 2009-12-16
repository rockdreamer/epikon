#include "epikonserver.h"
#include "epikonclient.h"
#include <QDebug>

using namespace Epikon::Server;

Q_GLOBAL_STATIC(Server, epikonServer)

Server *Server::instance()
 {
     return epikonServer();
 }

 void Server::addClient(Client *client)
 {
     clients << client;
     connect(client, SIGNAL(finished()), this, SLOT(removeClient()));
 }

 void Server::removeClient(Client *client)
 {
     disconnect(client, SIGNAL(finished()), this, SLOT(removeClient()));
     clients.removeAll(client);
     client->deleteLater();
 }

 bool Server::canAddClient() const
 {
     return (clients.size() < m_maxconnections);
 }

 void Server::removeClient()
 {
     Client *client = qobject_cast<Client *>(sender());
     qDebug() << "Removing client " << client;
     removeClient(client);
 }

 void Server::incomingConnection(int socketDescriptor)
 {
     if (canAddClient()) {
        qDebug() << "Incoming connection";
        Client *client = new Client(this);
        client->setSocketDescriptor(socketDescriptor);
        addClient(client);
        client->start();
        return;
     }
     qDebug() << "Incoming connection refused";
 }


