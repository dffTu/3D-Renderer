#pragma once

#include <renderer/utils/linalg.h>
#include <vector>
#include <SFML/Graphics.hpp>

enum ObjectType {
    LINES,
    LINE_STRIP,
    POLYGONS,
    POLYGONS_WITH_OUTLINE
};

class Object {
public:
    Object();
    Object(ObjectType aObjectType, const std::vector<Vec3>& aVertexes, const std::vector<int>& aVertexIndices);
    Object(const Object& aObject);
    Object(Object&& aObject);

    Object& operator=(const Object& aObject);
    Object& operator=(Object&& aObject);

    Object& setObjectType(ObjectType aObjectType);
    Object& setVertexes(const std::vector<Vec3>& aVertexes);
    Object& setVertexIndices(const std::vector<int>& aVertexIndices);
    Object& setColor(const sf::Color& aColor);

    Object& addVertex(const Vec3& aVertex, int vertexIndice);

    ObjectType getObjectType() const;
    std::vector<Vec3> getVertexes() const;
    std::vector<int> getVertexIndices() const;
    sf::Color getColor() const;
    Mat4 getTransformMatrix() const;

    void move(const Vec3& aOffset);
    void rotateX(double aRadians);
    void rotateY(double aRadians);
    void rotateZ(double aRadians);

private:
    ObjectType objectType_;
    std::vector<Vec3> vertexes_;
    std::vector<int> vertexIndices_;
    Mat4 moveMatrix_;
    Mat4 rotateMatrix_;
    sf::Color color_;
};
