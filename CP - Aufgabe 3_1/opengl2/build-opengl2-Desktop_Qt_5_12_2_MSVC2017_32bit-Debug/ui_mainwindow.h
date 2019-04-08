/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "oglwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    OGLWidget *glwidget;
    QSlider *sliderA;
    QSlider *sliderB;
    QSlider *sliderC;
    QSlider *sliderD;
    QSlider *sliderR;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(742, 716);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        glwidget = new OGLWidget(centralWidget);
        glwidget->setObjectName(QString::fromUtf8("glwidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(glwidget->sizePolicy().hasHeightForWidth());
        glwidget->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(glwidget);

        sliderA = new QSlider(centralWidget);
        sliderA->setObjectName(QString::fromUtf8("sliderA"));
        sliderA->setMaximum(100);
        sliderA->setSingleStep(1);
        sliderA->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(sliderA);

        sliderB = new QSlider(centralWidget);
        sliderB->setObjectName(QString::fromUtf8("sliderB"));
        sliderB->setMaximum(100);
        sliderB->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(sliderB);

        sliderC = new QSlider(centralWidget);
        sliderC->setObjectName(QString::fromUtf8("sliderC"));
        sliderC->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(sliderC);

        sliderD = new QSlider(centralWidget);
        sliderD->setObjectName(QString::fromUtf8("sliderD"));
        sliderD->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(sliderD);

        sliderR = new QSlider(centralWidget);
        sliderR->setObjectName(QString::fromUtf8("sliderR"));
        sliderR->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(sliderR);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 742, 26));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
