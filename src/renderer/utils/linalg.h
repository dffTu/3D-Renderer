#pragma once

#define _USE_MATH_DEFINES

#include <Eigen/Core>
#include <Eigen/Geometry>
#include <math.h>

using Vec2 = Eigen::Vector2f;
using Vec3 = Eigen::Vector3f;
using Vec4 = Eigen::Vector4f;

using Mat3 = Eigen::Matrix3f;
using Mat4 = Eigen::Matrix4f;

Mat4 getDefaultMat4();
Mat4 getMoveMatrix(const Vec3& aVec3);
Mat4 getXRotationMatrix(double aRadians);
Mat4 getYRotationMatrix(double aRadians);
Mat4 getZRotationMatrix(double aRadians);

bool isPointInTriangle(int x, int y, const Vec2& a, const Vec2& b, const Vec2& c);
float interpolateDepth(
    int x,
    int y,
    const std::tuple<Vec2, Vec2, Vec2>& screenVertices,
    const std::tuple<float, float, float>& depths);

Vec2 lerp(const Vec2& a, const Vec2& b, float t);
