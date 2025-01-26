#include "vertex.h"

Vertex::Vertex() {
    x_ = 0;
    y_ = 0;
    z_ = 0;
}

Vertex::Vertex(long double aX, long double aY, long double aZ) {
    x_ = aX;
    y_ = aY;
    z_ = aZ;
}

Vertex::Vertex(const Vec3& aVec3) {
    x_ = aVec3[0];
    y_ = aVec3[1];
    z_ = aVec3[2];
}

Vertex::Vertex(const Vertex& aVertex) {
    x_ = aVertex.getX();
    y_ = aVertex.getY();
    z_ = aVertex.getZ();
}

Vertex::Vertex(Vertex&& aVertex) {
    x_ = aVertex.getX();
    y_ = aVertex.getY();
    z_ = aVertex.getZ();
}

Vertex& Vertex::operator=(const Vertex& aVertex) {
    x_ = aVertex.getX();
    y_ = aVertex.getY();
    z_ = aVertex.getZ();
    return *this;
}

Vertex& Vertex::operator=(Vertex&& aVertex) {
    x_ = aVertex.getX();
    y_ = aVertex.getY();
    z_ = aVertex.getZ();
    return *this;
}

Vertex& Vertex::operator=(const Vec3& aVec3) {
    x_ = aVec3[0];
    y_ = aVec3[1];
    z_ = aVec3[2];
    return *this;
}

Vertex::operator Vec3() const {
    return Vec3(x_, y_, z_);
}

long double Vertex::getX() const {
    return x_;
}

long double Vertex::getY() const {
    return y_;
}

long double Vertex::getZ() const {
    return z_;
}
