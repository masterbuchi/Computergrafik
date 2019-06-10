#ifndef OGLWIDGET_H
#define OGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMouseEvent>
#include <QTimer>
#include <QVector3D>
#include "kugel.h"
#include "vector4.h"


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
    Vector4 CheckKollisionKugel(Kugel eins, Kugel zwei);
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
    const int Kanten=24;
    int Zeilen = Kanten;
    const int Spalten = 2;
    int Punkte = 0;
    boolean eckenbeschl = true;

    // Koordinaten des Randes
    //    int* points=new int[Zeilen*Spalten] {-2,-2,-2,6,2,6,2,10,6,10,6,2,2,2,2,-2};
    //    int* points=new int[Zeilen*Spalten] {-5,-2,-5,1,-7,1,-7,4,-3,4,-1,3,0,4,3,4,3,1,0,1,-1,2,-3,3,-5,3,-4,2,-3,2,-3,-2};
    //    int* points=new int[Zeilen*Spalten] {-8,-6,-8,8,-16,20,-16,28,-32,28,-36,16,-36,8,-28,20,-16,12,-24,0,-48,0,-48,16,-40,36,0,36,0,18,8,8,8,-6};
    double* points=new double[Zeilen*Spalten]
    {
            -8.59,0,
            -10,-1.41,
            -11.41,0,
            -10,1.41,
            -10,18.9,
            -12,19.2,
            -12,20.9,
            -10,21.1,
            -10,38.59,
            -11.41,40,
            -10,41.41,
            -8.59,40,
            8.59,40,
            10,41.41,
            11.41,40,
            10,38.59,
            10,21.1,
            12,20.9,
            12,19.2,
            10,18.9,
            10,1.41,
            11.41,0,
            10,-1.41,
            8.59,0
};



    int rotx=0;       // Rotation angles (0..360)
    int roty=0;
    int rotz=0;

    Kugel kugel_1;
    Kugel kugel_2;
    Kugel kugel_3;
    Kugel kugel_4;

    double pos_x;
    double pos_y;
    double pos_z;

    double mdx = 0;
    double mdz = 0;

    boolean shoot = false;

    double trans_lr;
    double trans_ou;



    // ZEIT
    double dt;

    double PI = 3.1415;
    float PIf = 3.1415f;


    int zoom;       // Zoom factor (0..200, 100 for 1:1)


    double unfold;     // Unfolding position (0..100, 0 closed)
    QPoint lastpos; // Last position of mouse pressed, used for dragging
};


#endif // OGLWIDGET_H
