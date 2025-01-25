#include "linalg.h"

Mat4 getDefaultMat4() {
    Mat4 result;
    result <<
        1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0;
    return result;
}

Mat4 getMoveMatrix(const Vec3& aVec3) {
    Mat4 result;
    result <<
        1.0, 0.0, 0.0, aVec3[0],
        0.0, 1.0, 0.0, aVec3[1],
        0.0, 0.0, 1.0, aVec3[2],
        0.0, 0.0, 0.0, 1.0;
    return result;
}

Mat4 getXRotationMatrix(double aRadians) {
    Mat4 result;
    result <<
        1.0, 0.0, 0.0, 0.0,
        0.0, cos(aRadians), -sin(aRadians), 0.0,
        0.0, sin(aRadians), cos(aRadians), 0.0,
        0.0, 0.0, 0.0, 1.0;
    return result;
}

Mat4 getYRotationMatrix(double aRadians) {
    Mat4 result;
    result <<
        cos(aRadians), 0.0, sin(aRadians), 0.0,
        0.0, 1.0, 0.0, 0.0,
        -sin(aRadians), 0.0, cos(aRadians), 0.0,
        0.0, 0.0, 0.0, 1.0;
    return result;
}

Mat4 getZRotationMatrix(double aRadians) {
    Mat4 result;
    result <<
        cos(aRadians), -sin(aRadians), 0.0, 0.0,
        sin(aRadians), cos(aRadians), 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0;
    return result;
}
