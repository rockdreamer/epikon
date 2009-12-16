#include "protocol.h"

namespace Epikon {
    namespace Protocol {

        int Timeout=30000;

        Protocol::Protocol(QObject *parent) :
                QThread(parent)
                
        {
            if (!m_socket)
                m_socket = new QTcpSocket();
        }

        Protocol::Protocol(int socketDescriptor, QObject *parent) :
                QThread(parent), m_descriptor(socketDescriptor), m_port(0), m_socket(0)
        {
            if (!m_socket)
                m_socket = new QTcpSocket();
        }

        Protocol::Protocol(const QString &hostname, quint16 port ,QObject *parent) :
                QThread(parent), m_descriptor(0), m_hostname(hostname), m_port(port), m_socket(0)
        {
            if (!m_socket)
                m_socket = new QTcpSocket();
        }

        Protocol::~Protocol()
        {
            quit();
            wait();
            delete m_socket;
        }

        void Protocol::sendCommand(const Command& cmd)
        {
            QMutexLocker locker(&mutex);
            cmd.sendToSocket(m_socket);
        }

        void Protocol::run()
        {
            qDebug() << "New Protocol Thread " << currentThreadId();


            if (!m_port){
                if (!m_socket->setSocketDescriptor(m_descriptor)) {
                    qWarning() << "Could not bind to socket " << m_descriptor;
                    emit error(m_socket->errorString());
                    return;
                }
                emit connected();
                qDebug() << "New connection on socket descriptor" << m_descriptor;
            } else {
                m_socket->connectToHost(m_hostname, m_port);
                if (!m_socket->waitForConnected(Timeout)) {
                    qWarning() << "Could not connect to host " << m_hostname << ":" << m_port;
                    emit error( tr("Could not connect to host %1:%2. Connection Timed out").arg(m_hostname).arg(m_port));
                    return;
                }
                emit connected();
                qDebug() << "New connection on socket descriptor" << m_descriptor;
            }

            connect(m_socket, SIGNAL(readyRead()), this, SLOT(readCommand()));
            connect(m_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(handleSocketError(QAbstractSocket::SocketError)));

            exec();
            qDebug() << "Leaving Protocol Thread ";

        }

        void Protocol::readCommand(){
            QDataStream in(m_socket);
            in.setVersion(QDataStream::Qt_4_6);

            if (waitingLength){
                if (m_socket->bytesAvailable() < (int)sizeof(quint16)){
                    return;
                }
                in >> blockSize;
                waitingLength=false;
            }

            if (m_socket->bytesAvailable() < blockSize){
                return;
            }
            in >> cmdtype;
            switch(cmdtype){

            case HELLO:{
                    Hello cmd;
                    in >> cmd;
                    qDebug() << "Hello from " << cmd.id();
                    emit hello(cmd);
                    break;
                }
            case ATTACK:{
                    Attack cmd;
                    in >> cmd;
                    qDebug() << "Got Attack";
                    emit attack(cmd);
                    break;
                }
            default:
                emit error("Unknown command type");
            }

            waitingLength=true;
            if (m_socket->bytesAvailable()>0){
                readCommand();
            }
        }

        void Protocol::handleSocketError(QAbstractSocket::SocketError socketError){
            switch (socketError){
            case QAbstractSocket::RemoteHostClosedError:
                emit closed();
                break;
            case QAbstractSocket::HostNotFoundError:
                error(tr("The host was not found. Please check the "
                         "host name and port settings."));
                break;
            case QAbstractSocket::ConnectionRefusedError:
                error(tr("The connection was refused by the server. "
                         "Check that the host name and port "
                         "settings are correct."
                         ));
                break;
            default:
                emit error(m_socket->errorString());
            }
        }

    } // namespace Protocol
} // namespace Epikon
