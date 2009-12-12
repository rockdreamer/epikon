#include "epikonconnectionmanager.h"

static const int MaxConnections = 250;

Q_GLOBAL_STATIC(EpikonConnectionManager, connectionManager)

 EpikonConnectionManager *EpikonConnectionManager::instance()
 {
     return connectionManager();
 }

 bool EpikonConnectionManager::canAddConnection() const
 {
     return (connections.size() < MaxConnections);
 }

 void EpikonConnectionManager::addConnection(EpikonClient *client)
 {
     connections << client;

 }

 void EpikonConnectionManager::removeConnection(EpikonClient *client)
 {
     connections.remove(client);

 }

 int EpikonConnectionManager::maxConnections() const
 {
     return MaxConnections;
 }
