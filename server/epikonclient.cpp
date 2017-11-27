#include "epikonclient.h"
#include <protocol/command.h>
#include <protocol/protocol.h>
#include <QDebug>

using namespace Epikon::Server;
using namespace Epikon::Protocol;

int Timeout=1000;
Client::Client(int descriptor, QObject *parent) :
        QThread(parent), m_descriptor(descriptor)
{

}

void Client::run()
{
    Epikon::Protocol::Protocol proto;
    connect(&proto, SIGNAL(connected()), this, SLOT(onConnected()));
    proto.setSocketDescriptor(m_descriptor);
    exec();
}

Client::~Client()
{
}

void Client::onConnected()
{
    Hello hi;
    hi.setId("Epikon Server");
    qobject_cast<Epikon::Protocol::Protocol*>(QObject::sender())->sendCommand(hi);
}
