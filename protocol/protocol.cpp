#include "protocol.h"
#include <QDebug>
#include <QStateMachine>
#include <QState>
#include <QFinalState>

namespace Epikon {
    namespace Protocol {

        int Timeout=30000;

        Protocol::Protocol(QObject *parent) :
                QTcpSocket(parent)
        {
            qDebug() << "Creating Protocol on thread "<< QThread::currentThreadId();

            prepareStateMachine();

            qDebug() << "Protocol: Connecting protocol signals";
            connect(this, SIGNAL(readyRead()), this, SLOT(readCommand()));
            connect(this, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(handleSocketError()));
            connect(this, SIGNAL(connected()), this, SLOT(onConnected()));

        }

        Protocol::~Protocol()
        {
            if (state()== QAbstractSocket::ConnectedState){
                qDebug() << "Protocol (destructor): disconnecting";
                disconnectFromHost();
                qDebug() << "Protocol: Disconnected from host";
            }
            qDebug() << "Protocol: disconnecting protocol signals";
            disconnect(this, SIGNAL(readyRead()), this, SLOT(readCommand()));
            disconnect(this, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(handleSocketError()));
            disconnect(this, SIGNAL(connected()), this, SLOT(onConnected()));
        }

        void Protocol::sendCommand(const Command& cmd)
        {
            qDebug() << "Protocol: sending command" << &cmd;
            QMutexLocker locker(&mutex);
            if (state()== QAbstractSocket::ConnectedState){
                cmd.sendToSocket(this);
            } else {
                qDebug() << "Cannot send command " << &cmd << " to non - connected socket" ;
            }
        }

        void Protocol::readCommand(){
            qDebug() << "Protocol: reading from socket";
            QDataStream in(this);
            in.setVersion(QDataStream::Qt_4_6);

            if (waitingLength){
                if (bytesAvailable() < (int)sizeof(quint16)){
                    return;
                }
                in >> blockSize;
                waitingLength=false;
            }

            if (bytesAvailable() < blockSize){
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
                emit protocolError("Unknown command type");
            }

            waitingLength=true;
            if (bytesAvailable()>0){
                readCommand();
            }
        }

        void Protocol::handleSocketError(){
            switch (error()){
            case QAbstractSocket::RemoteHostClosedError:
                emit closed();
                break;
            case QAbstractSocket::HostNotFoundError:
                protocolError(tr("The host was not found. Please check the "
                         "host name and port settings."));
                break;
            case QAbstractSocket::ConnectionRefusedError:
                protocolError(tr("The connection was refused by the server. "
                         "Check that the host name and port "
                         "settings are correct."
                         ));
                break;
            default:
                emit protocolError(errorString());
            }
        }

        void Protocol::prepareStateMachine(){
            qDebug() << "Protocol: Initialising Protocol State";
            QStateMachine *machine = new QStateMachine(this);

            /**
             *  Main states are connected, disconnected and done, we start disconnected
             *  and turn to connected when the socket is operational.
             *  All the other states are part of the connected state
             */
            QState *disconnected = new QState();
            QState *connected = new QState();
            QFinalState *done = new QFinalState();

            /**
             *  When first connected, we need to know the protocol version,
             *  then request authentication. We then either turn to the authenticated
             *  state or flee to *done
             */
            QState *waitingproto = new QState(connected);
            QState *waitingauthrequest = new QState(connected);
            QState *waitingauthstatus = new QState(connected);
            QState *authenticated = new QState(connected);
            connected->setInitialState(waitingproto);

            /**
             * When authenticated, the user must provide some information about himself
             * (nickname, status, planet picture, user picture, attack picture)
             * Then the user can request to join the chat room, get the list of games and users
             * join a game or create a game
             * In the chat room, the user sends and receives messages, and can eventually exit
             */
            QState *waitinguserdetails = new QState(authenticated);
            QState *waitingcommand = new QState(authenticated);
            QState *inchat = new QState(authenticated);
            QState *waitinggamecreation = new QState(authenticated);
            QState *waitinggamelist = new QState(authenticated);
            QState *waitinguserlist = new QState(authenticated);
            QState *joinedgame = new QState(authenticated);
            authenticated->setInitialState(waitinguserdetails);

            /**
             * When entering the game, we wait for the users to show up
             * then receive the game map
             * we then wait for the game to unpause, and the game progresses till
             * there's a winner or cancellation
             */
            QState *waitinguser = new QState(joinedgame);
            QState *waitingmap = new QState(joinedgame);
            QState *paused = new QState(joinedgame);
            QState *ingame = new QState(joinedgame);
            joinedgame->setInitialState(waitinguser);

            qDebug() << "Protocol: Connecting Protocol Signals";
            disconnected->addTransition(this, SIGNAL(connected()), connected);
            connected->addTransition(this, SIGNAL(closed()), done);
            waitingproto->addTransition(this, SIGNAL(protocol(QString)), waitingauthrequest);
            waitingauthrequest->addTransition(this, SIGNAL(authrequest(QString,QString)), waitingauthstatus);
            waitingauthstatus->addTransition(this, SIGNAL(authenticated()), authenticated);
            waitingauthstatus->addTransition(this, SIGNAL(protocolError(QString)), done);

            machine->addState(disconnected);
            machine->addState(connected);
            machine->setInitialState(disconnected);

            qDebug() << "Protocol: Starting State Machine";
            machine->start();
        }

    } // namespace Protocol
} // namespace Epikon
