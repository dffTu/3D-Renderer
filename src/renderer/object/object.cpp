#include "object.h"

Object::Object() {
    objectType_ = ObjectType::VERTEXES;
    vertexes_ = {};
    vertexIndices_ = {};
}

Object::Object(ObjectType aObjectType, const std::vector<Vertex>& aVertexes, const std::vector<int>& aVertexIndices) {
    objectType_ = aObjectType;
    vertexes_ = aVertexes;
    vertexIndices_ = aVertexIndices;
}

Object::Object(const Object& aObject) {
    objectType_ = aObject.objectType_;
    vertexes_ = aObject.vertexes_;
    vertexIndices_ = aObject.vertexIndices_;
}

Object::Object(Object&& aObject) {
    objectType_ = aObject.objectType_;
    vertexes_.swap(aObject.vertexes_);
    vertexIndices_.swap(aObject.vertexIndices_);
}

Object& Object::operator=(const Object& aObject) {
    objectType_ = aObject.objectType_;
    vertexes_ = aObject.vertexes_;
    vertexIndices_ = aObject.vertexIndices_;
    return *this;
}

Object& Object::operator=(Object&& aObject) {
    objectType_ = aObject.objectType_;
    vertexes_.swap(aObject.vertexes_);
    vertexIndices_.swap(aObject.vertexIndices_);
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
