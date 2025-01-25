#include <renderer/object/object.h>
#include <renderer/utils/linalg.h>

class World {
public:
    struct WorldObject {
        Object object;
        Vec3 delta;
        Mat3 rotateMatrix;
    };

    World() = default;
    void addObject(const Object& aObject);

    std::vector<WorldObject> getObjects() const;

private:

    std::vector<WorldObject> worldObjects_;
};