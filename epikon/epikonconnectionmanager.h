#ifndef EPIKONCONNECTIONMANAGER_H
#define EPIKONCONNECTIONMANAGER_H

#include <QByteArray>
#include <QSet>

class EpikonClient;
class EpikonConnectionManager
{
public:
    explicit inline EpikonConnectionManager(){};

    static EpikonConnectionManager *instance();
    bool canAddConnection() const;
    void addConnection(EpikonClient *connection);
    void removeConnection(EpikonClient *connection);
    int maxConnections() const;

private:
    QSet<EpikonClient *> connections;

};

#endif // EPIKONCONNECTIONMANAGER_H
