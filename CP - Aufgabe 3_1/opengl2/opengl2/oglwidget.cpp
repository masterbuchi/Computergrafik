#include "oglwidget.h"

OGLWidget::OGLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    parama = 0;
    paramb = 20;
    paramc = 20;
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


    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    //    glShadeModel(GL_SMOOTH);

    // GLfloat Ambient[4] = {0.2f, 0.2f, 0.2f, 1.0f};
    //Lighting set up
    // glLightModelfv(GL_LIGHT_MODEL_AMBIENT, Ambient);
    glEnable(GL_LIGHTING);

    GLfloat L2Position[4] = {1.0f,1.0f,1.0f,0 }; //Position Ersten drei Position in Koordinatensystem
    glLightfv(GL_LIGHT0, GL_POSITION, &L2Position[3]); //welches licht, welche Eigenschaft, welchen Wert

    //Diffuse
    GLfloat LDiffuse[] = {0.2f, 0.2f, 0.2f, 1.0};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, LDiffuse);
    glEnable(GL_LIGHT0);



    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);



}

void OGLWidget::einheitsquadrat() {
    glBegin(GL_QUADS);
    glColor3f(100.0f, 100.0f,0);
    glVertex3f(0,0,0); // hinten rechts
    glVertex3f(1.0f,0,0); // hinten links
    glVertex3f(1.0f,1.0f,0); // vorne links
    glVertex3f(0,1.0f,0); // vorne rechts
    glEnd();
}
void OGLWidget::boden() {
    glBegin(GL_QUADS);
    glColor3f(100.0f, 100.0f,100.0f);
    glVertex3f(50.0f,-0.1f,-50.0f); // hinten rechts
    glVertex3f(-50.0f,-0.1f,-50.0f); // hinten links
    glVertex3f(-50.0f,-0.1f,50.0f); // vorne links
    glVertex3f(50.0f,-0.1f,50.0f); // vorne rechts
    glEnd();
}

void OGLWidget::paintGL()
{




//    float PI = 3.14159f;


    float openingSlide180 = paramr * 1.8f;
    float openingSlide90 = paramr * 0.9f;

    float x = paramb*1.8f;   // degree to rotate
    float y = paramc*1.8f;   // degree to rotate
    float z = paramd*1.8f;   // degree to rotate


    // Clear the scene
    glClearColor(0.f, 0.f, 0.f, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glLoadIdentity();

    glScalef(0.5f,0.5f,0.5f);

    glRotatef(x, -1.0f, 0.0f, 0.0f); // Rotate by x degrees around x axis
    glRotatef(y, 0.0f, -1.0f, 0.0f); // Rotate by y degrees around y axis
    glRotatef(z, 0.0f, 0.0f, 1.0f); // Rotate by z degrees around z axis

    //    // Change light position
    //    float light_pos[] = { 10.f * cosf(parama*PI/180.f),
    //                          5.f,
    //                          10.f * sinf(parama*PI/180.f), 0.f };
    //    glLightfv(GL_LIGHT0, GL_POSITION,  light_pos);

    boden();
    glTranslatef(-1.0f,0,0);

    //Quadrat X-Y-Ebene
    einheitsquadrat();



    // Quadrat X-Z-Ebene    // Quadrat Y-Z-Ebene
    glRotatef(90.0f, 0, 1.0f,0); //Rotation um Y-Achse
    einheitsquadrat();
    glRotatef(90.0f, 0, -1.0f,0);
    glRotatef(90.0f, -1.0f, 0,0); //Rotation um X-Achse
    einheitsquadrat();
    glRotatef(90.0f, 1.0f, 0,0);




    // Verschobenes Quadrat Y-Z-Ebene
    glRotatef(90.0f, 0, 1.0f,0); //Rotation um Y-Achse
    glTranslatef(0, 0, 1.0f);    // Translation im neuen Koordinatensystem, also selbe Funktion (Hier aber in die andere Richtung)
    einheitsquadrat();
    glTranslatef(0, 0, -1.0f);
    glRotatef(90.0f, 0, -1.0f,0);

    // Verschobenes Quadrat X-Z-Ebene
    glRotatef(90.0f, -1.0f, 0,0); //Rotation um X-Achse
    glTranslatef(0, 0, 1.0f);    // Translation im neuen Koordinatensystem, also selbe Funktion (Hier aber in die andere Richtung)
    einheitsquadrat();
    glTranslatef(0, 0, -1.0f);
    glRotatef(90.0f, 1.0f, 0,0);



//        // Verschobenes Rechteck X-Y-Ebene Beginn
//            glTranslatef(0, 0, -1.0f);
//            glTranslatef(0.5f, 0, 0);             // Punkt um den man rotieren will
//            glRotatef(openingSlide90, -1.0f, 0, 0);
//            glTranslatef(-0.5f, 0, 0);          // Zurück an die eigentliche Stelle transformieren
//            einheitsquadrat();


//    // Verschobenes Rechteck X-Y-Ebene Beginn
//    glTranslatef(0, 0, -1.0f);


//    glTranslatef(0.5f, 0, 0);             // Punkt um den man rotieren will
//    glRotatef(openingSlide90, -1.0f, 0, 0);
//    glScalef(1.0f,0.25f,1.0f);
//    glTranslatef(-0.5f, 0, 0);          // Zurück an die eigentliche Stelle transformieren
//    einheitsquadrat();

//    glTranslatef(0, 1.0f, 0);             // Punkt um den man rotieren will
//    glRotatef(openingSlide180, 1.0f, 0, 0);
//    einheitsquadrat();


    // Verschobenes Rechteck X-Y-Ebene Beginn
    glTranslatef(0, 0, -1.0f);

    glPushMatrix();
    glTranslatef(0.5f, 0, 0);             // Punkt um den man rotieren will
    glRotatef(openingSlide90, -1.0f, 0, 0);
    glScalef(1.0f,0.25f,1.0f);
    glTranslatef(-0.5f, 0, 0);          // Zurück an die eigentliche Stelle transformieren
    einheitsquadrat();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.5f, 0.25f, 0);             // Punkt um den man rotieren will
    glRotatef(openingSlide180, 1.0f, 0, 0);
    glScalef(1.0f,0.25f,1.0f);
    glTranslatef(-0.5f, -0.25f, 0);          // Zurück an die eigentliche Stelle transformieren
    einheitsquadrat();
    glPopMatrix();






    //    // Oberes Rechteck 1
    //    glBegin(GL_QUADS);
    //    glColor3f(1.0f, 1.0f, 1.0f);
    //    glVertex3f(0.5, 0.5, -0.5); // hinten rechts
    //    glVertex3f( 0.25, 0.5, -0.5); // hinten links
    //    glVertex3f( 0.25,  0.5, 0.5); // vorne links
    //    glVertex3f(0.5, 0.5, 0.5); // vorne rechts
    //    glEnd();

    //    glTranslatef(0.25f, 0.5f, 0);             // Punkt um den man rotieren will
    //    glRotatef(openingSlide180, 0, 0, 1.0f);
    //    glTranslatef(-0.25f, -0.5f, 0);         // Zurück an die eigentliche Stelle transformieren

    //    // Oberes Rechteck 2
    //    glBegin(GL_QUADS);
    //    glVertex3f(0.25, 0.5, -0.5); // hinten rechts
    //    glVertex3f( 0, 0.5, -0.5); // hinten links
    //    glVertex3f( 0,  0.5, 0.5); // vorne links
    //    glVertex3f(0.25, 0.5, 0.5); // vorne rechts
    //    glEnd();

    //    glTranslatef(0, 0.5f, 0);             // Punkt um den man rotieren will
    //    glRotatef(openingSlide180, 0, 0, -1.0f);
    //    glTranslatef(0, -0.5f, 0);         // Zurück an die eigentliche Stelle transformieren


    //    // Oberes Rechteck 3
    //    glBegin(GL_QUADS);
    //    glVertex3f(0, 0.5, -0.5); // hinten rechts
    //    glVertex3f( -0.25, 0.5, -0.5); // hinten links
    //    glVertex3f( -0.25,  0.5, 0.5); // vorne links
    //    glVertex3f(0, 0.5, 0.5); // vorne rechts
    //    glEnd();

    //    glTranslatef(-0.25f, 0.5f, 0);             // Punkt um den man rotieren will
    //    glRotatef(openingSlide180, 0, 0, 1.0f);
    //    glTranslatef(0.25f, -0.5f, 0);         // Zurück an die eigentliche Stelle transformieren

    //    // Oberes Rechteck 4
    //    glBegin(GL_QUADS);
    //    glVertex3f(-0.25, 0.5, -0.5); // hinten rechts
    //    glVertex3f(-0.5, 0.5, -0.5); // hinten links
    //    glVertex3f(-0.5,  0.5, 0.5); // vorne links
    //    glVertex3f(-0.25, 0.5, 0.5); // vorne rechts
    //    glEnd();





}


void OGLWidget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

