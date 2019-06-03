#include "mainwindow.h"
#include <QApplication>
#include <QSizePolicy>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
     QDesktopWidget dw;
    MainWindow w;

//    QSizePolicy qsp(QSizePolicy::Preferred,QSizePolicy::Preferred);
//    qsp.setHeightForWidth(true);




    int y=int(dw.height()*0.8);
    w.setFixedSize(y,y);
//    w.resize(QSize(w.width, w.width));


    w.show();

    return a.exec();
}





