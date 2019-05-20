#ifndef VECTOR3_H
#define VECTOR3_H


class Vector3
{
public:
    Vector3(double x, double y, double z);
    double x, y, z;

    void normalize();
    double getLength();
    double getDistanceTo(Vector3 other);

    double dot(Vector3 other);

    Vector3 crossProduct(Vector3 b);




    Vector3 operator *(const double& i);
    Vector3 operator +(const Vector3 &other);
    void divideAllElementsBy(double i);
};

#endif // VECTOR3_H
