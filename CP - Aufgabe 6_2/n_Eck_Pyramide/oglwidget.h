#ifndef OGLWIDGET_H
#define OGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMouseEvent>
#include <QTimer>


class OGLWidget : public QOpenGLWidget,
                  protected QOpenGLFunctions
{
    Q_OBJECT

public:
    OGLWidget(QWidget *parent = nullptr);
    ~OGLWidget();

    // Used to rotate object by mouse
    void mousePressEvent(QMouseEvent *event);
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

    // Set zoom factor
    void setZoom( int newzoom );

    // Set unfolding position
    void setUnfold( int newunfold );


    void stepAnimation();


protected:
    void initializeGL();
    //void resizeGL(int w, int h);
    void paintGL();

protected:
    QTimer* animtimer; // Timer needed to step animation every x msec
    int animstep;      // Current animation step (used to rotate triangle
    void Tisch();
    void SetMaterialColor(int side, double r, double g, double b);

protected:
    double c;
    double dt;
    double px=0.0;
    double dx=-1;
    double py=0.0;
    double dy=1;
    double pz=0.0;
    double dz=2;

    double sx;
    double sz;


    // Anzahl der Ecken;
    double Ecken=7.0;

    // Größe des Feldes
    double s = 0;



    // Winkel in Radian
    double rot_rad = 2.0*3.14159/Ecken;




    int rotx=0;       // Rotation angles (0..360)
    int roty=0;
    int rotz=0;
    int zoom;       // Zoom factor (0..200, 100 for 1:1)


    double unfold;     // Unfolding position (0..100, 0 closed)
    QPoint lastpos; // Last position of mouse pressed, used for dragging
};


#endif // OGLWIDGET_H
