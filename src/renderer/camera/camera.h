#pragma once

#include <renderer/utils/linalg.h>

class Camera {
public:
    Camera();
    Camera(int aHeight, int aWidth, const Vec3& aPosition, const Vec3& aDirection);

    double getZPlane() const;
    unsigned int getHeight() const;
    unsigned int getWidth() const;
    Vec3 getPosition() const;
    Vec3 getDirection() const;
    
    void move(const Vec3& aOffset);

private:
    double zPlane_;
    unsigned int height_;
    unsigned int width_;
    Vec3 position_;
    Vec3 direction_;
};