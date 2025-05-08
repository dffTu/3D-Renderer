#pragma once

#include <renderer/utils/linalg.h>

class Camera {
public:
    Camera();

    double getZPlane() const;
    unsigned int getHeight() const;
    unsigned int getWidth() const;
    Vec3 getPosition() const;
    Vec3 getDirection() const;
    Vec3 getUp() const;
    Vec3 getRight() const;
    Mat4 getTransformMatrix() const;

    void updateDirection(const Vec2& aDelta);
    void move(const Vec3& aOffset);

private:
    double zPlane_;
    const double sensitivity_;
    unsigned int height_;
    unsigned int width_;
    Vec3 position_;
    Vec3 direction_;
    Vec3 right_;
    Vec3 up_;

    double yaw;
    double pitch;
};