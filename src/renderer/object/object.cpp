#include "object.h"
#include <renderer/utils/linalg.h>

namespace renderer
{

Object::Object() {
    objectType_ = ObjectType::LINES;
    vertexes_ = {};
    vertexIndices_ = {};
    rotateMatrix_ = getDefaultMat4();
    moveMatrix_ = getDefaultMat4();
    color_ = sf::Color::Black;
}

Object::Object(ObjectType aObjectType, const std::vector<Vec3>& aVertexes, const std::vector<int>& aVertexIndices) {
    objectType_ = aObjectType;
    vertexes_ = aVertexes;
    vertexIndices_ = aVertexIndices;
    rotateMatrix_ = getDefaultMat4();
    moveMatrix_ = getDefaultMat4();
    color_ = sf::Color::Black;
}

Object::Object(const Object& aObject) {
    objectType_ = aObject.objectType_;
    vertexes_ = aObject.vertexes_;
    vertexIndices_ = aObject.vertexIndices_;
    rotateMatrix_ = aObject.rotateMatrix_;
    moveMatrix_ = aObject.moveMatrix_;
    color_ = aObject.color_;
}

Object::Object(Object&& aObject) {
    objectType_ = aObject.objectType_;
    vertexes_.swap(aObject.vertexes_);
    vertexIndices_.swap(aObject.vertexIndices_);
    rotateMatrix_.swap(aObject.rotateMatrix_);
    moveMatrix_.swap(aObject.moveMatrix_);
    color_ = aObject.color_;
}

Object& Object::operator=(const Object& aObject) {
    objectType_ = aObject.objectType_;
    vertexes_ = aObject.vertexes_;
    vertexIndices_ = aObject.vertexIndices_;
    rotateMatrix_ = aObject.rotateMatrix_;
    moveMatrix_ = aObject.moveMatrix_;
    color_ = aObject.color_;
    return *this;
}

Object& Object::operator=(Object&& aObject) {
    objectType_ = aObject.objectType_;
    vertexes_.swap(aObject.vertexes_);
    vertexIndices_.swap(aObject.vertexIndices_);
    rotateMatrix_.swap(aObject.rotateMatrix_);
    moveMatrix_.swap(aObject.moveMatrix_);
    color_ = aObject.color_;
    return *this;
}

Object& Object::setObjectType(ObjectType aObjectType) {
    objectType_ = aObjectType;
    return *this;
}

Object& Object::setVertexes(const std::vector<Vec3>& aVertexes) {
    vertexes_ = aVertexes;
    return *this;
}

Object& Object::setVertexIndices(const std::vector<int>& aVertexIndices) {
    vertexIndices_ = aVertexIndices;
    return *this;
}

Object& Object::setColor(const sf::Color& aColor) {
    color_ = aColor;
    return *this;
}

Object& Object::addVertex(const Vec3& aVertex, int vertexIndice) {
    vertexes_.push_back(aVertex);
    vertexIndices_.push_back(vertexIndice);
    return *this;
}

ObjectType Object::getObjectType() const {
    return objectType_;
}

std::vector<Vec3> Object::getVertexes() const {
    return vertexes_;
}

std::vector<int> Object::getVertexIndices() const {
    return vertexIndices_;
}

sf::Color Object::getColor() const {
    return color_;
}

Mat4 Object::getTransformMatrix() const {
    return moveMatrix_ * rotateMatrix_;
}

void Object::move(const Vec3& aOffset) {
    moveMatrix_ = getMoveMatrix(aOffset) * moveMatrix_;
}

void Object::rotateX(double aRadians) {
    rotateMatrix_ = getXRotationMatrix(aRadians) * rotateMatrix_;
}

void Object::rotateY(double aRadians) {
    rotateMatrix_ = getYRotationMatrix(aRadians) * rotateMatrix_;
}

void Object::rotateZ(double aRadians) {
    rotateMatrix_ = getZRotationMatrix(aRadians) * rotateMatrix_;
}

}
