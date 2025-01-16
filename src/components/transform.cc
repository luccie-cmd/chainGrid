#include <components/transform.h>

namespace chainGrid::components{
    Transform::Transform(glm::u64vec2 initPos, glm::u16vec2 initRotation, glm::vec2 initScale, glm::u16vec2 initSize) :Component(ComponentType::Transform){
        this->pos = initPos;
        this->rotation = initRotation;
        this->scale = initScale;
        this->size = initSize;
        this->tmpPos = initPos;
        this->tmpRotation = initRotation;
        this->tmpScale = initScale;
        this->tmpSize = initSize;
    }
    Transform::~Transform(){}
    glm::u64vec2 Transform::getPos(){
        return this->pos;
    }
    glm::vec2 Transform::getScale(){
        return this->scale;
    }
    glm::u16vec2 Transform::getRotation(){
        return this->rotation;
    }
    glm::u16vec2 Transform::getSize(){
        return this->size;
    }
    void Transform::setTmpPos(glm::u64vec2 newPos){
        this->tmpPos = newPos;
    }
    void Transform::update(){
        this->pos = this->tmpPos;
        this->rotation = this->tmpRotation;
        this->scale = this->tmpScale;
        this->size = this->tmpSize;
    }
};