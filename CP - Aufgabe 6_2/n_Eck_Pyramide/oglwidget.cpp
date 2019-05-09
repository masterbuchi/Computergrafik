#include "oglwidget.h"
#include "vec3.hpp"
#include <cmath>



OGLWidget::OGLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    // Setup the animation timer to fire every x msec
    animtimer = new QTimer(this);
    animtimer->start( 10 );

    // Everytime the timer fires, the animation is going one step forward
    connect(animtimer, SIGNAL(timeout()), this, SLOT(stepAnimation()));

    animstep = 0;
    roty = 0;
    rotz = 0;
    zoom = 100;
    //    M_PI = 3.1415f
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

void OGLWidget::setUnfold(int newunfold)
{
    unfold = newunfold/2;
    update();
}


void OGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glClearColor(0,0,0,0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

}


void OGLWidget::paintGL()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glOrtho(-10, 10, -10, 10, 0, 200);
    c = animstep;   // rotate one degree with each step
    glTranslatef(0,0,-10);

    // Apply rotation angles
    glPushMatrix();
    glRotatef(-rotx, 1.0f, 0.0f, 0.0f); // Rotate around x axis
    glRotatef(-roty, 0.0f, 1.0f, 0.0f); // Rotate around y axis
    glRotatef(rotz, 0.0f, 0.0f, 1.0f); // Rotate around z axis

    //Apply scaling
    double scale = zoom/100.0;
    glScaled( scale, scale, scale ); // Scale along all axis

    glPushMatrix();
    Tisch();
    glPopMatrix();


    // Größe des Feldes
    s = 1/(2-2*cos(rot_rad));


    dt=unfold/200;


    px+=dx*dt;
    pz+=dz*dt;

    glPushMatrix();
    glTranslated(px,1,pz);



    glPopMatrix();
    glPopMatrix();

}



void OGLWidget::Tisch() {




    // For-Schleife für alle Dreiecke, werden durch i gedreht
    for (int i=0; i<Ecken; i++)
    {
        // Jeweiliges Dreieck
        glBegin(GL_TRIANGLES);

        //Normalenvektor, Senkrecht nach unten
        glNormal3d(0,-1,0);

        // Farbe (hellgrau)
        glColor3d(0.5, 0.5, 0.5);
        //Mittelpunkt
        glVertex3d(0, 0, 0);
        //Punkt Außen auf Z nach Vorne
        glVertex3d(s * -sin(i*rot_rad), 0 , s * cos(i*rot_rad));
        //Rotationspunkt
        glVertex3d(s * -sin((i+1)*rot_rad), 0 , s * cos((i+1)*rot_rad));
        glEnd();

        // Mantelstück
        glBegin(GL_QUADS);
        glColor3d(255.0, 0.0, 255.0);
        // Unten Links
        glVertex3d(s * -sin(i*rot_rad), 0, s * cos(i*rot_rad));
        // Unten Rechts
        glVertex3d(s * -sin((i+1)*rot_rad),0,  s * cos((i+1)*rot_rad) );
        // Oben Rechts
        glVertex3d(s * -sin((i+1)*rot_rad),1 , s * cos((i+1)*rot_rad) );
        // Oben Links
        glVertex3d(s * -sin(i*rot_rad), 1, s * cos(i*rot_rad));
        glEnd();

    }

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



// s * -sin(i*rot_rad) + lam * s * (-sin((i+1)*rot_rad) + sin( i * rot_rad)) = px + lam2 * dx;
// s * cos(i*rot_rad) + lam * s * (cos((i+1)*rot_rad) - cos( i * rot_rad)) = pz + lam2 * dz;

