#include <Eigen/Core>

using Vec2 = Eigen::Vector2f;
using Vec3 = Eigen::Vector3f;
using Vec4 = Eigen::Vector4f;

using Mat3 = Eigen::Matrix3f;
using Mat4 = Eigen::Matrix4f;

Mat3 getDefaultMat3();
Mat3 getXRotationMatrix(double aRadians);
Mat3 getYRotationMatrix(double aRadians);
Mat3 getZRotationMatrix(double aRadians);
