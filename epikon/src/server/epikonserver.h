#ifndef EPIKONSERVER_H
#define EPIKONSERVER_H

#include <QTcpServer>

class EpikonClient;
class EpikonServerGame;

class EpikonServer : public QTcpServer
{
Q_OBJECT
public:
    explicit inline EpikonServer(QObject *parent = 0){};
    static EpikonServer *instance();

    void addClient(EpikonClient *client);
    void removeClient(EpikonClient *client);

protected:
    void incomingConnection(int socketDescriptor);

private slots:
    void removeClient();

private:
    QList<EpikonClient *> clients;
    QList<EpikonServerGame *> games;

signals:

public slots:

};

#endif // EPIKONSERVER_H
