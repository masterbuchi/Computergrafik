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

public slots:
    void stepAnimation();


protected:
    void initializeGL();
    //void resizeGL(int w, int h);
    void paintGL();

protected:
    QTimer* animtimer; // Timer needed to step animation every x msec
    int animstep;      // Current animation step (used to rotate triangle
    void Kugel();
    void Tisch();
    void SetMaterialColor(int side, double r, double g, double b);

protected:
    float c;
    float dt;
    float px=0.0f;
    int dx=1;
    float py=0.0f;
    int dy=1;
    float pz=0.0f;
    int dz=2;


    // Anzahl der Ecken;
    double Ecken=180.0;
    double EckenArray[9][2];

    int rotx=0;       // Rotation angles (0..360)
    int roty=0;
    int rotz=0;
    int zoom;       // Zoom factor (0..200, 100 for 1:1)
//    float M_PI;
    float unfold;     // Unfolding position (0..100, 0 closed)
    QPoint lastpos; // Last position of mouse pressed, used for dragging
};


#endif // OGLWIDGET_H
