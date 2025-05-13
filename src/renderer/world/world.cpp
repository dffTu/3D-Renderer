#include "world.h"

void World::addObject(Object& aObject) {
    objects_.push_back(aObject);
}

void World::addObject(Object&& aObject) {
    objects_.push_back(aObject);
}

std::vector<std::reference_wrapper<Object>> World::getObjects() const {
    return objects_;
}
