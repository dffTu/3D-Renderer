#include "projector.h"
#include <renderer/object/object.h>
#include <tuple>
#include <iostream>

Projector::Projector() :
    world_(),
    camera_()
{
    zBuffer_.resize(camera_.height * camera_.width, std::numeric_limits<float>::max());
    colors_.resize(camera_.height * camera_.width, sf::Color::White);
    frameBuffer_ = sf::Image({camera_.width, camera_.height}, sf::Color::Transparent);
}

void Projector::projectObject(const Object& aObject)
{
    std::vector<Vec3> transformedVertexes = transformVertexes(aObject);
    std::vector<Vec2> screenVertexes = projectVertexes(transformedVertexes);
    std::vector<int> vertexIndices = aObject.getVertexIndices();

    if (aObject.getObjectType() == ObjectType::LINES)
    {
        projectLines(aObject, transformedVertexes);
    }
    else if (aObject.getObjectType() == ObjectType::LINE_STRIP)
    {
        projectLines(aObject, transformedVertexes);
    }
    else if (aObject.getObjectType() == ObjectType::POLYGONS) {
        projectPolygons(aObject, transformedVertexes);
    }
    else if (aObject.getObjectType() == ObjectType::POLYGONS_WITH_OUTLINE) {
        projectPolygons(aObject, transformedVertexes);
        projectPolygonsOutline(aObject, transformedVertexes);
    }
}

void Projector::projectLine(const Vec3& a, const Vec3& b, const sf::Color& color, const std::vector<Vec3>& aTransformedVertexes)
{
    Vec2 p1 = projectVertex(a);
    Vec2 p2 = projectVertex(b);

    if ((p1 - p2).norm() <= 0.0001) return;

    int x1 = static_cast<int>(std::round(p1[0]));
    int y1 = static_cast<int>(std::round(p1[1]));
    int x2 = static_cast<int>(std::round(p2[0]));
    int y2 = static_cast<int>(std::round(p2[1]));

    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);

    if (dx == 0 && dy == 0) return;

    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    double z = a[2];
    double zStep = (p2[2] - p1[2]) / std::max(dx, dy);

    while (true) {

        if (0 <= x1 && x1 < camera_.width && 0 <= y1 && y1 < camera_.height && (z < zBuffer_[y1 * camera_.width + x1] || std::abs(z - zBuffer_[y1 * camera_.width + x1]) <= 1))
        {
            zBuffer_[y1 * camera_.width + x1] = z;
            colors_[y1 * camera_.width + x1] = color;
        }

        if (x1 == x2 && y1 == y2) break;

        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}

void Projector::projectLines(const Object& aObject, const std::vector<Vec3>& aTransformedVertexes)
{
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
            projectLine(std::get<0>(clippedLine.value()), std::get<1>(clippedLine.value()), aObject.getColor(), aTransformedVertexes);
        }
    }
}

void Projector::projectPolygon(
    const std::tuple<Vec3, Vec3, Vec3>& polygon,
    const sf::Color& color)
{
    std::vector<std::pair<Vec2, float>> screenVertexesAndDepths =
    {
        {projectVertex(std::get<0>(polygon)), std::get<0>(polygon)[2]},
        {projectVertex(std::get<1>(polygon)), std::get<1>(polygon)[2]},
        {projectVertex(std::get<2>(polygon)), std::get<2>(polygon)[2]}
    };

    std::sort(
        screenVertexesAndDepths.begin(),
        screenVertexesAndDepths.end(),
        [&](const std::pair<Vec2, float>& a, const std::pair<Vec2, float>& b)
        {
            return a.first[1] < b.first[1];
        });
    
    std::vector<Vec2> screenVertexes =
    {
        screenVertexesAndDepths[0].first,
        screenVertexesAndDepths[1].first,
        screenVertexesAndDepths[2].first
    };

    Vec2 tmpPoint(
        screenVertexes[0][0] + (screenVertexes[1][1] - screenVertexes[0][1])
            * (screenVertexes[2][0] - screenVertexes[0][0]) / (screenVertexes[2][1] - screenVertexes[0][1]),
        screenVertexes[1][1]
    );

    std::tuple<Vec2, Vec2, Vec2> screenVertices = std::make_tuple(screenVertexes[0], screenVertexes[1], screenVertexes[2]);
    std::tuple<float, float, float> depths = std::make_tuple(
        screenVertexesAndDepths[0].second,
        screenVertexesAndDepths[1].second,
        screenVertexesAndDepths[2].second);

    for (int i = 0; i < 2; ++i)
    {
        if (std::abs(screenVertexes[i + 1][1] - screenVertexes[i][1]) <= 0.001) continue;
        int yLeftBorder = std::max(0, int(screenVertexes[i][1]));
        int yRightBorder = screenVertexes[i + 1][1];

        for (int y = yLeftBorder; y < yRightBorder && y < camera_.height; ++y)
        {
            Vec2 leftPoint, rightPoint;

            if (i == 0)
            {
                float t = (y - screenVertexes[0][1]) / (screenVertexes[1][1] - screenVertexes[0][1]);

                leftPoint = lerp(screenVertexes[0], screenVertexes[1], t);
                rightPoint = lerp(screenVertexes[0], tmpPoint, t);
            }
            else
            {
                float t = (y - screenVertexes[1][1]) / (screenVertexes[2][1] - screenVertexes[1][1]);

                leftPoint = lerp(screenVertexes[1], screenVertexes[2], t);
                rightPoint = lerp(tmpPoint, screenVertexes[2], t);
            }

            if (leftPoint[0] > rightPoint[0]) std::swap(leftPoint, rightPoint);

            for (int x = std::max(0, int(leftPoint[0])); x <= int(rightPoint[0]) && x < camera_.width; ++x)
            {
                if (!isPointInTriangle(x, y, screenVertexes[0], screenVertexes[1], screenVertexes[2])) {
                    continue;
                }

                float z = interpolateDepth(x, y, screenVertices, depths);

                if (z < zBuffer_[y * camera_.width + x]) {
                    zBuffer_[y * camera_.width + x] = z;
                    colors_[y * camera_.width + x] = color;
                }
            }
        }
    }
}

void Projector::projectPolygons(
    const Object& aObject,
    const std::vector<Vec3>& aTransformedVertexes)
{
    std::vector<int> vertexIndices = aObject.getVertexIndices();
    sf::Color color = aObject.getColor();
    int cameraWidth = camera_.width;
    int cameraHeight = camera_.height;

    for (int i = 2; i < vertexIndices.size(); i += 3)
    {
        std::vector<std::tuple<Vec3, Vec3, Vec3>> polygonsClipped =
            clipPolygon(
                aTransformedVertexes[vertexIndices[i - 2]],
                aTransformedVertexes[vertexIndices[i - 1]],
                aTransformedVertexes[vertexIndices[i]]);
        
        for (const std::tuple<Vec3, Vec3, Vec3>& polygon : polygonsClipped)
        {
            projectPolygon(polygon, color);
        }
    }
}

void Projector::projectPolygonsOutline(
    const Object& aObject,
    const std::vector<Vec3>& aTransformedVertexes)
{
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

    projectLines(newObject, aTransformedVertexes);
}

void Projector::projectObjects(sf::RenderWindow& aWindow)
{
    std::fill(zBuffer_.begin(), zBuffer_.end(), std::numeric_limits<float>::max());
    std::fill(colors_.begin(), colors_.end(), sf::Color::White);
    
    auto worldObjects = world_.getObjects();
    for (const auto& object : worldObjects) {
        projectObject(object);
    }

    for (size_t y = 0; y < camera_.height; ++y)
    {
        for (size_t x = 0; x < camera_.width; ++x)
        {
            frameBuffer_.setPixel(sf::Vector2u(x, y), colors_[y * camera_.width + x]);
        }
    }

    sf::Texture texture;
    bool _ = texture.loadFromImage(frameBuffer_);
    sf::Sprite sprite(texture);
    aWindow.draw(sprite);
}

World& Projector::getWorld()
{
    return world_;
}

Camera& Projector::getCamera()
{
    return camera_;
}

std::optional<std::tuple<Vec3, Vec3>> Projector::clipLine(Vec3 p1, Vec3 p2) const
{
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

std::vector<std::tuple<Vec3, Vec3, Vec3>> Projector::clipPolygon(const Vec3& p1, const Vec3& p2, const Vec3& p3) const
{
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

Vec3 Projector::transformVertex(const Object& aObject, const Vec3& aVertex) const
{

    Vec4 transformed =
        camera_.getTransformMatrix()
        * aObject.getTransformMatrix()
        * Vec4(aVertex[0], aVertex[1], aVertex[2], 1);
    return Vec3(transformed[0], transformed[1], transformed[2]);
}

std::vector<Vec3> Projector::transformVertexes(const Object& aObject) const
{
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

    double screen_x = (x_proj + 1.0) * camera_.width / 2;
    double screen_y = (y_proj + 1.0) * camera_.height / 2;

    return {screen_x, screen_y};
}

std::vector<Vec2> Projector::projectVertexes(const std::vector<Vec3>& aVertexes) const
{
    std::vector<Vec2> result;
    for (const auto& vertex : aVertexes) {
        result.push_back(projectVertex(vertex));
    }
    return result;
}
