#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGeoCoordinate>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void clickOnConvert();


private:
    Ui::MainWindow *ui;
    double latMinToDec(QString sLatitude);
    double longMinToDec(QString sLongitude);
    double latSecToDec(QString sLatitude);
    double longSecToDec(QString sLongitude);
    void traiteDMD(QGeoCoordinate posGeo);
    void traiteDMS(QGeoCoordinate posGeo);


};
#endif // MAINWINDOW_H
