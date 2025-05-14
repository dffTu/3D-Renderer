#pragma once

#include <renderer/object/object.h>

class World {
public:
    void addObject(const Object& aObject);
    void addObject(Object&& aObject);

    const std::vector<Object>& getObjects() const;

private:
    std::vector<Object> objects_;
};
