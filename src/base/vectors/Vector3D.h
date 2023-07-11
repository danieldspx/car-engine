//
// Created by daniel on 11/07/23.
//

#ifndef CANVAS_CLION_VECTOR3D_H
#define CANVAS_CLION_VECTOR3D_H

#include <iostream>
#include <cmath>
#include <stdexcept>

template<class T>
struct Vector3D {
public:
    T x, y, z;

    Vector3D(T x, T y, T z);

    Vector3D();

    Vector3D<T> operator+(Vector3D<T> v2);

    Vector3D<T> operator-(Vector3D<T> v2);

    Vector3D<T> operator*(T v);

    Vector3D<T> operator/(T v);

    Vector3D<T> operator+=(Vector3D<T> v1);

    Vector3D<T> operator-=(Vector3D<T> v1);

    Vector3D<T> operator/=(T v);

    Vector3D<T> operator*=(T v);

    bool operator==(Vector3D<T> v);

    T &operator[](int idx);

    T distance(Vector3D<T> v1);

    T modulo();

    void print();

    T dot(Vector3D<T> v1);

    T angle(Vector3D<T> v1);

    Vector3D<T> unit();

    Vector3D<T> rotate(float angle);

    Vector2D<T> toPerspective(float distance);
};

template<class T>
Vector3D<T>::Vector3D(T x, T y, T z) : x(x), y(y), z(z) {}

template<class T>
Vector3D<T>::Vector3D() : x(0), y(0), z(0) {}

template<class T>
Vector3D<T> Vector3D<T>::operator+(Vector3D<T> v2) {
    return Vector3D<T>(x + v2.x, y + v2.y, z + v2.z);
}

template<class T>
Vector3D<T> Vector3D<T>::operator-(Vector3D<T> v2) {
    return Vector3D<T>(x - v2.x, y - v2.y, z - v2.z);
}

template<class T>
Vector3D<T> Vector3D<T>::operator*(T v) {
    return Vector3D<T>(x * v, y * v, z * v);
}

template<class T>
Vector3D<T> Vector3D<T>::operator/(T v) {
    return Vector3D<T>(x / v, y / v, z / v);
}

template<class T>
Vector3D<T> Vector3D<T>::operator+=(Vector3D<T> v1) {
    x += v1.x;
    y += v1.y;
    z += v1.z;
    return *this;
}

template<class T>
Vector3D<T> Vector3D<T>::operator-=(Vector3D<T> v1) {
    x -= v1.x;
    y -= v1.y;
    z -= v1.z;
    return *this;
}

template<class T>
Vector3D<T> Vector3D<T>::operator/=(T v) {
    x /= v;
    y /= v;
    z /= v;
    return *this;
}

template<class T>
Vector3D<T> Vector3D<T>::operator*=(T v) {
    x *= v;
    y *= v;
    z *= v;
    return *this;
}

template<class T>
bool Vector3D<T>::operator==(Vector3D<T> v) {
    return v.x == x && v.y == y && v.z == z;
}

template<class T>
T &Vector3D<T>::operator[](int idx) {
    if (idx == 0) return x;
    if (idx == 1) return y;
    if (idx == 2) return z;
    throw std::out_of_range("Index out of bounds");
}

template<class T>
T Vector3D<T>::distance(Vector3D<T> v1) {
    return sqrt(pow(x - v1.x, 2) + pow(y - v1.y, 2) + pow(z - v1.z, 2));
}

template<class T>
T Vector3D<T>::modulo() {
    return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

template<class T>
T Vector3D<T>::dot(Vector3D<T> v1) {
    return x * v1.x + y * v1.y + z * v1.z;
}

template<class T>
T Vector3D<T>::angle(Vector3D<T> v1) {
    auto dp = dot(v1);
    float cosX = dp / (modulo() * v1.modulo());
    if (cosX > 1 || cosX < -1) cosX = (int) cosX;

    return acos(cosX);
}

template<class T>
Vector3D<T> Vector3D<T>::unit() {
    return Vector3D{x / modulo(), y / modulo(), z / modulo()};
}

template<class T>
void Vector3D<T>::print() {
    std::cout << "x: " << x << " y: " << y << " z: " << z << std::endl;
}

template<class T>
Vector2D<T> Vector3D<T>::toPerspective(float distance) {
    return Vector2D<T>{x * distance / z, y * distance / z};
}

typedef Vector3D<int> ivec3;
typedef Vector3D<double> dvec3;
typedef Vector3D<float> fvec3;

#endif //CANVAS_CLION_VECTOR3D_H
