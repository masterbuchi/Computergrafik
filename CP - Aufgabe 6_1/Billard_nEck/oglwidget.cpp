#include "oglwidget.h"
#include "vec3.hpp"
#include <cmath>



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
    PI = 3.1415f;
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

void OGLWidget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


void OGLWidget::paintGL()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glOrtho(-10, 10, -10, 10, 0, 200);
    c = animstep;   // rotate one degree with each step
    glTranslatef(0,0,-10);

    // Apply rotation angles
    glPushMatrix();
    glRotatef(-rotx, 1.0f, 0.0f, 0.0f); // Rotate around x axis
    glRotatef(-roty, 0.0f, 1.0f, 0.0f); // Rotate around y axis
    glRotatef(rotz, 0.0f, 0.0f, 1.0f); // Rotate around z axis

    //Apply scaling
    double scale = zoom/100.0;
    glScaled( scale, scale, scale ); // Scale along all axis

    glPushMatrix();
    Tisch();
    glPopMatrix();



    dt=unfold/200;


    px+=dx*dt;
    pz+=dz*dt;

    glPushMatrix();
    glTranslated(px,1,pz);


    for (int i=0; i<Ecken; i++)
    {
        Kollision(i);

    }


    Kugel(QVector3D(0, 0, 0), 1);

    glPopMatrix();
    glPopMatrix();

}

void OGLWidget::Kugel( const QVector3D& pos, float rad,
                            int nr_lat, int nr_lon )
{
    // Angle delta in both directions
    const float lat_delta = PI / float( nr_lat );
    const float lon_delta = PI / float( nr_lon );

    // Create horizontal stripes of squares
    for( float lon = 0.0f; lon < 1.0f*PI; lon += lon_delta )
    {
        glBegin( GL_QUAD_STRIP ) ;
        for( float lat = 0.0f; lat <= 2.0f*PI; lat += lat_delta )
        {
            // Each iteration adds another square, the other vertices
            // are taken from the existing stripe
            float xn1 = cosf( lat ) * sinf( lon );
            float yn1 = sinf( lat ) * sinf( lon );
            float zn1 = cosf( lon );

            // Set normal vector (important for lighting!)
            glNormal3f( xn1, yn1, zn1 );
            glVertex3f( pos.x()+rad*xn1, pos.y()+rad*yn1, pos.z()+rad*zn1 );

            float xn2 = cosf( lat ) * sinf( lon + lon_delta );
            float yn2 = sinf( lat ) * sinf( lon + lon_delta );
            float zn2 = cosf( lon + lon_delta );

            glNormal3f( xn2, yn2, zn2 );
            glVertex3f( pos.x()+rad*xn2, pos.y()+rad*yn2, pos.z()+rad*zn2 );
        }
        glEnd() ;
    }
}



void OGLWidget::Tisch() {

    // For-Schleife für alle Dreiecke, werden durch i gedreht
    for (int i=0; i<Ecken; i++)
    {
        // Jeweiliges Dreieck
        glBegin(GL_TRIANGLES);

        //Normalenvektor, Senkrecht nach unten
        glNormal3d(0,-1,0);

        // Farbe (hellgrau)
        glColor3d(0.5, 0.5, 0.5);
        //Mittelpunkt
        glVertex3d(0, 0, 0);
        //Punkt Außen auf Z nach Vorne
        glVertex3d(s * -sin(i*rot_rad), 0 , s * cos(i*rot_rad));
        //Rotationspunkt
        glVertex3d(s * -sin((i+1)*rot_rad), 0 , s * cos((i+1)*rot_rad));
        glEnd();

        // Mantelstück
        glBegin(GL_QUADS);
        glColor3d(255.0, 0.0, 255.0);
        // Unten Links
        glVertex3d(s * -sin(i*rot_rad), 0, s * cos(i*rot_rad));
        // Unten Rechts
        glVertex3d(s * -sin((i+1)*rot_rad),0,  s * cos((i+1)*rot_rad) );
        // Oben Rechts
        glVertex3d(s * -sin((i+1)*rot_rad),1 , s * cos((i+1)*rot_rad) );
        // Oben Links
        glVertex3d(s * -sin(i*rot_rad), 1, s * cos(i*rot_rad));
        glEnd();

    }

}

void OGLWidget::Schnittpunkt(int i) {

    // Berechnung der Lamdas des Schnittpunkt
    double lam = -(px + s*sin(i*rot_rad) - (dx*(pz - s*cos(i*rot_rad)))/dz)/(s*(sin(rot_rad*(i + 1)) - sin(i*rot_rad)) - (dx*s*(cos(i*rot_rad) - cos(rot_rad*(i + 1))))/dz);
    double lam2 = (s * cos(i*rot_rad) + lam * s * (cos((i+1)*rot_rad) - cos( i * rot_rad)) -pz) / dz;

    // Schnittpunkt
    sx = px + lam2  * dx;
    sz = pz + lam2 * dz;


}
void OGLWidget::Kollision(int i) {

    Schnittpunkt(i);

    // Zwischenrechnung
    double x_2 = pow((px-sx),2);
    double z_2 = pow((pz-sz),2);

    // Berechnung des Abstands zwischen Kreismittelpunkt und Schnittpunkt mit der jeweiligen Geraden
    double abstand = sqrt(x_2 + z_2);

    // Wenn der Kugelrand gegen den Schnittpunkt kommt
    if (abstand<1) {

        // NormalvektorKoordinaten
        double normx = -(s * (cos((i+1)*rot_rad) - cos( i * rot_rad)));
        double normz = (s * (-sin((i+1)*rot_rad) + sin( i * rot_rad)));

        //Zwischenrechnung
        double powx = pow(normx,2);
        double powz = pow(normz,2);
        double bruch = 2/(powx+powz);

        // Zwischenspeichern der alten dx und dz-Werte
        double dx_t = dx;
        double dz_t = dz;

        // Berechnung der neuen Werte
        dx = ((1-bruch*powx)*dx_t+(0-(bruch*normx*normz))*dz_t);
        dz = ((0-bruch*normx*normz)*dx_t+(1-bruch*powz)*dz_t);
    }

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



// s * -sin(i*rot_rad) + lam * s * (-sin((i+1)*rot_rad) + sin( i * rot_rad)) = px + lam2 * dx;
// s * cos(i*rot_rad) + lam * s * (cos((i+1)*rot_rad) - cos( i * rot_rad)) = pz + lam2 * dz;

