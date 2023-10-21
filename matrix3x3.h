#ifndef MATRIX3X3_H
#define MATRIX3X3_H

#include <math.h>

class Matrix3x3 {
public:
    float e[3][3];

    // Constructor returns identity matrix
    Matrix3x3() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                e[i][j] = (i == j);
            }
        }
    }

    Matrix3x3(const float& e00, const float& e01, const float& e02,
              const float& e10, const float& e11, const float& e12,
              const float& e20, const float& e21, const float& e22) {
        e[0][0] = e00;
        e[0][1] = e01;
        e[0][2] = e02;
        e[1][0] = e10;
        e[1][1] = e11;
        e[1][2] = e12;
        e[2][0] = e20;
        e[2][1] = e21;
        e[2][2] = e22;
    }

    Matrix3x3(const Matrix3x3& A) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                this->e[i][j] = A.e[i][j];
            }
        }
    }
};

inline Matrix3x3 operator*(const Matrix3x3& A, const Matrix3x3& B) {
    return {
        A.e[0][0] * B.e[0][0] + A.e[0][1] * B.e[1][0] + A.e[0][2] * B.e[2][0],
        A.e[0][0] * B.e[0][1] + A.e[0][1] * B.e[1][1] + A.e[0][2] * B.e[2][1],
        A.e[0][0] * B.e[0][2] + A.e[0][1] * B.e[1][2] + A.e[0][2] * B.e[2][2],
        A.e[1][0] * B.e[0][0] + A.e[1][1] * B.e[1][0] + A.e[1][2] * B.e[2][0],
        A.e[1][0] * B.e[0][1] + A.e[1][1] * B.e[1][1] + A.e[1][2] * B.e[2][1],
        A.e[1][0] * B.e[0][2] + A.e[1][1] * B.e[1][2] + A.e[1][2] * B.e[2][2],
        A.e[2][0] * B.e[0][0] + A.e[2][1] * B.e[1][0] + A.e[2][2] * B.e[2][0],
        A.e[2][0] * B.e[0][1] + A.e[2][1] * B.e[1][1] + A.e[2][2] * B.e[2][1],
        A.e[2][0] * B.e[0][2] + A.e[2][1] * B.e[1][2] + A.e[2][2] * B.e[2][2]
    };
}

inline Vec3 operator*(const Matrix3x3& A, const Vec3 v) {
    return {
        A.e[0][0] * v.e[0] + A.e[0][1] * v.e[1] + A.e[0][2] * v.e[2],
        A.e[1][0] * v.e[0] + A.e[1][1] * v.e[1] + A.e[1][2] * v.e[2],
        A.e[2][0] * v.e[0] + A.e[2][1] * v.e[1] + A.e[2][2] * v.e[2]
    };
}

// theta: Radian
inline Matrix3x3 rotationX(const float& theta)  {
    float cosTheta = std::cos(theta);
    float sinTheta = std::sin(theta);
    return {
        1.f, 0.f, 0.f,
        0.f, cosTheta, (-1.f)*sinTheta,
        0.f, sinTheta, cosTheta
    };
}

inline Matrix3x3 rotationY(const float& theta)  {
    float cosTheta = std::cos(theta);
    float sinTheta = std::sin(theta);
    return {
        cosTheta, 0.f, sinTheta,
        0.f, 1.f, 0.f,
        (-1.f)*sinTheta, 0.f, cosTheta
    };
}

inline Matrix3x3 rotationZ(const float& theta)  {
    float cosTheta = std::cos(theta);
    float sinTheta = std::sin(theta);
    return {
        cosTheta, (-1.f)*sinTheta, 0.f,
        sinTheta, cosTheta, 0.f,
        0.f, 0.f, 1.f
    };
}

// TODO: Make a function that simplifies deep copy

#endif //MATRIX3X3_H
