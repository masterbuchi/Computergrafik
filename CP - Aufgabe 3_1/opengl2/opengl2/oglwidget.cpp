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
 GLfloat Ambient[4] = {0.2f, 0.2f, 0.2f, 1.0f};
    //Lighting set up
     glLightModelfv(GL_LIGHT_MODEL_AMBIENT, Ambient);
//     glEnable(GL_LIGHT0);
     glEnable(GL_LIGHTING);


   glEnable(GL_DEPTH_TEST);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);



}

void OGLWidget::einheitsquadrat() {

}


void OGLWidget::paintGL()
{

//    GLfloat L2Position[4] = {1.0f, 1.0f, 1.0f, 1.0f}; //Position Ersten drei Position in Koordinatensystem
//    glLightfv(GL_LIGHT0, GL_POSITION, &L2Position[3]); //welches licht, welche Eigenschaft, welchen Wert

//    //Diffuse
//    GLfloat LDiffuse[] = {0.6f, 0.6f, 0.6f, 1.0};
//    glLightfv(GL_LIGHT0, GL_DIFFUSE, LDiffuse);


    float PI = 3.14159f;


    float i;
    float anzahl = 64;
    float rotationswinkel = 360/anzahl;
    float rotationswinkel_radian = 2*PI/anzahl;

    float s = parama+1; // change of size
    float x = paramb*3.6f;   // degree to rotate
    float y = paramc*3.6f;   // degree to rotate
    float z = paramd*3.6f;   // degree to rotate
    float t = paramr ;




    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    glScalef(0.01f,0.01f,0.01f);
    glTranslatef(t,0,0);

    glRotatef(x, -1.0f, 0.0f, 0.0f); // Rotate by x degrees around x axis
    glRotatef(y, 0.0f, -1.0f, 0.0f); // Rotate by y degrees around y axis
    glRotatef(z, 0.0f, 0.0f, 1.0f); // Rotate by z degrees around z axis






    for (i=0; i<anzahl; i++)
    {

        glRotatef(i*rotationswinkel, 0, 0, 1.0);

        glBegin(GL_TRIANGLES);
       glColor3f(255.0f, 255.0f, 0.0f);
        glVertex3f(0, 0, 0);
        glVertex3f(s* -sin(rotationswinkel_radian), s*cos(rotationswinkel_radian) , 0);
        glVertex3f(0, s, 0);

        glEnd();

        // Mantel
        glBegin(GL_QUADS);
        glColor3f(255.0f, 0.0f, 255.0f);

        // Oben Links
         glVertex3f(0, s, 0);
        // Oben Rechts
        glVertex3f(s * -sin(rotationswinkel_radian), s * cos(rotationswinkel_radian) , 0);
        // Unten Rechts
        glVertex3f(s * -sin(rotationswinkel_radian), s * cos(rotationswinkel_radian) , s);
        // Unten Links
        glVertex3f(0, s, s);

        glEnd();

        glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 255.0f, 255.0f);
        glVertex3f(0, 0, s);
        glVertex3f(s* -sin(rotationswinkel_radian), s* cos(rotationswinkel_radian) , s);
        glVertex3f(0, s, s);


        glEnd();


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

