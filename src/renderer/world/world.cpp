#include "world.h"

void World::addObject(const Object& aObject) {
    worldObjects_.push_back(aObject);
}

std::vector<Object> World::getObjects() const {
    return worldObjects_;
}
