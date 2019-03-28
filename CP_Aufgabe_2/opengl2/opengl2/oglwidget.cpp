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

    float diceRotation = paramr * 1.8f;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    glRotatef(r, 1.0f, 0.0f, 0.0f); // Rotate by r degrees around x axis
    glRotatef(s, 0.0f, 1.0f, 0.0f); // Rotate by s degrees around y axis
    glRotatef(t, 0.0f, 0.0f, 1.0f); // Rotate by t degrees around z axis

    glPushMatrix();

    glTranslatef(0.5f, 0.5, 0);             // Punkt um den man rotieren will
    glRotatef(diceRotation, 0, 0, -1.0f);
    glTranslatef(-0.5f, -0.5f, 0);          // Zurück an die eigentliche Stelle transformieren

    // Oberes Viereck - Deckel
    glBegin(GL_QUADS);
        glColor3f(1.0f-c, 0.0f+c, 0.0f+c);
        glVertex3f(0.5, 0.5, -0.5);
        glColor3f(0.0f+c, 1.0f-c, 0.0f+c);
        glVertex3f( -0.5, 0.5, -0.5);
        glColor3f(0.0f+c, 0.0f+c, 1.0f+c);
        glVertex3f( -0.5,  0.5, 0.5);
        glColor3f(1.0f-c, 0.0f+c, 0.0f+c);
        glVertex3f(0.5, 0.5, 0.5);
    glEnd();

    glPopMatrix();

    // Vorderes Viereck
    glBegin(GL_QUADS);
        glColor3f(1.0f-c, 0.0f+c, 0.0f+c);
        glVertex3f(-0.5, -0.5, -0.5);
        glColor3f(0.0f+c, 1.0f-c, 0.0f+c);
        glVertex3f( 0.5, -0.5, -0.5);
        glColor3f(0.0f+c, 0.0f+c, 1.0f+c);
        glVertex3f( 0.5,  0.5, -0.5);
        glColor3f(1.0f-c, 0.0f+c, 0.0f+c);
        glVertex3f(-0.5, 0.5, -0.5);
    glEnd();

    // Linkes Viereck
    glBegin(GL_QUADS);
        glColor3f(1.0f-c, 0.0f+c, 0.0f+c);
        glVertex3f(-0.5, -0.5, -0.5);
        glColor3f(0.0f+c, 1.0f-c, 0.0f+c);
        glVertex3f( -0.5, -0.5, 0.5);
        glColor3f(0.0f+c, 0.0f+c, 1.0f+c);
        glVertex3f( -0.5,  0.5, 0.5);
        glColor3f(1.0f-c, 0.0f+c, 0.0f+c);
        glVertex3f(-0.5, 0.5, -0.5);
    glEnd();

    // Rechtes Viereck
    glBegin(GL_QUADS);
        glColor3f(1.0f-c, 0.0f+c, 0.0f+c);
        glVertex3f(0.5, -0.5, -0.5);
        glColor3f(0.0f+c, 1.0f-c, 0.0f+c);
        glVertex3f( 0.5, -0.5, 0.5);
        glColor3f(0.0f+c, 0.0f+c, 1.0f+c);
        glVertex3f( 0.5,  0.5, 0.5);
        glColor3f(1.0f-c, 0.0f+c, 0.0f+c);
        glVertex3f(0.5, 0.5, -0.5);
    glEnd();

    // Unteres Viereck
    glBegin(GL_QUADS);
        glColor3f(1.0f-c, 0.0f+c, 0.0f+c);
        glVertex3f(0.5, -0.5, -0.5);
        glColor3f(0.0f+c, 1.0f-c, 0.0f+c);
        glVertex3f( -0.5, -0.5, -0.5);
        glColor3f(0.0f+c, 0.0f+c, 1.0f+c);
        glVertex3f( -0.5,  -0.5, 0.5);
        glColor3f(1.0f-c, 0.0f+c, 0.0f+c);
        glVertex3f(0.5, -0.5, 0.5);
    glEnd();

    // Hinteres Viereck
    glBegin(GL_QUADS);
        glColor3f(1.0f-c, 0.0f+c, 0.0f+c);
        glVertex3f(-0.5, -0.5, 0.5);
        glColor3f(0.0f+c, 1.0f-c, 0.0f+c);
        glVertex3f( 0.5, -0.5, 0.5);
        glColor3f(0.0f+c, 0.0f+c, 1.0f+c);
        glVertex3f( 0.5,  0.5, 0.5);
        glColor3f(1.0f-c, 0.0f+c, 0.0f+c);
        glVertex3f(-0.5, 0.5, 0.5);
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

