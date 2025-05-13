#pragma once

#include <renderer/utils/linalg.h>

class Camera {
public:
    Camera(int32_t height, int32_t width);

    Vec3 getPosition() const;
    Vec3 getDirection() const;
    Vec3 getUp() const;
    Vec3 getRight() const;
    Mat4 getTransformMatrix() const;

    void updateDirection(const Vec2& aDelta);
    void move(const Vec3& aOffset);

    const int32_t height;
    const int32_t width;
    static constexpr const float zPlane = 0.1;

private:
    const double sensitivity_;
    Vec3 position_;
    Vec3 direction_;
    Vec3 right_;
    Vec3 up_;

    double yaw;
    double pitch;
};