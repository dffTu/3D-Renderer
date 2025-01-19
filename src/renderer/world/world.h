#include <renderer/object/object.h>
#include <renderer/utils/linalg.h>

class World {
public:
    World() = default;
    void addObject(const Object& aObject);

private:
    struct WorldObject {
        Object object;
        Vec3 delta;
        Mat3 rotateMatrix;
    };

    std::vector<WorldObject> worldObjects_;
};