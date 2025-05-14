#pragma once

#include <renderer/world/world.h>
#include <renderer/camera/camera.h>
#include <renderer/screen/screen.h>
#include <tuple>
#include <vector>

namespace renderer
{

class Renderer {
public:
    Screen projectObjects(const World& world, const Camera& camera);

private:
    void projectObject(
        const Object& object,
        const Camera& camera,
        Screen& screen);

    void projectLines(
        const Object& object,
        const float zPlane,
        Screen& screen,
        const std::vector<Vec3>& aTransformedVertexes);
    
    void projectLine(
        Vec3 p1,
        Vec3 p2,
        Screen& screen,
        const Screen::TColor& color,
        const std::vector<Vec3>& aTransformedVertexes);
    
    void projectPolygons(
        const Object& object,
        const float zPlane,
        Screen& screen,
        const std::vector<Vec3>& aTransformedVertexes);
    
    void projectPolygon(
        const std::tuple<Vec3, Vec3, Vec3>& polygon,
        Screen& screen,
        const Screen::TColor& color);

    void projectPolygonsOutline(
        const Object& object,
        const float zPlane,
        Screen& screen,
        const std::vector<Vec3>& aTransformedVertexes);

    std::vector<Vec3> transformVertexes(
        const Object& object,
        const Camera& camera) const;

    Vec3 transformVertex(
        const Vec3& vertex,
        const Object& object,
        const Camera& camera) const;

    std::vector<Vec2> projectVertexes(
        const std::vector<Vec3>& aVertexes,
        const Screen& screen) const;

    Vec2 projectVertex(
        const Vec3& aVertex,
        const Screen& screen) const;

    std::optional<std::tuple<Vec3, Vec3>> clipLine(
        Vec3 p1,
        Vec3 p2,
        const float zPlane) const;

    std::vector<std::tuple<Vec3, Vec3, Vec3>> clipPolygon(
        const Vec3& p1,
        const Vec3& p2,
        const Vec3& p3,
        const float zPlane) const;

    std::vector<float> zBuffer_;
    static const constexpr int threadsCount_ = 8;
};

}
