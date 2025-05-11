#pragma once

#include <renderer/object/object.h>

class World {
public:
    World() = default;
    void addObject(Object& aObject);

    std::vector<std::reference_wrapper<Object>> getObjects() const;

    Object& getObject(int index);

private:
    std::vector<std::reference_wrapper<Object>> worldObjects_;
};