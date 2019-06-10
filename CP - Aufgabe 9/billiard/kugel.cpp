#include "kugel.h"
#include "vector3.h"
#include <cmath>
#include <iostream>
#include "oglwidget.h"



int Kugel::update(double dt, int Punkte, float cr, float cg, float cb) {

    this-> dt = dt;
    this->Punkte = Punkte;
    this->cr = cr;
    this->cg = cg;
    this->cb = cb;



//    dx *= 0.99;
//    dz *= 0.99;

    // Neuer Punkt wird bestimmt
    px += dx*dt;
    pz += dz*dt;

    Ende();

    Zeichnen();

    return this->Punkte;


}


void Kugel::Ende() {


    for (int i = 0; i < Zeilen; i++ ) {
        double abstandZiel = Vector3(px,0,pz).getDistanceTo(Vector3(ziele[0+Spalten*i],0,ziele[1+Spalten*i]));

        if ( abstandZiel < 1) {
            dx *= 0.7;
            dz *= 0.7;

            if (abs(dx) <= 0.0001 && abs(dz) <= 0.0001) {
                dx = 0;
                dz = 0;

                if (cr+cg+cb == 3) {
                    px = 0;
                    pz = 10;
                } else {

                    if (!win) {
                        Punkte += 10;
                        std::cout << "Sehr gut! "<< std::endl;
                        std::cout << " "<< std::endl;
                        std::cout << "Punkte: " << Punkte << std::endl;
                        win = true;
                    }
                }

            }


        }


    }



}


void Kugel::Zeichnen()
{
    glColor3f( cr, cg, cb );

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
