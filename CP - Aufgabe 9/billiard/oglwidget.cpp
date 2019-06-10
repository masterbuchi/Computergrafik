#include "oglwidget.h"
#include "vector3.h"
#include "vector4.h"
#include <cmath>
#include <iostream>
#include <QPainter>


// Kugel(px, py, pz, masse, radius, Kanten, rot_rad, s)
OGLWidget::OGLWidget(QWidget *parent)
    : QOpenGLWidget(parent),
      kugel_1(Kugel(0,0,0,1,0.45, zpx, zpz, points)),
      kugel_2(Kugel(0,0,20,1,0.45, zpx, zpz, points)),
      kugel_3(Kugel(0.45,0,20.78,1,0.45, zpx, zpz, points)),
      kugel_4(Kugel(-0.45,0,20.78,1,0.45, zpx, zpz, points))
{
    // Setup the animation timer to fire every x msec
    animtimer = new QTimer(this);
    animtimer->start( 5 );

    // Everytime the timer fires, the animation is going one step forward
    connect(animtimer, SIGNAL(timeout()), this, SLOT(stepAnimation()));

    animstep = 0;
    zoom = 45;
    rotx = -90;
    unfold = 5;
    trans_lr = 0;
    trans_ou = 4.5;


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

void OGLWidget::setRotZ(int newtrans_lr)
{
    trans_lr = newtrans_lr;
    update();
}


void OGLWidget::setEckenbeschl()
{
    if (eckenbeschl) eckenbeschl = false;
    else eckenbeschl = true;
    update();
}


void OGLWidget::setZoom(int newtrans_ou)
{
    trans_ou = newtrans_ou;
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


    //    GLfloat mat_specular[] = { 0.5f, 0.5f, 0.5f, 1.0 };
    //    GLfloat mat_shininess[] = { 20.0 };
    float light_position[] = { 50,
                               50,
                               50, 0 };
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_SMOOTH);

    //    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    //    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glEnable(GL_LIGHTING);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHT0);
    GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 0 };
    GLfloat light_diffuse[] = { 0.5f,0.5f,0.5f,0 };
    GLfloat light_specular[] = { 0.1f, 0.1f, 0.1f, 0 };
    GLfloat spot_direction[] = { 0.0f , -1.0f, 0.0 };


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

    float light_position[] = { 50,
                               50,
                               50, 0 };
    glLightfv(GL_LIGHT0, GL_POSITION,  light_position);

    // Prepare model matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();




    glTranslated(trans_lr,trans_ou,-20);



    //Apply scaling
    double scale = zoom/100.0;
    glScaled( scale, scale, scale ); // Scale along all axis

    // Apply rotation angles
    glRotated(-rotx, 1.0, 0.0, 0.0); // Rotate around x axis
    glRotated(-roty, 0.0, 1.0, 0.0); // Rotate around y axis
    glRotated(rotz, 0.0, 0.0, 1.0); // Rotate around z axis


    glColor3d(0, 1.0, 0.5);
    Kreis(0,0.1,0,0.1);

    glColor3d(1, 0, 0.5);
    Kreis(-12,0.1,6,0.2);


    if (eckenbeschl) {

        // Kollisionsprüfung der Ecken mit einer Beschleunigung
        for (int i=0; i<Kanten; i++)

        {
            // Jeweilige Ortsvektoren bestimmen
            Vector3 ov1 = Vector3(points[0+Spalten*i],0,points[1+Spalten*i]);

            Vector3 kugeldneu = Eckenbeschleunigung(kugel_1, ov1);
            kugel_1.dx = kugeldneu.x;
            kugel_1.dz = kugeldneu.z;

        }
    }

    // KugelKollision mit Kugel 2 prüfen
    Vector4 newd = CheckKollisionKugel(kugel_1, kugel_2);
    kugel_1.dx = newd.x;
    kugel_1.dz = newd.y;
    kugel_2.dx = newd.z;
    kugel_2.dz = newd.a;



    // KugelKollision mit Kugel 3 prüfen
    Vector4 newd2 = CheckKollisionKugel(kugel_1, kugel_3);
    kugel_1.dx = newd2.x;
    kugel_1.dz = newd2.y;
    kugel_3.dx = newd2.z;
    kugel_3.dz = newd2.a;

    // KugelKollision mit Kugel 3 prüfen
    Vector4 newd3 = CheckKollisionKugel(kugel_1, kugel_4);
    kugel_1.dx = newd3.x;
    kugel_1.dz = newd3.y;
    kugel_4.dx = newd3.z;
    kugel_4.dz = newd3.a;


    // KugelKollision mit Kugel 3 prüfen
    Vector4 newd4 = CheckKollisionKugel(kugel_2, kugel_3);
    kugel_2.dx = newd4.x;
    kugel_2.dz = newd4.y;
    kugel_3.dx = newd4.z;
    kugel_3.dz = newd4.a;

    // KugelKollision mit Kugel 3 prüfen
    Vector4 newd5 = CheckKollisionKugel(kugel_2, kugel_4);
    kugel_2.dx = newd5.x;
    kugel_2.dz = newd5.y;
    kugel_4.dx = newd5.z;
    kugel_4.dz = newd5.a;

    // KugelKollision mit Kugel 3 prüfen
    Vector4 newd6 = CheckKollisionKugel(kugel_3, kugel_4);
    kugel_3.dx = newd6.x;
    kugel_3.dz = newd6.y;
    kugel_4.dx = newd6.z;
    kugel_4.dz = newd6.a;



    // Kollisionsprüfung der Außenkanten
    for (int i=0; i<Kanten; i++)

    {
        // Jeweilige Ortsvektoren der Gerade bestimmen
        Vector3 ov1 = Vector3(points[0+Spalten*i],0,points[1+Spalten*i]);
        Vector3 ov2 = Vector3(points[0+Spalten*((i+1) % (Kanten))],0,points[1+Spalten*((i+1) % (Kanten))]);

        Vector3 kugeldneu = KollisionmitWand(kugel_1, ov1, ov2);
        kugel_1.dx = kugeldneu.x;
        kugel_1.dz = kugeldneu.z;

        Vector3 kugeldneu2 = KollisionmitWand(kugel_2, ov1, ov2);
        kugel_2.dx = kugeldneu2.x;
        kugel_2.dz = kugeldneu2.z;
        Vector3 kugeldneu3 = KollisionmitWand(kugel_3, ov1, ov2);
        kugel_3.dx = kugeldneu3.x;
        kugel_3.dz = kugeldneu3.z;
        Vector3 kugeldneu4 = KollisionmitWand(kugel_4, ov1, ov2);
        kugel_4.dx = kugeldneu4.x;
        kugel_4.dz = kugeldneu4.z;

    }

    // Zeichnen
    Pfeil();

    Boden();

    Bahn();

    float cr, cg, cb;
    cr = cg = cb = 1.0f;
    kugel_1.update(dt, Versuche, cr, cg, cb);

    cr = 1.0f;
    cg = cb = 0;
    kugel_2.update(dt, Versuche, cr, cg, cb);
    kugel_3.update(dt, Versuche, cr, cg, cb);
    kugel_4.update(dt, Versuche, cr, cg, cb);


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



Vector3 OGLWidget::Lotschnittpunkt(Kugel kugel, Vector3 ov1, Vector3 rv, Vector3 norm) {

    double lam = -(ov1.x*rv.z - ov1.z*rv.x - kugel.px*rv.z + kugel.pz*rv.x)/(norm.z*rv.x - norm.x*rv.z);

    //    double lam2 = -(norm.z*ov1.x - norm.x*ov1.z - norm.z*kugel.px + norm.x*kugel.pz)/(norm.z*rv.x - norm.x*rv.z);

    // Lotschnittpunkt
    Vector3 lot_s = Vector3((kugel.px + lam * norm.x), 0, (kugel.pz + lam * norm.z));
    //    lot_s = Vector3((ov1.x + lam2 * rv.x), 0, (ov1.z + lam2 * rv.z));

    return lot_s;


}
Vector3 OGLWidget::KollisionmitWand(Kugel kugel, Vector3 ov1, Vector3 ov2) {


    Vector3 rv = Vector3(ov2.x - ov1.x,0,ov2.z-ov1.z);

    // Normalvektor
    Vector3 norm = Vector3(-rv.z,0,rv.x);

    Vector3 lot_s = Lotschnittpunkt(kugel, ov1, rv, norm);

    // Zwischenrechnung
    double lpx = pow(kugel.px-lot_s.x,2);
    double lpz = pow(kugel.pz-lot_s.z,2);

    // Abstand zwischen p und Lotschnittpunkt
    double abstand_lot = sqrt(lpx + lpz);

    // Richtung des Lotvektors
    double lotrichtung = (lot_s.x-kugel.px)*kugel.dx + (lot_s.z-kugel.pz)* kugel.dz;

    if ( ((lot_s.x >= ov1.x) && (lot_s.x < ov2.x)) ||
         ((lot_s.x <= ov1.x) && (lot_s.x > ov2.x)) ||
         ((lot_s.z >= ov1.z) && (lot_s.z < ov2.z)) ||
         ((lot_s.z <= ov1.z) && (lot_s.z > ov2.z)) )
    {
        // Wenn der Kugelrand gegen den Lotpunkt kommt
        if (abstand_lot<=kugel.rad && lotrichtung > 0) {
            // Zwischenrechnung
            double powx = pow(norm.x,2);
            double powz = pow(norm.z,2);
            double bruch = 2/(powx+powz);

            // Zwischenspeichern der alten dx und dz-Werte
            double dx_t = kugel.dx;
            double dz_t = kugel.dz;

            // Berechnung der neuen Werte
            kugel.dx = ((1-bruch*powx)*dx_t+(0-(bruch*norm.x*norm.z))*dz_t);
            kugel.dz = ((0-bruch*norm.x*norm.z)*dx_t+(1-bruch*powz)*dz_t);
        }
    } else if ( ((lot_s.x <= ov1.x) && (lot_s.x+kugel.rad >= ov1.x)) ||
                ((lot_s.x >= ov1.x) && (lot_s.x-kugel.rad <= ov1.x)) ||
                ((lot_s.x <= ov2.x) && (lot_s.x+kugel.rad >= ov2.x)) ||
                ((lot_s.x >= ov2.x) && (lot_s.x-kugel.rad <= ov2.x)) ||

                ((lot_s.z <= ov1.z) && (lot_s.z+kugel.rad >= ov1.z)) ||
                ((lot_s.z >= ov1.z) && (lot_s.z-kugel.rad <= ov1.z)) ||
                ((lot_s.z <= ov2.z) && (lot_s.z+kugel.rad >= ov2.z)) ||
                ((lot_s.z >= ov2.z) && (lot_s.z-kugel.rad <= ov2.z))) {

        norm = Vector3(kugel.px-ov2.x,0,kugel.pz-ov2.z);

        double abstand_k_e = Vector3(kugel.px,0,kugel.pz).getDistanceTo(Vector3(ov2.x,0,ov2.z));

        // Wenn der Kugelrand gegen den Lotpunkt kommt
        if (abstand_k_e<=kugel.rad && lotrichtung > 0) {


            // Zwischenrechnung
            double powx = pow(norm.x,2);
            double powz = pow(norm.z,2);
            double bruch = 2/(powx+powz);

            // Zwischenspeichern der alten dx und dz-Werte
            double dx_t = kugel.dx;
            double dz_t = kugel.dz;

            // Berechnung der neuen Werte
            kugel.dx = ((1-bruch*powx)*dx_t+(0-(bruch*norm.x*norm.z))*dz_t);
            kugel.dz = ((0-bruch*norm.x*norm.z)*dx_t+(1-bruch*powz)*dz_t);

        }
    }

    return Vector3 (kugel.dx, 0, kugel.dz );
}




Vector3 OGLWidget::Eckenbeschleunigung(Kugel kugel, Vector3 ov) {

    Vector3 rv = Vector3(ov.x - kugel.px, 0, ov.z - kugel.pz);

    if (rv.getLength() <= 2) {

        kugel.dx += -4*rv.x * dt;
        kugel.dz += -4*rv.z * dt;
    }

    return Vector3 (kugel.dx, 0, kugel.dz);
}




Vector4 OGLWidget::CheckKollisionKugel(Kugel eins, Kugel zwei)
{


    // Kollision mit anderer Kugel

    // Geschwindigkeitsvektoren
    Vector3 geschw1 = Vector3(eins.dx, 0, eins.dz);
    Vector3 geschw2 = Vector3(zwei.dx, 0, zwei.dz);

    //Normalvektor der Ebene
    Vector3 norm = Vector3(eins.px-zwei.px, 0, eins.pz-zwei.pz);
    //Normalvektor der Ebene
    Vector3 norm2 = Vector3(zwei.px-eins.px, 0, zwei.pz-eins.pz);


    // Normalvektor normieren
    norm.normalize();
    norm2.normalize();

    double zw1 = pow(eins.px+-zwei.px,2);
    double zw2 = pow(eins.pz+-zwei.pz,2);
    double diff_y = zw1+zw2;

    double diff_rad = pow(eins.rad - zwei.rad,2);

    double diff = sqrt(diff_y + diff_rad);

    double radien = eins.rad + zwei.rad;

    // Wenn Kugeln sich aufeinander zubewegen
    if ((diff < 1.01*radien) && Vector3(zwei.px-eins.px, 0, zwei.pz-eins.pz).dot(Vector3(geschw1.x-geschw2.x, 0, geschw1.z-geschw2.z)) > 0) {

        // Berechnung der Massen und ds (in den Formeln vs)
        double gesamtmasse = eins.masse+zwei.masse;
        double dsx = (eins.dx*eins.masse + zwei.dx*zwei.masse) / gesamtmasse;
        double dsz = (eins.dz*eins.masse + zwei.dz*zwei.masse) / gesamtmasse;

        // Berechnung vom neuen dx und dz
        eins.dx -= dsx;
        eins.dz -= dsz;

        zwei.dx -=dsx;
        zwei.dz -=dsz;

        double powx = pow(norm.x,2);
        double powz = pow(norm.z,2);

        double powx2 = pow(norm2.x,2);
        double powz2 = pow(norm2.z,2);

        double bruch = 2/(powx+powz);
        double bruch2 = 2/(powx2+powz2);


        // Zwischenspeichern der alten dx und dz-Werte
        double dx_t = eins.dx;
        double dz_t = eins.dz;


        double dx_t2 = zwei.dx;
        double dz_t2 = zwei.dz;

        // Berechnung der neuen Werte
        eins.dx = ((1-bruch*powx)*dx_t+(0-(bruch*norm.x*norm.z))*dz_t);
        eins.dz = ((0-bruch*norm.x*norm.z)*dx_t+(1-bruch*powz)*dz_t);

        eins.dx += dsx;
        eins.dz += dsz;

        // Berechnung der neuen Werte
        zwei.dx = ((1-bruch2*powx2)*dx_t2+(0-(bruch2*norm2.x*norm2.z))*dz_t2);
        zwei.dz = ((0-bruch2*norm2.x*norm2.z)*dx_t2+(1-bruch2*powz2)*dz_t2);

        zwei.dx += dsx;
        zwei.dz += dsz;



        return Vector4( eins.dx,eins.dz,zwei.dx,zwei.dz );
        //        return Vector3(eins.dx, 0, eins.dz);
    } else {
        return  Vector4(geschw1.x, geschw1.z, geschw2.x, geschw2.z);
    }

}

void OGLWidget::Pfeil() {


    double newpos_x;
    double newpos_z;
    double newpos_x_zeichen;
    double newpos_z_zeichen;


    int width = this->geometry().width();
    int height = this->geometry().height();

    newpos_x =  - 0.5 * width + pos_x;
    newpos_z = - 0.5 * height + pos_y;

    newpos_x_zeichen = (newpos_x*20/width - trans_lr) / (zoom/100.0);
    newpos_z_zeichen = (newpos_z*20/height + trans_ou) / (zoom/100.0);

    mdx = (kugel_1.px - newpos_x_zeichen);
    mdz = (kugel_1.pz - newpos_z_zeichen);

    //    std::cout << "mdx: "<< mdx << std::endl;
    //    std::cout << "mdz: "<< mdz << std::endl;

    float f = float(sqrt((pow(mdx,2))+(pow(mdz,2))));

    if (f > 10) f = 10;

    if (shoot) {
        glColor3f(f/10,1-f/10,0);
        glLineWidth(10);
        glBegin(GL_LINES);
        glVertex3d(kugel_1.px, kugel_1.rad, kugel_1.pz);
        glVertex3d(newpos_x_zeichen, kugel_1.rad, newpos_z_zeichen);
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

void OGLWidget::Boden(){

    glColor3d(0, 0.5, 0.5);
    glBegin(GL_QUAD_STRIP); //Begin Polygon coordinates

    double x;
    double z;


    x = points[0+Spalten*0];
    z = points[1+Spalten*0];
    glNormal3d(0,1,0);
    glVertex3d(x,0,z);

    x = points[0+Spalten*(Kanten-1)];
    z = points[1+Spalten*(Kanten-1)];
    glNormal3d(0,1,0);
    glVertex3d(x,0,z);

    for (int i = 1; i <= Kanten/2; i++) {


        x = points[0+Spalten*i];
        z = points[1+Spalten*i];
        glNormal3d(0,1,0);
        glVertex3d(x,0,z);

        x = points[0+Spalten*(Kanten-(i+1))];
        z = points[1+Spalten*(Kanten-(i+1))];
        glNormal3d(0,1,0);
        glVertex3d(x,0,z);

    }

    glEnd();
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
        kugel_1.dx = -mdx;
        kugel_1.dz = -mdz;
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
