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
    void setEckenbeschl();

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
    void Boden();
    void Pfeil();
    Vector3 CheckKollisionKugel(Kugel eins, Kugel zwei);
    void Kreis(double xmp, double ymp, double zmp, double r);
    Vector3 KollisionmitWand(Kugel kugel, Vector3 ov1, Vector3 ov2);
    Vector3 Lotschnittpunkt(Kugel kugel, Vector3 ov1, Vector3 rv, Vector3 norm);
    Vector3 Eckenbeschleunigung(Kugel eins, Vector3 ov);


    void SetMaterialColor(int side, double r, double g, double b);

public:

    // Ziel
    int zpx = -12;
    int zpz = 6;



    // Anzahl der Kanten;
    int Kanten=17;
    int Zeilen = Kanten;
    int Spalten = 2;
    int Versuche = 0;
    boolean eckenbeschl = true;

    // Koordinaten des Randes
    //    int* points=new int[Zeilen*Spalten] {-2,-2,-2,6,2,6,2,10,6,10,6,2,2,2,2,-2};
    //    int* points=new int[Zeilen*Spalten] {-5,-2,-5,1,-7,1,-7,4,-3,4,-1,3,0,4,3,4,3,1,0,1,-1,2,-3,3,-5,3,-4,2,-3,2,-3,-2};
    //    int* points=new int[Zeilen*Spalten] {-8,-6,-8,8,-16,20,-16,28,-32,28,-36,16,-36,8,-28,20,-16,12,-24,0,-48,0,-48,16,-40,36,0,36,0,18,8,8,8,-6};
    int* points=new int[Zeilen*Spalten] {-4,-3,-4,4,-8,10,-8,14,-16,14,-18,8,-18,4,-14,10,-8,6,-12,0,-24,0,-24,8,-20,18,0,18,0,9,4,4,4,-3};



    int rotx=0;       // Rotation angles (0..360)
    int roty=0;
    int rotz=0;

    int width = 1200;

    Kugel kugel_1;
    Kugel kugel_2;
    Kugel kugel_3;

    double pos_x;
    double pos_y;
    double pos_z;

    double mdx = 0;
    double mdz = 0;

    boolean shoot = false;

    int trans_lr;
    int trans_ou;



    // ZEIT
    double dt;

    double PI = 3.1415;
    float PIf = 3.1415f;


    int zoom;       // Zoom factor (0..200, 100 for 1:1)


    double unfold;     // Unfolding position (0..100, 0 closed)
    QPoint lastpos; // Last position of mouse pressed, used for dragging
};


#endif // OGLWIDGET_H
