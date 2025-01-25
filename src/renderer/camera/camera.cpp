#include "camera.h"

Camera::Camera() {
    position_ = Vec3(0, 0, 0);
    direction_ = Vec3(0, 0, 1);
}

Camera::Camera(const Vec3& aPosition, const Vec3& aDirection) {
    position_ = aPosition;
    direction_ = aDirection;
}

Vec3 Camera::getPosition() const {
    return position_;
}

Vec3 Camera::getDirection() const {
    return direction_;
}
