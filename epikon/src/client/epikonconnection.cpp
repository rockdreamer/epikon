#include "epikonconnection.h"
#include "server/epikonprotocolcommand.h"

using namespace Epikon::Client;
using namespace Epikon::Protocol;

#include <QTcpSocket>
#include <QDebug>

int Timeout=1000;

Connection::Connection(QObject *parent) :
        QThread(parent), quit(false)
{
}

Connection::~Connection()
{
    mutex.lock();
    quit = true;
    cond.wakeOne();
    mutex.unlock();
    wait();
}

void Connection::connectToHost(const QString &hostName, quint16 port)
{
    QMutexLocker locker(&mutex);
    this->hostName = hostName;
    this->port = port;
    if (!isRunning())
        start();
}
void Connection::run()
{
    mutex.lock();
    QString serverName = hostName;
    quint16 serverPort = port;
    mutex.unlock();
    while(!quit){
        tcpSocket = new QTcpSocket();
        tcpSocket->connectToHost(serverName, serverPort);
        if (!tcpSocket->waitForConnected(Timeout)) {
            qWarning() << "Could not connect to " << serverName << ":" << serverPort;
            emit socketError(tcpSocket->error());
            return;
          }
        qDebug() << "Connected to " << serverName << ":" << serverPort;

        QDataStream in(tcpSocket);
        in.setVersion(QDataStream::Qt_4_6);

        Hello hi;
        hi.setId("Epikon Client");
        hi.sendToSocket(tcpSocket);

        while(!quit){
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
}
