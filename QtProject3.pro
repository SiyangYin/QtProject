#-------------------------------------------------
#
# Project created by QtCreator 2018-07-16T09:58:06
#
#-------------------------------------------------

QT       += core gui
QT       += serialport
#QT       += testlib
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SerialPortTool
TARGET = QtProject3
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DEFINES-= UNICODE

SOURCES += main.cpp\
        mainwindow.cpp \
    stdafx.cpp \
    lipkg.cpp \
    debug/moc_lipkg.cpp \
    debug/moc_mainwindow.cpp \
    sdk/src/rplidar_driver.cpp \
    sdk/src/hal/thread.cpp \
    sdk/src/arch/win32/net_serial.cpp \
    sdk/src/arch/win32/net_socket.cpp \
    sdk/src/arch/win32/timer.cpp

HEADERS  += mainwindow.h \
    stdafx.h \
    targetver.h \
    lipkg.h \
    debug/moc_predefs.h \
    sdk/include/rplidar.h \
    sdk/include/rplidar_cmd.h \
    sdk/include/rplidar_driver.h \
    sdk/include/rplidar_protocol.h \
    sdk/include/rptypes.h \
    sdk/src/rplidar_driver_impl.h \
    sdk/src/rplidar_driver_serial.h \
    sdk/src/rplidar_driver_TCP.h \
    sdk/src/sdkcommon.h \
    sdk/src/hal/abs_rxtx.h \
    sdk/src/hal/assert.h \
    sdk/src/hal/byteops.h \
    sdk/src/hal/event.h \
    sdk/src/hal/locker.h \
    sdk/src/hal/socket.h \
    sdk/src/hal/thread.h \
    sdk/src/hal/types.h \
    sdk/src/hal/util.h \
    sdk/src/arch/win32/arch_win32.h \
    sdk/src/arch/win32/net_serial.h \
    sdk/src/arch/win32/timer.h \
    sdk/src/arch/win32/winthread.hpp \
    ../../../../../Program Files (x86)/Windows Kits/10/Include/10.0.16299.0/ucrt/signal.h \
    sdk/src/hal/signal.h

UI_DIR= H:/Users/Administrator/Desktop/QtProject/build-QtProject3-Desktop_Qt_5_8_0_MSVC2015_64bit-Debug/debug \
        H:/Users/Administrator/Desktop/QtProject/build-QtProject3-Desktop_Qt_5_8_0_MSVC2015_64bit-Debug \
        H:/Users/Administrator/Desktop/QtProject/QtProject3
FORMS    += mainwindow.ui

INCLUDEPATH += H:/Users/Administrator/Downloads/opencv/build/include \
               H:/Users/Administrator/Downloads/opencv/build/include/opencv \
               H:/Users/Administrator/Downloads/opencv/build/include/opencv2 \
               H:/Users/Administrator/Desktop/QtProject/QtProject3/sdk/include \
               H:/Users/Administrator/Desktop/QtProject/QtProject3/sdk/src \
               H:/Users/Administrator/Desktop/QtProject/QtProject3/sdk/src/arch \
               H:/Users/Administrator/Desktop/QtProject/QtProject3/sdk/src/hal \
               #H:/Program Files (x86)/Windows Kits/10/Include/10.0.16299.0/ucrt
               H:/Program Files (x86)/Windows Kits/10/Include/10.0.17134.0/ucrt
               #H:/Qt/Qt5.6.1/5.6/mingw49_32/include/QtTest

CONFIG += C++11
#LIBS += H:/opencv/x86/mingw/lib/libopencv_*
#LIBS +=$$quote(H:/Users/Administrator/Downloads/opencv/build/x64/vc14/lib/opencv_world342d.lib) \

#INCLUDEPATH += C:\Users\Administrator\Downloads\opencv\build\include D:/vs2013/opencv/build/include

CONFIG(debug, debug|release): {
#LIBS +=$$quote(H:/Users/Administrator/Downloads/opencv/build/x64/vc14/lib/opencv_world342d.lib) \
        #H:/Qt/Qt5.6.1/5.6/mingw49_32/include/QtTest
#LIBS += -LD:/vs2013/opencv/build/x64/vc12/lib \

#-lopencv_core249d \
#-lopencv_imgproc249d \
#-lopencv_highgui249d \
#-lopencv_ml249d \
#-lopencv_video249d \
#-lopencv_features2d249d \
#-lopencv_calib3d249d \
#-lopencv_objdetect249d \
#-lopencv_contrib249d \
#-lopencv_legacy249d \
#-lopencv_flann249d
#} else:CONFIG(release, debug|release): {
#LIBS += -LD:/vs2013/opencv/build/x64/vc12/lib \
#-lopencv_core249 \
#-lopencv_imgproc249 \
#-lopencv_highgui249 \
#-lopencv_ml249 \
#-lopencv_video249 \
#-lopencv_features2d249 \
#-lopencv_calib3d249 \
#-lopencv_objdetect249 \
#-lopencv_contrib249 \
#-lopencv_legacy249 \
#-lopencv_flann249
}

DISTFILES += \
    opencv_world340d.lib \
    qtdialog.lib \
    D3Dcompiler_47.dll \
    libEGL.dll \
    libGLESV2.dll \
    opengl32sw.dll \
    Qt5Core.dll \
    Qt5Gui.dll \
    Qt5SerialPort.dll \
    Qt5Svg.dll \
    Qt5Widgets.dll \
    qtdialog.dll \
    translations/qt_bg.qm \
    translations/qt_ca.qm \
    translations/qt_cs.qm \
    translations/qt_da.qm \
    translations/qt_de.qm \
    translations/qt_en.qm \
    translations/qt_es.qm \
    translations/qt_fi.qm \
    translations/qt_fr.qm \
    translations/qt_gd.qm \
    translations/qt_he.qm \
    translations/qt_hu.qm \
    translations/qt_it.qm \
    translations/qt_ja.qm \
    translations/qt_ko.qm \
    translations/qt_lv.qm \
    translations/qt_pl.qm \
    translations/qt_ru.qm \
    translations/qt_sk.qm \
    translations/qt_uk.qm \
    iconengines/qsvgicon.dll \
    platforms/qwindows.dll \
    imageformats/qgif.dll \
    imageformats/qicns.dll \
    imageformats/qico.dll \
    imageformats/qjpeg.dll \
    imageformats/qsvg.dll \
    imageformats/qtga.dll \
    imageformats/qtiff.dll \
    imageformats/qwbmp.dll \
    imageformats/qwebp.dll \
    debug/LiDAR.pdb \
    debug/QtProject3.pdb \
    debug/QtProject3.vc.pdb \
    debug/opencv_world340d.lib \
    debug/qtdialog.lib \
    debug/D3Dcompiler_47.dll \
    debug/libEGL.dll \
    debug/libGLESV2.dll \
    debug/opengl32sw.dll \
    debug/Qt5Core.dll \
    debug/Qt5Gui.dll \
    debug/Qt5SerialPort.dll \
    debug/Qt5Svg.dll \
    debug/Qt5Widgets.dll \
    debug/qtdialog.dll \
    debug/lipkg.obj \
    debug/main.obj \
    debug/mainwindow.obj \
    debug/moc_lipkg.obj \
    debug/moc_mainwindow.obj \
    debug/stdafx.obj
