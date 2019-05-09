/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDial>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
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
    QDial *xRot;
    QLabel *lbZoom;
    QDial *yRot;
    QLabel *lbYRot;
    QLabel *lbXRot;
    QDial *ecken;
    QLabel *lbZRot;
    QDial *zRot;
    QLabel *lbEcken;
    QDial *zoom;
    QMenuBar *menuBar;
    QMenu *menuPyramide;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(910, 961);
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
        glwidget->setFocusPolicy(Qt::StrongFocus);

        verticalLayout->addWidget(glwidget);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        xRot = new QDial(centralWidget);
        xRot->setObjectName(QString::fromUtf8("xRot"));
        xRot->setMaximum(360);
        xRot->setWrapping(true);

        gridLayout->addWidget(xRot, 1, 1, 1, 1);

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

        lbYRot = new QLabel(centralWidget);
        lbYRot->setObjectName(QString::fromUtf8("lbYRot"));

        gridLayout->addWidget(lbYRot, 0, 2, 1, 1, Qt::AlignHCenter);

        lbXRot = new QLabel(centralWidget);
        lbXRot->setObjectName(QString::fromUtf8("lbXRot"));

        gridLayout->addWidget(lbXRot, 0, 1, 1, 1, Qt::AlignHCenter);

        ecken = new QDial(centralWidget);
        ecken->setObjectName(QString::fromUtf8("ecken"));
        ecken->setMinimum(3);
        ecken->setMaximum(20);
        ecken->setValue(7);

        gridLayout->addWidget(ecken, 1, 0, 1, 1);

        lbZRot = new QLabel(centralWidget);
        lbZRot->setObjectName(QString::fromUtf8("lbZRot"));

        gridLayout->addWidget(lbZRot, 0, 3, 1, 1, Qt::AlignHCenter);

        zRot = new QDial(centralWidget);
        zRot->setObjectName(QString::fromUtf8("zRot"));
        zRot->setMaximum(360);
        zRot->setWrapping(true);

        gridLayout->addWidget(zRot, 1, 3, 1, 1);

        lbEcken = new QLabel(centralWidget);
        lbEcken->setObjectName(QString::fromUtf8("lbEcken"));
        lbEcken->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lbEcken, 0, 0, 1, 1);

        zoom = new QDial(centralWidget);
        zoom->setObjectName(QString::fromUtf8("zoom"));
        zoom->setMaximum(200);
        zoom->setValue(100);
        zoom->setWrapping(false);

        gridLayout->addWidget(zoom, 1, 4, 1, 1);


        verticalLayout->addLayout(gridLayout);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 910, 26));
        menuPyramide = new QMenu(menuBar);
        menuPyramide->setObjectName(QString::fromUtf8("menuPyramide"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuPyramide->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        lbZoom->setText(QApplication::translate("MainWindow", "Zoom", nullptr));
        lbYRot->setText(QApplication::translate("MainWindow", "Y", nullptr));
        lbXRot->setText(QApplication::translate("MainWindow", "X", nullptr));
        lbZRot->setText(QApplication::translate("MainWindow", "Z", nullptr));
        lbEcken->setText(QApplication::translate("MainWindow", "Ecken", nullptr));
        menuPyramide->setTitle(QApplication::translate("MainWindow", "Pyramide", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
