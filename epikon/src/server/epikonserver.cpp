#include "epikonserver.h"
#include "epikonconnectionmanager.h"
#include "epikonclient.h"

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
     if (EpikonConnectionManager::instance()->canAddConnection() && !clients.isEmpty()) {
        EpikonClient *client = new EpikonClient(this);
        client->setSocketDescriptor(socketDescriptor);
        EpikonConnectionManager::instance()->addConnection(client);
        connect(client, SIGNAL(finished()), client, SLOT(deleteLater()));
        client->start();
        return;
     }

 }

 void EpikonServer::removeClient()
 {
     EpikonClient *peer = qobject_cast<EpikonClient *>(sender());
     peer->deleteLater();
 }

