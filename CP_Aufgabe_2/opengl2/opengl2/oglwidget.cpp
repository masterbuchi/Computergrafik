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


    glEnable(GL_LIGHTING);


    glEnable(GL_DEPTH_TEST);

    //glDepthFunc(GL_LESS);
    glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);


    // Farbparameter werden vorgegeben.
    GLfloat farbModell[4] = {0.2f, 0.2f, 0.2f, 1.0f};


    // Ambientes Licht wird mit den obrigen Parametern erzeugt
    // Ambientes Licht ist global und strahlt von allen Seiten
    // Es sollte eher subtil eingesetzt werden, daher nur 0.2 als "Unterstützungswert"
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,farbModell);


}

void OGLWidget::paintGL()
{
//    GLfloat LPosition[4] = {1.0f, 1.0f, 1.0f, 1.0f}; //Position Ersten drei Position in Koordinatensystem
//    glLightfv(GL_LIGHT0, GL_POSITION, &LPosition[3]); //welches licht, welche Eigenschaft, welchen Wert

      GLfloat L1Position[4] = {2.0f, 2.0f, 2.0f, 2.0f}; //Position Ersten drei Position in Koordinatensystem
      glLightfv(GL_LIGHT0, GL_POSITION, &L1Position[3]); //welches licht, welche Eigenschaft, welchen Wert

      GLfloat L2Position[4] = {-2.0f, 2.0f, 2.0f, 2.0f}; //Position Ersten drei Position in Koordinatensystem
      glLightfv(GL_LIGHT1, GL_POSITION, &L2Position[3]); //welches licht, welche Eigenschaft, welchen Wert


//    //Ambiente: (hat keine position)
//    GLfloat LAmbient[] = {1.0f, 1.0f, 1.0f, 1.0}; //RED GREEN BLUE ALPHA(immer 1.0) Alle Farbwerte gleich = weißes licht
//    glLightfv(GL_LIGHT0, GL_AMBIENT, &LAmbient[0]);

//    //Diffuse
//    //GLfloat LDiffuse[] = {0.6, 0.6, 0.6, 1.0};
//    //glLightfv(GL_LIGHT1, GL_DIFFUSE, LDiffuse);

//    //Spot
    GLfloat LSPot[] = {0.13f, 0.70f, 0.80f, 0.5f};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, LSPot);

    // Spot 2
    GLfloat LSPot2[] = {1.0f, 0.0f, 0.0f, 0.5f};
    glLightfv(GL_LIGHT1, GL_DIFFUSE, LSPot2);




//    //Material: (für farbige reflexionen (schwarz deaktiviert)
//    GLfloat mWhite[] = {255.0, 255.0, 255.0, 1.0};
    //GLfloat mGreen[] = {0.0, 255.0, 0.0, 1.0};
    //glMaterialfv(GL_FRONT, GL_AMBIENT, mGreen);
//    glMaterialfv(GL_FRONT, GL_DIFFUSE, mWhite);
//    glMaterialf(GL_FRONT, GL_SHININESS, 0.0);



    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);

    //float c = parama/100.0f; // change of color
    float r = paramb*3.6f;   // degree to rotate
    float s = paramc*3.6f;   // degree to rotate
    float t = paramd*3.6f;   // degree to rotate

    float openingSlide180 = paramr * 1.8f;
    float openingSlide90 = paramr * 0.9f;

     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    glRotatef(r, -1.0f, 0.0f, 0.0f); // Rotate by r degrees around x axis
    glRotatef(s, 0.0f, -1.0f, 0.0f); // Rotate by s degrees around y axis
    glRotatef(t, 0.0f, 0.0f, 1.0f); // Rotate by t degrees around z axis


    //      // Alter Deckel
    //    glPushMatrix();

    //    glTranslatef(0.5f, 0.5, 0);             // Punkt um den man rotieren will
    //    glRotatef(opening, 0, 0, -1.0f);
    //    glTranslatef(-0.5f, -0.5f, 0);          // Zurück an die eigentliche Stelle transformieren

    //    // Oberes Viereck - Deckel
    //    glBegin(GL_QUADS);
    //        glColor3f(1.0f-c, 0.0f+c, 0.0f+c);
    //        glVertex3f(0.5, 0.5, -0.5); // hinten rechts
    //        glColor3f(1.0f-c, 0.0f+c, 0.0f+c);
    //        glVertex3f( -0.5, 0.5, -0.5); // hinten links
    //        glColor3f(1.0f-c, 0.0f+c, 0.0f+c);
    //        glVertex3f( -0.5,  0.5, 0.5); // vorne links
    //        glColor3f(1.0f-c, 0.0f+c, 0.0f+c);
    //        glVertex3f(0.5, 0.5, 0.5); // vorne rechts
    //    glEnd();

    //    glPopMatrix();

    glPushMatrix();

    glTranslatef(0.5f, 0.5f, 0);             // Punkt um den man rotieren will
    glRotatef(openingSlide90, 0, 0, -1.0f);
    glTranslatef(-0.5f, -0.5f, 0);          // Zurück an die eigentliche Stelle transformieren

    // Oberes Rechteck 1
    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(0.5, 0.5, -0.5); // hinten rechts
    glVertex3f( 0.25, 0.5, -0.5); // hinten links
    glVertex3f( 0.25,  0.5, 0.5); // vorne links
    glVertex3f(0.5, 0.5, 0.5); // vorne rechts
    glEnd();

    glTranslatef(0.25f, 0.5f, 0);             // Punkt um den man rotieren will
    glRotatef(openingSlide180, 0, 0, 1.0f);
    glTranslatef(-0.25f, -0.5f, 0);         // Zurück an die eigentliche Stelle transformieren

    // Oberes Rechteck 2
    glBegin(GL_QUADS);
    glVertex3f(0.25, 0.5, -0.5); // hinten rechts
    glVertex3f( 0, 0.5, -0.5); // hinten links
    glVertex3f( 0,  0.5, 0.5); // vorne links
    glVertex3f(0.25, 0.5, 0.5); // vorne rechts
    glEnd();

    glTranslatef(0, 0.5f, 0);             // Punkt um den man rotieren will
    glRotatef(openingSlide180, 0, 0, -1.0f);
    glTranslatef(0, -0.5f, 0);         // Zurück an die eigentliche Stelle transformieren


    // Oberes Rechteck 3
    glBegin(GL_QUADS);
    glVertex3f(0, 0.5, -0.5); // hinten rechts
    glVertex3f( -0.25, 0.5, -0.5); // hinten links
    glVertex3f( -0.25,  0.5, 0.5); // vorne links
    glVertex3f(0, 0.5, 0.5); // vorne rechts
    glEnd();

    glTranslatef(-0.25f, 0.5f, 0);             // Punkt um den man rotieren will
    glRotatef(openingSlide180, 0, 0, 1.0f);
    glTranslatef(0.25f, -0.5f, 0);         // Zurück an die eigentliche Stelle transformieren

    // Oberes Rechteck 4
    glBegin(GL_QUADS);
    glVertex3f(-0.25, 0.5, -0.5); // hinten rechts
    glVertex3f(-0.5, 0.5, -0.5); // hinten links
    glVertex3f(-0.5,  0.5, 0.5); // vorne links
    glVertex3f(-0.25, 0.5, 0.5); // vorne rechts
    glEnd();



    glPopMatrix();




    // Vorderes Viereck
    glBegin(GL_QUADS);
    glVertex3f(-0.5, -0.5, -0.5);
    glVertex3f(0.5, -0.5, -0.5);
    glVertex3f( 0.5,  0.5, -0.5);
    glVertex3f(-0.5, 0.5, -0.5);
    glEnd();

    // Linkes Viereck
    glBegin(GL_QUADS);
    glVertex3f(-0.5, -0.5, -0.5);
    glVertex3f( -0.5, -0.5, 0.5);
    glVertex3f( -0.5,  0.5, 0.5);
    glVertex3f(-0.5, 0.5, -0.5);
    glEnd();

//      glColor3f(1.0f, 0.0f, 1.0f);
    // Rechtes Viereck
    glBegin(GL_QUADS);
    glVertex3f(0.5, -0.5, -0.5);
    glVertex3f( 0.5, -0.5, 0.5);
    glVertex3f( 0.5,  0.5, 0.5);
    glVertex3f(0.5, 0.5, -0.5);
    glEnd();

    // Unteres Viereck
    glBegin(GL_QUADS);
    glVertex3f(0.5, -0.5, -0.5);
    glVertex3f( -0.5, -0.5, -0.5);
    glVertex3f( -0.5,  -0.5, 0.5);
    glVertex3f(0.5, -0.5, 0.5);
    glEnd();

    // Hinteres Viereck
    glBegin(GL_QUADS);
    glVertex3f(-0.5, -0.5, 0.5);
    glVertex3f( 0.5, -0.5, 0.5);
    glVertex3f( 0.5,  0.5, 0.5);
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

