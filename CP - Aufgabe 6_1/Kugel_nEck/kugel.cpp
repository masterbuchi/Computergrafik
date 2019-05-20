#include "kugel.h"
#include "vector3.h"
#include <cmath>
#include <iostream>
#include "oglwidget.h"



void Kugel::update(Kugel other, double rotx, double rotz, double dt) {



    this -> rotx = rotx;
    this -> rotz = rotz;
    this-> dt = dt;


    ax = -sin((rotz*PI/180));
    az = -sin((rotx*PI/180));


    glPushMatrix();

    for (int i=0; i<Ecken; i++)

    {
        Kollision(i);

    }


    // Neuer Punkt wird bestimmt
    px += dx*dt;
    pz += dz*dt;

    // AB HIER WIRD MIT DER VEKTORKLASSE GEARBEITET, WEIL DAS OHNE ECHT NICHT GEHT.

    // Kollision mit anderer Kugel

    // Geschwindigkeitsvektoren
    Vector3 geschw = Vector3(dx, 0, dz);
    Vector3 geschw_other = Vector3(other.dx, 0, other.dz);

    //Normalvektor der Ebene
    Vector3 norm = Vector3(px-other.px, 0, pz-other.pz);

    // Normalvektor normieren
    norm.normalize();

    // Wenn Kugeln sich aufeinander zubewegen

    if (Vector3(other.px-px, 0, other.pz-pz).dot(Vector3(geschw.x-geschw_other.x, 0, geschw.z-geschw_other.z)) > 0 && CheckKollisionKugel(other)) {

        // Berechnung der Massen und ds (in den Formeln vs)
        double gesamtmasse = masse+other.masse;
        double dsx = (dx*masse + other.dx*other.masse) / gesamtmasse;
        double dsz = (dz*masse + other.dz*other.masse) / gesamtmasse;

        // Berechnung vom neuen dx und dz
        dx -= dsx;
        dz -= dsz;

        other.dx -= dsx;
        other.dz -= dsz;

        double powx = pow(norm.x,2);
        double powz = pow(norm.z,2);

        double bruch = 2/(powx+powz);

        // Zwischenspeichern der alten dx und dz-Werte
        double dx_t = dx;
        double dz_t = dz;

        // Berechnung der neuen Werte
        dx = ((1-bruch*powx)*dx_t+(0-(bruch*norm.x*norm.z))*dz_t);
        dz = ((0-bruch*norm.x*norm.z)*dx_t+(1-bruch*powz)*dz_t);

        dx += dsx;
        dz += dsz;

        other.dx += dsx;
        other.dz += dsz;



    }


    zeichnen();



    dx += ax*dt;
    dx *= 0.99;
    dz += az*dt;
    dz *= 0.99;


    glPopMatrix();


}


bool Kugel::CheckKollisionKugel(Kugel other)
{

    //
    double zw1 = pow(px+-other.px,2);
    double zw2 = pow(pz+-other.pz,2);
    double diff_y = zw1+zw2;

    double diff_rad = pow(rad - other.rad,2);

    double diff = sqrt(diff_y + diff_rad);


    double radien = rad + other.rad;
    if (diff < 1.01*radien) {
        return true;
    }else {
        return false;
    }

}


void Kugel::Lotschnittpunkt(int i) {

    // s * -sin(i*rot_rad) + lam * s * (-sin((i+1)*rot_rad) + sin( i * rot_rad)) = px + lam2 * -(s * (cos((i+1)*rot_rad) - cos( i * rot_rad)));
    // double lam2 = ((s * cos(i*rot_rad) + lam * s * (cos((i+1)*rot_rad) - cos( i * rot_rad))) - pz)  / (s * (-sin((i+1)*rot_rad) + sin( i * rot_rad))) ;

    double lam = -(s - pz*cos(i*rot_rad) + px*sin(i*rot_rad) - s*cos(rot_rad) + pz*cos(rot_rad*(i + 1)) - px*sin(rot_rad*(i + 1)))/(2*s*(cos(rot_rad) - 1));
    double lam2 = (pz - s*cos(i*rot_rad) + lam*s*(cos(i*rot_rad) - cos(rot_rad*(i + 1))))/(s*(sin(rot_rad*(i + 1)) - sin(i*rot_rad)));


    // Lotschnittpunkt
    lot_sx = px + lam2 * -s * (cos((i+1)*rot_rad) - cos( i * rot_rad));
    lot_sz = pz + lam2 * s * (-sin((i+1)*rot_rad) + sin( i * rot_rad));


}
void Kugel::Kollision(int i) {


    // NormalvektorKoordinaten
    double normx = -s * (cos((i+1)*rot_rad) - cos( i * rot_rad));
    double normz = s * (-sin((i+1)*rot_rad) + sin( i * rot_rad));

    Lotschnittpunkt(i);

    // Zwischenrechnung
    double lpx = pow(px-lot_sx,2);
    double lpz = pow(pz-lot_sz,2);

    // Abstand zwischen p und Lotschnittpunkt
    double abstand_lot = sqrt(lpx + lpz);

    // Richtung des Lotvektors
    double lotrichtung = (lot_sx-px)*dx + (lot_sz-pz)* dz;


    // Wenn der Kugelrand gegen den Lotpunkt kommt
    if (abstand_lot<rad && lotrichtung > 0) {


        // Zwischenrechnung
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

void Kugel::zeichnen()
{
    glColor3f( 1.0f, 1.0f, 0.0f );

    // Angle delta in both directions
    const float lat_delta = PIf / float( nr_lat );
    const float lon_delta = PIf / float( nr_lon );

    // Create horizontal stripes of squares
    for( float lon = 0.0f; lon < 1.0f*PIf; lon += lon_delta )
    {
        glBegin( GL_QUAD_STRIP ) ;
        for( float lat = 0.0f; lat <= 2.0f*PIf; lat += lat_delta )
        {
            // Each iteration adds another square, the other vertices
            // are taken from the existing stripe
            float xn1 = cosf( lat ) * sinf( lon );
            float yn1 = sinf( lat ) * sinf( lon );
            float zn1 = cosf( lon );

            // Set normal vector (important for lighting!)
            glNormal3f( xn1, yn1, zn1 );

            // Nächster Punkt
            glVertex3f( float(px)+float(rad)*xn1, float(py)+float(rad)*yn1, float(pz)+float(rad)*zn1 );

            float xn2 = cosf( lat ) * sinf( lon + lon_delta );
            float yn2 = sinf( lat ) * sinf( lon + lon_delta );
            float zn2 = cosf( lon + lon_delta );

            // normalvektor
            glNormal3f( xn2, yn2, zn2 );

            // Nächster Punkt
            glVertex3f( float(px)+float(rad)*xn2, float(py)+float(rad)*yn2, float(pz)+float(rad)*zn2 );
        }
        glEnd() ;
    }
}




