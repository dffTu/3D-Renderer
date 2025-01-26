#include "world.h"

void World::addObject(const Object& aObject) {
    worldObjects_.push_back(aObject);
}

std::vector<Object> World::getObjects() const {
    return worldObjects_;
}

Object& World::getObject(int index) {
    return worldObjects_[index];
}
