#include "camera.h"
#include <renderer/utils/constants.h>

Camera::Camera() : sensitivity_(0.1) {
    zPlane_ = constants::Z_PLANE;
    height_ = constants::CAMERA_HEIGHT;
    width_ = constants::CAMERA_WIDTH;
    position_ = Vec3(0, 0, 0);
    direction_ = Vec3(0, 0, 1);
    up_ = Vec3(0, 1, 0);
    yaw = 90.0;
    pitch = 0.0;
}

double Camera::getZPlane() const {
    return zPlane_;
}

unsigned int Camera::getHeight() const {
    return height_;
}

unsigned int Camera::getWidth() const {
    return width_;
}

Vec3 Camera::getPosition() const {
    return position_;
}

Vec3 Camera::getDirection() const {
    return direction_;
}

Vec3 Camera::getUp() const {
    return up_;
}

Vec3 Camera::getRight() const {
    return right_;
}

Mat4 Camera::getTransformMatrix() const {
    Mat4 result;
    result <<
        right_[0],    up_[0],    direction_[0],   0.0,
        right_[1],    up_[1],    direction_[1],   0.0,
        right_[2],    up_[2],    direction_[2],   0.0,
        -position_.dot(right_), 
        -position_.dot(up_), 
        -position_.dot(direction_), 
        1.0;
    return result.transpose();
}

void Camera::move(const Vec3& aOffset) {
    position_ += aOffset;
}

void Camera::updateDirection(const Vec2& aDelta) {
    yaw -= aDelta[0] * sensitivity_;
    pitch += aDelta[1] * sensitivity_;

    if (pitch > 89.0) pitch = 89.0;
    if (pitch < -89.0) pitch = -89.0;

    direction_[0] = cos(yaw * M_PI / 180.0f) * cos(pitch * M_PI / 180.0f);
    direction_[1] = sin(pitch * M_PI / 180.0f);
    direction_[2] = sin(yaw * M_PI / 180.0f) * cos(pitch * M_PI / 180.0f);
    direction_.normalize();

    right_ = direction_.cross(Vec3(0.0, -1.0, 0.0)).normalized();
    up_ = right_.cross(direction_).normalized();
}
