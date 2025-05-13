#pragma once

#include <renderer/object/object.h>

class World {
public:
    void addObject(Object& aObject);
    void addObject(Object&& aObject);

    const std::vector<Object>& getObjects() const;

private:
    std::vector<Object> objects_;
};
