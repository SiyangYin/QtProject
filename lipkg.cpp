#include "lipkg.h"
#include "QDebug"
#include<QtMath>
#include<map>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore/QProcess>
#include <iostream>
#include <QtCore/QTextStream>
#include <QtCore/QIODevice>
using namespace std;

LiPkg::LiPkg(QObject *parent) : QObject(parent)
{
    //Ui::MainWindow *ui = (new Ui::MainWindow);
//    extern Ui::MainWindow *ui;
    //extern Ui::MainWindow ui;
    //connect(this,SIGNAL(pkgReady()),this,SLOT(assemble()));
    //connect(ui->startButton,SIGNAL(clicked()),this,SLOT(assemble()));
}

static const uint8_t CrcTable[256] =
{
    0x00, 0x4d, 0x9a, 0xd7, 0x79, 0x34, 0xe3,
    0xae, 0xf2, 0xbf, 0x68, 0x25, 0x8b, 0xc6, 0x11, 0x5c, 0xa9, 0xe4, 0x33,
    0x7e, 0xd0, 0x9d, 0x4a, 0x07, 0x5b, 0x16, 0xc1, 0x8c, 0x22, 0x6f, 0xb8,
    0xf5, 0x1f, 0x52, 0x85, 0xc8, 0x66, 0x2b, 0xfc, 0xb1, 0xed, 0xa0, 0x77,
    0x3a, 0x94, 0xd9, 0x0e, 0x43, 0xb6, 0xfb, 0x2c, 0x61, 0xcf, 0x82, 0x55,
    0x18, 0x44, 0x09, 0xde, 0x93, 0x3d, 0x70, 0xa7, 0xea, 0x3e, 0x73, 0xa4,
    0xe9, 0x47, 0x0a, 0xdd, 0x90, 0xcc, 0x81, 0x56, 0x1b, 0xb5, 0xf8, 0x2f,
    0x62, 0x97, 0xda, 0x0d, 0x40, 0xee, 0xa3, 0x74, 0x39, 0x65, 0x28, 0xff,
    0xb2, 0x1c, 0x51, 0x86, 0xcb, 0x21, 0x6c, 0xbb, 0xf6, 0x58, 0x15, 0xc2,
    0x8f, 0xd3, 0x9e, 0x49, 0x04, 0xaa, 0xe7, 0x30, 0x7d, 0x88, 0xc5, 0x12,
    0x5f, 0xf1, 0xbc, 0x6b, 0x26, 0x7a, 0x37, 0xe0, 0xad, 0x03, 0x4e, 0x99,
    0xd4, 0x7c, 0x31, 0xe6, 0xab, 0x05, 0x48, 0x9f, 0xd2, 0x8e, 0xc3, 0x14,
    0x59, 0xf7, 0xba, 0x6d, 0x20, 0xd5, 0x98, 0x4f, 0x02, 0xac, 0xe1, 0x36,
    0x7b, 0x27, 0x6a, 0xbd, 0xf0, 0x5e, 0x13, 0xc4, 0x89, 0x63, 0x2e, 0xf9,
    0xb4, 0x1a, 0x57, 0x80, 0xcd, 0x91, 0xdc, 0x0b, 0x46, 0xe8, 0xa5, 0x72,
    0x3f, 0xca, 0x87, 0x50, 0x1d, 0xb3, 0xfe, 0x29, 0x64, 0x38, 0x75, 0xa2,
    0xef, 0x41, 0x0c, 0xdb, 0x96, 0x42, 0x0f, 0xd8, 0x95, 0x3b, 0x76, 0xa1,
    0xec, 0xb0, 0xfd, 0x2a, 0x67, 0xc9, 0x84, 0x53, 0x1e, 0xeb, 0xa6, 0x71,
    0x3c, 0x92, 0xdf, 0x08, 0x45, 0x19, 0x54, 0x83, 0xce, 0x60, 0x2d, 0xfa,
    0xb7, 0x5d, 0x10, 0xc7, 0x8a, 0x24, 0x69, 0xbe, 0xf3, 0xaf, 0xe2, 0x35,
    0x78, 0xd6, 0x9b, 0x4c, 0x01, 0xf4, 0xb9, 0x6e, 0x23, 0x8d, 0xc0, 0x17,
    0x5a, 0x06, 0x4b, 0x9c, 0xd1, 0x7f, 0x32, 0xe5, 0xa8
};


void LiPkg::parsePkg(const QByteArray &data)
{
    foreach(char c,data)
    {
        dataQueue<<(uint8_t)c;
    }

    if(dataQueue.size()<sizeof(LiPkgTypeDef))
        return;

    if(dataQueue.size()>sizeof(LiPkgTypeDef)*100)
    {
        pkgErrorCounter++;
        emit errorIncrease();
        dataQueue.clear();
        return;
    }

    uint16_t start = 0;

    while(start<dataQueue.size() -1)
    {
        start = 0;
        while(start<dataQueue.size() -1)
        {
            if((dataQueue[start] == PKG_HEADER)&&(dataQueue[start+1] == PKG_VER_LEN))
            {
                break;
            }

            if((dataQueue[start] == PKG_HEADER)&&(dataQueue[start+1] == (PKG_VER_LEN | (0x07<<5))))
            {
                break;
            }


            start++;
        }

        if(start!=0)
        {
            pkgErrorCounter++;
            emit errorIncrease();
            for(int i=0;i<start;i++)
            {
                dataQueue.dequeue();
            }
        }

        if(dataQueue.size()<sizeof(LiPkgTypeDef))
            return;

        uint8_t tmp[sizeof(LiPkgTypeDef)];
        for(int i = 0;i<sizeof(LiPkgTypeDef);i++)
        {
            tmp[i] = dataQueue[i];
        }

        LiPkgTypeDef liPkg = *(LiPkgTypeDef *)tmp;
        uint8_t crc = 0;

        for (int i = 0; i < sizeof(LiPkgTypeDef) - 1; i++)
        {
            crc = CrcTable[(crc ^ tmp[i]) & 0xff];
        }

        if(crc == liPkg.Crc8)
        {
            double diff =(liPkg.EndAngle/100-liPkg.StartAngle/100+360)%360;
            if(diff>(double)liPkg.Speed*POINT_PER_PACK/2300*3/2)
            {
                qDebug()<<"diff angle:";
                qDebug()<<(liPkg.StartAngle/100 - 150 + 360)%360<<(liPkg.EndAngle/100 - 150 + 360)%360<<diff;
//                pkgErrorCounter++;
//                emit errorIncrease();
            }
            if(liPkg.VerAndLength & (0x7<<5))
            {
                version = *(qint32 *)liPkg.LidarPoint;
                qDebug()<<hex<<version;
            }
            pkgQueue.enqueue(liPkg);
            speed.enqueue(liPkg.Speed);
            timestamp.enqueue(liPkg.Timestamp);
            emit pkgReady();
            for(int i = 0;i<sizeof(LiPkgTypeDef);i++)
            {
                dataQueue.dequeue();
            }
        }
        else
        {
            pkgErrorCounter++;
            emit errorIncrease();
            /*only remove header,not all frame,because lidar data may contain head*/
            for(int i = 0;i<2;i++)
            {
                dataQueue.dequeue();
            }
        }

    }

    return;
}

uint32_t LiPkg::getPkgErrorCount(void)
{
    return pkgErrorCounter;
}

void LiPkg::clearPkgErrorCount()
{
    pkgErrorCounter = 0;
}

void LiPkg::setConvertEnable(bool enable)
{
    isConvertEnable = enable;
}

uint32_t LiPkg::getMapErrorCount()
{
    return mapErrorCounter;
}

double LiPkg::getSpeed(void)
{
    double speed;
    if(!this->speed.isEmpty())
    {
        speed =  this->speed.last();

        return speed/360.0;
    }
    else
    {
        return 0;
    }
}

uint16_t LiPkg::getTimestamp(void)
{
    if(!this->timestamp.isEmpty())
    {
        return this->timestamp.last();
    }
    else
    {
        return 0;
    }
}

uint32_t LiPkg::getValidPointAmount()
{
    uint32_t amount = 0;
    for(MapDataTypeDef m : map)
    {
        if(m.distance != 0)
            amount++;
    }

    return amount;
}

uint32_t LiPkg::getPointAmount()
{
    return mapEndPoint - mapStartPoint;
}

double LiPkg::getMapFrameRate()
{
    if(mapFrameRate != 0)
        return 1000.0/(double)mapFrameRate;
    else
        return 0;
}

QList<LiPkg::MapDataTypeDef> LiPkg::getMap(void)
{
    return this->map;
}

uint16_t LiPkg::getAnglePos(float angle)
{
    uint16_t i =0;
    std::pair<float , int> angle_pair;
    std::map<float , int> angle_map;

    for(MapDataTypeDef m : this->map)
    {
        angle_pair = std::make_pair(m.angle,i++);
        angle_map.insert(angle_pair);
    }

    float lastAngle;
    uint16_t lastPos;
    for(auto data : angle_map)
    {
        if(data.first == 720)
            break;

        if(data.first > angle)
        {
            if(data.first - angle > 2)
            {
                return map.size()-1;
            }
            else
            {
                float diffLast = abs(angle - lastAngle);
                float diffCurrent = abs(angle - data.second);

                if(diffLast < diffCurrent)
                {
                    return lastPos;
                }
                else
                {
                    return data.second;
                }
            }
        }
        lastAngle = data.first;
        lastPos = data.second;
    }

    if(abs(lastAngle  - angle) <2)
    {
        return lastPos;
    }
    else
    {
        return map.size()-1;
    }
}

uint16_t LiPkg::getSingleDistance(float angle)
{
    uint16_t pos = getAnglePos(angle);

    uint16_t distance = this->map[pos].distance;

    return distance;
}

uint16_t LiPkg::getSingleConfidence(float angle)
{
    uint16_t pos = getAnglePos(angle);

    uint16_t confidence = this->map[pos].confidence;

    return confidence;
}

QList<uint8_t> LiPkg::getVersion()
{
    QList<uint8_t> v;
    v.append(version>>24);
    v.append((version>>16) &0xff);
    v.append(version&0xffff);

    return v;
}

int LiPkg::findTransitionPoint(uint32_t startPos)
{
    int transitionPos = -1;

    for(int i=startPos;i<mapQueue.size()-1;i++)
    {
        if(mapQueue[i+1].angle-mapQueue[i].angle < 0)
        {
            if((mapQueue[i+1].angle < 10)&&mapQueue[i].angle>350)
            {
                transitionPos = i+1;
                break;
            }
        }
    }

    return transitionPos;
}

void LiPkg::clearBuffer()
{
    for(int i=0;i<mapStartPoint;i++)
        mapQueue.dequeue();
    mapEndPoint -= mapStartPoint;
    for(int i=0;i<speed.size()-1;i++)
    {
        speed.dequeue();
    }

    for(int i=0;i<timestamp.size()-1;i++)
    {
        timestamp.dequeue();
    }
}

bool LiPkg::isMapRight()
{
    if(mapEndPoint - mapStartPoint < 250)
    {
        mapErrorCounter++;
        emit errorIncrease();
        return false;
    }

    return true;
}

void LiPkg::assemble()
{
    LiPkgTypeDef liPkg;
    MapDataTypeDef mapData;

        QFile file("C:\\Users\\12170\\Desktop\\Data\\data23.csv");
        file.open(QIODevice::WriteOnly | QIODevice::Append);
        QTextStream stream( &file);
//        QByteArray buf;
//        QSerialPort *serial = new QSerialPort ;
//        buf = serial->readAll();
//        while(1)
//        {
//            for(int i= 0 ; i <= 360 ; i++ )
//            {
//                stream << buf << ",";
//            }
//            stream << "\n";
//        }


    while(!pkgQueue.isEmpty())
    {
        liPkg = pkgQueue.dequeue();
        uint32_t diff = ((uint32_t)liPkg.EndAngle + 36000 - (uint32_t)liPkg.StartAngle)%36000;
        double step = diff /(POINT_PER_PACK-1)/100.0;
        double start = (double)liPkg.StartAngle/100.0;
        double end = (double)(liPkg.EndAngle%36000)/100.0;

        int countEffectivePoint = 0;		//initialize the number.

        for(int i=0;i<POINT_PER_PACK;i++)
        {
            mapData.distance = liPkg.LidarPoint[i].Distance;

            stream << mapData.distance << ",";

            mapData.angle = start + i*step;
            if(mapData.angle>=360.0)
            {
                mapData.angle -= 360.0;
            }
            mapData.confidence=liPkg.LidarPoint[i].Confidence;
            mapQueue.enqueue(mapData);
        }

            float effectivePointRate = ((float)countEffectivePoint) / POINT_PER_PACK;		//calculate the effective point rate.
            //outFile << effectivePointRate <<"\n";		//write the effective point rate at the end of each line and change line.

            stream << effectivePointRate <<"\n";

        //prevent angle invert
        mapQueue.last().angle = end;

    }

    file.close();

    int newStart = (mapEndPoint >3)?mapEndPoint-3:mapEndPoint;

    int transitionPoint = findTransitionPoint(newStart);
    if(transitionPoint != -1)
    {
        mapStartPoint = transitionPoint;
        transitionPoint = findTransitionPoint(mapStartPoint + 50);
        if(transitionPoint != -1)
        {
            mapEndPoint = transitionPoint;

            if(isMapRight())
            {
                updateFrameRate();
                cacheMap();
                emit mapReady();
            }

            //            if(mapStartPoint>400)
            //                qDebug()<<mapStartPoint;

            if(isRecordEnable == false)
            {
                clearBuffer();
            }
        }
    }
}


void LiPkg::updateFrameRate()
{
    if(rateTimer.isValid())
    {
        mapFrameRate = rateTimer.elapsed();
        rateTimer.restart();
    }
    else
    {
        rateTimer.start();
    }
}

void LiPkg::cacheMap()
{
    map.clear();

    for(int i=mapStartPoint;i<mapEndPoint;i++)
    {
        if(mapQueue[i].distance != 0)
            map<<mapQueue[i];
    }

    if(isConvertEnable)
    {
        for(int i=0;i<map.size();i++)
        {
            double beta = 0;
            if(map[i].distance!=0)
            {
                beta= 57.2957 * qTan(23.1629 / (float)map[i].distance - 0.1192);
                map[i].angle += beta;
            }

            map[i].angle+=360.0;
            if(map[i].angle>=360.0)
            {
                map[i].angle -= 360.0;
            }
        }

    }

    MapDataTypeDef nullPoint;
    nullPoint.angle = 720;
    nullPoint.confidence = 0;
    nullPoint.distance = 0;

    map.append(nullPoint);
}
