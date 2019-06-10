#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent=nullptr);
    ~MainWindow();
//    virtual int heightForWidth ( int w ) const { return w*9/16;};
    int width = 1200;

private slots:
    void onChangeRotation( int dx, int dy, int dz );

private:
    Ui::MainWindow *ui;



};

#endif // MAINWINDOW_H


//class MyWidget:public QWidget
//{
//public:
//  MyWidget():QWidget(){};
//  ~MyWidget(){};
//  virtual int heightForWidth ( int w ) const { return w*9/16;};
//};
