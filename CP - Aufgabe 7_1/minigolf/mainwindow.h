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

    int width = 800;

private slots:
    void onChangeRotation( int dx, int dy, int dz );

private:
    Ui::MainWindow *ui;



};

#endif // MAINWINDOW_H
