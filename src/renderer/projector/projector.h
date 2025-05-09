#pragma once

#include <renderer/world/world.h>
#include <renderer/camera/camera.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Projector {
public:
    Projector() = default;

    void projectObject(const Object& aObject, sf::RenderWindow& aWindow);
    void projectObjects(sf::RenderWindow& aWindow);

    World& getWorld();
    Camera& getCamera();

    std::optional<std::tuple<Vec3, Vec3>> clipLine(Vec3 p1, Vec3 p2) const;
    std::vector<std::tuple<Vec3, Vec3, Vec3>> clipPolygon(const Vec3& p1, const Vec3& p2, const Vec3& p3) const;

private:
    Vec3 transformVertex(const Object& aObject, const Vec3& aVertex) const;
    std::vector<Vec3> transformVertexes(const Object& aObject) const;
    Vec2 projectVertex(const Vec3& aVertex) const;
    std::vector<Vec2> projectVertexes(const std::vector<Vec3>& aVertexes) const;

    World world_;
    Camera camera_;
};