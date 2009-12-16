#include <QCoreApplication>
#include "server/epikonserver.h"
#include "epikondefs.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    qDebug() << "Starting Epikon server v" << EPIKON_VERSION_STRING;
    QCoreApplication a(argc, argv);
    Epikon::Server::Server* srv = Epikon::Server::Server::instance();
    srv->setParent(&a);
    qDebug() << "Listening on port 20000";
    srv->listen(QHostAddress::Any, 20000);
    return a.exec();
}
