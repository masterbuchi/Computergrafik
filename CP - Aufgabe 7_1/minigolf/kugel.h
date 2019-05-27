#ifndef KUGEL_H
#define KUGEL_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMouseEvent>
#include <QTimer>
#include <QVector3D>
#include <vector3.h>

class Kugel
{
public:

    Kugel(double px, double py, double pz, double masse, double radius, int Kanten, int Spalten, int zpx, int zpz, int* points, int nr_lat = 90, int nr_lon = 90)
    {

        this->px = px;
        this->py = py;
        this->pz = pz;
        this->rad = radius;
        this->masse = masse;
        this->nr_lat = nr_lat;
        this->nr_lon = nr_lon;
        this->Kanten = Kanten;
        this->py = radius;
        this->points = points;
        this->Spalten = Spalten;
        this->zpx = zpx;
        this->zpz = zpz;
        this->Versuche = Versuche;

    }

     // Richtungsvektoren GESCHWINDIGKEIT
    double dx = 0;
    double dy = 0;
    double dz = 0;

    // ORT
    double px = 0.0;
    double py = 0.0;
    double pz = 0.0;

    Vector3 ov = Vector3(0,0,0);
    Vector3 ov2 = Vector3(0,0,0);
    Vector3 rv = Vector3(0,0,0);
    Vector3 norm = Vector3(0,0,0);
    Vector3 lot_s = Vector3(0,0,0);

    //Daten Kugel
    double rad;
    double masse;
    int nr_lat;
    int nr_lon;

    //Allgemeine Daten

    int Kanten;
    int Spalten;
    int Versuche;

    int* points;


    //Ziel
    int zpx;
    int zpz;
    boolean win = false;

    // BESCHLEUNIGUNG
    double ax;
    double az;

    double rotx;
    double rotz;
    double dt;

    double PI = 3.1415;
    float PIf = 3.1414f;

    void update(Kugel other, double rotx, double rotz, double dt, int Versuche);


    void CheckKollisionKugel(Kugel other);


    void Ende();
    void Zeichnen();
    void Lotschnittpunkt();
    void KollisionmitKugel(Kugel);
    void KollisionmitWand(int i);
};

#endif // KUGEL_H
