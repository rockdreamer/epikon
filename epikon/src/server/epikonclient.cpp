#include "epikonclient.h"
#include <protocol/epikonprotocolcommand.h>
#include <QTcpSocket>
#include <QDebug>

using namespace Epikon::Server;
using namespace Epikon::Protocol;

int Timeout=1000;
Client::Client(QObject *parent) :
        QThread(parent),quit(false)
{

}

Client::~Client()
{
    mutex.lock();
     quit = true;
     cond.wakeOne();
     mutex.unlock();
     wait();
}

void Client::sendCommand(const Command& cmd)
{
    QMutexLocker locker(&mutex);
    cmd.sendToSocket(tcpSocket);
}

void Client::run()
{
    tcpSocket = new QTcpSocket();
    if (!tcpSocket->setSocketDescriptor(m_descriptor)) {
        qWarning() << "Could not bind to socket " << m_descriptor;
        emit socketError(tcpSocket->error());
        return;
    }
    qDebug() << "New connection on socket " << m_descriptor;

    QDataStream in(tcpSocket);
    in.setVersion(QDataStream::Qt_4_6);

    Hello hi;
    hi.setId("Epikon Server");
    sendCommand(hi);

    while (!quit){
        while (tcpSocket->bytesAvailable() < (int)sizeof(quint16)) {
            if (!tcpSocket->waitForReadyRead()) {
                emit socketError(tcpSocket->error());
                return;
            }
        }

        // read the command length
        quint16 blockSize;
        in >> blockSize;

        while (tcpSocket->bytesAvailable() < blockSize) {
            if (!tcpSocket->waitForReadyRead(Timeout)) {
                emit socketError(tcpSocket->error());
                return;
            }
        }

        // read the command type
        CommandType cmdtype;
        in >> cmdtype;

        switch(cmdtype){
        case HELLO:{
                Hello cmd;
                in >> cmd;
                qDebug() << "Hello from " << cmd.id();
             break;
        }
        default:
            emit error("Unknown command type");
        }

    }
}
