#ifndef MATRIX3X3_H
#define MATRIX3X3_H

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
};
/*
matrix3x3 identity3x3() {
    return matrix3x3();
}*/

// TODO: Make rotation matrix functions

// TODO: Implement matrix multiplications

// TODO: Make a function that simplifies deep copy

#endif //MATRIX3X3_H
