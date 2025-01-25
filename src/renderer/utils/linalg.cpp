#include "linalg.h"

Mat3 getDefaultMat3() {
    Mat3 result;
    result <<
        1.0, 0.0, 0.0,
        0.0, 1.0, 0.0,
        0.0, 0.0, 1.0;
    return result;
}

Mat3 getXRotationMatrix(double aRadians) {
    Mat3 result;
    result <<
        1.0, 0.0, 0.0,
        0.0, cos(aRadians), -sin(aRadians),
        0.0, sin(aRadians), cos(aRadians);
    return result;
}

Mat3 getYRotationMatrix(double aRadians) {
    Mat3 result;
    result <<
        cos(aRadians), 0.0, sin(aRadians),
        0.0, 1.0, 0.0,
        -sin(aRadians), 0.0, cos(aRadians);
    return result;
}

Mat3 getZRotationMatrix(double aRadians) {
    Mat3 result;
    result <<
        cos(aRadians), -sin(aRadians), 0.0,
        sin(aRadians), cos(aRadians), 0.0,
        0.0, 0.0, 1.0;
    return result;
}
