#include "linalg.h"
#include <iostream>

Mat4 getDefaultMat4()
{
    Mat4 result;
    result <<
        1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0;
    return result;
}

Mat4 getMoveMatrix(const Vec3& aVec3)
{
    Mat4 result;
    result <<
        1.0, 0.0, 0.0, aVec3[0],
        0.0, 1.0, 0.0, aVec3[1],
        0.0, 0.0, 1.0, aVec3[2],
        0.0, 0.0, 0.0, 1.0;
    return result;
}

Mat4 getXRotationMatrix(double aRadians)
{
    Mat4 result;
    result <<
        1.0, 0.0, 0.0, 0.0,
        0.0, cos(aRadians), -sin(aRadians), 0.0,
        0.0, sin(aRadians), cos(aRadians), 0.0,
        0.0, 0.0, 0.0, 1.0;
    return result;
}

Mat4 getYRotationMatrix(double aRadians)
{
    Mat4 result;
    result <<
        cos(aRadians), 0.0, sin(aRadians), 0.0,
        0.0, 1.0, 0.0, 0.0,
        -sin(aRadians), 0.0, cos(aRadians), 0.0,
        0.0, 0.0, 0.0, 1.0;
    return result;
}

Mat4 getZRotationMatrix(double aRadians)
{
    Mat4 result;
    result <<
        cos(aRadians), -sin(aRadians), 0.0, 0.0,
        sin(aRadians), cos(aRadians), 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0;
    return result;
}

bool isPointInTriangle(int x, int y, const Vec2& a, const Vec2& b, const Vec2& c)
{
    double first = (a[0] - x) * (b[1] - a[1]) - (b[0] - a[0]) * (a[1] - y);
    double second = (b[0] - x) * (c[1] - b[1]) - (c[0] - b[0]) * (b[1] - y);
    double third = (c[0] - x) * (a[1] - c[1]) - (a[0] - c[0]) * (c[1] - y);

    return (first <= 0 && second <= 0 && third <= 0) || (first >= 0 && second >= 0 && third >= 0);
}

void calculateBarycentric(
    int x,
    int y,
    const std::tuple<Vec2, Vec2, Vec2>& triangle,
    float& alpha,
    float& beta,
    float& gamma)
{
    Vec2 A = std::get<0>(triangle);
    Vec2 B = std::get<1>(triangle);
    Vec2 C = std::get<2>(triangle);

    Vec2 AB = B - A;
    Vec2 AC = C - A;
    Vec2 AP(x - A[0], y - A[1]);
    
    float dotABAB = AB.dot(AB);
    float dotABAC = AB.dot(AC);
    float dotACAC = AC.dot(AC);
    float dotAPAB = AP.dot(AB);
    float dotAPAC = AP.dot(AC);
    
    float invDenominator = 1.0f / (dotABAB * dotACAC - dotABAC * dotABAC);
    
    beta = (dotACAC * dotAPAB - dotABAC * dotAPAC) * invDenominator;
    gamma = (dotABAB * dotAPAC - dotABAC * dotAPAB) * invDenominator;
    alpha = 1.0f - beta - gamma;
}

float interpolateDepth(
    int x,
    int y,
    const std::tuple<Vec2, Vec2, Vec2>& screenVertices,
    const std::tuple<float, float, float>& depths)
{
    float alpha, beta, gamma;
    calculateBarycentric(x, y, screenVertices, alpha, beta, gamma);
    return alpha * std::get<0>(depths) + beta * std::get<1>(depths) + gamma * std::get<2>(depths);
}

Vec2 lerp(const Vec2& a, const Vec2& b, float t)
{
    return a + (b - a) * t;
}
