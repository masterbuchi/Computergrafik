#ifndef OGLWIDGET_H
#define OGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMouseEvent>
#include <QTimer>
#include <QVector3D>
#include "kugel.h"


class OGLWidget : public QOpenGLWidget,
        protected QOpenGLFunctions
{
    Q_OBJECT

public:
    OGLWidget(QWidget *parent = nullptr) ;
    ~OGLWidget();

    // Used to rotate object by mouse
    void mousePressEvent(QMouseEvent *event);

    void mouseReleaseEvent(QMouseEvent *event);


    void mouseMoveEvent(QMouseEvent *event);

    // Used to rotate object by keys (requires focus for OpenGL widget)
    void keyPressEvent(QKeyEvent *event);

signals:
    // Emitted whenever a change of rotation angles is requested (e.g. by mouse or key)
    void changeRotation( int dx, int dy, int dz );

public slots:
    // Set the rotation angles
    void setRotX( int newrx );
    void setRotY( int newry );
    void setRotZ( int newrz );

    //    void setWinkelX(int newwinkelX);
    //    void setWinkelZ(int newwinkelZ);

    // Set zoom factor
    void setZoom( int newzoom );

    // Set unfolding position
    void setUnfold( int newunfold );

    void stepAnimation();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

protected:
    QTimer* animtimer; // Timer needed to step animation every x msec
    int animstep;      // Current animation step (used to rotate triangle
    void Bahn();
    void Pfeil();
    void Kreis(double xmp, double ymp, double zmp, double r);


    void SetMaterialColor(int side, double r, double g, double b);

public:

    // Ziel
    int zpx = 4;
    int zpz = 8;
    // Anzahl der Kanten;
    int Kanten=8;
    int Zeilen = Kanten;
    int Spalten = 2;


    // Koordinaten des Randes
    int* points=new int[Zeilen*Spalten] {-2,-2,-2,6,2,6,2,10,6,10,6,2,2,2,2,-2};


    //    int points [Kanten][2] {
    //        {-2,-2},
    //        {-2,6},
    //        {2,6},
    //        {2,10},
    //        {6,10},
    //        {6,2},
    //        {2,2},
    //        {2,-2}
    //    };

    int rotx=0;       // Rotation angles (0..360)
    int roty=0;
    int rotz=0;

    int width = 1200;

    Kugel kugel_1;
    Kugel kugel_2;


    double pos_x;
    double pos_y;
    double pos_z;

    double mdx = 0;
    double mdz = 0;

    boolean shoot = false;



    // ZEIT
    double dt;

    double PI = 3.1415;
    float PIf = 3.1415f;


    int zoom;       // Zoom factor (0..200, 100 for 1:1)


    double unfold;     // Unfolding position (0..100, 0 closed)
    QPoint lastpos; // Last position of mouse pressed, used for dragging
};


#endif // OGLWIDGET_H
