#include "protocol.h"
#include <QDebug>

namespace Epikon {
    namespace Protocol {

        int Timeout=30000;

        Protocol::Protocol(QObject *parent) :
                QThread(parent)
        {}

        Protocol::Protocol(int socketDescriptor, QObject *parent) :
                QThread(parent), m_descriptor(socketDescriptor), m_port(0)
        {
        }

        Protocol::Protocol(const QString &hostname, quint16 port ,QObject *parent) :
                QThread(parent), m_descriptor(0), m_hostname(hostname), m_port(port)
        {
        }

        Protocol::~Protocol()
        {
            qDebug() << "Protocol (destructor): killing thread";
            quit();
            qDebug() << "Protocol (destructor): waiting for thread to end";
            wait();
        }

        void Protocol::sendCommand(const Command& cmd)
        {
            qDebug() << "Protocol: sending command" << &cmd;
            QMutexLocker locker(&mutex);
            if (m_sockptr->state()== QAbstractSocket::ConnectedState){
                cmd.sendToSocket(m_sockptr);
            } else {
                qDebug() << "Cannot send command " << &cmd << " to non - connected socket" ;
            }
        }

        void Protocol::run()
        {
            qDebug() << "Protocol: New Protocol Thread " << currentThreadId();
            QTcpSocket m_socket;
            m_sockptr=&m_socket;

            qDebug() << "Protocol: Connecting protocol signals";
            connect(&m_socket, SIGNAL(readyRead()), this, SLOT(readCommand()));
            connect(&m_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(handleSocketError()));
            connect(this, SIGNAL(connected()), this, SLOT(onConnected()));

            if (!m_port){
                qDebug() << "Protocol: setting socket descriptor " << m_descriptor;
                if (!m_socket.setSocketDescriptor(m_descriptor)) {
                    qWarning() << "Protocol: Could not bind to socket " << m_descriptor;
                    emit error(m_socket.errorString());
                    return;
                }
                emit connected();
                qDebug() << "Protocol: New connection on socket descriptor" << m_descriptor;
            } else {
                qDebug() << "Protocol: connecting to host " << m_hostname << ":" << m_port;
                m_socket.connectToHost(m_hostname, m_port);
                if (!m_socket.waitForConnected(Timeout)) {
                    qWarning() << "Protocol: Could not connect to host " << m_hostname << ":" << m_port;
                    emit error( tr("Protocol: Could not connect to host %1:%2. Connection Timed out").arg(m_hostname).arg(m_port));
                    return;
                }
                qDebug() << "Protocol: connected to host " << m_hostname << ":" << m_port;
                emit connected();
            }
            qDebug() << "Protocol: Starting protocol loop";
            exec();
            qDebug() << "Protocol: End of protocol loop, disconnecting";
            m_socket.disconnectFromHost();
            qDebug() << "Protocol: Waiting disconnect";
            m_socket.waitForDisconnected();
            qDebug() << "Protocol: Disconnected from host, disconnecting protocol signals";

            disconnect(&m_socket, SIGNAL(readyRead()), this, SLOT(readCommand()));
            disconnect(&m_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(handleSocketError()));
            disconnect(this, SIGNAL(connected()), this, SLOT(onConnected()));

        }

        void Protocol::readCommand(){
            qDebug() << "Protocol: reading from socket";
            QDataStream in(qobject_cast<QTcpSocket*>( sender()));
            in.setVersion(QDataStream::Qt_4_6);

            if (waitingLength){
                if (m_sockptr->bytesAvailable() < (int)sizeof(quint16)){
                    return;
                }
                in >> blockSize;
                waitingLength=false;
            }

            if (m_sockptr->bytesAvailable() < blockSize){
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
            if (m_sockptr->bytesAvailable()>0){
                readCommand();
            }
        }

        void Protocol::handleSocketError(){
            switch (m_sockptr->error()){
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
                emit error(m_sockptr->errorString());
            }
        }

    } // namespace Protocol
} // namespace Epikon
