#include "kugel.h"
#include "vector3.h"
#include <cmath>
#include <iostream>
#include "oglwidget.h"



void Kugel::update(double rotx, double rotz, double dt, int Versuche) {

    this -> rotx = rotx;
    this -> rotz = rotz;
    this-> dt = dt;
    this->Versuche = Versuche;

//    ax = -sin((rotz*PI/180));
//    az = -sin((rotx*PI/180));


//    glPushMatrix();

    Ende();


    // Neuer Punkt wird bestimmt
    px += dx*dt;
    pz += dz*dt;

    Zeichnen();

    //    dx += ax*dt;
    dx *= 0.99;
    //    dz += az*dt;
    dz *= 0.99;



//    glPopMatrix();


}


void Kugel::Ende() {

    double abstandZiel = Vector3(px,0,pz).getDistanceTo(Vector3(zpx,0,zpz));

    if ( abstandZiel < 0.2) {
        dx = 0;
        dz = 0;
        if (!win) {

            std::cout << "Gewonnen! "<< std::endl;
            std::cout << " "<< std::endl;
            std::cout << "Anzahl der Versuche: " << Versuche << std::endl;
            win = true;
        }
    }
}




void Kugel::Zeichnen()
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
    }
    glEnd() ;
}




//void Kugel::Lotschnittpunkt() {

//    double lam = -(ov.x*rv.z - ov.z*rv.x - px*rv.z + pz*rv.x)/(norm.z*rv.x - norm.x*rv.z);

//    double lam2 = -(norm.z*ov.x - norm.x*ov.z - norm.z*px + norm.x*pz)/(norm.z*rv.x - norm.x*rv.z);

//    // Lotschnittpunkt
//    lot_s = Vector3((px + lam * norm.x), 0, (pz + lam * norm.z));
//    lot_s = Vector3((ov.x + lam2 * rv.x), 0, (ov.z + lam2 * rv.z));


//}
//void Kugel::KollisionmitWand(int i) {


//    ov = Vector3(points[0+Spalten*i],0,points[1+Spalten*i]);
//    ov2 = Vector3(points[0+Spalten*((i+1) % (Kanten))],0,points[1+Spalten*((i+1) % (Kanten))]);
//    rv = Vector3(ov2.x - ov.x,0,ov2.z-ov.z);

//    // Normalvektor
//    norm = Vector3(-rv.z,0,rv.x);

//    Lotschnittpunkt();

//    // Zwischenrechnung
//    double lpx = pow(px-lot_s.x,2);
//    double lpz = pow(pz-lot_s.z,2);

//    // Abstand zwischen p und Lotschnittpunkt
//    double abstand_lot = sqrt(lpx + lpz);

//    // Richtung des Lotvektors
//    double lotrichtung = (lot_s.x-px)*dx + (lot_s.z-pz)* dz;

//    if ( ((lot_s.x >= ov.x) && (lot_s.x < ov2.x)) ||
//         ((lot_s.x <= ov.x) && (lot_s.x > ov2.x)) ||
//         ((lot_s.z >= ov.z) && (lot_s.z < ov2.z)) ||
//         ((lot_s.z <= ov.z) && (lot_s.z > ov2.z)) )
//    {
//        // Wenn der Kugelrand gegen den Lotpunkt kommt
//        if (abstand_lot<=rad && lotrichtung > 0) {
//            // Zwischenrechnung
//            double powx = pow(norm.x,2);
//            double powz = pow(norm.z,2);
//            double bruch = 2/(powx+powz);

//            // Zwischenspeichern der alten dx und dz-Werte
//            double dx_t = dx;
//            double dz_t = dz;

//            // Berechnung der neuen Werte
//            dx = ((1-bruch*powx)*dx_t+(0-(bruch*norm.x*norm.z))*dz_t);
//            dz = ((0-bruch*norm.x*norm.z)*dx_t+(1-bruch*powz)*dz_t);
//        }
//    } else if ( ((lot_s.x <= ov.x) && (lot_s.x+rad >= ov.x)) ||
//                ((lot_s.x >= ov.x) && (lot_s.x-rad <= ov.x)) ||
//                ((lot_s.x <= ov2.x) && (lot_s.x+rad >= ov2.x)) ||
//                ((lot_s.x >= ov2.x) && (lot_s.x-rad <= ov2.x)) ||

//                ((lot_s.z <= ov.z) && (lot_s.z+rad >= ov.z)) ||
//                ((lot_s.z >= ov.z) && (lot_s.z-rad <= ov.z)) ||
//                ((lot_s.z <= ov2.z) && (lot_s.z+rad >= ov2.z)) ||
//                ((lot_s.z >= ov2.z) && (lot_s.z-rad <= ov2.z))) {

//        norm = Vector3(px-ov2.x,0,pz-ov2.z);

//        double abstand_k_e = Vector3(px,0,pz).getDistanceTo(Vector3(ov2.x,0,ov2.z));

//        // Wenn der Kugelrand gegen den Lotpunkt kommt
//        if (abstand_k_e<=rad && lotrichtung > 0) {


//            // Zwischenrechnung
//            double powx = pow(norm.x,2);
//            double powz = pow(norm.z,2);
//            double bruch = 2/(powx+powz);

//            // Zwischenspeichern der alten dx und dz-Werte
//            double dx_t = dx;
//            double dz_t = dz;

//            // Berechnung der neuen Werte
//            dx = ((1-bruch*powx)*dx_t+(0-(bruch*norm.x*norm.z))*dz_t);
//            dz = ((0-bruch*norm.x*norm.z)*dx_t+(1-bruch*powz)*dz_t);

//        }
//    }
//}

