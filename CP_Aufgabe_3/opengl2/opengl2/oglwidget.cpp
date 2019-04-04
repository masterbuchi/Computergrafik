#include "oglwidget.h"

OGLWidget::OGLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    parama = 0;
    paramb = 0;
    paramc = 0;
    paramd = 0;

    // Rotation value at the start

    paramr = 0;
}

OGLWidget::~OGLWidget()
{
}


void OGLWidget::setParamA(int newa)
{
    parama = newa; // Set new value
    update();      // Trigger redraw of scene with paintGL
}

void OGLWidget::setParamB(int newb)
{
    paramb = newb;
    update();
}

void OGLWidget::setParamC(int newc)
{
    paramc = newc;
    update();
}

void OGLWidget::setParamD(int newd)
{
    paramd = newd;
    update();
}

void OGLWidget::setParamR(int newr)
{
    paramr = newr;
    update();
}


void OGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    //glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1-0);

    //Lighting set up
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    glEnable(GL_LIGHT0);  // Aktiviert die allgemeine lichtquelle(Ambientes licht) keine position
     glEnable(GL_LIGHT1);
     glEnable(GL_LIGHTING);


   glEnable(GL_DEPTH_TEST);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);



}

void OGLWidget::paintGL()
{
   GLfloat LPosition[4] = {1.0f, 1.0f, 1.0f, 1.0f}; //Position Ersten drei Position in Koordinatensystem
   glLightfv(GL_LIGHT0, GL_POSITION, &LPosition[3]); //welches licht, welche Eigenschaft, welchen Wert

    GLfloat L2Position[4] = {1.0f, 1.0f, 1.0f, 1.0f}; //Position Ersten drei Position in Koordinatensystem
    glLightfv(GL_LIGHT1, GL_POSITION, &L2Position[3]); //welches licht, welche Eigenschaft, welchen Wert

    //Ambiente: (hat keine position)
    GLfloat LAmbient[] = {0.0f, 0.0f, 0.0f, 1.0}; //RED GREEN BLUE ALPHA(immer 1.0) Alle Farbwerte gleich = weißes licht
    glLightfv(GL_LIGHT0, GL_AMBIENT, &LAmbient[0]);

    //Diffuse
    //GLfloat LDiffuse[] = {0.6, 0.6, 0.6, 1.0};
    //glLightfv(GL_LIGHT1, GL_DIFFUSE, LDiffuse);

    //Spot
    GLfloat LSPot[] = {0.6f, 0.6f, 0.6f, 1.0};
    glLightfv(GL_LIGHT1, GL_SPECULAR, LSPot);

    float c = parama+1; // change of color
    float r = paramb*3.6f;   // degree to rotate
    float s = paramc*3.6f;   // degree to rotate
    float t = paramd*3.6f;   // degree to rotate

    float PI = 3.14159f;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    glRotatef(r, -1.0f, 0.0f, 0.0f); // Rotate by r degrees around x axis
    glRotatef(s, 0.0f, -1.0f, 0.0f); // Rotate by s degrees around y axis
    glRotatef(t, 0.0f, 0.0f, 1.0f); // Rotate by t degrees around z axis

    float i;
    float anzahl = 64;
    float rotationswinkel = 360/anzahl;
    float rotationswinkel_radian = 2*PI/anzahl;

    for (i=0; i<anzahl; i++)
    {

        glRotatef(i*rotationswinkel, 0, 0, 1.0);

        glBegin(GL_TRIANGLES);

        glVertex3f(0, 0, 0);
        glColor3f(0.0f, 1.0f, 1.0f);

        glVertex3f(-sin(rotationswinkel_radian), cos(rotationswinkel_radian) , 0);
        glColor3f(0.0f, 1.0f, 1.0f);

        glVertex3f(0, 1, 0);
        glColor3f(0.0f, 1.0f, 1.0f);

        glEnd();

        // Mantel
        glBegin(GL_QUADS);
        // Oben Links
        glVertex3f(0, 1, 0);
        glColor3f(255.0f, 0.0f, 1.0f);
        // Oben Rechts
        glVertex3f(-sin(rotationswinkel_radian), cos(rotationswinkel_radian) , 0);
        glColor3f(255.0f, 0.0f, 1.0f);
        // Unten Rechts
        glVertex3f(-sin(rotationswinkel_radian), cos(rotationswinkel_radian) , 1);
        glColor3f(0.0f, 0.0f, 1.0f);
        // Unten Links
        glVertex3f(0, 1, 1);
        glColor3f(0.0f, 0.0f, 1.0f);

        glEnd();

        glBegin(GL_TRIANGLES);

        glVertex3f(0, 0, 1);
        glColor3f(0.0f, 1.0f, 1.0f);

        glVertex3f(-sin(rotationswinkel_radian), cos(rotationswinkel_radian) , 1);
        glColor3f(0.0f, 1.0f, 1.0f);

        glVertex3f(0, 1, 1);
        glColor3f(0.0f, 1.0f, 1.0f);

        glEnd();


    }

 /*   glRotatef(0*3.6, 0, 0, 1.0);
    glBegin(GL_TRIANGLES);
    // Ursprung
    glVertex3f(0, 0, 1);
    glColor3f(0.0f-c, 0.0f+c, 1.0f+c);
    // Oben Links
    glVertex3f(0, 0.5, 1);
    glColor3f(0.0f-c, 0.0f+c, 1.0f+c);
    // Oben Rechts
    glVertex3f(0.5, 0, 1);
    glColor3f(0.0f-c, 0.0f+c, 1.0f+c);
    glEnd(); */


/*

    // Oberes Linkes Dreieck
    glPushMatrix();
    glRotatef(25*3.6, 0, 0, 1.0);
    glBegin(GL_TRIANGLES);
    // Ursprung
    glVertex3f(0, 0, 0);
    glColor3f(0.0f-c, 0.0f+c, 1.0f+c);
    // Oben Links
    glVertex3f(0, 0.5, 0);
    glColor3f(0.0f-c, 0.0f+c, 1.0f+c);
    // Oben Rechts
    glVertex3f(0.5, 0, 0);
    glColor3f(0.0f-c, 0.0f+c, 1.0f+c);
    glEnd();
    glPopMatrix();

    // Unteres Linkes Dreieck
    glPushMatrix();
    glRotatef(50*3.6, 0, 0, 1.0);
    glBegin(GL_TRIANGLES);
    // Ursprung
    glVertex3f(0, 0, 0);
    glColor3f(0.0f-c, 0.0f+c, 1.0f+c);
    // Oben Links
    glVertex3f(0, 0.5, 0);
    glColor3f(0.0f-c, 0.0f+c, 1.0f+c);
    // Oben Rechts
    glVertex3f(0.5, 0, 0);
    glColor3f(0.0f-c, 0.0f+c, 1.0f+c);
    glEnd();
    glPopMatrix();

    // Unteres Rechtes Dreieck
    glPushMatrix();
    glRotatef(75*3.6, 0, 0, 1.0);
    glBegin(GL_TRIANGLES);
    // Ursprung
    glVertex3f(0, 0, 0);
    glColor3f(0.0f-c, 0.0f+c, 1.0f+c);
    // Oben Links
    glVertex3f(0, 0.5, 0);
    glColor3f(0.0f-c, 0.0f+c, 1.0f+c);
    // Oben Rechts
    glVertex3f(0.5, 0, 0);
    glColor3f(0.0f-c, 0.0f+c, 1.0f+c);
    glEnd();
    glPopMatrix();
*/
}

void OGLWidget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

