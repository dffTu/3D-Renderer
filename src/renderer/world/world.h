#pragma once

#include <renderer/object/object.h>

namespace renderer
{

class World {
public:
    void addObject(const Object& aObject);
    void addObject(Object&& aObject);

    void addSampleObjects();
    void animateObjects(float timePassed);

    const std::vector<Object>& getObjects() const;

private:
    std::vector<Object> objects_;
};

}
