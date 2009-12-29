#include "epikonclient.h"
#include <protocol/command.h>
#include <QTcpSocket>
#include <QDebug>

using namespace Epikon::Server;
using namespace Epikon::Protocol;

int Timeout=1000;
Client::Client(int descriptor, QObject *parent) :
        Protocol(descriptor, parent)
{

}

Client::~Client()
{
}

void Client::onConnected()
{
    Hello hi;
    hi.setId("Epikon Server");
    sendCommand(hi);
}
