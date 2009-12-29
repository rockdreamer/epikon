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
     qDebug() << "Adding client " << client;
     clients << client;
     qDebug() << "Server: Connecting client slots";
     connect(client, SIGNAL(finished()), this, SLOT(removeClient()));
     connect(client, SIGNAL(finished()), client, SLOT(deleteLater()));
 }

 void Server::removeClient(Client *client)
 {
     disconnect(client, SIGNAL(finished()), this, SLOT(removeClient()));
     clients.removeAll(client);
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
         qDebug() << "Server: Incoming connection";
        Client *client = new Client(socketDescriptor, this);
        addClient(client);
        qDebug() << "Server: Starting protocol thread";
        client->start();
        return;
     }
     qDebug() << "Incoming connection refused";
 }

