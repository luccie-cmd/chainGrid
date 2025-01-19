#include <components/collision2d.h>
#include <algorithm>
#include <common.h>

namespace chainGrid::components{
    Collision2D::Collision2D() :Component(ComponentType::Collision2D){
        this->transform = nullptr;
        this->onCollision = nullptr;
        this->onNoCollision = nullptr;
        this->ignoredTypes.clear();
        this->ignoredTypes.shrink_to_fit();
    }
    Collision2D::~Collision2D(){}
    void Collision2D::addOnCollision(onCollisionPrototype onCollision){
        this->onCollision = onCollision;
    }
    void Collision2D::addOnNoCollision(onNoCollisionPrototype onNoCollision){
        this->onNoCollision = onNoCollision;
    }
    void Collision2D::addIgnoredType(entities::EntityType ignoredType){
        this->ignoredTypes.push_back(ignoredType);
    }
    void Collision2D::linkTransform(Transform* transform){
        this->transform = transform;
    }
    void Collision2D::update(std::vector<entities::Entity*> entities){
        for(entities::Entity* entity : entities){
            Transform* entityTransform = reinterpret_cast<Transform*>(entity->getComponent(ComponentType::Transform));
            if(entity->hasComponent(ComponentType::Collision2D) && 
                AABBu64vec2(entityTransform->getPos(), entityTransform->getSize(), this->transform->getPos(), this->transform->getSize()) && 
                std::find(this->ignoredTypes.begin(), this->ignoredTypes.end(), entity->getType()) == this->ignoredTypes.end()
            ){
                if(this->onCollision){
                    this->onCollision(entity);
                }
                return;
            }
        }
        if(this->onNoCollision){
            this->onNoCollision();
        }
    }
};