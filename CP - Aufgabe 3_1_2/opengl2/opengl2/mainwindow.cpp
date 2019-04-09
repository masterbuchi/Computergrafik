#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Connect slider A to change param A in OGLWidget
    connect(ui->sliderA, SIGNAL(valueChanged(int)), ui->glwidget, SLOT(setParamA(int)));

    // Connect slider B to change param B in OGLWidget
    connect(ui->sliderB, SIGNAL(valueChanged(int)), ui->glwidget, SLOT(setParamB(int)));

    // Connect slider C to change param C in OGLWidget
    connect(ui->sliderC, SIGNAL(valueChanged(int)), ui->glwidget, SLOT(setParamC(int)));

    // Connect slider D to change param D in OGLWidget
    connect(ui->sliderD, SIGNAL(valueChanged(int)), ui->glwidget, SLOT(setParamD(int)));

    // Connect slider R to change param R in OGLWidget
    connect(ui->sliderR, SIGNAL(valueChanged(int)), ui->glwidget, SLOT(setParamR(int)));

}

MainWindow::~MainWindow()
{
    delete ui;
}
