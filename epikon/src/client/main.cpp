#include <QtGui/QApplication>
#include "epikonmainwindow.h"
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile file(":/resources/style/epikon.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    a.setStyleSheet(styleSheet);
    EpikonMainWindow w;
    w.show();
    return a.exec();
}
