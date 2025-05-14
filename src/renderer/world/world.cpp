#include "world.h"

namespace renderer
{

void World::addObject(const Object& aObject)
{
    objects_.push_back(aObject);
}

void World::addObject(Object&& aObject)
{
    objects_.push_back(aObject);
}

void World::addSampleObjects()
{
    const int cubes_count = 50;

    std::vector<Object> objects;

    for (size_t i = 0; i < cubes_count; ++i)
    {
        for (size_t j = 0; j < cubes_count; ++j)
        {
            Object obj(
                ObjectType::PolygonsWithOutline,
                {Vec3{50, 50, 50}, Vec3{50, -50, 50}, Vec3{-50, -50, 50}, Vec3{-50, 50, 50},
                Vec3{50, 50, -50}, Vec3{50, -50, -50}, Vec3{-50, -50, -50}, Vec3{-50, 50, -50}},
                {0, 1, 2, 0, 2, 3, 0, 1, 5, 0, 5, 4, 2, 3, 6, 3, 7, 6, 4, 5, 6, 4, 6, 7, 0, 3, 4, 3, 4, 7, 1, 2, 5, 2, 5, 6});
            obj.move(Vec3{float(110 * i), float(110 * j), 0});
            obj.setColor(sf::Color::Green);
            objects_.push_back(obj);
        }
    }
}

void World::animateObjects(float timePassed)
{
    for (auto& object : objects_)
    {
        object.rotateX(0.01 * timePassed * 300);
        object.rotateY(0.01 * timePassed * 300);
        object.rotateZ(0.01 * timePassed * 300);
    }
}

const std::vector<Object>& World::getObjects() const
{
    return objects_;
}

}
