#include "oglwidget.h"
#include "vec3.hpp"
//#include <cmath>
#include <stdio.h>      /* printf */
#include <math.h>       /* acos */
#include <iostream>


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
    glTranslatef(0,0,-10.0f);

    // Apply rotation angles
    glPushMatrix();
    glRotatef(-rotx, 1.0f, 0.0f, 0.0f); // Rotate around x axis
    glRotatef(-roty, 0.0f, 1.0f, 0.0f); // Rotate around y axis
    glRotatef(rotz, 0.0f, 0.0f, 1.0f); // Rotate around z axis

    //Apply scaling
    float scale = zoom/100.0f;
    glScalef( scale, scale, scale ); // Scale along all axis
    glPushMatrix();
    glScalef(5.0f,2.0f,5.0f);
    glRotatef(0, 0.0f, 1.0f, 0.0f); // Rotate around y axis
    Tisch();
    glPopMatrix();
    dt=unfold/200.0f;
    px+=dx*dt;
    pz+=dz*dt;

    //Schritte beschreibt die Anzahl der Ecken. Die Punkte der Ecken sind global im Array in den Header Dateien gespeichert.
    //Es wird jede Ebene auf Kollision überprüft und die Letzte Kante gesondert, weil diese die punkte vom ersten und letzten Wert
    //Verbindet. Das wäre in einer schleife schwer realisierbar gewesen.
    for(int i=0; i<Kanten-1; i++){

        collide(Ecken[i][0], Ecken[i][1], Ecken[i+1][0], Ecken[i+1][1], px/5, pz/5);

    }

    collide(Ecken[int(Kanten-1)][0], Ecken[int(Kanten-1)][1], Ecken[0][0], Ecken[0][1], px/5, pz/5);


    glPushMatrix();
    glTranslatef(px,1,pz);
    Kugel();


    glPopMatrix();
    glPopMatrix();
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

void OGLWidget::Tisch(){


    float bogenLaenge=360/Kanten;
    float tempFirstX;
    float tempFirstY;
    float tempX;
    float tempY;
    int zaehler=0;



    for(float i=0; i<=360; i+=bogenLaenge){


        if(i==0){
            tempX=cos((bogenLaenge)*M_PI/180);
            tempY=sin((bogenLaenge)*M_PI/180);
            tempFirstX=tempX;
            tempFirstY=tempY;


            Ecken[0][0]=tempX;
            Ecken[0][1]=tempY;
            continue;

        }
        if(i>0 && i<359.95){
            zaehler++;
            glBegin(GL_TRIANGLES);
            glColor3f(0.0, 0.0, 1.0);
            glVertex3f( tempX, 0.0, tempY);
            float tempX1=tempX;
            float tempY1=tempY;


            tempX=cos(((i+bogenLaenge)*M_PI)/180.0f);
            tempY=sin(((i+bogenLaenge)*M_PI)/180.0f);

            Ecken[zaehler][0]=tempX;
            Ecken[zaehler][1]=tempY;
            glVertex3f( 0.0, 0.0, 0.0);
            glVertex3f( tempX,0.0 , tempY);
            glEnd();

            glBegin(GL_QUADS);
            glNormal3f(1,0,0);
            glColor3d(1.0,0.0,1.0);
            glVertex3f(tempX1,0.0,tempY1);
            glVertex3f(tempX1,1.0,tempY1);
            glVertex3f(tempX,0.0,tempY);
            glVertex3f(tempX,1.0,tempY);
            glEnd();
            continue;

        }

        glBegin(GL_TRIANGLES);
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f( 0.0, 0.0, 0.0);
        glVertex3f( tempX,0.0 , tempY);
        glVertex3f(tempFirstX, 0.0, tempFirstY);
        glEnd();

        glBegin(GL_QUADS);
        glNormal3f(1,0,0);
        glColor3d(1.0,0.0,1.0);
        glVertex3f(tempX,0.0,tempY);
        glVertex3f(tempX,1.0,tempY);
        glVertex3f(tempFirstX,0.0,tempFirstY);
        glVertex3f(tempFirstX,1.0,tempFirstY);
        glEnd();
    }

}



void OGLWidget::collide(float ax, float ay, float bx, float by, float cx, float cy){
    float m=(by-ay)/(bx-ax);//Steigung...
    float n= ay-(m*ax);//Y-Achsen Abschnitt


    float d=abs(((m*cx)-(cy+n))/sqrtf(powf(m,2)+2));//Abstand zwischen Ball und Lotpunkt


    //Abstand zwischen Schnittpunkt und Ball aber nicht messbarer abstand sondern sozusagen lambda in vektorformel
    float abstand = (((bx-ax)*(cy-ay))-((by-ay)*(cx-ax)))/(((by-ay)*(dx-cx))-((bx-ax)*(dz-cy)));

    float abstand2 = ((px-ax)*(bx-ax)+((py-ay)*(by-ay)))/(((bx-ax)*(bx-ax))+((by-ay)*(by-ay)));

        float spx=cx+abstand*dx;//Schnittpunkt von Ball und Gerade X Koordinate
        float spy=cy+abstand*dz;//Schnittpunkt von Ball und Gerade Y Koordinate



          float lotx=ax+abstand2*(by-ay); //Gespiegelter Punkt, berechnet durch Lotpunkt(x und y koordinaten müssen getauscht und der untere negativ sein)
          float loty=ay+abstand2*(bx-ax);
//        float px=cx+(2*abstand2*(by)); //Gespiegelter Punkt, berechnet durch Lotpunkt(x und y koordinaten müssen getauscht und der untere negativ sein)
//        float py=cy+(2*abstand2*(-bx));

                //neuberechnung von dx und dz(ja, dz weil oben drauf geschaut wird und die variablen vorher schon gesetzt wurden). Es wird der Schnittpunkt
                //von X und Y - der gespiegelte Punkt berechnet und als neuer Richtungsvektor gesetzt.
        float lotx_neu=px+(2*(lotx));
        float loty_neu=py+(2*(loty));





    //Der Abstand muss 0,2 sein, da der BilliardTisch mit *5 Skalliert wurde. Der Radius der Kugel beträgt 1. 1/5=0.2
    if(d<0.2f){

        dx=lotx_neu-spx;
        dz=loty_neu-spy;

        //Sorgt dafür, dass die Geschwindigkeit immer gleich bleibt
        float v= sqrt((dx*dx)+(dz*dz));
        dx=dx/v;
        dz=dz/v;



    }


}

//v=sqrt(richtungX^2+richtungY^2)
//richtungX=richtungX/v;
//richtungY=richtungY/v;


