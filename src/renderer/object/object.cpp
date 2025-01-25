#include "object.h"
#include <renderer/utils/linalg.h>

Object::Object() {
    objectType_ = ObjectType::VERTEXES;
    vertexes_ = {};
    vertexIndices_ = {};
    transformMatrix_ = getDefaultMat4();
}

Object::Object(ObjectType aObjectType, const std::vector<Vertex>& aVertexes, const std::vector<int>& aVertexIndices) {
    objectType_ = aObjectType;
    vertexes_ = aVertexes;
    vertexIndices_ = aVertexIndices;
    transformMatrix_ = getDefaultMat4();
}

Object::Object(const Object& aObject) {
    objectType_ = aObject.objectType_;
    vertexes_ = aObject.vertexes_;
    vertexIndices_ = aObject.vertexIndices_;
    transformMatrix_ = aObject.transformMatrix_;
}

Object::Object(Object&& aObject) {
    objectType_ = aObject.objectType_;
    vertexes_.swap(aObject.vertexes_);
    vertexIndices_.swap(aObject.vertexIndices_);
    transformMatrix_.swap(aObject.transformMatrix_);
}

Object& Object::operator=(const Object& aObject) {
    objectType_ = aObject.objectType_;
    vertexes_ = aObject.vertexes_;
    vertexIndices_ = aObject.vertexIndices_;
    transformMatrix_ = aObject.transformMatrix_;
    return *this;
}

Object& Object::operator=(Object&& aObject) {
    objectType_ = aObject.objectType_;
    vertexes_.swap(aObject.vertexes_);
    vertexIndices_.swap(aObject.vertexIndices_);
    transformMatrix_.swap(aObject.transformMatrix_);
    return *this;
}

Object& Object::setObjectType(ObjectType aObjectType) {
    objectType_ = aObjectType;
    return *this;
}

Object& Object::setVertexes(const std::vector<Vertex>& aVertexes) {
    vertexes_ = aVertexes;
    return *this;
}

Object& Object::setVertexIndices(const std::vector<int>& aVertexIndices) {
    vertexIndices_ = aVertexIndices;
    return *this;
}

Object& Object::addVertex(const Vertex& aVertex, int vertexIndice) {
    vertexes_.push_back(aVertex);
    vertexIndices_.push_back(vertexIndice);
    return *this;
}

std::vector<Vertex> Object::getVertexes() const {
    return vertexes_;
}

std::vector<int> Object::getVertexIndices() const {
    return vertexIndices_;
}

Mat4 Object::getTransformMatrix() const {
    return transformMatrix_;
}

void Object::move(const Vec3& aOffset) {
    transformMatrix_ = getMoveMatrix(aOffset) * transformMatrix_;
}

void Object::rotateX(double aRadians) {
    transformMatrix_ = getXRotationMatrix(aRadians) * transformMatrix_;
}

void Object::rotateY(double aRadians) {
    transformMatrix_ = getYRotationMatrix(aRadians) * transformMatrix_;
}

void Object::rotateZ(double aRadians) {
    transformMatrix_ = getZRotationMatrix(aRadians) * transformMatrix_;
}
