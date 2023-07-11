//
// Created by daniel on 11/07/23.
//

#ifndef CANVAS_CLION_VECTOR4D_H
#define CANVAS_CLION_VECTOR4D_H

#include <cmath>
#include <stdexcept>
#include <iostream>
#include "Matrix.h"

template<class t>
struct Vector4D {
public:
    t x, y, z, w;

    Vector4D(t x, t y, t z, t w);

    Vector4D();

    Vector4D(Matrix<t> v);

    Vector4D<t> operator+(Vector4D<t> v2) const;

    Vector4D<t> operator-(const Vector4D<t> v2) const;

    Vector4D<t> operator-() const;

    Vector4D<t> operator*(t v) const;

    Vector4D<t> operator/(t v) const;

    Vector4D<t> operator+=(const Vector4D<t> v1);

    Vector4D<t> operator-=(const Vector4D<t> v1);

    Vector4D<t> operator/=(const t v);

    Vector4D<t> operator*=(const t v);

    t &operator[](int idx);

    bool operator==(const Vector4D &rhs) const;

    bool operator!=(const Vector4D &rhs) const;

    void print();

    t modulo();

    Vector4D<t> unit();

    Matrix<t> toMatrix() const;
};

template<class t>
Vector4D<t>::Vector4D(t x, t y, t z, t w) : x(x), y(y), z(z), w(w) {

}

template<class t>
Vector4D<t>::Vector4D() : x(0), y(0), z(0), w(0) {

}

template<class t>
Vector4D<t> Vector4D<t>::operator+(const Vector4D<t> v2) const {
    return Vector4D<t>(x + v2.x, y + v2.y, z + v2.z, w + v2.w);
}

template<class t>
Vector4D<t> Vector4D<t>::operator-(const Vector4D<t> v2) const {
    return Vector4D<t>(x - v2.x, y - v2.y, z - v2.z, w - v2.w);
}

template<class t>
Vector4D<t> Vector4D<t>::operator*(const t v) const {
    return Vector4D<t>(x * v, y * v, z * v, w * v);
}

template<class t>
Vector4D<t> Vector4D<t>::operator/(const t v) const {
    return Vector4D<t>(x / v, y / v, z / v, w / v);
}

template<class t>
Vector4D<t> Vector4D<t>::operator+=(Vector4D<t> v1) {
    x += v1.x;
    y += v1.y;
    z += v1.z;
    w += v1.w;
}

template<class t>
Vector4D<t> Vector4D<t>::operator-=(Vector4D<t> v1) {
    x -= v1.x;
    y -= v1.y;
    z -= v1.z;
    w -= v1.w;
}

template<class t>
Vector4D<t> Vector4D<t>::operator/=(t v) {
    x /= v;
    y /= v;
    z /= v;
    w /= v;
}

template<class t>
Vector4D<t> Vector4D<t>::operator*=(t v) {
    x *= v;
    y *= v;
    z *= v;
    w *= v;
}

template<class t>
t Vector4D<t>::modulo() {
    return std::sqrt(x * x + y * y + z * z + w * w);
}

template<class t>
Vector4D<t> Vector4D<t>::unit() {
    t l = modulo();
    return Vector4D<t>(x / l, y / l, z / l, w / l);
}

template<class t>
t &Vector4D<t>::operator[](int idx) {
    if (idx == 0) return x;
    if (idx == 1) return y;
    if (idx == 2) return z;
    if (idx == 3) return w;
    else
        throw std::out_of_range("Index out of bounds");
}

template<class t>
Vector4D<t> Vector4D<t>::operator-() const {
    return Vector4D<t>(-x, -y, -z, -w);
}

template<class t>
void Vector4D<t>::print() {
    std::cout << "x: " << x << " y: " << y << " z: " << z << " w: " << w << std::endl;
}

template<class t>
bool Vector4D<t>::operator==(const Vector4D &rhs) const {
    return x == rhs.x &&
           y == rhs.y &&
           z == rhs.z &&
           w == rhs.w;
}

template<class t>
bool Vector4D<t>::operator!=(const Vector4D &rhs) const {
    return !(rhs == *this);
}

template<class t>
Matrix<t> Vector4D<t>::toMatrix() const {
    Matrix<t> M(4, 1);
    M.setCol(*this, 0);
    return M;
}

template<class t>
Vector4D<t>::Vector4D(Matrix<t> matrix) : x(matrix.m[0][0]), y(matrix.m[1][0]), z(matrix.m[2][0]), w(matrix.m[3][0]) {
}


typedef Vector4D<int> ivec4;
typedef Vector4D<double> dvec4;
typedef Vector4D<float> fvec4;

#endif //CANVAS_CLION_VECTOR4D_H
