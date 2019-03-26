#include "oglwidget.h"

OGLWidget::OGLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    parama = 0;
    paramb = 0;
    paramc = 0;
    paramd = 0;
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


void OGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0,0,0,1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
}

void OGLWidget::paintGL()
{
    float c = parama/100.0f; // change of color
    float r = paramb*3.6f;   // degree to rotate
    float s = paramc*3.6f;   // degree to rotate
    float t = paramd*3.6f;   // degree to rotate


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    glRotatef(r, 1.0f, 0.0f, 0.0f); // Rotate by r degrees around x axis
    glRotatef(s, 0.0f, 1.0f, 0.0f); // Rotate by s degrees around y axis
    glRotatef(t, 0.0f, 0.0f, 1.0f); // Rotate by t degrees around z axis


    // Vorderes Viereck
    glBegin(GL_QUADS);
        glColor3f(1.0-c, 0.0+c, 0.0+c);
        glVertex3f(-0.5, -0.5, 0);
        glColor3f(0.0+c, 1.0-c, 0.0+c);
        glVertex3f( 0.5, -0.5, 0);
        glColor3f(0.0+c, 0.0+c, 1.0+c);
        glVertex3f( 0.5,  0.5, 0);
        glColor3f(1.0-c, 0.0+c, 0.0+c);
        glVertex3f(-0.5, 0.5, 0);
    glEnd();

    // Linkes Viereck
    glBegin(GL_QUADS);
        glColor3f(1.0-c, 0.0+c, 0.0+c);
        glVertex3f(-0.5, -0.5, 0);
        glColor3f(0.0+c, 1.0-c, 0.0+c);
        glVertex3f( -0.5, -0.5, 1);
        glColor3f(0.0+c, 0.0+c, 1.0+c);
        glVertex3f( -0.5,  0.5, 1);
        glColor3f(1.0-c, 0.0+c, 0.0+c);
        glVertex3f(-0.5, 0.5, 0);
    glEnd();

    // Rechtes Viereck
    glBegin(GL_QUADS);
        glColor3f(1.0-c, 0.0+c, 0.0+c);
        glVertex3f(0.5, -0.5, 0);
        glColor3f(0.0+c, 1.0-c, 0.0+c);
        glVertex3f( 0.5, -0.5, 1);
        glColor3f(0.0+c, 0.0+c, 1.0+c);
        glVertex3f( 0.5,  0.5, 1);
        glColor3f(1.0-c, 0.0+c, 0.0+c);
        glVertex3f(0.5, 0.5, 0);
    glEnd();

    // Unteres Viereck
    glBegin(GL_QUADS);
        glColor3f(1.0-c, 0.0+c, 0.0+c);
        glVertex3f(0.5, -0.5, 0);
        glColor3f(0.0+c, 1.0-c, 0.0+c);
        glVertex3f( -0.5, -0.5, 0);
        glColor3f(0.0+c, 0.0+c, 1.0+c);
        glVertex3f( -0.5,  -0.5, 1);
        glColor3f(1.0-c, 0.0+c, 0.0+c);
        glVertex3f(0.5, -0.5, 1);
    glEnd();

    // Hinteres Viereck
    glBegin(GL_QUADS);
        glColor3f(1.0-c, 0.0+c, 0.0+c);
        glVertex3f(-0.5, -0.5, 1);
        glColor3f(0.0+c, 1.0-c, 0.0+c);
        glVertex3f( 0.5, -0.5, 1);
        glColor3f(0.0+c, 0.0+c, 1.0+c);
        glVertex3f( 0.5,  0.5, 1);
        glColor3f(1.0-c, 0.0+c, 0.0+c);
        glVertex3f(-0.5, 0.5, 1);
    glEnd();

    // Oberes Viereck
    glBegin(GL_QUADS);
        glColor3f(1.0-c, 0.0+c, 0.0+c);
        glVertex3f(0.5, 0.5, 0);
        glColor3f(0.0+c, 1.0-c, 0.0+c);
        glVertex3f( -0.5, 0.5, 0);
        glColor3f(0.0+c, 0.0+c, 1.0+c);
        glVertex3f( -0.5,  0.5, 1);
        glColor3f(1.0-c, 0.0+c, 0.0+c);
        glVertex3f(0.5, 0.5, 1);
    glEnd();

}

void OGLWidget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

