#include "oglwidget.h"
#include "vector3.h"
#include <cmath>
#include <iostream>


// Kugel(px, py, pz, masse, radius, Kanten, rot_rad, s)
OGLWidget::OGLWidget(QWidget *parent)
    : QOpenGLWidget(parent),
      kugel_1(Kugel(0,0,1.99,1,0.5,Kanten, Spalten, zpx, zpz, points)),
      kugel_2(Kugel(0,0,-100,1,1,Kanten, Spalten, zpx, zpz, points))
{
    // Setup the animation timer to fire every x msec
    animtimer = new QTimer(this);
    animtimer->start( 10 );

    // Everytime the timer fires, the animation is going one step forward
    connect(animtimer, SIGNAL(timeout()), this, SLOT(stepAnimation()));

    animstep = 0;
    zoom = 100;
    rotx = -60;
    roty= 40;
    unfold = 1;
    kugel_1.dx = 2;

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

    //    // Use depth testing and the depth buffer
    //    glEnable(GL_DEPTH_TEST);
    //    glDepthFunc(GL_LESS);

    //    // Calculate color for each pixel fragment
    //    glShadeModel(GL_SMOOTH);

    //    // Enable lighting in scene
    //    glEnable(GL_LIGHTING);


    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_SMOOTH);

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glEnable(GL_LIGHTING);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHT0);
    GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat spot_direction[] = { 0.0f , -1.0f, 1.0 };


    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);


    // Use the color of an object for light calculation
    glColorMaterial( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );
    glEnable(GL_COLOR_MATERIAL);
}

void OGLWidget::resizeGL(int width, int height)
{

    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
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

    // Change light position
    float light_pos[] = { float(kugel_1.px),
                          10,
                          float(kugel_1.pz), 1 };
    glLightfv(GL_LIGHT0, GL_POSITION,  light_pos);

    // Prepare model matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslated(0,0,-15);

    // Apply rotation angles
    glRotated(-rotx, 1.0, 0.0, 0.0); // Rotate around x axis
    glRotated(-roty, 0.0, 1.0, 0.0); // Rotate around y axis
    glRotated(rotz, 0.0, 0.0, 1.0); // Rotate around z axis

    //Apply scaling
    double scale = zoom/100.0;
    glScaled( scale, scale, scale ); // Scale along all axis

    Bahn();

    glColor3d(0, 1.0, 0.5);
    Kreis(0,0,0,0.1);

    glColor3d(1, 0, 0.5);
    Kreis(4,0,8,0.2);

    kugel_1.update(kugel_2, rotx, rotz, dt, Versuche);

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
        glNormal3d(0,1,0);
        glVertex3d(x,y,z);
    }
    glEnd();
}



void OGLWidget::Pfeil() {


    double newpos_x;
    double newpos_y;


    if (pos_x < 0) pos_x = 0;
    if (pos_y < 0) pos_y = 0;
    if (pos_x > 800) pos_x = 800;
    if (pos_y > 800) pos_y = 800;


    newpos_x = - 0.5 * width + pos_x;
    newpos_y = - 0.5 * width + pos_y;


    mdx = newpos_x * 2/width * 10;
    mdz = newpos_y * 2/width * 10;


    float f = float(sqrt((pow(mdx,2))+(pow(mdz,2))));

    if (f > 10) f = 10;

    //   std::cout << "force: "<< f << std::endl;

    if (shoot) {
        glColor3f(f/10,1-f/10,0);
        glLineWidth(10);
        glBegin(GL_LINES);
        glVertex3d(kugel_1.px, kugel_1.rad, kugel_1.pz);
        glVertex3d(kugel_1.px + mdx, kugel_1.rad,kugel_1.pz + mdz);
        glEnd();
    }

}




void OGLWidget::Bahn() {

    for (int i=0; i<Kanten; i++) {

        // Kantenstück
        glBegin(GL_QUADS);
        glColor3d(0.5, 0.0, 0.5);

        Vector3 ov = Vector3(points[0+Spalten*i],0,points[1+Spalten*i]);
        Vector3 ov2 = Vector3(points[0+Spalten*((i+1) % (Kanten))],0,points[1+Spalten*((i+1) % (Kanten))]);
        Vector3 rv = Vector3(ov2.x - ov.x,0,ov2.z-ov.z);

        // Normalvektor
        Vector3 norm = Vector3(rv.z,0,rv.x);


        // Normalvektor normieren
        norm.normalize();

        //Normalenvektor
        glNormal3d(norm.x,0,norm.z);
        // Unten Links
        glVertex3d(points[0+Spalten*i],0,points[1+Spalten*i]);

        //Normalenvektor
        glNormal3d(norm.x,0,norm.z);
        // Unten Links
        glVertex3d(points[0+Spalten*((i+1) % Kanten)],0,points[1+Spalten*((i+1) % Kanten)]);

        //Normalenvektor
        glNormal3d(norm.x,0,norm.z);
        // Unten Links
        glVertex3d(points[0+Spalten*((i+1) % Kanten)],0.5,points[1+Spalten*((i+1) % Kanten)]);

        //Normalenvektor
        glNormal3d(norm.x,0,norm.z);
        // Unten Links
        glVertex3d(points[0+Spalten*i],0.5,points[1+Spalten*i]);

        glEnd();
    }

}


void OGLWidget::mousePressEvent(QMouseEvent *event)
{
    // Upon mouse pressed, we store the current position...
    lastpos = event->pos();
    pos_x = (event->buttons() & Qt::LeftButton) ? event->x() : 0;
    pos_y = (event->buttons() & Qt::LeftButton) ? event->y() : 0;
    shoot = true;
    Versuche++;
}


void OGLWidget::mouseReleaseEvent(QMouseEvent *event)
{

    if (event->button() == Qt::LeftButton && shoot) {
        kugel_1.dx = mdx;
        kugel_1.dz = mdz;
        shoot = false;
        update();
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
