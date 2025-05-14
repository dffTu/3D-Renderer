#include "world.h"

void World::addObject(const Object& aObject) {
    objects_.push_back(aObject);
}

void World::addObject(Object&& aObject) {
    objects_.push_back(aObject);
}

const std::vector<Object>& World::getObjects() const {
    return objects_;
}
