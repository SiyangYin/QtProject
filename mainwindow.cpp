//made some change

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore/QProcess>
#include <iostream>
#include <QtCore/QTextStream>
#include <QtCore/QIODevice>
//#include "LiDAR.cpp"
#include "lipkg.h"
#include "QDebug"
#include<QtMath>
#include<map>
#include <qfile.h>
#include <QTime>
#include <QTest>
#include <qtest.h>
//#include <synchapi.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "rplidar.h"
#include "rplidar_driver.h"


using namespace std;
using namespace rp;
using namespace standalone;
using namespace rplidar;


LiPkg *lipkg = (new LiPkg);

//#include "lipkg.cpp"

//QObject::connect(ui->lidarBox,SIGNAL(valueChanged(int)),this,SLOT(setOutputDir()));


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
//MainWindow::MainWindow(QWidget *parent) :
//    QMainWindow(parent),
//    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //查找可用的串口
    foreach (const QSerialPortInfo &info,QSerialPortInfo::availablePorts())
    {
        QSerialPort serial;
        serial.setPort(info);
        if(serial.open(QIODevice::ReadWrite))
        {
            ui->PortBox->addItem(serial.portName());
            serial.close();
        }
    }
    //设置波特率下拉菜单默认显示第4项
    ui->BaudBox->setCurrentIndex(4);


    countEffectivePoint = 0;		//initialize the number.
    pkgNumber=0;
    circleNumber=0;
     threshold=130;
     for(int i=0;i<12;i++)
     {
         counter[i]=0;
     }

    //connect(ui->lidarBox,SIGNAL(valueChanged(int)),this,SLOT(setOutputDir()));
    //connect(ui->startButton,SIGNAL(clicked()),this,SLOT(ReadData()));
    //connect(ui->startButton,SIGNAL(clicked()),this,SLOT(selectSDKPath(outputDir)));
    //connect(ui->lidarBox,ui->lidarBox->currentIndexChanged(),this,&MainWindow::setOutputDir);
    //connect(ui->startButton,&QPushButton::clicked,this,&MainWindow::updateDisplay);//usable
    //connect(ui->lidarBox,SIGNAL(SelectedValueChanged()),this,SLOT(setOutputDir()));//
    connect(ui->updateButton,SIGNAL(clicked()),this,SLOT(setOutputDir()));//usable
    connect(ui->updateButton,SIGNAL(clicked()),this,SLOT(updateDisplay()));//usable
    //connect(ui->lidarBox,SIGNAL(currentIndexChanged(int)),this,SLOT(setOutputDir()));//usable
    //connect(ui->envirBox,SIGNAL(currentIndexChanged(int)),this,SLOT(setOutputDir()));//usable
    //connect(ui->condiBox,SIGNAL(currentIndexChanged(int)),this,SLOT(setOutputDir()));//usable
    //connect(ui->lidarBox,SIGNAL(currentIndexChanged(int)),this,SLOT(selectSDKPath()));//usable
    //connect(ui->startButton,SIGNAL(clicked()),this,SLOT(updateDisplay()));//usable
    //connect(ui->startButton,SIGNAL(clicked()),this,SLOT(invokeSDK()));//usable
    //LiPkg *lipkg = (new LiPkg);
    //connect(ui->startButton,SIGNAL(clicked()),lipkg,SLOT(assemble()));//usable
    //connect(ui->startButton,SIGNAL(clicked()),this,SLOT(lidar()));//usable
    connect(ui->searchButton,SIGNAL(clicked()),this,SLOT(searchSerialPort()));//usable
    connect(ui->startButton,SIGNAL(clicked()),this,SLOT(sampling()));//usable
    //connect(ui->SendButton,SIGNAL(clicked()),this,SLOT(ReadData()));
    connect(ui->resetButton,SIGNAL(clicked()),this,SLOT(reset()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::reset()
{
    countEffectivePoint = 0;		//initialize the number.
    pkgNumber=0;
    circleNumber=0;
     threshold=130;
     for(int i=0;i<12;i++)
     {
         counter[i]=0;
     }
}

//void QTest::qSleep(int ms){ QTEST_ASSERT(ms > 0);
//                        #ifdef Q_OS_WIN Sleep(uint(ms));
//                        #else struct timespec ts = { ms / 1000, (ms % 1000) * 1000 * 1000 };
//                            nanosleep(&ts, NULL);
//                        #endif}



//#include <QDateTime>

//void MainWindow::sleep(int msec) //自定义Qt延时函数,单位毫秒
//{
//    QDateTime last = QDateTime::currentDateTime();
//    QDateTime now;
//    while (1)
//    {
//        now = QDateTime::currentDateTime();
//        if (last.msecsTo(now) >= msec)
//        {
//            break;
//        }
//    }
//}



//void QSleepTimeSet::Delay_MSec_Suspend(unsigned int msec)
//{

//    QTime _Timer = QTime::currentTime();

//    QTime _NowTimer;
//    do{
//              _NowTimer=QTime::currentTime();
//    }while (_Timer.msecsTo(_NowTimer)<=msec);

//}


//void MainWindow::sleep(unsigned int msec)

//{

//QTime dieTime = QTime::currentTime().addMSecs(msec);

//while( QTime::currentTime() < dieTime )

//QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

//}


//class SleeperThread : public QThread
//{
//public:
//static void msleep(unsigned long msecs)
//{
//QThread::msleep(msecs);
//}
//};

// 调用方法
//SleeperThread::msleep(1000);


void MainWindow::sampling()
{


    const char * opt_com_path = NULL;
    _u32         baudrateArray[2] = {115200, 256000};
    _u32         opt_com_baudrate = 0;
    u_result     op_result;

    bool useArgcBaudrate = false;

    printf("Ultra simple LIDAR data grabber for RPLIDAR.\n",
           "Version: \"RPLIDAR_SDK_VERSION\"\n");

    // read serial port from the command line...
    //if (argc>1) opt_com_path = argv[1]; // or set to a fixed value: e.g. "com3"

    // read baud rate from the command line if specified...
//    if (argc>2)
//    {
//        opt_com_baudrate = strtoul(argv[2], NULL, 10);
//        useArgcBaudrate = true;
//    }

    if (!opt_com_path) {
#ifdef _WIN32
        // use default com port
        opt_com_path = "\\\\.\\com3";
#else
        opt_com_path = "/dev/ttyUSB0";
#endif
    }

    // create the driver instance
    RPlidarDriver * drv = RPlidarDriver::CreateDriver(DRIVER_TYPE_SERIALPORT);
    if (!drv) {
        fprintf(stderr, "insufficent memory, exit\n");
        exit(-2);
    }

    rplidar_response_device_info_t devinfo;
    bool connectSuccess = false;
    // make connection...
    if(useArgcBaudrate)
    {
        if(!drv)
            drv = RPlidarDriver::CreateDriver(DRIVER_TYPE_SERIALPORT);
        if (IS_OK(drv->connect(opt_com_path, opt_com_baudrate)))
        {
            op_result = drv->getDeviceInfo(devinfo);

            if (IS_OK(op_result))
            {
                connectSuccess = true;
            }
            else
            {
                delete drv;
                drv = NULL;
            }
        }
    }
    else
    {
        size_t baudRateArraySize = (sizeof(baudrateArray))/ (sizeof(baudrateArray[0]));
        for(size_t i = 0; i < baudRateArraySize; ++i)
        {
            if(!drv)
                drv = RPlidarDriver::CreateDriver(DRIVER_TYPE_SERIALPORT);
            if(IS_OK(drv->connect(opt_com_path, baudrateArray[i])))
            {
                op_result = drv->getDeviceInfo(devinfo);

                if (IS_OK(op_result))
                {
                    connectSuccess = true;
                    break;
                }
                else
                {
                    delete drv;
                    drv = NULL;
                }
            }
        }
    }
//    if (!connectSuccess) {

//        fprintf(stderr, "Error, cannot bind to the specified serial port %s.\n"
//            , opt_com_path);
//        goto on_finished;
//    }

    // print out the device serial number, firmware and hardware version number..
    printf("RPLIDAR S/N: ");
    for (int pos = 0; pos < 16 ;++pos) {
        printf("%02X", devinfo.serialnum[pos]);
    }

    printf("\n"
            "Firmware Ver: %d.%02d\n"
            "Hardware Rev: %d\n"
            , devinfo.firmware_version>>8
            , devinfo.firmware_version & 0xFF
            , (int)devinfo.hardware_version);



    // check health...
//    if (!checkRPLIDARHealth(drv)) {
//        goto on_finished;
//    }

//    signal(SIGINT, ctrlc);
    //LidarMgr::GetInstance().lidar_drv->setMotorPWM(pwm);
    //drv->setMotorPWM(565);
    drv->startMotor();
    drv->setMotorPWM(562);
    // start scan...
    drv->startScan(0,1);

    // fetech result and print it out...

    //QFile file("H:\\Users\\Administrator\\Desktop\\Data\\data42.csv");
    QFile file(outputDir);
    file.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream stream( &file);

//    while (1) {
    while (circleNumber< threshold+500) {
        rplidar_response_measurement_node_t nodes[8192];
        size_t   count = _countof(nodes);
        op_result = drv->grabScanData(nodes, count);
        if (IS_OK(op_result)) {
            drv->ascendScanData(nodes, count);
//            ofstream outFile;
//            outFile.open("H:\\Users\\Administrator\\Desktop\\Data\\data40.csv", ios::app);		 //  create the file.
//            QFile file("H:\\Users\\Administrator\\Des/ktop\\Data\\data40.csv");
//            file.open(QIODevice::WriteOnly | QIODevice::Append);
//            QTextStream stream( &file);
            int countEffectivePoint = 0;		//initialize the number.
//            for (int pos = 0; pos < (int)count ; ++pos)
            for (int pos = 0; pos < 360 ; ++pos)
            {
                printf("%s theta: %03.2f Dist: %08.2f Q: %d \n",
                    (nodes[pos].sync_quality & RPLIDAR_RESP_MEASUREMENT_SYNCBIT) ?"S ":"  ",
                    (nodes[pos].angle_q6_checkbit >> RPLIDAR_RESP_MEASUREMENT_ANGLE_SHIFT)/64.0f,
                    nodes[pos].distance_q2/4.0f,
                    nodes[pos].sync_quality >> RPLIDAR_RESP_MEASUREMENT_QUALITY_SHIFT);

                if(circleNumber>= threshold)
                {
                    if (nodes[pos].distance_q2 / 4.0f != 0) countEffectivePoint++;		//count the number of effecive point.
    //                outFile << nodes[pos].distance_q2 / 4.0f << ',';		//write distance data, comma break.
                    ui->textReceive->append(QString::number(nodes[pos].distance_q2 / 4.0f));
                    stream << nodes[pos].distance_q2 / 4.0f << ',';		//write distance data, comma break.
                }


            }
            if(circleNumber>= threshold)
            {
//                float effectivePointRate = ((float)countEffectivePoint) / count;		//calculate the effective point rate.
                float effectivePointRate = ((float)countEffectivePoint) / 360;		//calculate the effective point rate.
                stream << effectivePointRate << "\n";		//write the effective point rate at the end of each line and change line.
            }

//            outFile << effectivePointRate << "\n";		//write the effective point rate at the end of each line and change line.

            circleNumber++;
//            outFile.close();		//close the file.
//            file.close();		//close the file.

        }

//        if (ctrl_c_pressed){
//            break;
//        }
    }

    file.close();		//close the file.

    drv->stop();
    drv->stopMotor();
    // done!
on_finished:
    RPlidarDriver::DisposeDriver(drv);
    drv = NULL;
    //return 0;


//    QByteArray buf;
//    buf = serial->readAll();
//    LiPkgTypeDef liPkg;
//    QFile file("H:\\Users\\Administrator\\Des/ktop\\Data\\data24.csv");
//    file.open(QIODevice::WriteOnly | QIODevice::Append);
//    QTextStream stream( &file);
//        //if(!buf.isEmpty())
//        {
//            lipkg->parsePkg(buf);
//            //if(!lipkg->pkgQueue.isEmpty())
//            {
//                for(int circleNumber=0;circleNumber<500;circleNumber++)     //sampling 500 circle.
//                {
//                    int countEffectivePoint = 0;		//initialize the number.
//                    for(int pkgNumber=0;pkgNumber<30;pkgNumber++)   //one circle consists of 30 package, put in one row.
//                    {
//                        liPkg = lipkg->pkgQueue.dequeue();
//                        for(int i=0;i<POINT_PER_PACK;i++)
//                        {
//                            uint16_t distance = liPkg.LidarPoint[i].Distance;
//                            if(distance!=0) countEffectivePoint++;
//                            //stream << distance << ",";
//                            file.write(QString::number(distance).toUtf8());
//                            file.write(",");
//                        }
//                    }
//                    float effectivePointRate = ((float)countEffectivePoint) / (30*POINT_PER_PACK);		//calculate the effective point rate.
//                    //stream << effectivePointRate <<"\n";		//write the effective point rate at the end of each line and change line.
//                    file.write("\n");
//                }
//            }
//        }
//        file.close();
    //        buf.clear();
}




//void MainWindow::assemble()
//{
//    LiPkgTypeDef liPkg;
//    MapDataTypeDef mapData;

//        QFile file("H:\\Users\\Administrator\\Desktop\\Data\\data21.csv");
//        file.open(QIODevice::WriteOnly | QIODevice::Append);
//        QTextStream stream( &file);

//    while(!pkgQueue.isEmpty())
//    {
//        liPkg = pkgQueue.dequeue();
//        uint32_t diff = ((uint32_t)liPkg.EndAngle + 36000 - (uint32_t)liPkg.StartAngle)%36000;
//        double step = diff /(POINT_PER_PACK-1)/100.0;
//        double start = (double)liPkg.StartAngle/100.0;
//        double end = (double)(liPkg.EndAngle%36000)/100.0;

//        int countEffectivePoint = 0;		//initialize the number.

//        for(int i=0;i<POINT_PER_PACK;i++)
//        {
//            mapData.distance = liPkg.LidarPoint[i].Distance;

//            stream << mapData.distance << ",";

//            mapData.angle = start + i*step;
//            if(mapData.angle>=360.0)
//            {
//                mapData.angle -= 360.0;
//            }
//            mapData.confidence=liPkg.LidarPoint[i].Confidence;
//            mapQueue.enqueue(mapData);
//        }

//            float effectivePointRate = ((float)countEffectivePoint) / POINT_PER_PACK;		//calculate the effective point rate.
//            //outFile << effectivePointRate <<"\n";		//write the effective point rate at the end of each line and change line.

//            stream << effectivePointRate <<"\n";

//        //prevent angle invert
//        mapQueue.last().angle = end;

//    }


//void MainWindow::assemble()
//{
//   // LiPkgTypeDef liPkg;
//    //MapDataTypeDef mapData;
////    QString fileName = QFileDialog::getSaveFileName(this, tr("H:\\Users\\Administrator\\Desktop\\Data\\data19.csv"), qApp->applicationDirPath (),

////                                                tr("Files (*.csv)"));
//    //QFile file(fileName);
//    QByteArray buf;
//    buf = serial->readAll();
//    QString e = ui->textReceive->toPlainText();
//    QFile file("H:\\Users\\Administrator\\Desktop\\Data\\data21.csv");
//    file.open(QIODevice::WriteOnly | QIODevice::Append);
//    QTextStream stream( &file);
////    file.write(e.toUtf8());
////    file.close();

//    while(1)
//    //if(!buf.isEmpty())
//    {
////        QString str = ui->textReceive->toPlainText();
////        str+=tr(buf);
////        ui->textReceive->clear();
////        ui->textReceive->append(str);
//        stream << buf << ",";
//        //file.write(buf.toUtf8());
////        file.write(buf);
//    }
//       file.close();		//close the file.

////    QFile file("data19.csv");
////           if(!file.open(QIODevice::WriteOnly | QIODevice::Append))
////           {
////               std::cerr << "Cannot open file for writing: "
////                         << qPrintable(file.errorString()) << std::endl;
////               //return;
////           }
////           if ( file.open(QIODevice::WriteOnly)) {
////               //QTextStream outFile(&file);
////               QDataStream out(&file);
////               out << QString("the answer is");
////               out << (qint32)42;
//////               while(1)
//////               {
//////                   outFile << serial->readAll() << "/n";
//////               }
//}




void MainWindow::searchSerialPort()
{
    foreach (const QSerialPortInfo &info,QSerialPortInfo::availablePorts())
    {
        QSerialPort serial;
        serial.setPort(info);
        if(serial.open(QIODevice::ReadWrite) && (serial.portName() != ui->PortBox->currentText()))
        {
            ui->PortBox->addItem(serial.portName());
            serial.close();
        }
    }
}







void MainWindow::on_OpenSerialButton_clicked()
{
    //if(ui->OpenSerialButton->text() == tr("打开串口"))
    if(ui->OpenSerialButton->text() == tr("L0/L1采集"))
    {
        serial = new QSerialPort;
        //设置串口名
        serial->setPortName(ui->PortBox->currentText());
        //打开串口
        serial->open(QIODevice::ReadWrite);
        //设置波特率
        serial->setBaudRate(QSerialPort::Baud115200);//设置波特率为115200
        //设置数据位数
        switch (ui->BitBox->currentIndex())
        {
        case 8:
            serial->setDataBits(QSerialPort::Data8);//设置数据位8
            break;
        default:
            break;
        }
        //设置校验位
        switch (ui->ParityBox->currentIndex())
        {
        case 0:
            serial->setParity(QSerialPort::NoParity);
            break;
        default:
            break;
        }
        //设置停止位
        switch (ui->BitBox->currentIndex())
        {
        case 1:
            serial->setStopBits(QSerialPort::OneStop);//停止位设置为1
            break;
        case 2:
            serial->setStopBits(QSerialPort::TwoStop);
        default:
            break;
        }
        //设置流控制
        serial->setFlowControl(QSerialPort::NoFlowControl);//设置为无流控制

        //关闭设置菜单使能
        ui->PortBox->setEnabled(false);
        ui->BaudBox->setEnabled(false);
        ui->BitBox->setEnabled(false);
        ui->ParityBox->setEnabled(false);
        ui->StopBox->setEnabled(false);
        //ui->OpenSerialButton->setText(tr("关闭串口"));
        ui->OpenSerialButton->setText(tr("停止采集"));

        //连接信号槽
        //QObject::connect(serial,&QSerialPort::readyRead,this,&MainWindow::sampling);
        QObject::connect(serial,&QSerialPort::readyRead,this,&MainWindow::ReadData);
        QObject::connect(this,&MainWindow::on_SendButton_clicked,this,&MainWindow::ReadData);
        //QObject::connect(ui->lidarBox,SIGNAL(valueChanged(int)),this,SLOT(setOutputDir()));
    }
    else
    {
        //关闭串口
        serial->clear();
        serial->close();
        serial->deleteLater();

        //恢复设置使能
        ui->PortBox->setEnabled(true);
        ui->BaudBox->setEnabled(true);
        ui->BitBox->setEnabled(true);
        ui->ParityBox->setEnabled(true);
        ui->StopBox->setEnabled(true);
        //ui->OpenSerialButton->setText(tr("打开串口"));
        ui->OpenSerialButton->setText(tr("L0/L1采集"));

    }




}
//读取接收到的信息
void MainWindow::ReadData()
{
    //ui->textReceive->append(outputDir);

//    QByteArray buf;
//    buf = serial->readAll();
//    LiPkgTypeDef liPkg;
//    QFile file("H:\\Users\\Administrator\\Des/ktop\\Data\\data24.csv");
//    file.open(QIODevice::WriteOnly | QIODevice::Append);
//    QTextStream stream(&file);
//    //if(!buf.isEmpty())
//    {
//        lipkg->parsePkg(buf);
//        //if(!lipkg->pkgQueue.isEmpty())
//        {
//            for(int circleNumber=0;circleNumber<500;circleNumber++)     //sampling 500 circle.
//            {
//                int countEffectivePoint = 0;		//initialize the number.
//                for(int pkgNumber=0;pkgNumber<30;pkgNumber++)   //one circle consists of 30 package, put in one row.
//                {
//                    liPkg = lipkg->pkgQueue.dequeue();
//                    for(int i=0;i<POINT_PER_PACK;i++)
//                    {
//                        uint16_t distance = liPkg.LidarPoint[i].Distance;
//                        if(distance!=0) countEffectivePoint++;
//                        ui->textReceive->append(QString::number(distance));
//                        stream << distance << ",";
////                            file.write(QString::number(distance).toUtf8());
////                            file.write(",");
//                    }
//                }
//                float effectivePointRate = ((float)countEffectivePoint) / (30*POINT_PER_PACK);		//calculate the effective point rate.
//                stream << effectivePointRate <<"\n";		//write the effective point rate at the end of each line and change line.
//                //file.write("\n");
//            }
//        }
//    }
//        file.close();
//        buf.clear();


    if(circleNumber<500)
    {
        //QFile file("H:\\Users\\Administrator\\Desktop\\Data\\data43.csv");
        QFile file(outputDir);
        file.open(QIODevice::WriteOnly | QIODevice::Append);
        QTextStream stream( &file);
        if(pkgNumber<30)
        {
            QByteArray buf;
            buf = serial->readAll();
            if(!buf.isEmpty())
            {
                lipkg->parsePkg(buf);
                buf.clear();
                while(lipkg->pkgQueue.isEmpty())
                {
                    Sleep(5);
                }
                LiPkgTypeDef liPkg;
                liPkg = lipkg->pkgQueue.dequeue();
                for(int i=0;i<POINT_PER_PACK;i++)
                {
                    //sleep(10);
                    uint16_t distance = liPkg.LidarPoint[i].Distance;
                    if(distance!=0) countEffectivePoint++;
                    ui->textReceive->append(QString::number(distance));
                    //qDebug()<<distance<<endl;
                    stream << distance << ",";
//                            file.write(QString::number(distance).toUtf8());
//                            file.write(",");
                }
                pkgNumber++;
            }
        }
        else if(pkgNumber==30)
        {
            float effectivePointRate = ((float)countEffectivePoint) / (30*POINT_PER_PACK);		//calculate the effective point rate.
            stream << effectivePointRate <<"\n";		//write the effective point rate at the end of each line and change line.
            countEffectivePoint=0;
            pkgNumber=0;
            circleNumber++;
        }
        file.close();
    }
//    else if(circleNumber==500)
//    {
//        file.close();
//        circleNumber++;
//    }
    else
        return;




////        QByteArray buf;
////        buf = serial->readAll();
//        LiPkgTypeDef liPkg;
//        QFile file("H:\\Users\\Administrator\\Desktop\\Data\\data37.csv");
//        file.open(QIODevice::WriteOnly | QIODevice::Append);
//        QTextStream stream( &file);
//        int circleNumber=0;
////        if(!buf.isEmpty())
////        {
////            lipkg->parsePkg(buf);
//            while(circleNumber<500)
//            {
//        //        if(!buf.isEmpty())
//        //        {
//        //            lipkg->parsePkg(buf);
//                    int countEffectivePoint = 0;		//initialize the number.
//                    int pkgNumber=0;
//                    while(pkgNumber<30)
//                    {
//                        while(!&QSerialPort::readyRead)
//                        {
//                            Sleep(5);
//                        }
//                        QByteArray buf;
//                        buf = serial->readAll();
//                        //qWait(10);
//                        if(!buf.isEmpty())
//                        {
//                            lipkg->parsePkg(buf);
//                            buf.clear();
//                            while(lipkg->pkgQueue.isEmpty())
//                            {
//                                Sleep(5);
//                            }
//                            liPkg = lipkg->pkgQueue.dequeue();
//                            for(int i=0;i<POINT_PER_PACK;i++)
//                            {
//                                //sleep(10);
//                                uint16_t distance = liPkg.LidarPoint[i].Distance;
//                                if(distance!=0) countEffectivePoint++;
//                                ui->textReceive->append(QString::number(distance));
//                                //qDebug()<<distance<<endl;
//                                stream << distance << ",";
//        //                            file.write(QString::number(distance).toUtf8());
//        //                            file.write(",");
//                            }
//                            pkgNumber++;
//                        }
//                    }
//                    if(pkgNumber==30)
//                    {
//                        float effectivePointRate = ((float)countEffectivePoint) / (30*POINT_PER_PACK);		//calculate the effective point rate.
//                        stream << effectivePointRate <<"\n";		//write the effective point rate at the end of each line and change line.
//                        pkgNumber=0;
//                        circleNumber++;
//                    }
//        //        }
//            }
////        }
//        file.close();


//    QByteArray buf;
//    buf = serial->readAll();
//    LiPkgTypeDef liPkg;
//    QFile file("H:\\Users\\Administrator\\Desktop\\Data\\data29.csv");
//    file.open(QIODevice::WriteOnly | QIODevice::Append);
//    QTextStream stream( &file);
//    int circleNumber=0;
//    if(!buf.isEmpty())
//    {
//        lipkg->parsePkg(buf);
//        while(circleNumber<500)
//        {
//    //        if(!buf.isEmpty())
//    //        {
//    //            lipkg->parsePkg(buf);
//                int countEffectivePoint = 0;		//initialize the number.
//                int pkgNumber=0;
//                while(pkgNumber<30)
//                {
//                    while  (!data_reach)
//                    {
//                        //sleep(5)
//                    }
//                    until do :
//                    //qWait(10);
//                    if(!lipkg->pkgQueue.isEmpty())
//                    {
//                        liPkg = lipkg->pkgQueue.dequeue();
//                        for(int i=0;i<POINT_PER_PACK;i++)
//                        {
//                            //sleep(10);
//                            uint16_t distance = liPkg.LidarPoint[i].Distance;
//                            if(distance!=0) countEffectivePoint++;
//                            ui->textReceive->append(QString::number(distance));
//                            //qDebug()<<distance<<endl;
//                            stream << distance << ",";
//    //                            file.write(QString::number(distance).toUtf8());
//    //                            file.write(",");
//                        }
//                        pkgNumber++;
//                    }
//                }
//                if(pkgNumber==30)
//                {
//                    float effectivePointRate = ((float)countEffectivePoint) / (30*POINT_PER_PACK);		//calculate the effective point rate.
//                    stream << effectivePointRate <<"\n";		//write the effective point rate at the end of each line and change line.
//                    pkgNumber=0;
//                    circleNumber++;
//                }
//    //        }
//        }
//    }
//    file.close();
//    buf.clear();


//    QByteArray buf;
//    buf = serial->readAll();
//    LiPkgTypeDef liPkg;
//    QFile file("H:\\Users\\Administrator\\Desktop\\Data\\data36.csv");
//    file.open(QIODevice::WriteOnly | QIODevice::Append);
//    QTextStream stream( &file);
//    if(!buf.isEmpty())
//    {
//        lipkg->parsePkg(buf);
////        if(!lipkg->pkgQueue.isEmpty())
////        {
////            liPkg = lipkg->pkgQueue.dequeue();
//            for(int circleNumber=0;circleNumber<500;circleNumber++)     //sampling 500 circle.
//            {
//                int countEffectivePoint = 0;		//initialize the number.
//                for(int pkgNumber=0;pkgNumber<30;pkgNumber++)   //one circle consists of 30 package, put in one row.
//                {
//                    //Sleep(10);
//                    //QTest::qWait(10);
//                    //QTest::qSleep(10);
//                    //sleep(100);
//                    //SleeperThread::msleep(10);
//                    //liPkg = lipkg->pkgQueue.dequeue();
////                    if(!buf.isEmpty())
////                    {
////                        lipkg->parsePkg(buf);
//                        if(!lipkg->pkgQueue.isEmpty())
//                        {
//                            liPkg = lipkg->pkgQueue.dequeue();
//                    for(int i=0;i<POINT_PER_PACK;i++)
//                    {
//                        //Sleep(10);
//                        uint16_t distance = liPkg.LidarPoint[i].Distance;
//                        if(distance!=0) countEffectivePoint++;
//                        ui->textReceive->append(QString::number(distance));
//                        //qDebug()<<distance<<endl;
//                        stream << distance << ",";
////                            file.write(QString::number(distance).toUtf8());
////                            file.write(",");
//                    }
//                        }
////                float effectivePointRate = ((float)countEffectivePoint) / (30*POINT_PER_PACK);		//calculate the effective point rate.
////                stream << effectivePointRate <<"\n";		//write the effective point rate at the end of each line and change line.
//                //file.write("\n");
//            }

//                float effectivePointRate = ((float)countEffectivePoint) / (30*POINT_PER_PACK);		//calculate the effective point rate.
//                stream << effectivePointRate <<"\n";		//write the effective point rate at the end of each line and change line.
////            for(int i=0;i<POINT_PER_PACK;i++)
////            {
////                uint16_t distance = liPkg.LidarPoint[i].Distance;
//////                QByteArray distance = liPkg.LidarPoint[i].Distance;
//////                QString dis = ui->textReceive->toPlainText();
//////                dis += tr(distance);
////                ui->textReceive->append(QString::number(distance));
////                stream << distance << ",";
////                //ui->textReceive->append(QString::number(buf));
////            }
////            stream << "\n";
//        }
////                float effectivePointRate = ((float)countEffectivePoint) / (30*POINT_PER_PACK);		//calculate the effective point rate.
////                stream << effectivePointRate <<"\n";		//write the effective point rate at the end of each line and change line.

////        QString str = ui->textReceive->toPlainText();
////        str+=tr(buf);
////        ui->textReceive->clear();
////        ui->textReceive->append(str);
////        stream << buf << ",";
//        //file.write(buf.toUtf8());
////        file.write(buf);
//    }
//    file.close();
//    buf.clear();
}

//发送按钮槽函数
void MainWindow::on_SendButton_clicked()
{
    serial->write(ui->textSend->toPlainText().toLatin1());
}


//#ifndef M_PI
//#define M_PI 3.14159265358979323846
//#endif

//#ifndef M_2PI
//#define M_2PI 6.2831853071795864769
//#endif

//#ifndef DEG2RAD
//#define DEG2RAD(x) ((x) * M_PI / 180.0)
//#endif

//#ifndef RAD2DEG
//#define RAD2DEG(x) ((x) * 180.0 / M_PI)
//#endif

//#define MAP_RESOLUTION 2
//#define MIN_DISTANCE 100
//#define MAX_DISTANCE 1000
//#define LIDAR_RESOLUTION 0.02
//#define IMAGE_SIZE (MAX_DISTANCE/MAP_RESOLUTION+10)*2
//#define DEEPTH 30.0
//#define HZ 6.0
//#define QUALITY 200

//#define FILTER_RADIUS 3

////extern "C" __declspec(dllimport) bool openLiDAR(char * comName);
//extern "C" __declspec(dllimport) bool openLiDAR(const char comName[5]);
//extern "C" __declspec(dllimport) bool isMapReady();
//extern "C" __declspec(dllimport) int getMapData(char *buff);

//typedef struct MapDataTypeDef{
//    float angle;
//    uint16_t distance;
//    uint8_t confidence;
//};


//typedef struct LidarPoint
//{
//    MapDataTypeDef data;
//    int flag;
//    //Point2i p;
//};

//int MainWindow::lidar()
//{
//    //fun();
//    //testInput(argc, argv);

//    getchar();

//    unsigned long long PointLen = sizeof(MapDataTypeDef);
//    char *p = new char[PointLen * 3000];
//    MapDataTypeDef map;
//    LidarPoint tmpPoint;

////    ofstream outFile;
////    //outFile.open(argv[1]);		 //  create the file.
////    outFile.open("H:\\Users\\Administrator\\Desktop\\Data\\data5.csv");		 //  create the file.

//    QFile file("H:\\Users\\Administrator\\Desktop\\Data\\data21.csv");
//    file.open(QIODevice::WriteOnly | QIODevice::Append);
//    QTextStream stream( &file);

//    if (openLiDAR("COM3"))
//    {
//        int frameAmount = 0;		//initialize the frameAmount
//        while (++frameAmount <= 500)		//count the frameAmount
//        {
//            if (isMapReady())
//            {
//                vector<LidarPoint> Lidar2D;

//                int len = getMapData(p)/PointLen -1;
//                char *pt = p;

//                int countEffectivePoint = 0;		//initialize the number.

//                //for (int i = 0; i < len; i++) {
//                for (int i = 0; i < 360; i++) {
//                    tmpPoint.data = *(MapDataTypeDef*)pt;
//                    if (tmpPoint.data.distance > MAX_DISTANCE || tmpPoint.data.distance < MIN_DISTANCE)
//                        tmpPoint.data.distance = 0;
//                    tmpPoint.flag = tmpPoint.data.distance > 0 ? 1 : 0;
//                    tmpPoint.flag = tmpPoint.data.confidence > QUALITY ? 1 : 0;

//                    if (tmpPoint.data.distance != 0) countEffectivePoint++;		//count the number of effecive point.


//                    stream << tmpPoint.data.distance << ",";
//                    //outFile << tmpPoint.data.distance << ',';		//write distance data, comma break.

//                    //tmpPoint.data.angle = (int)(tmpPoint.data.angle + 0.5);
////                    tmpPoint.p.x = tmpPoint.data.distance * sin(DEG2RAD(tmpPoint.data.angle));
////                    tmpPoint.p.y = tmpPoint.data.distance * cos(DEG2RAD(tmpPoint.data.angle));
////                    Lidar2D.push_back(tmpPoint);
////                    pt += PointLen;
//                }

//                float effectivePointRate = ((float)countEffectivePoint) / len;		//calculate the effective point rate.
//                //outFile << effectivePointRate <<"\n";		//write the effective point rate at the end of each line and change line.

//                stream << effectivePointRate <<"\n";


////                sort(Lidar2D.begin(), Lidar2D.end(), cmp_angle);

////                vector<Point2i> vpos;
////                WriteLidar(Lidar2D, "lidar original", vpos);

////                Point2i ChargPos;
////                float angle;
////                FindCharger(Lidar2D, ChargPos, angle, vpos);

////                WriteLidar(Lidar2D, "lidar", vpos);
////                waitKey(100);
//            }
//        }
//    }

//    file.close();
//    //outFile.close();		//close the file.

//    delete p;

//    getchar();

//    return 0;
//}


//void MainWindow::selectSDKPath()
//{
//    if(ui->lidarBox->currentIndex() == 0 || ui->lidarBox->currentIndex() == 1)
//        SDKPath = "H:\\Users\\Administrator\\Desktop\\Project\\LiDAR\\x64\\Debug\\LiDAR.exe";       //L0,L1
//    //if(ui->lidarBox->currentIndex() == 2)
//                //EAI
//    //if(ui->lidarBox->currentIndex() == 3 || ui->lidarBox->currentIndex() == 4)
//                //Air1,Air2
//}



void MainWindow::updateDisplay()
{
//    file("H:\\Users\\Administrator\\Desktop\\Data\\data37.csv");
//    file.open(QIODevice::WriteOnly | QIODevice::Append);
//    stream(&file);
//    ui->textReceive->setText((QString)file);
    ui->textReceive->setText(outputDir);
}



//void MainWindow::invokeSDK()
//{
//    QProcess *process=new QProcess();
//    QStringList strlist;
//    strlist.append(outputDir);
//    process->setWorkingDirectory( "./QtProject3" );
//    process->setProgram("QtProject3/LiDAR.exe");
//    //process->start();
//    process->setArguments(strlist);
//    process->start(QIODevice::ReadWrite);
//    process->start( QApplication::applicationDirPath() + "QtProject3/LiDAR.exe" );
//    //process->start(SDKPath,strlist);
//    process->waitForStarted();
//    process->waitForFinished();
//}



void MainWindow::setOutputDir()
{
    switch (ui->lidarBox->currentIndex())
    {
    case 0:
        outputDirPart1 = "H:\\Users\\Administrator\\Desktop\\DataSet\\L0";
        break;
    case 1:
        outputDirPart1 = "H:\\Users\\Administrator\\Desktop\\DataSet\\L1";
        break;
    case 2:
        outputDirPart1 = "H:\\Users\\Administrator\\Desktop\\DataSet\\EAI";
        break;
    case 3:
        outputDirPart1 = "H:\\Users\\Administrator\\Desktop\\DataSet\\A1";
        break;
    case 4:
        outputDirPart1 = "H:\\Users\\Administrator\\Desktop\\DataSet\\A2";
        break;
    default:
        break;
    }

    switch (ui->envirBox->currentIndex())
    {
    case 0:
        outputDirPart2 = "\\WhiteWall";
        break;
    case 1:
        outputDirPart2 = "\\BlackWall";
        break;
    case 2:
        outputDirPart2 = "\\Plank";
        break;
    case 3:
        outputDirPart2 = "\\Mirror";
        break;
    case 4:
        outputDirPart2 = "\\TestRoom\\testroomData" + QString::number(++counter[0]) + ".csv";
        break;
    case 5:
        outputDirPart2 = "\\Hall\\hallData" + QString::number(++counter[1]) + ".csv";
        break;
    case 6:
        outputDirPart2 = "\\MeetingRoom\\meetingroomData" + QString::number(++counter[2]) + ".csv";
        break;
    case 7:
        outputDirPart2 = "\\DarkRoom\\darkroom" + QString::number(++counter[3]) + ".csv";
        break;
    case 8:
        outputDirPart2 = "\\Corridor\\corridor" + QString::number(++counter[4]) + ".csv";
        break;
    default:
        break;
    }

    switch (ui->condiBox->currentIndex())
    {
    case 0:
        outputDirPart3 = "\\1m\\1m" + QString::number(++counter[5]) + ".csv";
        break;
    case 1:
        outputDirPart3 = "\\2m\\2m" + QString::number(++counter[6]) + ".csv";
        break;
    case 2:
        outputDirPart3 = "\\3m\\3m" + QString::number(++counter[7]) + ".csv";
        break;
    case 3:
        outputDirPart3 = "\\4m\\4m" + QString::number(++counter[8]) + ".csv";
        break;
    case 4:
        outputDirPart3 = "\\6m\\6m" + QString::number(++counter[9]) + ".csv";
        break;
    case 5:
        outputDirPart3 = "\\30degree\\30degree" + QString::number(++counter[10]) + ".csv";
        break;
    case 6:
        outputDirPart3 = "\\60degree\\60degree" + QString::number(++counter[11]) + ".csv";
        break;
    default:
        break;
    }

    if(ui->envirBox->currentIndex() >= 0 && ui->envirBox->currentIndex() <= 3)
    {
        outputDir = outputDirPart1 + outputDirPart2 + outputDirPart3;
    }
    if(ui->envirBox->currentIndex() >= 4 && ui->envirBox->currentIndex() <= 8)
    {
        outputDir = outputDirPart1 + outputDirPart2;
    }
}

/*

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
*/
