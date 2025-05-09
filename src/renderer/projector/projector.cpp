#include "projector.h"
#include <renderer/object/object.h>
#include <tuple>

void Projector::projectObject(const Object& aObject, sf::RenderWindow& aWindow) {
    std::vector<Vec3> transformedVertexes = transformVertexes(aObject);
    std::vector<Vec2> screenVertexes = projectVertexes(transformedVertexes);
    std::vector<int> vertexIndices = aObject.getVertexIndices();

    for (const auto& vertex : screenVertexes)
    {
        auto circle = sf::CircleShape(6);
        circle.setPosition({vertex[0] - 6, vertex[1] - 6});
        aWindow.draw(circle);
    }
    if (aObject.getObjectType() == ObjectType::LINES)
    {
        projectLines(aObject, transformedVertexes, aWindow);
    }
    else if (aObject.getObjectType() == ObjectType::LINE_STRIP)
    {
        projectLines(aObject, transformedVertexes, aWindow);
    }
    else if (aObject.getObjectType() == ObjectType::POLYGONS) {
        projectPolygons(aObject, transformedVertexes, aWindow);
    }
    else if (aObject.getObjectType() == ObjectType::POLYGONS_WITH_OUTLINE) {
        projectPolygons(aObject, transformedVertexes, aWindow);
        projectPolygonsOutline(aObject, transformedVertexes, aWindow);
    }
}

void Projector::projectLines(const Object& aObject, const std::vector<Vec3>& aTransformedVertexes, sf::RenderWindow& aWindow) {
    std::vector<sf::Vertex> lineVertexes;
    std::vector<int> vertexIndices = aObject.getVertexIndices();

    int delta;

    if (aObject.getObjectType() == ObjectType::LINES) delta = 2;
    else if (aObject.getObjectType() == ObjectType::LINE_STRIP) delta = 1;
    else assert(false && "Unknown ObjectType for projecting lines!");

    for (size_t i = 1; i < vertexIndices.size(); i += delta)
    {
        std::optional<std::tuple<Vec3, Vec3>> clippedLine =
            clipLine(aTransformedVertexes[vertexIndices[i - 1]], aTransformedVertexes[vertexIndices[i]]);

        if (clippedLine.has_value())
        {
            Vec2 p1 = projectVertex(std::get<0>(clippedLine.value()));
            Vec2 p2 = projectVertex(std::get<1>(clippedLine.value()));

            lineVertexes.push_back(sf::Vertex{{p1[0], p1[1]}});
            lineVertexes.push_back(sf::Vertex{{p2[0], p2[1]}});
        }
    }

    for (auto& vertex : lineVertexes)
    {
        vertex.color = aObject.getColor();
    }

    aWindow.draw(lineVertexes.data(), lineVertexes.size(), sf::PrimitiveType::Lines);
}

void Projector::projectPolygons(const Object& aObject, const std::vector<Vec3>& aTransformedVertexes, sf::RenderWindow& aWindow) {
    std::vector<sf::Vertex> lineVertexes;
    std::vector<int> vertexIndices = aObject.getVertexIndices();

    for (int i = 2; i < vertexIndices.size(); i += 3)
    {
        std::vector<std::tuple<Vec3, Vec3, Vec3>> polygonsClipped =
            clipPolygon(
                aTransformedVertexes[vertexIndices[i - 2]],
                aTransformedVertexes[vertexIndices[i - 1]],
                aTransformedVertexes[vertexIndices[i]]);
        
        for (const std::tuple<Vec3, Vec3, Vec3>& polygon : polygonsClipped)
        {
            Vec2 p1 = projectVertex(std::get<0>(polygon));
            Vec2 p2 = projectVertex(std::get<1>(polygon));
            Vec2 p3 = projectVertex(std::get<2>(polygon));

            sf::ConvexShape convex;
            convex.setPointCount(3);
            convex.setPoint(0, {p1[0], p1[1]});
            convex.setPoint(1, {p2[0], p2[1]});
            convex.setPoint(2, {p3[0], p3[1]});
            convex.setFillColor(aObject.getColor());

            aWindow.draw(convex);
        }
    }

    for (auto& vertex : lineVertexes)
    {
        vertex.color = sf::Color::Black;
    }

    aWindow.draw(lineVertexes.data(), lineVertexes.size(), sf::PrimitiveType::Lines);
}

void Projector::projectPolygonsOutline(const Object& aObject, const std::vector<Vec3>& aTransformedVertexes, sf::RenderWindow& aWindow) {
    std::vector<int> newIndices;
    std::vector<int> vertexIndices = aObject.getVertexIndices();

    for (int i = 2; i < vertexIndices.size(); i += 3)
    {
        newIndices.push_back(vertexIndices[i - 2]);
        newIndices.push_back(vertexIndices[i - 1]);
        newIndices.push_back(vertexIndices[i - 2]);
        newIndices.push_back(vertexIndices[i]);
        newIndices.push_back(vertexIndices[i - 1]);
        newIndices.push_back(vertexIndices[i]);
    }

    Object newObject(ObjectType::LINES, aObject.getVertexes(), newIndices);
    newObject.setColor(sf::Color::Black);

    projectLines(newObject, aTransformedVertexes, aWindow);
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

std::optional<std::tuple<Vec3, Vec3>> Projector::clipLine(Vec3 p1, Vec3 p2) const {
    std::vector<Vec2> result;
    double z_plane = camera_.getZPlane();

    bool firstInside = p1[2] >= z_plane;
    bool secondInside = p2[2] >= z_plane;
    
    if (firstInside && secondInside)
    {
        return std::make_tuple(p1, p2);
    }
    else if (!firstInside && !secondInside)
    {
        return std::nullopt;
    }

    if (!firstInside) swap(p1, p2);
    double t = (z_plane - p1[2]) / (p1[2] - p2[2]);
    return std::make_tuple(p1, p1 + t * (p1 - p2));
}

std::vector<std::tuple<Vec3, Vec3, Vec3>> Projector::clipPolygon(const Vec3& p1, const Vec3& p2, const Vec3& p3) const {
    std::vector<std::tuple<Vec3, Vec3, Vec3>> result;
    double z_plane = camera_.getZPlane();
    std::vector<Vec3> vertexes{p1, p2, p3};

    std::vector<Vec3> vertices;

    for (size_t i = 0; i < vertexes.size(); ++i) {
        const Vec3& current = vertexes[i];
        const Vec3& next = vertexes[(i + 1) % vertexes.size()];

        bool currentInside = (current[2] >= z_plane);
        bool nextInside = (next[2] >= z_plane);

        if (currentInside && nextInside) {
            vertices.push_back(next);
        } 
        else if (currentInside && !nextInside) {
            float t = (z_plane - current[2]) / (next[2] - current[2]);
            Vec3 intersection{
                current[0] + t * (next[0] - current[0]),
                current[1] + t * (next[1] - current[1]),
                float(z_plane)
            };
            vertices.push_back(intersection);
        }
        else if (!currentInside && nextInside) {
            float t = (z_plane - current[2]) / (next[2] - current[2]);
            Vec3 intersection{
                current[0] + t * (next[0] - current[0]),
                current[1] + t * (next[1] - current[1]),
                float(z_plane)
            };
            vertices.push_back(intersection);
            vertices.push_back(next);
        }
    }

    for (int i = 2; i < vertices.size(); ++i) {
        result.push_back(std::make_tuple(vertices[i - 1], vertices[i], vertices[0]));
    }

    return result;
}

Vec3 Projector::transformVertex(const Object& aObject, const Vec3& aVertex) const {

    Vec4 transformed =
        camera_.getTransformMatrix()
        * aObject.getTransformMatrix()
        * Vec4(aVertex[0], aVertex[1], aVertex[2], 1);
    return Vec3(transformed[0], transformed[1], transformed[2]);
}

std::vector<Vec3> Projector::transformVertexes(const Object& aObject) const {
    std::vector<Vec3> result;
    for (const Vec3& vertex: aObject.getVertexes()) {
        result.push_back(transformVertex(aObject, vertex));
    }
    return result;
}

Vec2 Projector::projectVertex(const Vec3& aVertex) const {
    double z = aVertex[2];
    if (z <= 0) z = 0.0001;

    double fov = 90.0;
    double scale = 1.0 / tan(fov * M_PI / 360.0);

    double x_proj = aVertex[0] * scale / z;
    double y_proj = -aVertex[1] * scale / z;

    double screen_x = (x_proj + 1.0) * camera_.getWidth() / 2;
    double screen_y = (y_proj + 1.0) * camera_.getHeight() / 2;

    return {screen_x, screen_y};
}

std::vector<Vec2> Projector::projectVertexes(const std::vector<Vec3>& aVertexes) const {
    std::vector<Vec2> result;
    for (const auto& vertex : aVertexes) {
        result.push_back(projectVertex(vertex));
    }
    return result;
}
