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

long double Vertex::getX() const {
    return x_;
}

long double Vertex::getY() const {
    return y_;
}

long double Vertex::getZ() const {
    return z_;
}
