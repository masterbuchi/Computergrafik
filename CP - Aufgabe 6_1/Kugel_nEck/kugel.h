#ifndef KUGEL_H
#define KUGEL_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMouseEvent>
#include <QTimer>
#include <QVector3D>

class Kugel
{
public:

    Kugel(double px, double py, double pz, double masse, double radius, int Ecken, double rot_rad, int s, int nr_lat = 90, int nr_lon = 90)
    {

        this->px = px;
        this->py = py;
        this->pz = pz;
        this->rad = radius;
        this->masse = masse;
        this->nr_lat = nr_lat;
        this->nr_lon = nr_lon;
        this->Ecken = Ecken;
        this->rot_rad = rot_rad;
        this->s = s;

        this->py = radius;


        //        this->initpx = px;
        //        this->initpy = py;
        //        this->initpz = pz;
    }

    //    void reset() {
    //        this->px = initpx;
    //        this->py = initpy;
    //        this->pz = initpz;
    //    }




    //    bool isCollidingX, isCollidingZ;

    // Richtungsvektoren GESCHWINDIGKEIT
    double dx = 0;
    double dy = 0;
    double dz = 0;

    // ORT
    double px = 0.0;
    double py = 0.0;
    double pz = 0.0;

    //    // Ursprungsort
    //    double initpx, initpy, initpz;

    //Daten Kugel
    double rad;
    double masse;
    int nr_lat;
    int nr_lon;

    //Allgemeine Daten

    int Ecken;
    double rot_rad;
    int s;

    // BESCHLEUNIGUNG
    double ax;
    double az;

    double rotx;
    double rotz;
    double dt;


    //    // Schnittpunkt Koordinaten
    //    double sx;
    //    double sz;

    //Lotschnittpunkt Koordinaten
    double lot_sx;
    double lot_sz;

    double PI = 3.1415;
    float PIf = 3.1414f;

    void update(Kugel other, double rotx, double rotz, double dt);


    bool CheckKollisionKugel(Kugel other);


    void zeichnen();
    //    void Schnittpunkt(int i);
    void Lotschnittpunkt(int i);
    void Kollision(int i);
};

#endif // KUGEL_H
