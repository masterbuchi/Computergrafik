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

    Kugel(double px, double py, double pz, double masse, double radius, int zpx, int zpz, double* points, int nr_lat = 90, int nr_lon = 90)
    {
        this->px = px;
        this->py = py;
        this->pz = pz;
        this->rad = radius;
        this->masse = masse;
        this->nr_lat = nr_lat;
        this->nr_lon = nr_lon;
        this->py = radius;
        this->points = points;
        this->zpx = zpx;
        this->zpz = zpz;

    }

     // Richtungsvektoren GESCHWINDIGKEIT
    double dx = 0;
    double dy = 0;
    double dz = 0;

    // ORT
    double px = 0.0;
    double py = 0.0;
    double pz = 0.0;

    //Daten Kugel
    double rad;
    double masse;
    int nr_lat;
    int nr_lon;

    //Allgemeine Daten

   //Farben rgb
    float cr,cg,cb;

    int Punkte;

    double* points;

    int Zeilen = 6.0;
            int Spalten = 2;


    double* ziele=new double[Zeilen*Spalten]
    {
            -10,0,
            -11,20,
            -10,40,
            10,40,
            11,20,
            10,0

};


    //Ziel
    int zpx;
    int zpz;
    boolean win = false;


    double dt;

    double PI = 3.1415;
    float PIf = 3.1414f;

    int update(double dt, int Punkte,float cr, float cg, float cb);

    void Ende();
    void Zeichnen();
};

#endif // KUGEL_H
