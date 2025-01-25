#include "object.h"
#include <renderer/utils/linalg.h>

Object::Object() {
    objectType_ = ObjectType::VERTEXES;
    vertexes_ = {};
    vertexIndices_ = {};
    rotateMatrix_ = getDefaultMat3();
    worldOffset_ = Vec3(0, 0, 0);
}

Object::Object(ObjectType aObjectType, const std::vector<Vertex>& aVertexes, const std::vector<int>& aVertexIndices) {
    objectType_ = aObjectType;
    vertexes_ = aVertexes;
    vertexIndices_ = aVertexIndices;
    rotateMatrix_ = getDefaultMat3();
    worldOffset_ = Vec3(0, 0, 0);
}

Object::Object(const Object& aObject) {
    objectType_ = aObject.objectType_;
    vertexes_ = aObject.vertexes_;
    vertexIndices_ = aObject.vertexIndices_;
    rotateMatrix_ = aObject.rotateMatrix_;
    worldOffset_ = aObject.worldOffset_;
}

Object::Object(Object&& aObject) {
    objectType_ = aObject.objectType_;
    vertexes_.swap(aObject.vertexes_);
    vertexIndices_.swap(aObject.vertexIndices_);
    rotateMatrix_.swap(aObject.rotateMatrix_);
    worldOffset_.swap(aObject.worldOffset_);
}

Object& Object::operator=(const Object& aObject) {
    objectType_ = aObject.objectType_;
    vertexes_ = aObject.vertexes_;
    vertexIndices_ = aObject.vertexIndices_;
    rotateMatrix_ = aObject.rotateMatrix_;
    worldOffset_ = aObject.worldOffset_;
    return *this;
}

Object& Object::operator=(Object&& aObject) {
    objectType_ = aObject.objectType_;
    vertexes_.swap(aObject.vertexes_);
    vertexIndices_.swap(aObject.vertexIndices_);
    rotateMatrix_.swap(aObject.rotateMatrix_);
    worldOffset_.swap(aObject.worldOffset_);
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

Mat3 Object::getRotationMatrix() const {
    return rotateMatrix_;
}

Vec3 Object::getWorldOffset() const {
    return worldOffset_;
}

void Object::move(const Vec3& aOffset) {
    worldOffset_ += aOffset;
}

void Object::rotateX(double aRadians) {
    rotateMatrix_ = getXRotationMatrix(aRadians) * rotateMatrix_;
}

void Object::rotateY(double aRadians) {
    rotateMatrix_ = getYRotationMatrix(aRadians) * rotateMatrix_;
}

void Object::rotateX(double aRadians) {
    rotateMatrix_ = getZRotationMatrix(aRadians) * rotateMatrix_;
}
