#include "oglwidget.h"
#include "vector3.h"
#include <cmath>
#include <iostream>


OGLWidget::OGLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    roty = 0;
    rotz = 0;
    zoom = 100;

    Ecken = 7;
    rot_rad = 2.0*3.14159/Ecken;

    //    M_PI = 3.1415f
}

OGLWidget::~OGLWidget()
{
}


void OGLWidget::setEcken(int newEcken)
{
    Ecken = newEcken;

    rot_rad = 2.0*3.14159/Ecken;

    update();

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
    //    glEnable(GL_LIGHT0);
    //    glEnable(GL_LIGHTING);
    //    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

}


void OGLWidget::paintGL()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glOrtho(-10, 10, -10, 10, 0, 200);
    glTranslatef(0,0,-10);

    // Apply rotation angles
    glPushMatrix();
    glRotatef(-rotx, 1.0f, 0.0f, 0.0f); // Rotate around x axis
    glRotatef(-roty, 0.0f, 1.0f, 0.0f); // Rotate around y axis
    glRotatef(rotz, 0.0f, 0.0f, 1.0f); // Rotate around z axis

    //Apply scaling
    double scale = zoom/100.0;
    glScaled( scale, scale, scale ); // Scale along all axis

    // Größe des Feldes
    s = 1/(2-2*cos(rot_rad));

    glPushMatrix();
    Pyramide();
    glPopMatrix();



    dt=unfold/200;

    px+=dx*dt;
    pz+=dz*dt;

    glPushMatrix();
    glTranslated(px,1,pz);

    glPopMatrix();
    glPopMatrix();

}



void OGLWidget::Pyramide() {

    // For-Schleife für alle Dreiecke, werden durch i gedreht
    for (int i=0; i<Ecken; i++)
    {
        // Jeweiliges Dreieck
        glBegin(GL_TRIANGLES);

        int cx = rand();
        int cy = rand();
        int cz = rand();

        // Farbe
        glColor3f((cx % 100) / 100.f ,(cy % 100) / 100.f ,(cz % 100) / 100.f );
        //Normalenvektor
        glNormal3d(0,0,0);
        //Mittelpunkt
        glVertex3d(0, 0, 0);

        //Normalenvektor
        glNormal3d(s * -sin(i*rot_rad), 0 , s * cos(i*rot_rad));
        //Punkt Außen auf Z nach Vorne
        glVertex3d(s * -sin(i*rot_rad), 0 , s * cos(i*rot_rad));

        //Normalenvektor
        glNormal3d(s * -sin((i+1)*rot_rad), 0 , s * cos((i+1)*rot_rad));
        //Rotationspunkt
        glVertex3d(s * -sin((i+1)*rot_rad), 0 , s * cos((i+1)*rot_rad));
        glEnd();


        glColor3f((cx % 100) / 100.f ,(cy % 100) / 100.f ,(cz % 100) / 100.f );
        //Pyramidenspitze
        glBegin(GL_TRIANGLES);

        //Normalenvektor
        glNormal3d(s * -sin(i*rot_rad), 0, s * cos(i*rot_rad));
        // i Punkt
        glVertex3d(s * -sin(i*rot_rad), 0, s * cos(i*rot_rad));

        //Normalenvektor
        glNormal3d(s * -sin((i+1)*rot_rad),0,  s * cos((i+1)*rot_rad));
        // i++ Punkt
        glVertex3d(s * -sin((i+1)*rot_rad),0,  s * cos((i+1)*rot_rad) );

        //Normalenvektor
        glNormal3d(0,5,0);
        // Mittelpunkt
        glVertex3d(0,5,0);
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
