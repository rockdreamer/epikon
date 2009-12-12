#include <QCoreApplication>
#include "server/epikonserver.h"
#include "epikondefs.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    qDebug() << "Staring Epikon server v";
    QCoreApplication a(argc, argv);
    EpikonServer* srv = EpikonServer::instance();
    srv->setParent(&a);
    srv->listen(QHostAddress::Any, 20000);
    return a.exec();
}
