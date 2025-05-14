#include "camera.h"

namespace renderer
{

Camera::Camera(int32_t height, int32_t width) :
    sensitivity_(0.1),
    height(height),
    width(width),
    position_(Vec3(0, 0, 0)),
    direction_(Vec3(0, 0, 1)),
    up_(Vec3(0, 1, 0)),
    yaw_(90.0),
    pitch_(0.0),
    velocity_(600)
{
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

void Camera::updateDirection(const Vec2& aDelta) {
    yaw_ -= aDelta[0] * sensitivity_;
    pitch_ += aDelta[1] * sensitivity_;

    if (pitch_ > 89.0) pitch_ = 89.0;
    if (pitch_ < -89.0) pitch_ = -89.0;

    direction_[0] = cos(yaw_ * M_PI / 180.0f) * cos(pitch_ * M_PI / 180.0f);
    direction_[1] = sin(pitch_ * M_PI / 180.0f);
    direction_[2] = sin(yaw_ * M_PI / 180.0f) * cos(pitch_ * M_PI / 180.0f);
    direction_.normalize();

    right_ = direction_.cross(Vec3(0.0, -1.0, 0.0)).normalized();
    up_ = right_.cross(direction_).normalized();
}

void Camera::move(const Vec3& aOffset) {
    position_ += aOffset;
}

int Camera::getVelocity() const
{
    return velocity_;
}

void Camera::setVelocity(int newVelocity)
{
    velocity_ = newVelocity;
}

}
