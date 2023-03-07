#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   QObject::connect(ui->btn_Convert,&QPushButton::clicked,this,&MainWindow::clickOnConvert);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clickOnConvert()
{
    QGeoCoordinate posGeo;

    if(ui->rb_DMS->isChecked())
    {
        QString sLat=QString("%1,%2,%3,%4")
                .arg(ui->cb_NS_DMS->currentText())
                .arg(ui->sp_DegLat_DMS->value())
                .arg(ui->sp_MinLat_DMS->value())
                .arg(ui->sp_SecLat->value());
        QString sLong=QString("%1,%2,%3,%4")
                .arg(ui->cb_EO_DMS->currentText())
                .arg(ui->sp_DegLon_DMS->value())
                .arg(ui->sp_MinLon_DMS->value())
                .arg(ui->sp_SecLon->value());

        double dLat=latSecToDec(sLat);
        double dLong=longSecToDec(sLong);

        ui->sp_DegLat_DD->setValue(dLat);
        ui->sp_DegLon_DD->setValue(dLong);

        QGeoCoordinate posGeo;
        posGeo.setLatitude(dLat);
        posGeo.setLongitude(dLong);
        traiteDMD(posGeo);



    }
    if(ui->rb_DMD->isChecked())
    {
        QString sLat=QString("%1,%2,%3")
                .arg(ui->cb_NS_DMD->currentText())
                .arg(ui->sp_DegLat_DMD->value())
                .arg(ui->sp_MinLat_DMD->value());
        QString sLong=QString("%1,%2,%3")
                .arg(ui->cb_EO_DMD->currentText())
                .arg(ui->sp_DegLon_DMD->value())
                .arg(ui->sp_MinLon_DMD->value());

        double dLat=latMinToDec(sLat);
        double dLong=longMinToDec(sLong);

        ui->sp_DegLat_DD->setValue(dLat);
        ui->sp_DegLon_DD->setValue(dLong);

        QGeoCoordinate posGeo;
        posGeo.setLatitude(dLat);
        posGeo.setLongitude(dLong);
        traiteDMS(posGeo);



    }
    if(ui->rb_DD->isChecked())
    {
        double dLat=ui->sp_DegLat_DD->value();
        double dLong=ui->sp_DegLon_DD->value();

        ui->sp_DegLat_DD->setValue(dLat);
        ui->sp_DegLon_DD->setValue(dLong);

        QGeoCoordinate posGeo;
        posGeo.setLatitude(dLat);
        posGeo.setLongitude(dLong);
        traiteDMS(posGeo);
        traiteDMD(posGeo);
    }
}

double MainWindow::latMinToDec(QString sLatitude)
{
    //format : H,DD,MM.ddddd,
        //         S,12,30.54443
        int nDeg=sLatitude.section(",",1,1).toInt();
        double dMin=sLatitude.section(",",2,2).toDouble();
        QString cHemi=sLatitude.section(",",0,0);

        double dLatDec=nDeg+(dMin/60);
        if(cHemi=="S")
            dLatDec=-dLatDec;

        return dLatDec;
}

double MainWindow::longMinToDec(QString sLongitude)
{
    //format :H,DDD,MM.ddddd
    //        E,044,55.20103
    int nDeg=sLongitude.section(",",1,1).toInt();
    double dMin=sLongitude.section(",",2,2).toDouble();
    QString cHemi=sLongitude.section(",",0,0);

    double dLongDec=nDeg+(dMin/60);
    if(cHemi=="W")
        dLongDec=-dLongDec;

    return dLongDec;
}

double MainWindow::latSecToDec(QString sLatitude)
{
    //format : H,DD,MM,SS.d,
        //         S,12,30,15.2
    int nDeg=sLatitude.section(",",1,1).toInt();
    int nMin=sLatitude.section(",",2,2).toInt();
    double dSec=sLatitude.section(",",3,3).toDouble();
    QString cHemi=sLatitude.section(",",0,0);
    double dLatDec=nDeg+(nMin+(dSec/60))/60;
    if(cHemi=="S")
        dLatDec=-dLatDec;

    return dLatDec;


}

double MainWindow::longSecToDec(QString sLongitude)
{
    //format :H,DDD,MM,SS.d
    //        E,044,55,30.2
    int nDeg=sLongitude.section(",",1,1).toInt();
        int nMin=sLongitude.section(",",2,2).toInt();
        double dSec=sLongitude.section(",",3,3).toDouble();
        QString cHemi=sLongitude.section(",",0,0);
        double dLongDec=nDeg+(nMin+(dSec/60))/60;
        if(cHemi=="W")
            dLongDec=-dLongDec;

        return dLongDec;
}

void MainWindow::traiteDMD(QGeoCoordinate posGeo)
{
    QString sPos=posGeo.toString(QGeoCoordinate::DegreesMinutesWithHemisphere);
    //"47° 37.800' N, 12° 7.680' E"
    QString sLat=sPos.section(",",0,0);
    QString sLong=sPos.section(",",1,1);
    qDebug()<<sPos;
    ui->sp_DegLat_DMD->setValue(sLat.section("°",0,0).toInt());
    ui->sp_MinLat_DMD->setValue(sLat.section("°",1,1).section("\'",0,0).remove(" ").toDouble());
    if(sLat.contains("N"))
        ui->cb_NS_DMD->setCurrentIndex(0);
    else
        ui->cb_NS_DMD->setCurrentIndex(1);

    ui->sp_DegLon_DMD->setValue(sLong.section("°",0,0).remove(" ").toInt());
    ui->sp_MinLon_DMD->setValue(sLong.section("°",1,1).section("\'",0,0).remove(" ").toDouble());
    if(sLong.contains("E"))
        ui->cb_EO_DMD->setCurrentIndex(0);
    else
        ui->cb_EO_DMD->setCurrentIndex(1);


}

void MainWindow::traiteDMS(QGeoCoordinate posGeo)
{
    QString sPos=posGeo.toString();
    //"47° 35' 36.0\" N, 12° 40' 30.0\" W"
    QString sLat=sPos.section(",",0,0);
    QString sLong=sPos.section(",",1,1);
    ui->sp_DegLat_DMS->setValue(sLat.section("°",0,0).remove("\"").toInt());
    ui->sp_MinLat_DMS->setValue(sLat.section("\'",0,0).section(" ",1,1).toInt());
    ui->sp_SecLat->setValue(sLat.section("\'",1,1).section("\"",0,0).toDouble());
    if(sLat.contains("N"))
        ui->cb_NS_DMS->setCurrentIndex(0);
    else
        ui->cb_NS_DMS->setCurrentIndex(1);


    ui->sp_DegLon_DMS->setValue(sLong.section("°",0,0).remove(" ").toInt());
    ui->sp_MinLon_DMS->setValue(sLong.section("°",1,1).section("\'",0,0).remove(" ").toInt());
    ui->sp_SecLon->setValue(sLong.section("\'",1,1).section("\"",0,0).remove(" ").toDouble());
    if(sLong.contains("E"))
        ui->cb_EO_DMS->setCurrentIndex(0);
    else
        ui->cb_EO_DMS->setCurrentIndex(1);

}

