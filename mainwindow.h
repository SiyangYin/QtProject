
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <string>
#include "lipkg.h"
#include <qfile.h>
#include<QtMath>
#include<map>
#include <QObject>
#include "pro.h"
#include <QQueue>
#include "QTime"
#include <QApplication>
#include <QFileDialog>
#include <QDebug>
#include <QString>
#include <QtGui>
#include <qfile.h>
#include <qiodevice.h>
#include <qtextstream.h>
#include <string.h>
#include "rplidar.h"
#include "rplidar_driver.h"

//#include <QTest>
//#include <qtest.h>



using namespace std;

namespace Ui {

//extern void LiPkg::assemble();

class MainWindow;
class RPlidarDriver;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


    void sleep(unsigned int msec);
signals:

    void clicked();

public slots:

    void setOutputDir();

//    void selectSDKPath();

    void updateDisplay();

//    void invokeSDK();

    //int lidar();

    //extern void LiPkg::assemble();

    //void assemble();

    void searchSerialPort();

    void sampling();

    void reset();

private slots:
    void on_OpenSerialButton_clicked();

    void ReadData();

    void on_SendButton_clicked();

    //void setOutputDir();

    //void selectSDKPath(QString outputPath);


private:
    Ui::MainWindow *ui;
    QSerialPort *serial;
    QString outputDir;
    QString outputDirPart1;
    QString outputDirPart2;
    QString outputDirPart3;
    QString SDKPath;
    QTextStream stream;
    QFile file;
    int countEffectivePoint;
    int pkgNumber;
    int circleNumber;
    int threshold;
    int counter[12];
//    int counter1;
//    int counter2;
//    int counter3;
//    int counter4;
//    int counter5;
//    int counter6;
//    int counter7;
//    int counter8;
//    int counter9;
//    int counter10;
//    int counter11;
//    int counter12;


};

#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H


