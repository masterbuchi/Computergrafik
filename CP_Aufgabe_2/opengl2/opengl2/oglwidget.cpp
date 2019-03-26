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


    //Schattenverhalten?
    glShadeModel(GL_SMOOTH);

    //Zwei Lampen?
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);


    //Positionen der Lampen
    GLfloat lp1[4]  = { -20, 0, 0, 0};
    GLfloat lp2[4]  = { 20, 0, 0, 0};

    //Hintergrundfarbe?
    glClearColor(0,0,0,1);

    //Keine Ahnung
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    //Licht wird allgemein aktiviert
    glEnable(GL_LIGHTING);
    //Lichtquelle 0 wird aktiviert
    glEnable(GL_LIGHT0);
    //Lichtquelle 1 wird aktiviert
    glEnable(GL_LIGHT1);

    // Licht 0 bekommt Verhaltensweisen (Position) übergeben
    glLightfv(GL_LIGHT0, GL_POSITION, lp1);
     // Licht 0 bekommt Verhaltensweisen (Position) übergeben
    glLightfv(GL_LIGHT1, GL_POSITION, lp2);

    //Licht bekommt Materialangaben (noch austesten)
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    //Materialverhalten wird aktiviert?
    glEnable(GL_COLOR_MATERIAL);
}

void OGLWidget::paintGL()
{
    float c = 0; // change of color
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
    glColor3f(1.0f-c, 0.0f+c, 0.0f+c);
    glVertex3f(-0.5, -0.5, -0.5);
    glColor3f(1.0f-c, 0.0f+c, 0.0f+c);
    glVertex3f( 0.5, -0.5, -0.5);
    glColor3f(1.0f-c, 0.0f+c, 0.0f+c);
    glVertex3f( 0.5,  0.5, -0.5);
    glColor3f(1.0f-c, 0.0f+c, 0.0f+c);
    glVertex3f(-0.5, 0.5, -0.5);
    glEnd();

    // Linkes Viereck
    glBegin(GL_QUADS);
    glColor3f(0.0f+c, 1.0f-c, 0.0f+c);
    glVertex3f(-0.5, -0.5, -0.5);
    glColor3f(0.0f+c, 1.0f-c, 0.0f+c);
    glVertex3f( -0.5, -0.5, 0.5);
    glColor3f(0.0f+c, 1.0f-c, 0.0f+c);
    glVertex3f( -0.5,  0.5, 0.5);
    glColor3f(0.0f+c, 1.0f-c, 0.0f+c);
    glVertex3f(-0.5, 0.5, -0.5);
    glEnd();

    // Rechtes Viereck
    glBegin(GL_QUADS);
    glColor3f(0.0f+c, 0.0f+c, 1.0f+c);
    glVertex3f(0.5, -0.5, -0.5);
    glColor3f(0.0f+c, 0.0f+c, 1.0f+c);
    glVertex3f( 0.5, -0.5, 0.5);
    glColor3f(0.0f+c, 0.0f+c, 1.0f+c);
    glVertex3f( 0.5,  0.5, 0.5);
    glColor3f(0.0f+c, 0.0f+c, 1.0f+c);
    glVertex3f(0.5, 0.5, -0.5);
    glEnd();

    // Unteres Viereck
    glBegin(GL_QUADS);
    glColor3f(1.0f-c, 1.0f+c, 0.0f+c);
    glVertex3f(0.5, -0.5, -0.5);
    glColor3f(1.0f-c, 1.0f+c, 0.0f+c);
    glVertex3f( -0.5, -0.5, -0.5);
    glColor3f(1.0f-c, 1.0f+c, 0.0f+c);
    glVertex3f( -0.5,  -0.5, 0.5);
    glColor3f(1.0f-c, 1.0f+c, 0.0f+c);
    glVertex3f(0.5, -0.5, 0.5);
    glEnd();

    // Hinteres Viereck
    glBegin(GL_QUADS);
    glColor3f(1.0f-c, 0.0f+c, 1.0f+c);
    glVertex3f(-0.5, -0.5, 0.5);
    glColor3f(1.0f-c, 0.0f+c, 1.0f+c);
    glVertex3f( 0.5, -0.5, 0.5);
    glColor3f(1.0f-c, 0.0f+c, 1.0f+c);
    glVertex3f( 0.5,  0.5, 0.5);
    glColor3f(1.0f-c, 0.0f+c, 1.0f+c);
    glVertex3f(-0.5, 0.5, 0.5);
    glEnd();

    // Oberes Viereck
    glBegin(GL_QUADS);
    glColor3f(1.0f-c, 1.0f+c, 0.0f+c);
    glVertex3f(0.5, 0.5, -0.5);
    glColor3f(1.0f-c, 1.0f+c, 0.0f+c);
    glVertex3f( -0.5, 0.5, -0.5);
    glColor3f(1.0f-c, 1.0f+c, 0.0f+c);
    glVertex3f( -0.5,  0.5, 0.5);
    glColor3f(1.0f-c, 1.0f+c, 0.0f+c);
    glVertex3f(0.5, 0.5, 0.5);
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

