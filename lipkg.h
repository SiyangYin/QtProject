#ifndef LIPKG_H
#define LIPKG_H

#include <QObject>
#include "pro.h"
#include <QQueue>
#include "QTime"
#include <QApplication>
#include <QFileDialog>
#include <QDebug>
#include <QString>
#include <mainwindow.h>

class LiPkg : public QObject
{
    Q_OBJECT

public:
    typedef struct
    {
        float angle;
        uint16_t distance;
        uint8_t confidence;
    }MapDataTypeDef;

public:
    explicit LiPkg(QObject *parent = nullptr);
    void parsePkg(const QByteArray &data);
    uint32_t getPkgErrorCount(void);

    uint32_t getMapErrorCount(void);
    void clearMapErrorCount(void);

    double getSpeed(void);
    double getMapFrameRate(void);
    uint16_t getTimestamp(void);
    uint32_t getValidPointAmount(void);
    uint32_t getPointAmount(void);
    QList<MapDataTypeDef> getMap(void);
    uint16_t getAnglePos(float angle);
    uint16_t getSingleDistance(float angle);
    uint16_t getSingleConfidence(float angle);
    QList<uint8_t> getVersion();


signals:
    void pkgReady(void);
    void mapReady(void);
    void errorIncrease();


public slots:
    void clearPkgErrorCount();
    void setConvertEnable(bool enable);
//private:
public:
    QQueue<uint8_t> dataQueue;
    QQueue<LiPkgTypeDef> pkgQueue;
    QQueue<MapDataTypeDef>mapQueue;
    quint32 pkgErrorCounter = 0;
    quint32 mapErrorCounter = 0;
    QQueue<uint16_t> speed;
    QQueue<uint16_t> timestamp;
    QList<MapDataTypeDef> map;
    int mapStartPoint=0;
    int mapEndPoint=0;
    bool isRecordEnable = false;
    bool isConvertEnable = true;
    QTime rateTimer;
    uint16_t mapFrameRate = 0;
    quint32 version;

private:
    int findTransitionPoint(uint32_t start);
    void clearBuffer(void);
    bool isMapRight(void);
    void updateFrameRate();
    void cacheMap();

//private slots:
public slots:
    void assemble();

};

#endif // LIPKG_H
