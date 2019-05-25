#include "oglwidget.h"
#include "vector3.h"
#include <cmath>
#include <iostream>


// Kugel(px, py, pz, masse, radius, Kanten, rot_rad, s)
OGLWidget::OGLWidget(QWidget *parent)
    : QOpenGLWidget(parent),
      kugel_1(Kugel(2.1,0,3,1,0.5,Kanten, Spalten, zpx, zpz, points)),
      kugel_2(Kugel(0,0,-100,1,1,Kanten, Spalten, zpx, zpz, points))
{
    // Setup the animation timer to fire every x msec
    animtimer = new QTimer(this);
    animtimer->start( 10 );

    // Everytime the timer fires, the animation is going one step forward
    connect(animtimer, SIGNAL(timeout()), this, SLOT(stepAnimation()));

    animstep = 0;
    zoom = 100;
    rotx = -30;
    roty= 40;
    unfold = 15;

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
    rotx = newrx % 360;
    update();
}

void OGLWidget::setRotY(int newry)
{
    roty = newry % 360;
    update();
}

void OGLWidget::setRotZ(int newrz)
{
    rotz = newrz % 360;
    update();
}



void OGLWidget::setZoom(int newzoom)
{
    zoom = newzoom;
    update();
}

void OGLWidget::setUnfold(int newunfold)
{
    unfold = newunfold;
    update();
}


void OGLWidget::initializeGL()
{


    initializeOpenGLFunctions();

    // Use depth testing and the depth buffer
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Calculate color for each pixel fragment
    glShadeModel(GL_SMOOTH);

    // Enable lighting in scene
    glEnable(GL_LIGHTING);

    // Set position of light source
    float light_pos[] = { 10.f, 10.f, 10.f, 0.f };
    glLightfv(GL_LIGHT1, GL_POSITION, light_pos );

    // Set color for this light source
    // (We are only specifying a diffuse light source)
    float light_diffuse[] = { .9f, .9f, .9f, 1.f };
    glLightfv(GL_LIGHT1, GL_DIFFUSE,  light_diffuse );

    // Turn on this light
    glEnable(GL_LIGHT1);

    // Use the color of an object for light calculation
    glColorMaterial( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );
    glEnable(GL_COLOR_MATERIAL);
}

void OGLWidget::resizeGL(int width, int height)
{
//        int side = qMin(width, height);
//            glViewport((width - side) / 2, (height - side) / 2, side, side);

//            glMatrixMode(GL_PROJECTION);
//            glLoadIdentity();
//        #ifdef QT_OPENGL_ES_1
//            glOrthof(-0.5, +0.5, -0.5, +0.5, 4.0, 15.0);
//        #else
//            glOrtho(-0.5, +0.5, -0.5, +0.5, 4.0, 15.0);
//        #endif
//            glMatrixMode(GL_MODELVIEW);
}


void OGLWidget::paintGL()
{

    dt = unfold/200;
    // Clear the scene
    glClearColor(0.f, 0.f, 0.f, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Prepare projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10, 10, -10, 10, 0, 200);

    // Prepare model matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();



    glTranslated(0,0,-15);

    // Change light position
    float light_pos[] = { (float)kugel_1.px,
                          1.0f,
                          (float)kugel_1.pz, 0.f };
    glLightfv(GL_LIGHT1, GL_POSITION,  light_pos);


    //    // Change light position
    //    float light_pos[] = { 10.f * cosf(animstep*PIf/180.f),
    //                          10.f,
    //                          10.0f * sinf(animstep*PIf/180.f), 0.f };
    //    glLightfv(GL_LIGHT1, GL_POSITION,  light_pos);

    // Apply rotation angles
    glRotated(-rotx, 1.0, 0.0, 0.0); // Rotate around x axis
    glRotated(-roty, 0.0, 1.0, 0.0); // Rotate around y axis
    glRotated(rotz, 0.0, 0.0, 1.0); // Rotate around z axis

    //Apply scaling
    double scale = zoom/100.0;
    glScaled( scale, scale, scale ); // Scale along all axis



    Bahn();


    Kreis(4,0.1,8,0.2);


    //    kugel_2.update(kugel_1, rotx, rotz, dt);

    kugel_1.update(kugel_2, rotx, rotz, dt);


    Pfeil();



}


// Geklaute Methode aus dem Netz
void OGLWidget::Kreis(double xmp, double ymp, double zmp, double r)
{
    double x,z;
    double y=ymp;

    glBegin(GL_POLYGON); //Begin Polygon coordinates
    for (double theta=0 ; theta<(2*3.1416) ; theta+=(2*3.1416)/360)
    {
        x = xmp+(cos(theta)*r);
        z = zmp+(sin(theta)*r);
        glVertex3d(x,y,z);
    }
    glEnd();
}



void OGLWidget::Pfeil() {

    double mx;
    double mz;

    if (pos_x < 0) pos_x = 0;
    if (pos_y < 0) pos_y = 0;
    if (pos_x > 1200) pos_x = 1200;
    if (pos_y > 1200) pos_y = 1200;

    if (pos_x == 0 && pos_y == 0) {
        mx = 0;
        mz = 0;
    } else {
        mx = (kugel_1.px -10) + (pos_x/width) * 20;
        mz = (kugel_1.pz -10) + (pos_y/width) * 20;
    }

    glColor3f(0, 1.0, 1.0);
    glLineWidth(20);
    glBegin(GL_LINES);
    glVertex3d(kugel_1.px, kugel_1.rad, kugel_1.pz);
    glVertex3d(mx, kugel_1.rad,mz);
    glEnd();

    mdx = mx - kugel_1.px;
    mdz = mz - kugel_1.pz;

      if (shoot) {
//        std::cout << "shoot: "<< shoot << std::endl;
        kugel_1.dx = mdx;
        kugel_1.dz = mdz;
        shoot = false;
        update();
    }

}



void OGLWidget::Bahn() {

    //und dann statt matrix[x][y]=5;
    //matrix[x+anzahlSpalten*y]=5;



    for (int i=0; i<Kanten; i++) {

        // Kantenstück
        glBegin(GL_QUADS);
        glColor3d(0.5, 0.0, 0.5);

        //Normalenvektor
        glNormal3d(points[0+Spalten*i],0,points[1+Spalten*i]);
        // Unten Links
        glVertex3d(points[0+Spalten*i],0,points[1+Spalten*i]);

        //Normalenvektor
        glNormal3d(points[0+Spalten*((i+1) % Kanten)],0,points[1+Spalten*((i+1) % Kanten)]);
        // Unten Links
        glVertex3d(points[0+Spalten*((i+1) % Kanten)],0,points[1+Spalten*((i+1) % Kanten)]);

        //Normalenvektor
        glNormal3d(points[0+Spalten*((i+1) % Kanten)],0.5,points[1+Spalten*((i+1) % Kanten)]);
        // Unten Links
        glVertex3d(points[0+Spalten*((i+1) % Kanten)],0.5,points[1+Spalten*((i+1) % Kanten)]);

        //Normalenvektor
        glNormal3d(points[0+Spalten*i],0.5,points[1+Spalten*i]);
        // Unten Links
        glVertex3d(points[0+Spalten*i],0.5,points[1+Spalten*i]);

        glEnd();
    }

}


void OGLWidget::mousePressEvent(QMouseEvent *event)
{
    // Upon mouse pressed, we store the current position...
    lastpos = event->pos();
}


void OGLWidget::mouseReleaseEvent(QMouseEvent *event)
{

    if (event->button() == Qt::LeftButton && !shoot) {
        shoot = true;
        Pfeil();
    }
}


void OGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    // ... and while moving, we calculate the dragging deltas
    // Left button: Rotating around x and y axis
    pos_x = (event->buttons() & Qt::LeftButton) ? event->x() : 0;
    pos_y = (event->buttons() & Qt::LeftButton) ? event->y() : 0;


    //    // Right button: Rotating around z and y axis
    //    pos_z = (event->buttons() & Qt::RightButton) ? event->y() : 0;


//    std::cout << "pos_x: "<< pos_x << std::endl;
//    std::cout << "pos_y: "<< pos_y << std::endl;
//    std::cout << "pos_z: "<< pos_z << std::endl;




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



        // Left/Right: Rotating around z axis
    case Qt::Key_Left:
        emit changeRotation( 0, 0, keyDelta );
        break;
    case Qt::Key_Right:
        emit changeRotation( 0, 0, -keyDelta );
        break;


        // Pg up/down: Rotating around y axis
    case Qt::Key_PageUp:
        emit changeRotation( 0, keyDelta, 0 );
        break;
    case Qt::Key_PageDown:
        emit changeRotation( 0, -keyDelta, 0 );
        break;

        // All other will be ignored
    default:
        break;
    }
}
