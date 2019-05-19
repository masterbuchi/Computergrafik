#ifndef KUGEL_H
#define KUGEL_H

#include <QOpenGLFunctions>


class Kugel
{
public:
    Kugel(int px, int py, int pz, double radius, double mass, int dz) {
        this->initpx = px;
        this->initpy = py;
        this->initpz = pz;
        this->px = px;
        this->py = py;
        this->pz = pz;
        this->radius = radius;
        this->mass = mass;
        this->dz = dz;
        this->vz = dz*0.06;
    }
    void reset() {
        this->px = initpx;
        this->py = initpy;
        this->pz = initpz;
        this->vz = dz*0.06;
    }
    void render();

    double initpx, initpy, initpz;
    double radius;
    double mass;
    double friction = 0.005;
    bool isCollidingX, isCollidingZ;
    double vx, vz = 0;
    double px=0.0;
    int dx=0;
    double py=0.0;
    int dy=0;
    double pz=0.0;
    int dz=0;

    void update(double dt, Kugel other);
    bool checkCollision(Kugel other);
};

#endif // KUGEL_H
