#pragma once

#include <Eigen/Core>

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
