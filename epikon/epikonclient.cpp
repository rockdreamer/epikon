#include "epikonclient.h"
#include <QTcpSocket>

EpikonClient::EpikonClient(QObject *parent) :
    QThread(parent)
{
}

void EpikonClient::run()
{
    QTcpSocket tcpSocket;
        if (!tcpSocket.setSocketDescriptor(m_descriptor)) {
            emit socketError(tcpSocket.error());
            return;
        }
}
