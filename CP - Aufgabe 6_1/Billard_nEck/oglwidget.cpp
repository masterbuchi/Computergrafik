#include "oglwidget.h"
#include "vec3.hpp"
#include <cmath>
#include <iostream>



OGLWidget::OGLWidget(QWidget *parent)
    : QOpenGLWidget(parent),
      kugel_1(Kugel(QVector3D(0, 1, 0),1,1,Ecken,rot_rad,s)),
      kugel_2(Kugel(QVector3D(1, 1, 0),1,1,Ecken,rot_rad,s))
{
    // Setup the animation timer to fire every x msec
    animtimer = new QTimer(this);
    animtimer->start( 10 );

    // Everytime the timer fires, the animation is going one step forward
    connect(animtimer, SIGNAL(timeout()), this, SLOT(stepAnimation()));

    animstep = 0;
    zoom = 100;
    PI = 3.1415;
    PIf = 3.1414f;
}

OGLWidget::~OGLWidget()
{
}

void OGLWidget::stepAnimation()
{
    animstep++;    // Increase animation steps
    update();      // Trigger redraw of scene with paintGL
}

void OGLWidget::setRotX(int newrx)
{
    rotx = newrx % 360;
    update();
}

void OGLWidget::setRotY(int newry)
{
    roty = newry % 360;
    update();
}

void OGLWidget::setRotZ(int newrz)
{
    rotz = newrz % 360;
    update();
}



void OGLWidget::setZoom(int newzoom)
{
    zoom = newzoom;
    update();
}

void OGLWidget::setUnfold(int newunfold)
{
    unfold = newunfold/2;
    update();
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
    float light_pos[] = { 10.f, 10.f, 10.f, 0.f };
    glLightfv(GL_LIGHT1, GL_POSITION, light_pos );

    // Set color for this light source
    // (We are only specifying a diffuse light source)
    float light_diffuse[] = { .9f, .9f, .9f, 1.f };
    glLightfv(GL_LIGHT1, GL_DIFFUSE,  light_diffuse );

    // Turn on this light
    glEnable(GL_LIGHT1);

    // Use the color of an object for light calculation
    glColorMaterial( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );
    glEnable(GL_COLOR_MATERIAL);

}

void OGLWidget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


void OGLWidget::paintGL()
{

    // Clear the scene
    glClearColor(0.f, 0.f, 0.f, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Prepare projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10, 10, -10, 10, 0, 200);
    // Prepare model matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();



    glTranslated(0,0,-10);

    // Apply rotation angles
    glPushMatrix();
    glRotated(-rotx, 1.0, 0.0, 0.0); // Rotate around x axis
    glRotated(-roty, 0.0, 1.0, 0.0); // Rotate around y axis
    glRotated(rotz, 0.0, 0.0, 1.0); // Rotate around z axis

    // Change light position
    float light_pos[] = { 10.f * cosf(animstep*PIf/180.f),
                          10.f,
                          10.0f * sinf(animstep*PIf/180.f), 0.f };
    glLightfv(GL_LIGHT1, GL_POSITION,  light_pos);


    //Apply scaling
    double scale = zoom/100.0;
    glScaled( scale, scale, scale ); // Scale along all axis

    Tisch();


    dt = unfold/200;


        kugel_1.update(kugel_2, rotx, rotz, dt);
        kugel_2.update(kugel_1, rotx, rotz, dt);





//    kugel_1.update(kugel_2, rotx, rotz, dt);
//    kugel_2.update(kugel_1, rotx, rotz, dt);

    glPopMatrix();


}


void OGLWidget::Tisch() {

    // For-Schleife für alle Dreiecke, werden durch i gedreht
    for (int i=0; i<Ecken; i++)
    {
        // Jeweiliges Dreieck
        glBegin(GL_TRIANGLES);
        // Farbe (hellgrau)
        glColor3d(0.8, 0.8, 0.8);

        //Normalenvektor
        glNormal3d(0,0,0);
        //Mittelpunkt
        glVertex3d(0, 0, 0);

        //Normalenvektor
        glNormal3d(-sin(i*rot_rad), 0 ,cos(i*rot_rad));
        //Punkt Außen auf Z nach Vorne
        glVertex3d(s * -sin(i*rot_rad), 0 , s * cos(i*rot_rad));


        //Normalenvektor
        glNormal3d(-sin((i+1)*rot_rad), 0 ,cos((i+1)*rot_rad));
        //Rotationspunkt
        glVertex3d(s * -sin((i+1)*rot_rad), 0 , s * cos((i+1)*rot_rad));
        glEnd();


        // Mantelstück
        glBegin(GL_QUADS);
        glColor3d(0.5, 0.0, 0.5);

        //Normalenvektor
        glNormal3d(s * -sin(i*rot_rad), 0, s * cos(i*rot_rad));
        // Unten Links
        glVertex3d(s * -sin(i*rot_rad), 0, s * cos(i*rot_rad));

        //Normalenvektor
        glNormal3d(s * -sin((i+1)*rot_rad),0,  s * cos((i+1)*rot_rad));
        // Unten Rechts
        glVertex3d(s * -sin((i+1)*rot_rad),0,  s * cos((i+1)*rot_rad) );

        //Normalenvektor
        glNormal3d(s * -sin((i+1)*rot_rad),0.5 , s * cos((i+1)*rot_rad));
        // Oben Rechts
        glVertex3d(s * -sin((i+1)*rot_rad),0.5 , s * cos((i+1)*rot_rad) );

        //Normalenvektor
        glNormal3d(s * -sin(i*rot_rad), 0.5, s * cos(i*rot_rad));
        // Oben Links
        glVertex3d(s * -sin(i*rot_rad), 0.5, s * cos(i*rot_rad));
        glEnd();

    }

}



//void OGLWidget::mousePressEvent(QMouseEvent *event)
//{
//    // Upon mouse pressed, we store the current position...
//    lastpos = event->pos();
//}

//void OGLWidget::mouseMoveEvent(QMouseEvent *event)
//{
//    // ... and while moving, we calculate the dragging deltas
//    // Left button: Rotating around x and y axis
//    int dx = (event->buttons() & Qt::LeftButton) ? lastpos.y() - event->y() : 0;
//    int dy = lastpos.x() - event->x();
//    // Right button: Rotating around z and y axis
//    int dz = (event->buttons() & Qt::RightButton) ? lastpos.y() - event->y() : 0;

//    // Now let the world know that we want to rotate
//    emit changeRotation( dx, dy, dz );

//    // Make the current position the starting point for the next dragging step
//    lastpos = event->pos();
//}

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



        // Left/Right: Rotating around z axis
    case Qt::Key_Left:
        emit changeRotation( 0, 0, keyDelta );
        break;
    case Qt::Key_Right:
        emit changeRotation( 0, 0, -keyDelta );
        break;


        // Pg up/down: Rotating around y axis
    case Qt::Key_PageUp:
        emit changeRotation( 0, keyDelta, 0 );
        break;
    case Qt::Key_PageDown:
        emit changeRotation( 0, -keyDelta, 0 );
        break;

        // All other will be ignored
    default:
        break;
    }
}



// s * -sin(i*rot_rad) + lam * s * (-sin((i+1)*rot_rad) + sin( i * rot_rad)) = px + lam2 * dx;
// s * cos(i*rot_rad) + lam * s * (cos((i+1)*rot_rad) - cos( i * rot_rad)) = pz + lam2 * dz;

