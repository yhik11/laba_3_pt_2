/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QSpinBox *spinBoxA;
    QSpinBox *spinBoxB;
    QSpinBox *spinBoxC;
    QSlider *SliderA;
    QSlider *SliderB;
    QSlider *SliderC;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(628, 260);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(90, 60, 63, 20));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(270, 60, 63, 20));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(460, 60, 63, 20));
        spinBoxA = new QSpinBox(centralwidget);
        spinBoxA->setObjectName("spinBoxA");
        spinBoxA->setGeometry(QRect(60, 100, 71, 29));
        spinBoxB = new QSpinBox(centralwidget);
        spinBoxB->setObjectName("spinBoxB");
        spinBoxB->setGeometry(QRect(250, 100, 71, 29));
        spinBoxC = new QSpinBox(centralwidget);
        spinBoxC->setObjectName("spinBoxC");
        spinBoxC->setGeometry(QRect(440, 100, 71, 29));
        SliderA = new QSlider(centralwidget);
        SliderA->setObjectName("SliderA");
        SliderA->setGeometry(QRect(20, 140, 160, 18));
        SliderA->setOrientation(Qt::Horizontal);
        SliderB = new QSlider(centralwidget);
        SliderB->setObjectName("SliderB");
        SliderB->setGeometry(QRect(210, 140, 160, 18));
        SliderB->setOrientation(Qt::Horizontal);
        SliderC = new QSlider(centralwidget);
        SliderC->setObjectName("SliderC");
        SliderC->setGeometry(QRect(400, 140, 160, 18));
        SliderC->setOrientation(Qt::Horizontal);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 628, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "A", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "B", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "C", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
