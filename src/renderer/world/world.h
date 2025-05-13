#pragma once

#include <renderer/object/object.h>

class World {
public:
    void addObject(Object& aObject);
    void addObject(Object&& aObject);

    std::vector<std::reference_wrapper<Object>> getObjects() const;

private:
    std::vector<std::reference_wrapper<Object>> objects_;
};
