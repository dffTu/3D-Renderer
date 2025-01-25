#include "projector.h"

Projector::Projector(const World& aWorld, const Camera& aCamera) {
    world_ = aWorld;
    camera_ = aCamera;
}

void Projector::projectObject(const Object& aObject, sf::RenderWindow& aWindow) {
    std::vector<Vec3> transformedVertexes = transformVertexes(aObject);
    long double z_plane = 200.0;
    for (const auto& vertex : transformedVertexes) {
        Vec2 point(
            camera_.getWidth() / 2 + vertex[0] * z_plane / vertex[2],
            camera_.getHeight() / 2 - vertex[1] * z_plane / vertex[2]
        );
        auto circle = sf::CircleShape(5);
        circle.setOutlineColor(sf::Color::Black);
        circle.setPosition({point[0], point[1]});
        aWindow.draw(circle);
    }
}

void Projector::projectObjects(sf::RenderWindow& aWindow) {
    auto worldObjects = world_.getObjects();
    for (const auto& object : worldObjects) {
        projectObject(object, aWindow);
    }
}

World& Projector::getWorld() {
    return world_;
}

Camera& Projector::getCamera() {
    return camera_;
}

std::vector<Vec3> Projector::transformVertexes(const Object& aObject) {
    std::vector<Vec3> result;
    for (const Vertex& vertex: aObject.getVertexes()) {
        Vec4 transformed = aObject.getTransformMatrix() * Vec4(vertex.getX(), vertex.getY(), vertex.getZ(), 1);
        Vec3 tmp = Vec3(transformed[0], transformed[1], transformed[2]) - camera_.getPosition();
        result.push_back(tmp);
    }
    return result;
}
