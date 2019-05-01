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

//double OGLWidget:: AbstandPunktGerade(A,B,C,P) {

//    a = [A,B];
//            lamda = (C - dot(a,P))/(dot(a,a));
//            L = lamda * a + P;

//            ergebnis = sqrt((P(1) - L(1))^2 + (P(2) - L(2))^2);
//            return ergebnis;
//}

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
    float scale = zoom/100.0f;
    glScalef( scale, scale, scale ); // Scale along all axis
    //SetMaterialColor(0,0,0,1);

    float size = 5.0f;

    glPushMatrix();
    glScalef(size,2.0f,size);
    //    glRotatef(45, 0.0f, 1.0f, 0.0f); // Rotate around y axis
    Tisch();
    glPopMatrix();



    dt=unfold/200;
    px+=dx*dt;
    pz+=dz*dt;

    glPushMatrix();
    glTranslatef(px,1,pz);

    if (px+1.0f>size or px-1.0f<-size)
    {
        dx =-dx;
    }

    if (pz+1>size or pz-1<-size)  {
        //glRotated(180.0,1,0,0);
        dz =-dz;
    }

    Kugel();

    glPopMatrix();
    glPopMatrix();

}




void OGLWidget::Tisch() {

    // Winkel in Radian
    double rotationswinkel_radian = 2.0*3.14159/Ecken;
    // Größe des Feldes
    double s = 2; // change of size

    for (int i=0; i<Ecken; i++)
    {
        // Jeweiliges Dreieck
        glBegin(GL_TRIANGLES);

        //Normalenvektor, Senkrecht nach unten
        glNormal3d(0,-1,0);

        glColor3d(0.5/i, 0.5/i, 0.5/i);
        //Mittelpunkt
        glVertex3d(0, 0, 0);
        //Punkt Außen auf Z nach Vorne
        glVertex3d(s * -sin(i*rotationswinkel_radian), 0 , s * cos(i*rotationswinkel_radian));
        //Rotationspunkt
        glVertex3d(s * -sin((i+1)*rotationswinkel_radian), 0 , s * cos((i+1)*rotationswinkel_radian));
        glEnd();

        // Mantelstück
        glBegin(GL_QUADS);
        glColor3d(255.0, 0.0, 255.0);
        // Unten Links
        glVertex3d(s * -sin(i*rotationswinkel_radian), 0, s * cos(i*rotationswinkel_radian));
        // Unten Rechts
        glVertex3d(s * -sin((i+1)*rotationswinkel_radian),0,  s * cos((i+1)*rotationswinkel_radian) );
        // Oben Rechts
        glVertex3d(s * -sin((i+1)*rotationswinkel_radian),1 , s * cos((i+1)*rotationswinkel_radian) );
        // Oben Links
        glVertex3d(s * -sin(i*rotationswinkel_radian), 1, s * cos(i*rotationswinkel_radian));
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
void OGLWidget::Kugel()
{
    int n=10; // Anzahl der 1.0ngrade
    int m=20; // Anzahl der Längengrade
    double dalpha=2.0*M_PI/m;
    double dbeta=M_PI/n/2.0;
    int k=0,j=0;
    double x1,x2,y1,y2,z1,z2=0;
    double x3,x4,y3,y4,z3,z4=0;

    for(j=0;j < n ;j+=1)
        for(k=0;k < m ;k+=1)
        {
            x1=cos(j*dbeta)*cos(k*dalpha);
            y1=sin(j*dbeta);
            z1=-cos(j*dbeta)*sin(k*dalpha);
            x2=cos((j+1)*dbeta)*cos(k*dalpha);
            y2=sin((j+1)*dbeta);
            z2=-cos((j+1)*dbeta)*sin(k*dalpha);
            x3=cos((j+1)*dbeta)*cos((k+1)*dalpha);
            y3=sin((j+1)*dbeta);
            z3=-cos((j+1)*dbeta)*sin((k+1)*dalpha);
            x4=cos(j*dbeta)*cos((k+1)*dalpha);
            y4=sin(j*dbeta);
            z4=-cos(j*dbeta)*sin((k+1)*dalpha);
            glBegin(GL_QUADS);
            glNormal3d(-x1,-y1,-z1);
            glColor3d(1.0,0.0,1.0);
            glVertex3d(x1,y1,z1);
            //          glColor3f(0.0,0.0,1.0);
            glVertex3d(x2,y2,z2);
            //          glColor3f(0.0,0.0,1.0);
            glVertex3d(x3,y3,z3);
            //          glColor3f(0.0,0.0,1.0);
            glVertex3d(x4,y4,z4);
            glEnd();
            glBegin(GL_QUADS);
            glNormal3d(-x1,-y1,-z1);
            //          glColor3f(0.0,0.0,1.0);
            glVertex3d(x1,-y1,z1);
            //          glColor3f(0.0,0.0,1.0);
            glVertex3d(x2,-y2,z2);
            //          glColor3f(0.0,0.0,1.0);
            glVertex3d(x3,-y3,z3);
            //          glColor3f(0.0,0.0,1.0);
            glVertex3d(x4,-y4,z4);
            glEnd();
        }
}

