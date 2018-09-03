/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QComboBox *PortBox;
    QComboBox *BaudBox;
    QComboBox *BitBox;
    QComboBox *ParityBox;
    QLabel *label_4;
    QLabel *label_6;
    QComboBox *StopBox;
    QPushButton *OpenSerialButton;
    QTextEdit *textReceive;
    QTextEdit *textSend;
    QPushButton *SendButton;
    QLabel *label_5;
    QComboBox *lidarBox;
    QLabel *label_7;
    QComboBox *envirBox;
    QLabel *label_8;
    QComboBox *condiBox;
    QPushButton *startButton;
    QPushButton *updateButton;
    QPushButton *searchButton;
    QPushButton *resetButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(424, 427);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 20, 54, 12));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 60, 54, 12));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(20, 100, 54, 12));
        PortBox = new QComboBox(centralWidget);
        PortBox->setObjectName(QStringLiteral("PortBox"));
        PortBox->setGeometry(QRect(110, 20, 69, 22));
        PortBox->setEditable(false);
        BaudBox = new QComboBox(centralWidget);
        BaudBox->setObjectName(QStringLiteral("BaudBox"));
        BaudBox->setGeometry(QRect(110, 60, 69, 22));
        BitBox = new QComboBox(centralWidget);
        BitBox->setObjectName(QStringLiteral("BitBox"));
        BitBox->setGeometry(QRect(110, 90, 69, 22));
        ParityBox = new QComboBox(centralWidget);
        ParityBox->setObjectName(QStringLiteral("ParityBox"));
        ParityBox->setGeometry(QRect(110, 130, 69, 22));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(20, 130, 61, 16));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(20, 170, 54, 12));
        StopBox = new QComboBox(centralWidget);
        StopBox->setObjectName(QStringLiteral("StopBox"));
        StopBox->setGeometry(QRect(110, 170, 69, 22));
        OpenSerialButton = new QPushButton(centralWidget);
        OpenSerialButton->setObjectName(QStringLiteral("OpenSerialButton"));
        OpenSerialButton->setGeometry(QRect(310, 310, 81, 23));
        textReceive = new QTextEdit(centralWidget);
        textReceive->setObjectName(QStringLiteral("textReceive"));
        textReceive->setGeometry(QRect(210, 20, 161, 181));
        textSend = new QTextEdit(centralWidget);
        textSend->setObjectName(QStringLiteral("textSend"));
        textSend->setGeometry(QRect(210, 220, 161, 31));
        SendButton = new QPushButton(centralWidget);
        SendButton->setObjectName(QStringLiteral("SendButton"));
        SendButton->setGeometry(QRect(110, 220, 75, 31));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(20, 280, 54, 12));
        lidarBox = new QComboBox(centralWidget);
        lidarBox->setObjectName(QStringLiteral("lidarBox"));
        lidarBox->setGeometry(QRect(110, 280, 69, 22));
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(220, 280, 54, 12));
        envirBox = new QComboBox(centralWidget);
        envirBox->setObjectName(QStringLiteral("envirBox"));
        envirBox->setGeometry(QRect(310, 280, 69, 22));
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(20, 330, 54, 12));
        condiBox = new QComboBox(centralWidget);
        condiBox->setObjectName(QStringLiteral("condiBox"));
        condiBox->setGeometry(QRect(110, 330, 69, 22));
        startButton = new QPushButton(centralWidget);
        startButton->setObjectName(QStringLiteral("startButton"));
        startButton->setGeometry(QRect(304, 340, 91, 23));
        updateButton = new QPushButton(centralWidget);
        updateButton->setObjectName(QStringLiteral("updateButton"));
        updateButton->setGeometry(QRect(210, 310, 75, 23));
        searchButton = new QPushButton(centralWidget);
        searchButton->setObjectName(QStringLiteral("searchButton"));
        searchButton->setGeometry(QRect(10, 210, 75, 23));
        resetButton = new QPushButton(centralWidget);
        resetButton->setObjectName(QStringLiteral("resetButton"));
        resetButton->setGeometry(QRect(210, 340, 75, 23));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 424, 23));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        PortBox->setCurrentIndex(-1);
        BaudBox->setCurrentIndex(4);
        BitBox->setCurrentIndex(0);
        ParityBox->setCurrentIndex(0);
        StopBox->setCurrentIndex(0);
        lidarBox->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "\344\270\262\345\217\243", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "\346\263\242\347\211\271\347\216\207", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "\346\225\260\346\215\256\344\275\215", Q_NULLPTR));
        BaudBox->clear();
        BaudBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "9600", Q_NULLPTR)
         << QApplication::translate("MainWindow", "19200", Q_NULLPTR)
         << QApplication::translate("MainWindow", "38400", Q_NULLPTR)
         << QApplication::translate("MainWindow", "57600", Q_NULLPTR)
         << QApplication::translate("MainWindow", "115200", Q_NULLPTR)
        );
        BaudBox->setCurrentText(QApplication::translate("MainWindow", "115200", Q_NULLPTR));
        BitBox->clear();
        BitBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "8", Q_NULLPTR)
        );
        ParityBox->clear();
        ParityBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "0", Q_NULLPTR)
        );
        label_4->setText(QApplication::translate("MainWindow", "\346\240\241\351\252\214\344\275\215", Q_NULLPTR));
        label_6->setText(QApplication::translate("MainWindow", "\345\201\234\346\255\242\344\275\215", Q_NULLPTR));
        StopBox->clear();
        StopBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "1", Q_NULLPTR)
        );
        OpenSerialButton->setText(QApplication::translate("MainWindow", "L0/L1\351\207\207\351\233\206", Q_NULLPTR));
        SendButton->setText(QApplication::translate("MainWindow", "\346\265\213\350\257\225", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "\351\233\267\350\276\276\347\261\273\345\236\213", Q_NULLPTR));
        lidarBox->clear();
        lidarBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "L0", Q_NULLPTR)
         << QApplication::translate("MainWindow", "L1", Q_NULLPTR)
         << QApplication::translate("MainWindow", "EAI", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Air1", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Air2", Q_NULLPTR)
        );
        label_7->setText(QApplication::translate("MainWindow", "\346\265\213\350\257\225\347\216\257\345\242\203", Q_NULLPTR));
        envirBox->clear();
        envirBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "\347\231\275\345\242\231", Q_NULLPTR)
         << QApplication::translate("MainWindow", "\351\273\221\345\242\231", Q_NULLPTR)
         << QApplication::translate("MainWindow", "\346\234\250\346\235\277", Q_NULLPTR)
         << QApplication::translate("MainWindow", "\347\216\273\347\222\203", Q_NULLPTR)
         << QApplication::translate("MainWindow", "\346\265\213\350\257\225\346\210\277", Q_NULLPTR)
         << QApplication::translate("MainWindow", "\345\244\247\345\216\205", Q_NULLPTR)
         << QApplication::translate("MainWindow", "\344\274\232\350\256\256\345\256\244", Q_NULLPTR)
         << QApplication::translate("MainWindow", "\345\260\217\351\273\221\345\261\213", Q_NULLPTR)
         << QApplication::translate("MainWindow", "\350\265\260\345\273\212", Q_NULLPTR)
        );
        label_8->setText(QApplication::translate("MainWindow", "\346\265\213\350\257\225\346\235\241\344\273\266", Q_NULLPTR));
        condiBox->clear();
        condiBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "1m", Q_NULLPTR)
         << QApplication::translate("MainWindow", "2m", Q_NULLPTR)
         << QApplication::translate("MainWindow", "3m", Q_NULLPTR)
         << QApplication::translate("MainWindow", "4m", Q_NULLPTR)
         << QApplication::translate("MainWindow", "6m", Q_NULLPTR)
         << QApplication::translate("MainWindow", "30\345\272\246", Q_NULLPTR)
         << QApplication::translate("MainWindow", "60\345\272\246", Q_NULLPTR)
        );
        startButton->setText(QApplication::translate("MainWindow", "Air1/Air2\351\207\207\351\233\206", Q_NULLPTR));
        updateButton->setText(QApplication::translate("MainWindow", "\346\233\264\346\226\260", Q_NULLPTR));
        searchButton->setText(QApplication::translate("MainWindow", "\346\237\245\346\211\276\344\270\262\345\217\243", Q_NULLPTR));
        resetButton->setText(QApplication::translate("MainWindow", "\351\207\215\347\275\256", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
