#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/icon.png"));
    QCoreApplication::setOrganizationName("OceanCrossing");
    QCoreApplication::setApplicationName("ConvertisseurGPS");
    MainWindow w;
    w.show();
    return a.exec();
}
