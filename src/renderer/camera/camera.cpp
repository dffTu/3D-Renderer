#include "camera.h"
#include <renderer/utils/constants.h>

Camera::Camera() {
    zPlane_ = constants::Z_PLANE;
    height_ = constants::CAMERA_HEIGHT;
    width_ = constants::CAMERA_WIDTH;
    position_ = Vec3(0, 0, 0);
    direction_ = Vec3(0, 0, 1);
}

Camera::Camera(int aHeight, int aWidth, const Vec3& aPosition, const Vec3& aDirection) {
    zPlane_ = constants::Z_PLANE;
    height_ = aHeight;
    width_ = aWidth;
    position_ = aPosition;
    direction_ = aDirection;
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

void Camera::move(const Vec3& aOffset) {
    position_ += aOffset;
}
