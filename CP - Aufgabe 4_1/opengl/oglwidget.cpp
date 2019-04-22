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
    varA = 1;
    varB = 1;
    varC = 1;
    varDelta = 0.1f;
    zoom  = 100;
    PI = 3.14159f;
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

void OGLWidget::setVarA(int newA)
{
    varA = 10.0f/newA;
    update();
}

void OGLWidget::setVarB(int newB)
{
    varB = 10.0f/newB;
    update();
}

void OGLWidget::setVarC(int newC)
{
    varC = newC;
    update();
}

void OGLWidget::setVarDelta(int newDelta)
{
    varDelta = (0.1f) / (0.1f *newDelta);
    update();
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





void OGLWidget::testFunktion(float a,float b, float c) {

    float dx;
    float dy;
    float k;
    float u;

    dx = varDelta;
    dy = dx;

    int size = 40 / dx;


    int begin = 0-size/2;

    int end = 0+size/2;


    glBegin (GL_POINTS);


    for (int i = begin; i < end; i++)
    {
        k = sin(i);
        u = cos(i);
        for (int j = begin; j < end; j++){
//            float z = sin(a* i *dx + b*j*dx + c);
            float z = cos(abs(a*i*dx)+abs(b*j*dx))*(abs(a*i*dx)+abs(b*j*dx));
            glColor3f( abs(z), abs(z), abs(z) );

            glVertex3f (i*dx, j*dx, z);
        }
    }

    glEnd ();





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

    //    // Draw three spheres and a triangle
    //    glColor3f( 1.0f, 0.0f, 0.0f );
    //    drawSphere(QVector3D( 5, 0, 0), 2);

//    glColor3f( 1.0f, 1.0f, 0.0f );
//    drawSphere(QVector3D(-5, 0, 0), 2);

    testFunktion(varA,varB,varC);


    //    glColor3f( 0.0f, 0.0f, 1.0f );
    //    drawSphere(QVector3D( 0, 5, 0), 2);

    //    glColor3f( 0.0f, 1.0f, 0.0f );

    //    glBegin(GL_TRIANGLES);
    //    glNormal3f( 0.0,  0.0, 1.0);
    //    glVertex3f( 0.0,  2.0, 0.0);
    //    glVertex3f(-2.0, -2.0, 0.0);
    //    glVertex3f( 2.0, -2.0, 0.0);
    //    glEnd();

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
    const int keyDelta = 10;

    switch(event->key())
    {
    // Up/Down: Rotating around x axis
    case Qt::Key_Up:
        emit changeRotation( keyDelta, 0, 0 );
        break;
    case Qt::Key_Down:
        emit changeRotation( -keyDelta, 0, 0 );
        break;

        // Left/Right: Rotating around y axis
    case Qt::Key_Left:
        emit changeRotation( 0, keyDelta, 0 );
        break;
    case Qt::Key_Right:
        emit changeRotation( 0, -keyDelta, 0 );
        break;

        // Pg up/down: Rotating around z axis
    case Qt::Key_PageUp:
        emit changeRotation( 0, 0, keyDelta );
        break;
    case Qt::Key_PageDown:
        emit changeRotation( 0, 0, -keyDelta );
        break;

        // All other will be ignored
    default:
        break;
    }
}
