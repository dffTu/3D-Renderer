#include <renderer/object/object.h>

class World {
public:
    World() = default;
    void addObject(const Object& aObject);

    std::vector<Object> getObjects() const;

private:
    std::vector<Object> worldObjects_;
};