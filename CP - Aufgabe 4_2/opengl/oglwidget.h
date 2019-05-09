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
    OGLWidget(QWidget *parent = nullptr);
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
    void changePlace( int dx, int dy, int dz );

public slots:
    // Set the rotation angles
    void setRotX( int newrx );
    void setRotY( int newry );
    void setRotZ( int newrz );

    // Set Place
    void setPlaceX( int newPlaceX );
    void setPlaceY( int newPlaceX );


    void setCubeRotX( int newrx );
    void setCubeRotY( int newry );
    void setCubeRotZ( int newrz );
    void setCubeSize( int newrz );

    // Set zoom factor
    void setZoom( int newzoom );

    // Set light position
    void setLight(int newlight );


protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void EinheitsQuadrat();
    void EinheitsWuerfel();
    void bodenFlaeche();

protected:
    int rotx;       // Rotation angles (0..360)
    int roty;
    int rotz;
    float placeX;
    float placeY;

    float cubeRotX;
    float cubeRotY;
    float cubeRotZ;
    float cubeSize;
    int zoom;       // Zoom factor (0..200, 100 for 1:1)
    int light;      // Light position (0..360, around y axis)
    float PI;
    boolean wuerfel;
    QPoint lastpos; // Last position of mouse pressed, used for dragging
};


#endif // OGLWIDGET_H
