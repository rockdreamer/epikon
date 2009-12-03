#include <QtGui/QApplication>
#include "epikonmainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EpikonMainWindow w;
    w.show();
    return a.exec();
}
