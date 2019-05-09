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
#include <QtWidgets/QDial>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
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
    QGridLayout *gridLayout;
    QLabel *label;
    QLabel *lbYRot;
    QLabel *lbZoom;
    QDial *yRot;
    QDial *light;
    QDial *xRot;
    QDial *zRot;
    QDial *zoom;
    QLabel *lbZRot;
    QLabel *lbXRot;
    QLabel *lbUnfold;
    QDial *rotateX;
    QLabel *label_2;
    QDial *rotateY;
    QLabel *label_3;
    QDial *rotateZ;
    QLabel *label_4;
    QDial *sizeCube;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(792, 593);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        glwidget = new OGLWidget(centralWidget);
        glwidget->setObjectName(QString::fromUtf8("glwidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(glwidget->sizePolicy().hasHeightForWidth());
        glwidget->setSizePolicy(sizePolicy1);
        glwidget->setFocusPolicy(Qt::StrongFocus);

        verticalLayout->addWidget(glwidget);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 2, 0, 1, 1);

        lbYRot = new QLabel(centralWidget);
        lbYRot->setObjectName(QString::fromUtf8("lbYRot"));

        gridLayout->addWidget(lbYRot, 0, 2, 1, 1, Qt::AlignHCenter);

        lbZoom = new QLabel(centralWidget);
        lbZoom->setObjectName(QString::fromUtf8("lbZoom"));

        gridLayout->addWidget(lbZoom, 0, 4, 1, 1, Qt::AlignHCenter);

        yRot = new QDial(centralWidget);
        yRot->setObjectName(QString::fromUtf8("yRot"));
        yRot->setMaximum(360);
        yRot->setValue(0);
        yRot->setWrapping(true);
        yRot->setNotchesVisible(false);

        gridLayout->addWidget(yRot, 1, 2, 1, 1);

        light = new QDial(centralWidget);
        light->setObjectName(QString::fromUtf8("light"));
        light->setMaximum(360);
        light->setWrapping(true);
        light->setNotchesVisible(false);

        gridLayout->addWidget(light, 1, 0, 1, 1);

        xRot = new QDial(centralWidget);
        xRot->setObjectName(QString::fromUtf8("xRot"));
        xRot->setMaximum(360);
        xRot->setWrapping(true);

        gridLayout->addWidget(xRot, 1, 1, 1, 1);

        zRot = new QDial(centralWidget);
        zRot->setObjectName(QString::fromUtf8("zRot"));
        zRot->setMaximum(360);
        zRot->setWrapping(true);

        gridLayout->addWidget(zRot, 1, 3, 1, 1);

        zoom = new QDial(centralWidget);
        zoom->setObjectName(QString::fromUtf8("zoom"));
        zoom->setMaximum(200);
        zoom->setValue(100);
        zoom->setWrapping(false);

        gridLayout->addWidget(zoom, 1, 4, 1, 1);

        lbZRot = new QLabel(centralWidget);
        lbZRot->setObjectName(QString::fromUtf8("lbZRot"));

        gridLayout->addWidget(lbZRot, 0, 3, 1, 1, Qt::AlignHCenter);

        lbXRot = new QLabel(centralWidget);
        lbXRot->setObjectName(QString::fromUtf8("lbXRot"));

        gridLayout->addWidget(lbXRot, 0, 1, 1, 1, Qt::AlignHCenter);

        lbUnfold = new QLabel(centralWidget);
        lbUnfold->setObjectName(QString::fromUtf8("lbUnfold"));

        gridLayout->addWidget(lbUnfold, 0, 0, 1, 1, Qt::AlignHCenter);

        rotateX = new QDial(centralWidget);
        rotateX->setObjectName(QString::fromUtf8("rotateX"));
        rotateX->setMinimum(1);
        rotateX->setMaximum(100);

        gridLayout->addWidget(rotateX, 3, 0, 1, 1);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 2, 1, 1, 1);

        rotateY = new QDial(centralWidget);
        rotateY->setObjectName(QString::fromUtf8("rotateY"));
        rotateY->setMinimum(1);
        rotateY->setMaximum(100);

        gridLayout->addWidget(rotateY, 3, 1, 1, 1);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 2, 1, 1);

        rotateZ = new QDial(centralWidget);
        rotateZ->setObjectName(QString::fromUtf8("rotateZ"));
        rotateZ->setMinimum(1);
        rotateZ->setMaximum(100);

        gridLayout->addWidget(rotateZ, 3, 2, 1, 1);

        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 2, 3, 1, 1);

        sizeCube = new QDial(centralWidget);
        sizeCube->setObjectName(QString::fromUtf8("sizeCube"));
        sizeCube->setMinimum(1);
        sizeCube->setMaximum(100);
        sizeCube->setSingleStep(1);

        gridLayout->addWidget(sizeCube, 3, 3, 1, 1);


        verticalLayout->addLayout(gridLayout);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 792, 17));
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
        label->setText(QApplication::translate("MainWindow", "<html><head/><body><p align=\"center\">Rot X-Achse</p></body></html>", nullptr));
        lbYRot->setText(QApplication::translate("MainWindow", "Y", nullptr));
        lbZoom->setText(QApplication::translate("MainWindow", "Zoom", nullptr));
        lbZRot->setText(QApplication::translate("MainWindow", "Z", nullptr));
        lbXRot->setText(QApplication::translate("MainWindow", "X", nullptr));
        lbUnfold->setText(QApplication::translate("MainWindow", "Light", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "<html><head/><body><p align=\"center\">Rot Y-Achse</p></body></html>", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "<html><head/><body><p align=\"center\">Rot Z-Achse</p></body></html>", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "<html><head/><body><p align=\"center\">Size</p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
