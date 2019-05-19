#include "kugel.h"
#include "vec3.hpp"
#include <cmath>
#include <iostream>
#include "oglwidget.h"



void Kugel::update(Kugel other, double rotx, double rotz, double dt) {

    ax = -sin((rotz*PI/180));
    az = -sin((rotx*PI/180));

    dx += ax*dt;
    dx *= 0.99;
    dz += az*dt;
    dz *= 0.99;

    for (int i=0; i<Ecken; i++)

    {
        Kollision(i);

    }



    //    // ANDERE KUGEL
    //    if (checkCollision(other)) {
    //        std::cout << "collision" << std::endl;

    //        Vector3 pos = Vector3(px, 0, pz);
    //        Vector3 other_pos = Vector3(other.px, 0, other.pz);
    //        Vector3 velocity = Vector3(vx, 0, vz);
    //        Vector3 other_velocity = Vector3(other.vx, 0, other.vz);

    //        Vector3 collisionNormal = Vector3(px-other.px, 0, pz-other.pz);
    //        collisionNormal.normalize(); // normalvector der kollisionsebene

    //        // bewegen sich die kugeln aufeinander zu dann löse kollision auf
    //        if (Vector3(other.px-px, 0, other.pz-pz).dotProduct(Vector3(velocity.x-other_velocity.x, 0, velocity.z-other_velocity.z)) > 0) {

    //            double totalmass = mass+other.mass;
    //            double vsx = (vx*mass + other.vx*other.mass) / totalmass;
    //            double vsz = (vz*mass + other.vz*other.mass) / totalmass;

    //            vx -= vsx; vz -= vsz;
    //            other.vx -= vsx; other.vz -= vsz;

    //            double tempvx=vx;
    //            double tempvz=vz;

    //            vx=vx-((((collisionNormal.x*collisionNormal.x)*tempvx)+(collisionNormal.z*tempvz*collisionNormal.x))/((collisionNormal.x*collisionNormal.x)+(collisionNormal.z*collisionNormal.z)));
    //            vz=vz-((((collisionNormal.z*collisionNormal.z)*tempvz)+(collisionNormal.z*tempvx*collisionNormal.x))/((collisionNormal.x*collisionNormal.x)+(collisionNormal.z*collisionNormal.z)));

    //            vx += vsx; vz += vsz;
    //            other.vx += vsx; other.vz += vsz;

    //        }
    //    }



    // Neuer Punkt wird bestimmt
    px += dx*dt;
    pz += dz*dt;

    zeichnen();
}

//  //Returns true if the circles are touching, or false if they are not

//bool Kugel::checkCollision(Kugel other)
//{
//    double dx = other.px - px+vx;
//    double dy = other.pz - pz+vz;
//    double radii = radius + other.radius;
//    return ((dx*dx)+(dy*dy)<radii*radii) ? true : false;
//}



//void Kugel::Schnittpunkt(int i) {

//    // Berechnung der Lamdas des Schnittpunkt
//    double lam = -(px + s*sin(i*rot_rad) - (dx*(pz - s*cos(i*rot_rad)))/dz)/(s*(sin(rot_rad*(i + 1)) - sin(i*rot_rad)) - (dx*s*(cos(i*rot_rad) - cos(rot_rad*(i + 1))))/dz);
//    double lam2 = -(pz - s*cos(i*rot_rad) + lam*s*(cos(i*rot_rad) - cos(rot_rad*(i + 1))))/dz;

//    // Schnittpunkt
//    sx = px + lam2  * dx;
//    sz = pz + lam2 * dz;


//}

void Kugel::Lotschnittpunkt(int i) {

    // s * -sin(i*rot_rad) + lam * s * (-sin((i+1)*rot_rad) + sin( i * rot_rad)) = px + lam2 * -(s * (cos((i+1)*rot_rad) - cos( i * rot_rad)));
    // double lam2 = ((s * cos(i*rot_rad) + lam * s * (cos((i+1)*rot_rad) - cos( i * rot_rad))) - pz)  / (s * (-sin((i+1)*rot_rad) + sin( i * rot_rad))) ;

    double lam = -(s - pz*cos(i*rot_rad) + px*sin(i*rot_rad) - s*cos(rot_rad) + pz*cos(rot_rad*(i + 1)) - px*sin(rot_rad*(i + 1)))/(2*s*(cos(rot_rad) - 1));
    double lam2 = (pz - s*cos(i*rot_rad) + lam*s*(cos(i*rot_rad) - cos(rot_rad*(i + 1))))/(s*(sin(rot_rad*(i + 1)) - sin(i*rot_rad)));


    // Schnittpunkt
    lot_sx = px + lam2 * -s * (cos((i+1)*rot_rad) - cos( i * rot_rad));
    lot_sz = pz + lam2 * s * (-sin((i+1)*rot_rad) + sin( i * rot_rad));


}
void Kugel::Kollision(int i) {


    // NormalvektorKoordinaten
    double normx = -s * (cos((i+1)*rot_rad) - cos( i * rot_rad));
    double normz = s * (-sin((i+1)*rot_rad) + sin( i * rot_rad));


    //    Schnittpunkt(i);

    Lotschnittpunkt(i);

    //    // Zwischenrechnung
    //    double x_2 = pow((px-sx),2);
    //    double z_2 = pow((pz-sz),2);

    //    // Berechnung des Abstands zwischen Kreismittelpunkt und Schnittpunkt mit der jeweiligen Geraden
    //    double abstand = sqrt(x_2 + z_2);

    double lpx = pow(px-lot_sx,2);
    double lpz = pow(pz-lot_sz,2);

    double abstand_lot = sqrt(lpx + lpz);

    double lotrichtung = (lot_sx-px)*dx + (lot_sz-pz)* dz;

    // Wenn der Kugelrand gegen den Lotpunkt kommt
    if (abstand_lot<radius && lotrichtung > 0) {

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

glPushMatrix();
    glTranslated(px,0,pz);
    glColor3f( 1.0f, 1.0f, 0.0f );

    // Angle delta in both directions
    const double lat_delta = PI / nr_lat;
    const double lon_delta = PI /  nr_lon;

    // Create horizontal stripes of squares
    for( double lon = 0.0; lon < 1.0*PI; lon += lon_delta )
    {
        glBegin( GL_QUAD_STRIP ) ;
        for( double lat = 0.0; lat <= 2.0*PI; lat += lat_delta )
        {
            // Each iteration adds another square, the other vertices
            // are taken from the existing stripe
            double xn1 = cos( lat ) * sin( lon );
            double yn1 = sin( lat ) * sin( lon );
            double zn1 = cos( lon );

            // Set normal vector (important for lighting!)
            glNormal3d( xn1, yn1, zn1 );

            // Nächster Punkt
            glVertex3d( px+radius*xn1, py+radius*yn1, pz+radius*zn1 );

            double xn2 = cos( lat ) * sin( lon + lon_delta );
            double yn2 = sin( lat ) * sin( lon + lon_delta );
            double zn2 = cos( lon + lon_delta );

            // normalvektor
            glNormal3d( xn2, yn2, zn2 );

            // Nächster Punkt
            glVertex3d( px+radius*xn2, py+radius*yn2, pz+radius*zn2 );
        }
        glEnd() ;
    }
glPopMatrix();


}
