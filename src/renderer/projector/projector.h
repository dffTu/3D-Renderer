#pragma once

#include <renderer/world/world.h>
#include <renderer/camera/camera.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Projector {
public:
    Projector() = default;
    Projector(const World& aWorld, const Camera& aCamera);

    void projectObject(const Object& aObject, sf::RenderWindow& aWindow);
    void projectObjects(sf::RenderWindow& aWindow);

    World& getWorld();
    Camera& getCamera();

private:
    std::vector<Vec3> transformVertexes(const Object& aObject);
    std::vector<Vec2> projectVertexes(const std::vector<Vec3>& aVertexes);

    World world_;
    Camera camera_;
};