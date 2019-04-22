#include "oglwidget.h"
#include <cmath>
#include <QDebug>

OGLWidget::OGLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    light = 0;
    rotx  = 0;
    roty  = 0;
    rotz  = 0;
    cubeRotX = 0;
    cubeRotY = 0;
    cubeRotZ = 0;

    cubeSize = 1.0f;


    placeX = 0;
    placeY = 0;
    zoom  = 100;
    PI = 3.14159f;
    wuerfel = false;
}

OGLWidget::~OGLWidget()
{
}


void OGLWidget::setRotX(int newrx)
{
    rotx = newrx;
    update();
}

void OGLWidget::setRotY(int newry)
{
    roty = newry;
    update();
}

void OGLWidget::setRotZ(int newrz)
{
    rotz = newrz;
    update();
}


void OGLWidget::setCubeRotX(int newrx)
{
    cubeRotX = newrx*3.6f;
    update();
}

void OGLWidget::setCubeRotY(int newry)
{
    cubeRotY = newry*3.6f;
    update();
}

void OGLWidget::setCubeRotZ(int newrz)
{
    cubeRotZ = newrz*3.6f;
    update();
}


void OGLWidget::setCubeSize(int newrz)
{
    cubeSize = newrz*3.6f/10;
    update();
}

void OGLWidget::setZoom(int newzoom)
{
    zoom = newzoom;
    update();
}

void OGLWidget::setLight(int newlight)
{
    light = newlight;
    update();
}

void OGLWidget::setPlaceX(int newPlaceX)
{
    if (newPlaceX == 0)
        placeX = 0;
    else {

        if((placeX <=20) && (placeX >=-20))
            placeX = placeX + newPlaceX/10.0f;
    }
    update();
}

void OGLWidget::setPlaceY(int newPlaceY)
{

    if (newPlaceY == 0)
        placeY = 0;
    else {
        if ((placeY <=20) && (placeY >=-20))
            placeY = placeY + newPlaceY/10.0f;
        update();
    }
}


void OGLWidget::drawSphere( const QVector3D& pos, float rad,
                            int nr_lat, int nr_lon )
{
    // Angle delta in both directions
    const float lat_delta = PI / float( nr_lat );
    const float lon_delta = PI / float( nr_lon );

    // Create horizontal stripes of squares
    for( float lon = 0.0f; lon < 1.0f*PI; lon += lon_delta )
    {
        glBegin( GL_QUAD_STRIP ) ;
        for( float lat = 0.0f; lat <= 2.0f*PI; lat += lat_delta )
        {
            // Each iteration adds another square, the other vertices
            // are taken from the existing stripe
            float xn1 = cosf( lat ) * sinf( lon );
            float yn1 = sinf( lat ) * sinf( lon );
            float zn1 = cosf( lon );

            // Set normal vector (important for lighting!)
            glNormal3f( xn1, yn1, zn1 );
            glVertex3f( pos.x()+rad*xn1, pos.y()+rad*yn1, pos.z()+rad*zn1 );

            float xn2 = cosf( lat ) * sinf( lon + lon_delta );
            float yn2 = sinf( lat ) * sinf( lon + lon_delta );
            float zn2 = cosf( lon + lon_delta );

            glNormal3f( xn2, yn2, zn2 );
            glVertex3f( pos.x()+rad*xn2, pos.y()+rad*yn2, pos.z()+rad*zn2 );
        }
        glEnd() ;
    }
}


void OGLWidget::EinheitsQuadrat() {
    glBegin(GL_QUADS);
    glColor3f(100.0f, 100.0f,0);
    glNormal3f(0,0,1);
    glVertex3f(0,0,0); // hinten rechts
    glVertex3f(cubeSize,0,0); // hinten links
    glVertex3f(cubeSize,cubeSize,0); // vorne links
    glVertex3f(0,cubeSize,0); // vorne rechts
    glEnd();
}


void OGLWidget::bodenFlaeche() {
    glBegin(GL_QUADS);
    glColor3f(10.0f, 10.0f,10.0f);
    glVertex3f(-20.f,-20.f,0);
    glVertex3f(-20.f,20.f,0);
    glVertex3f(20.f,20.f,0);
    glVertex3f(20.f,-20.f,0);
    glEnd();
}

void OGLWidget::EinheitsWuerfel() {

    glColor3f( 1.0f, 1.0f, 0.0f );
    glTranslatef(placeX,placeY,0.01f);
    glPushMatrix();
    glRotatef(cubeRotX,1.0f,0,0);
    glRotatef(cubeRotY,0,1.0f,0);
    glRotatef(cubeRotZ,0,0,1.0f);


    glPushMatrix();

    glRotatef(180.0f,1.0f,0,0);
    //Quadrat X-Y-Ebene
    EinheitsQuadrat();

    // Quadrat X-Z-Ebene
    glRotatef(90.0f, 0, 1.0f,0);
    EinheitsQuadrat();
    glRotatef(90.0f, 0, -1.0f,0);
    glRotatef(90.0f, -1.0f, 0,0);
    EinheitsQuadrat();
    glRotatef(90.0f, 1.0f, 0,0);

    // Verschobenes Quadrat Y-Z-Ebene
    glRotatef(90.0f, 0, 1.0f,0);
    glTranslatef(0, 0, cubeSize);
    EinheitsQuadrat();
    glTranslatef(0, 0, -cubeSize);
    glRotatef(90.0f, 0, -1.0f,0);

    // Verschobenes Quadrat X-Z-Ebene
    glRotatef(90.0f, -1.0f, 0,0);
    glTranslatef(0, 0, cubeSize);
    EinheitsQuadrat();
    glTranslatef(0, 0, -cubeSize);
    glRotatef(90.0f, 1.0f, 0,0);

    // Verschobenes Rechteck X-Y-Ebene Beginn
    glTranslatef(0, 0, -cubeSize);
    // Zurück an die eigentliche Stelle transformieren
    EinheitsQuadrat();
    glTranslatef(0, 0, cubeSize);


    glPopMatrix();
    glPopMatrix();
}


void OGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    // Use depth testing and the depth buffer
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Calculate color for each pixel fragment
    glShadeModel(GL_SMOOTH);

    // Enable lighting in scene
    glEnable(GL_LIGHTING);

    // Set position of light source
    float light_pos[] = { 10.f, 5.f, 10.f, 0.f };
    glLightfv(GL_LIGHT1, GL_POSITION, light_pos );

    // Set color for this light source
    // (We are only specifying a diffuse light source)
    float light_diffuse[] = { .8f, .8f, .8f, 1.f };
    glLightfv(GL_LIGHT1, GL_DIFFUSE,  light_diffuse );

    // Turn on this light
    glEnable(GL_LIGHT1);

    // Use the color of an object for light calculation
    glColorMaterial( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );
    glEnable(GL_COLOR_MATERIAL);
}

void OGLWidget::paintGL()
{
    // Clear the scene
    glClearColor(0.f, 0.f, 0.f, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Prepare projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Parallel projection with
    glOrtho(-10, 10, // clipping planes: left,   right
            -10, 10, //                  bottom, top
            -10, 10);//                  near,   far

    // Prepare model matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Apply rotation angles
    glRotatef(rotx, 1.0f, 0.0f, 0.0f); // Rotate around x axis
    glRotatef(roty, 0.0f, 1.0f, 0.0f); // Rotate around y axis
    glRotatef(rotz, 0.0f, 0.0f, 1.0f); // Rotate around z axis

    // Apply scaling
    float scale = zoom/100.0f;
    glScalef(scale, scale, scale ); // Scale along all axis

    // --> Now, every position is multiplied by the rotation matrix
    //     and by the scaling matrix

    // Change light position
    float light_pos[] = { 10.f * cosf(light*PI/180.f),
                          5.f,
                          10.f * sinf(light*PI/180.f), 0.f };
    glLightfv(GL_LIGHT1, GL_POSITION,  light_pos);


    //    glColor3f( 1.0f, 1.0f, 0.0f );
    //    drawSphere(QVector3D(-5, 0, 0), 2);

    bodenFlaeche();


    if(wuerfel) {
        EinheitsWuerfel();
    }

}

void OGLWidget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void OGLWidget::mousePressEvent(QMouseEvent *event)
{
    // Upon mouse pressed, we store the current position...
    lastpos = event->pos();
}

void OGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    // ... and while moving, we calculate the dragging deltas
    // Left button: Rotating around x and y axis
    int dx = (event->buttons() & Qt::LeftButton) ? lastpos.y() - event->y() : 0;
    int dy = lastpos.x() - event->x();

    // Right button: Rotating around z and y axis
    int dz = (event->buttons() & Qt::RightButton) ? lastpos.y() - event->y() : 0;

    // Now let the world know that we want to rotate
    emit changeRotation( dx, dy, dz );

    // Make the current position the starting point for the next dragging step
    lastpos = event->pos();
}

void OGLWidget::keyPressEvent(QKeyEvent *event)
{
    // This is the delta we want to use for rotating
    const int keyDelta = 1;

    switch(event->key())
    {
    // Up/Down: Rotating around x axis
    case Qt::Key_Up:
        setPlaceY(keyDelta);
        break;
    case Qt::Key_Down:
        setPlaceY(-keyDelta);
        break;

        // Left/Right: Rotating around y axis
    case Qt::Key_Left:
        setPlaceX(-keyDelta);
        break;
    case Qt::Key_Right:
        setPlaceX(keyDelta);
        break;

        // Pg up/down: Rotating around z axis
    case Qt::Key_PageUp:
        emit changeRotation( 0, 0, keyDelta );
        break;
    case Qt::Key_PageDown:
        emit changeRotation( 0, 0, -keyDelta );
        break;
    case Qt::Key_Insert:
        wuerfel = true;
        setPlaceX(0);
        setPlaceY(0);
        setCubeRotX(0);
        setCubeRotY(0);
        setCubeRotZ(0);
        setCubeSize(1.0f);
        update();
        break;
    case Qt:: Key_Delete:
        exit(0);
        // All other will be ignored
    default:
        break;
    }
}
