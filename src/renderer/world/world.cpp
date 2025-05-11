#include "world.h"

void World::addObject(Object& aObject) {
    worldObjects_.push_back(aObject);
}

std::vector<std::reference_wrapper<Object>> World::getObjects() const {
    return worldObjects_;
}

Object& World::getObject(int index) {
    return worldObjects_[index];
}
