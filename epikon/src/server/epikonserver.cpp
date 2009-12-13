#include "epikonserver.h"
#include "epikonconnectionmanager.h"
#include "epikonclient.h"
#include <QDebug>

using namespace Epikon::Server;

Q_GLOBAL_STATIC(EpikonServer, epikonServer)

EpikonServer *EpikonServer::instance()
 {
     return epikonServer();
 }

 void EpikonServer::addClient(EpikonClient *client)
 {
     clients << client;
 }

 void EpikonServer::removeClient(EpikonClient *client)
 {
     clients.removeAll(client);
 }

 void EpikonServer::incomingConnection(int socketDescriptor)
 {
     if (EpikonConnectionManager::instance()->canAddConnection()) {
        qDebug() << "Incoming connection";
        Client *client = new Client(this);
        client->setSocketDescriptor(socketDescriptor);
        EpikonConnectionManager::instance()->addConnection(client);
        connect(client, SIGNAL(finished()), client, SLOT(deleteLater()));
        client->start();
        return;
     }
     qDebug() << "Incoming connection refused";
 }

 void EpikonServer::removeClient()
 {
     Client *peer = qobject_cast<Client *>(sender());
     qDebug() << "Removing client " << peer;
     peer->deleteLater();
 }

