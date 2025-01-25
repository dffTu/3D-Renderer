#include <renderer/utils/linalg.h>

class Camera {
public:
    Camera();
    Camera(const Vec3& aPosition, const Vec3& aDirection);

    Vec3 getPosition() const;
    Vec3 getDirection() const;

private:
    Vec3 position_;
    Vec3 direction_;
};