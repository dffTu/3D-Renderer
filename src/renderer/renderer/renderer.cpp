#include "renderer.h"

namespace renderer
{

Screen Renderer::projectObjects(const World& world, const Camera& camera)
{
    Screen screen(camera.height, camera.width);
    
    if (screen.height * screen.width > zBuffer_.size())
    {
        zBuffer_.resize(screen.height * screen.width);
    }

    std::fill(zBuffer_.begin(), zBuffer_.end(), std::numeric_limits<float>::max());
    
    auto worldObjects = world.getObjects();
    for (const auto& object : worldObjects) {
        projectObject(object, camera, screen);
    }

    return screen;
}

void Renderer::projectObject(const Object& object, const Camera& camera, Screen& screen)
{
    std::vector<Vec3> transformedVertexes = transformVertexes(object, camera);

    switch (object.getObjectType())
    {
        case ObjectType::LINES:
        case ObjectType::LINE_STRIP:
            projectLines(object, camera.zPlane, screen, transformedVertexes);
            return;
        case ObjectType::POLYGONS:
            projectPolygons(object, camera.zPlane, screen, transformedVertexes);
            return;
        case ObjectType::POLYGONS_WITH_OUTLINE:
            projectPolygons(object, camera.zPlane, screen, transformedVertexes);
            projectPolygonsOutline(object, camera.zPlane, screen, transformedVertexes);
            return;
        default:
            assert(false && "Unknown ObjectType!");
            return;
    }
}

void Renderer::projectLines(
    const Object& object,
    const float zPlane,
    Screen& screen,
    const std::vector<Vec3>& aTransformedVertexes)
{
    std::vector<int> vertexIndices = object.getVertexIndices();

    size_t delta;

    if (object.getObjectType() == ObjectType::LINES) delta = 2;
    else if (object.getObjectType() == ObjectType::LINE_STRIP) delta = 1;
    else assert(false && "Unknown ObjectType for projecting lines!");

    for (size_t i = 1; i < vertexIndices.size(); i += delta)
    {
        std::optional<std::tuple<Vec3, Vec3>> clippedLine =
            clipLine(
                aTransformedVertexes[vertexIndices[i - 1]],
                aTransformedVertexes[vertexIndices[i]],
                zPlane);

        if (clippedLine.has_value())
        {
            projectLine(
                std::get<0>(clippedLine.value()),
                std::get<1>(clippedLine.value()),
                screen,
                object.getColor(),
                aTransformedVertexes);
        }
    }
}

void Renderer::projectLine(
    const Vec3& a,
    const Vec3& b,
    Screen& screen,
    const Screen::TColor& color,
    const std::vector<Vec3>& aTransformedVertexes)
{
    Vec2 p1 = projectVertex(a, screen);
    Vec2 p2 = projectVertex(b, screen);

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

    float z = a[2];
    float zStep = (p2[2] - p1[2]) / std::max(dx, dy);

    while (true) {

        if (0 <= x1 && x1 < screen.width && 0 <= y1 && y1 < screen.height && (z < zBuffer_[y1 * screen.width + x1] || std::abs(z - zBuffer_[y1 * screen.width + x1]) <= 1))
        {
            zBuffer_[y1 * screen.width + x1] = z;
            screen.setPixel(x1, y1, color);
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

void Renderer::projectPolygons(
    const Object& object,
    const float zPlane,
    Screen& screen,
    const std::vector<Vec3>& aTransformedVertexes)
{
    std::vector<int> vertexIndices = object.getVertexIndices();

    for (int i = 2; i < vertexIndices.size(); i += 3)
    {
        std::vector<std::tuple<Vec3, Vec3, Vec3>> polygonsClipped =
            clipPolygon(
                aTransformedVertexes[vertexIndices[i - 2]],
                aTransformedVertexes[vertexIndices[i - 1]],
                aTransformedVertexes[vertexIndices[i]],
                zPlane);
        
        for (const std::tuple<Vec3, Vec3, Vec3>& polygon : polygonsClipped)
        {
            projectPolygon(polygon, screen, object.getColor());
        }
    }
}

void Renderer::projectPolygon(
    const std::tuple<Vec3, Vec3, Vec3>& polygon,
    Screen& screen,
    const Screen::TColor& color)
{
    std::vector<std::pair<Vec2, float>> screenVertexesAndDepths =
    {
        {projectVertex(std::get<0>(polygon), screen), std::get<0>(polygon)[2]},
        {projectVertex(std::get<1>(polygon), screen), std::get<1>(polygon)[2]},
        {projectVertex(std::get<2>(polygon), screen), std::get<2>(polygon)[2]}
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

        for (int y = yLeftBorder; y < yRightBorder && y < screen.height; ++y)
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

            for (int x = std::max(0, int(leftPoint[0])); x <= int(rightPoint[0]) && x < screen.width; ++x)
            {
                if (!isPointInTriangle(x, y, screenVertexes[0], screenVertexes[1], screenVertexes[2])) {
                    continue;
                }

                float z = interpolateDepth(x, y, screenVertices, depths);

                if (z < zBuffer_[y * screen.width + x]) {
                    zBuffer_[y * screen.width + x] = z;
                    screen.setPixel(x, y, color);
                }
            }
        }
    }
}

void Renderer::projectPolygonsOutline(
    const Object& object,
    const float zPlane,
    Screen& screen,
    const std::vector<Vec3>& aTransformedVertexes)
{
    std::vector<int> newIndices;
    std::vector<int> vertexIndices = object.getVertexIndices();

    for (int i = 2; i < vertexIndices.size(); i += 3)
    {
        newIndices.push_back(vertexIndices[i - 2]);
        newIndices.push_back(vertexIndices[i - 1]);
        newIndices.push_back(vertexIndices[i - 2]);
        newIndices.push_back(vertexIndices[i]);
        newIndices.push_back(vertexIndices[i - 1]);
        newIndices.push_back(vertexIndices[i]);
    }

    Object newObject(ObjectType::LINES, object.getVertexes(), newIndices);

    projectLines(newObject, zPlane, screen, aTransformedVertexes);
}

std::vector<Vec3> Renderer::transformVertexes(
    const Object& object,
    const Camera& camera) const
{
    std::vector<Vec3> result;
    for (const Vec3& vertex: object.getVertexes()) {
        result.push_back(transformVertex(vertex, object, camera));
    }
    return result;
}

Vec3 Renderer::transformVertex(
    const Vec3& vertex,
    const Object& object,
    const Camera& camera) const
{

    Vec4 transformed =
        camera.getTransformMatrix()
        * object.getTransformMatrix()
        * Vec4(vertex[0], vertex[1], vertex[2], 1);
    return Vec3(transformed[0], transformed[1], transformed[2]);
}

std::vector<Vec2> Renderer::projectVertexes(
    const std::vector<Vec3>& aVertexes,
    const Screen& screen) const
{
    std::vector<Vec2> result;
    for (const auto& vertex : aVertexes) {
        result.push_back(projectVertex(vertex, screen));
    }
    return result;
}

Vec2 Renderer::projectVertex(
    const Vec3& aVertex,
    const Screen& screen) const
{
    float z = aVertex[2];
    if (z <= 0) z = 0.0001;

    float fov = 90.0;
    float scale = 1.0 / tan(fov * M_PI / 360.0);

    float x_proj = aVertex[0] * scale / z;
    float y_proj = -aVertex[1] * scale / z;

    float screen_x = (x_proj + 1.0) * screen.width / 2;
    float screen_y = (y_proj + 1.0) * screen.height / 2;

    return {screen_x, screen_y};
}

std::optional<std::tuple<Vec3, Vec3>> Renderer::clipLine(Vec3 p1, Vec3 p2, const float zPlane) const
{
    std::vector<Vec2> result;

    bool firstInside = p1[2] >= zPlane;
    bool secondInside = p2[2] >= zPlane;
    
    if (firstInside && secondInside)
    {
        return std::make_tuple(p1, p2);
    }
    else if (!firstInside && !secondInside)
    {
        return std::nullopt;
    }

    if (!firstInside) swap(p1, p2);
    float t = (zPlane - p1[2]) / (p1[2] - p2[2]);
    return std::make_tuple(p1, p1 + t * (p1 - p2));
}

std::vector<std::tuple<Vec3, Vec3, Vec3>> Renderer::clipPolygon(
    const Vec3& p1,
    const Vec3& p2,
    const Vec3& p3,
    const float zPlane) const
{
    std::vector<std::tuple<Vec3, Vec3, Vec3>> result;
    std::vector<Vec3> vertexes{p1, p2, p3};

    std::vector<Vec3> vertices;

    for (size_t i = 0; i < vertexes.size(); ++i) {
        const Vec3& current = vertexes[i];
        const Vec3& next = vertexes[(i + 1) % vertexes.size()];

        bool currentInside = (current[2] >= zPlane);
        bool nextInside = (next[2] >= zPlane);

        if (!currentInside && !nextInside)
        {
            continue;
        }
        else if (currentInside && nextInside) {
            vertices.push_back(next);
        }
        else
        {
            float t = (zPlane - current[2]) / (next[2] - current[2]);

            Vec3 intersection{
                current[0] + t * (next[0] - current[0]),
                current[1] + t * (next[1] - current[1]),
                zPlane
            };

            vertices.push_back(intersection);

            if (!currentInside && nextInside) {
                vertices.push_back(next);
            }
        }
    }

    for (int i = 2; i < vertices.size(); ++i) {
        result.push_back(std::make_tuple(vertices[i - 1], vertices[i], vertices[0]));
    }

    return result;
}

}
