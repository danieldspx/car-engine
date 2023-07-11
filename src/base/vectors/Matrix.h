//
// Created by daniel on 11/07/23.
//

#ifndef CANVAS_CLION_MATRIX_H
#define CANVAS_CLION_MATRIX_H

#include <cmath>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <type_traits>

#include "Vector3D.h"
#include "Vector4D.h"

template<class T>
struct Vector3D;

template<class T>
struct Vector4D;

template<class T>
class Matrix {
public:
    std::vector<std::vector<T>> m;
    int rows, cols;

    Matrix<T>(int rows, int cols);

    Matrix<T>();

    std::vector<T> &operator[](int idx);

    Matrix<T> operator*(Matrix<T> Mat);

    Matrix<T> operator*(Vector3D<T> v);

    Matrix<T> operator*(Vector4D<T> v);

    void setCol(const Vector3D<T> v, int col);

    void setCol(const Vector4D<T> v, int col);

    void setRow(const Vector3D<T> v, int row);

    void setRow(const Vector4D<T> v, int row);

    static Matrix<T> identity(int size);

    void printMatrix();

    Matrix<T> invert();
    Matrix<T> clone();

    Vector3D<T> toVector3();

    Vector4D<T> toVector4();

    static Matrix<T> translate(const Vector3D<T> translationAmount);

    static Matrix<T> rotateZ(float angle);

    static Matrix<T> rotateY(float angle);

    static Matrix<T> rotateX(float angle);

    static Matrix<T> scale(const Vector3D<T> scale);
};

template<class T>
Matrix<T>::Matrix(int rows, int cols) : rows(rows), cols(cols) {
    m = std::vector<std::vector<T>>(rows);
    for (int i = 0; i < rows; ++i) {
        m[i] = std::vector<T>(cols);
    }
}

template<class T>
std::vector<T> &Matrix<T>::operator[](int idx) {
    if (idx >= 0 && idx < rows) return m[idx];
    return m[0];
}

template<class T>
Matrix<T> Matrix<T>::operator*(Matrix<T> Mat) {
    if (Mat.rows != this->cols) {
        std::cerr << "INVALID MATRIX MUL" << std::endl;
        return Mat;
    }
    Matrix<T> Result(rows, Mat.cols);

    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < Mat.cols; ++x) {
            for (int i = 0; i < cols; ++i) {
                Result[y][x] += m[y][i] * Mat[i][x];
            }
        }
    }
    return Result;
}

template<class T>
typename std::enable_if<std::is_same<T, float>::value, void>::type
printValue(const T& value) {
    std::cout << " " << value;
}

template<class T>
typename std::enable_if<std::is_same<T, Vector3D<float>>::value, void>::type
printValue(const T& value) {
    std::cout << "( " << value.x << ", " << value.y << ", " << value.z << " )";
}

template<class T>
void Matrix<T>::printMatrix() {
    std::cout << std::endl;
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            printValue(m[y][x]);
        }
        std::cout << std::endl;
    }
}

template<class T>
Matrix<T>::Matrix() {
    Matrix<T>(4, 4);
}

template<class T>
Matrix<T> Matrix<T>::invert() {
    if (rows != cols) return Matrix<T>();
    // augmenting the square matrix with the identity matrix of the same dimensions a => [ai]
    Matrix result(rows, cols * 2);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            result[i][j] = m[i][j];
    for (int i = 0; i < rows; i++)
        result[i][i + cols] = 1;

    for (int i = 0; i < rows; i++) {
        T pivo;
        for (int j = 0; j < cols * 2; ++j) {
            if (result[i][j] != 0) {
                pivo = result[i][j];
                break;
            }
        }

        for (int j = 0; j < cols * 2; ++j) {
            result[i][j] = result[i][j] / pivo;
        }

        for (int k = 0; k < rows; ++k) {
            T mult = result[k][i];
            if (k == i) continue;
            for (int j = 0; j < cols * 2; ++j) {
                result[k][j] = result[k][j] - result[i][j] * mult;
            }
        }
    }
    Matrix truncate(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            truncate[i][j] = result[i][j + cols];
        }
    }

    return truncate;
}

template<class T>
Matrix<T> Matrix<T>::clone() {
    Matrix<T> cloned(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cloned[i][j] = m[i][j];
        }
    }
    return cloned;
}

template<class T>
Matrix<T> Matrix<T>::operator*(Vector3D<T> v) {
    Matrix<T> V = v.toVector4(1).toMatrix();
    return *this * V;
}


template<class T>
Matrix<T> Matrix<T>::operator*(Vector4D<T> v) {
    Matrix<T> V = v.toMatrix();
    return *this * V;
}


template<class T>
Matrix<T> Matrix<T>::identity(int size) {
    Matrix<T> M(size, size);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            M.m[i][j] = 0;
            if (i == j)
                M.m[i][j] = 1;
        }
    }
    return M;
}

template<class T>
void Matrix<T>::setCol(const Vector3D<T> v, int col) {
    if (rows != 3 || col >= this->cols || col < 0) {
        std::cerr << "INVALID MATRIX SET COL" << std::endl;
    }
    this->m[0][col] = v.x;
    this->m[1][col] = v.y;
    this->m[2][col] = v.z;
}

template<class T>
void Matrix<T>::setCol(const Vector4D<T> v, int col) {
    if (rows != 4 || col >= this->cols || col < 0) {
        std::cerr << "INVALID MATRIX SET COL" << std::endl;
    }
    this->m[0][col] = v.x;
    this->m[1][col] = v.y;
    this->m[2][col] = v.z;
    this->m[3][col] = v.w;
}

template<class T>
void Matrix<T>::setRow(const Vector3D<T> v, int row) {
    if (cols != 3 || row >= this->rows || row < 0) {
        std::cerr << "INVALID MATRIX SET ROW" << std::endl;
    }
    this->m[row] = {v.x, v.y, v.z};
}

template<class T>
void Matrix<T>::setRow(const Vector4D<T> v, int row) {
    if (cols != 4 || row >= this->rows || row < 0) {
        std::cerr << "INVALID MATRIX SET ROW" << std::endl;
    }
    this->m[row] = {v.x, v.y, v.z, v.w};
}

template<class T>
Vector3D<T> Matrix<T>::toVector3() {
    return Vector3D<T>(m[0][0], m[1][0], m[2][0]);
}

template<class T>
Matrix<T> Matrix<T>::translate(const Vector3D<T> translationAmount) {
    Matrix<T> TR = Matrix<T>::identity(4);
    TR.setCol(translationAmount.toVector4(1), 3);
    return TR;
}

template<class T>
Matrix<T> Matrix<T>::rotateZ(float angle) {
    Matrix<T> R(4, 4);
    R.m = {{std::cos(angle), -std::sin(angle), 0, 0},
           {std::sin(angle), std::cos(angle),  0, 0},
           {0,          0,           1, 0},
           {0,          0,           0, 1}};
    return R;
}

template<class T>
Matrix<T> Matrix<T>::rotateY(float angle) {
    Matrix<T> R(4, 4);
    R.m = {{cos(angle),  0, sin(angle), 0},
           {0,           1, 0,          0},
           {-sin(angle), 0, cos(angle), 0},
           {0,           0, 0,          1}};
    return R;
}

template<class T>
Matrix<T> Matrix<T>::rotateX(float angle) {
    Matrix<T> R(4, 4);
    R.m = {{1, 0,          0,           0},
           {0, cos(angle), -sin(angle), 0},
           {0, sin(angle), cos(angle),  0},
           {0, 0,          0,           1}};
    return R;
}

template<class T>
Matrix<T> Matrix<T>::scale(const Vector3D<T> scale) {
    Matrix<T> S(4, 4);
    S.m = {{scale.x, 0,       0,       0},
           {0,       scale.y, 0,       0},
           {0,       0,       scale.z, 0},
           {0,       0,       0,       1}};
    return S;
}

template<class T>
Vector4D<T> Matrix<T>::toVector4() {
    return Vector4D<T>(m[0][0], m[1][0], m[2][0], m[3][0]);
}

typedef Matrix<Vector3D<float>> v3matrix;

#endif //CANVAS_CLION_MATRIX_H
