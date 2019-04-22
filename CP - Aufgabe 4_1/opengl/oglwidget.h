#ifndef OGLWIDGET_H
#define OGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMouseEvent>
#include <QVector3D>

class OGLWidget : public QOpenGLWidget,
                  protected QOpenGLFunctions
{
    Q_OBJECT

public:
    OGLWidget(QWidget *parent = 0);
    ~OGLWidget();

    // Used to rotate object by mouse
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    // Used to rotate object by keys (requires focus for OpenGL widget)
    void keyPressEvent(QKeyEvent *event);

    // Draw a sphere with center pos, radius rad and nr_lat/nr_lon segments
    void drawSphere(const QVector3D &pos,
                    float rad = 1.f,
                    int nr_lat = 90, int nr_lon = 90 );
signals:
    // Emitted whenever a change of rotation angles is requested (e.g. by mouse or key)
    void changeRotation( int dx, int dy, int dz );

public slots:
    // Set the rotation angles
    void setRotX( int newrx );
    void setRotY( int newry );
    void setRotZ( int newrz );

    // Set Variables and Delta
    void setVarA( int newA );
    void setVarB( int newB );
    void setVarC( int newC );
    void setVarDelta( int newDelta );

    // Set zoom factor
    void setZoom( int newzoom );

    // Set light position
    void setLight(int newlight );


protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void testFunktion(float a, float b, float c);

protected:
    int rotx;       // Rotation angles (0..360)
    int roty;
    int rotz;
    float varA;
    float varB;
    float varC;
    float varDelta;
    int zoom;       // Zoom factor (0..200, 100 for 1:1)
    int light;      // Light position (0..360, around y axis)
    float PI;
    QPoint lastpos; // Last position of mouse pressed, used for dragging
};


#endif // OGLWIDGET_H
