#include "projector.h"
#include <renderer/object/object.h>

void Projector::projectObject(const Object& aObject, sf::RenderWindow& aWindow) {
    std::vector<Vec3> transformedVertexes = transformVertexes(aObject);
    std::vector<Vec2> screenVertexes = projectVertexes(transformedVertexes);
    for (const auto& vertex : screenVertexes) {
        auto circle = sf::CircleShape(6);
        circle.setPosition({vertex[0] - 6, vertex[1] - 6});
        aWindow.draw(circle);
    }
    if (aObject.getObjectType() == ObjectType::LINES || aObject.getObjectType() == ObjectType::LINE_STRIP) {
        std::vector<int> vertexIndices = aObject.getVertexIndices();
        std::vector<sf::Vertex> lineVertexes;

        for (int indice: vertexIndices) {
            lineVertexes.push_back(sf::Vertex{{screenVertexes[indice][0], screenVertexes[indice][1]}});
        }

        if (aObject.getObjectType() == ObjectType::LINES) {
            aWindow.draw(lineVertexes.data(), lineVertexes.size(), sf::PrimitiveType::Lines);
        } else {
            aWindow.draw(lineVertexes.data(), lineVertexes.size(), sf::PrimitiveType::LineStrip);
        }
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
        Vec4 transformed =
            camera_.getTransformMatrix()
            * aObject.getTransformMatrix()
            * Vec4(vertex.getX(), vertex.getY(), vertex.getZ(), 1);
        Vec3 tmp = Vec3(transformed[0], transformed[1], transformed[2]);
        result.push_back(tmp);
    }
    return result;
}

std::vector<Vec2> Projector::projectVertexes(const std::vector<Vec3>& aVertexes) {
    std::vector<Vec2> result;
    for (const auto& vertex : aVertexes) {
        double z = vertex[2];
        if (z <= 0) z = 0.0001;
    
        double fov = 90.0;
        double scale = 1.0 / tan(fov * M_PI / 360.0);
    
        double x_proj = vertex[0] * scale / z;
        double y_proj = -vertex[1] * scale / z;
    
        double screen_x = (x_proj + 1.0) * camera_.getWidth() / 2;
        double screen_y = (y_proj + 1.0) * camera_.getHeight() / 2;
    
        result.push_back({screen_x, screen_y});
    }
    return result;
}
