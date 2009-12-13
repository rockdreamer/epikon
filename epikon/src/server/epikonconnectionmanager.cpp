#include "epikonconnectionmanager.h"

static const int MaxConnections = 250;
using namespace Epikon::Server;

Q_GLOBAL_STATIC(EpikonConnectionManager, connectionManager)

 EpikonConnectionManager *EpikonConnectionManager::instance()
 {
     return connectionManager();
 }

 bool EpikonConnectionManager::canAddConnection() const
 {
     return (connections.size() < MaxConnections);
 }

 void EpikonConnectionManager::addConnection(Client *client)
 {
     connections << client;

 }

 void EpikonConnectionManager::removeConnection(Client *client)
 {
     connections.remove(client);

 }

 int EpikonConnectionManager::maxConnections() const
 {
     return MaxConnections;
 }
