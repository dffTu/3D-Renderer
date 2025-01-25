#include "world.h"

void World::addObject(const Object& aObject) {
    WorldObject worldObject = {
        .object = aObject,
        .delta = Vec3(0, 0, 0),
        .rotateMatrix = Mat3()
    };
    worldObject.rotateMatrix <<
        1.0, 0.0, 0.0,
        0.0, 1.0, 0.0,
        0.0, 0.0, 1.0;
    worldObjects_.push_back(worldObject);
}

std::vector<World::WorldObject> World::getObjects() const {
    return worldObjects_;
}
