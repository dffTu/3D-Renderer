#include "vertex.h"
#include <vector>

enum ObjectType {
    VERTEXES,
    LINE,
    POLYGONS
};

class Object {
public:
    Object();
    Object(ObjectType aObjectType, const std::vector<Vertex>& aVertexes, const std::vector<int>& aVertexIndices);
    Object(const Object& aObject);
    Object(Object&& aObject);

    Object& operator=(const Object& aObject);
    Object& operator=(Object&& aObject);

    Object& setObjectType(ObjectType aObjectType);
    Object& setVertexes(const std::vector<Vertex>& aVertexes);
    Object& setVertexIndices(const std::vector<int>& aVertexIndices);

    Object& addVertex(const Vertex& aVertex, int vertexIndice);

    std::vector<Vertex> getVertexes() const;
    std::vector<int> getVertexIndices() const;
    Mat3 getRotationMatrix() const;
    Vec3 getWorldOffset() const;

    void move(const Vec3& aOffset);
    void rotateX(double aRadians);
    void rotateY(double aRadians);
    void rotateX(double aRadians);

private:
    ObjectType objectType_;
    std::vector<Vertex> vertexes_;
    std::vector<int> vertexIndices_;
    Mat3 rotateMatrix_;
    Vec3 worldOffset_;
};
