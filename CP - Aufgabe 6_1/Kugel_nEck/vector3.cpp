#include "vector3.h"
#include <tgmath.h>
#include <iostream>
Vector3::Vector3(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector3 Vector3::crossProduct(Vector3 b) {

    double retX = y * b.z - z * b.y;
    double retY = z * b.x - x * b.z;
    double retZ = x * b.y - y * b.x;

    return Vector3(retX, retY, retZ);
}

double Vector3::getLength() {
    return std::sqrt((x*x) + (y*y) + (z*z));
}

Vector3 Vector3::operator*(const double& i)
{
    x *= i;
    y *= i;
    z *= i;

    return *this;
}

Vector3 Vector3::operator+(const Vector3& other) {
    x += other.x;
    y += other.y;
    z += other.z;

    return *this;
}

void Vector3::divideAllElementsBy(double i) {
    x /= i;
    y /= i;
    z /= i;
}

double Vector3::getDistanceTo(Vector3 other) {
    return sqrt(pow(this->x - other.x,2) + pow(this->y - other.y,2)+ pow(this->z - other.z,2));
}

void Vector3::normalize() {
    this->x = x/this->getLength();
    this->y = y/this->getLength();
    this->z = z/this->getLength();
}
double Vector3::dot(Vector3 other) {

    double sum = 0;
    sum += x * other.x;
    sum += y * other.y;
    sum += z * other.z;
    return sum;
}
