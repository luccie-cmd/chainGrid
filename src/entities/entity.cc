#include <entities/entity.h>
#include <cstdio>
#include <components/transform.h>
#include <cstdlib>
#include <common.h>
#include <components/drawable.h>

namespace chainGrid::entities{
    Entity::Entity(EntityType type, glm::u64vec2 initPos, GLFWwindow* window, rendering::Renderer* renderer){
        this->__window = window;
        this->__renderer = renderer;
        this->__type = type;
        this->__components.clear();
        this->addComponent(new components::Transform(convertFromGridToScreen(initPos), glm::u16vec2(0), glm::vec2(1), glm::u16vec2(GRID_BLOCK_SIZE)));
    }
    Entity::~Entity(){
        for(components::Component* component : this->__components){
            delete component;
        }
    }
    EntityType Entity::getType(){
        return this->__type;
    }
    void Entity::addComponent(components::Component* component){
        for(components::Component* comp : this->__components){
            if(comp->getComponentType() == component->getComponentType()){
                std::printf("ERROR: Attempted to have same component twice!!!\n");
                std::exit(1);
            }
        }
        this->__components.push_back(component);
    }
    components::Component* Entity::getComponent(components::ComponentType type){
        for(components::Component* comp : this->__components){
            if(comp->getComponentType() == type){
                return comp;
            }
        }
        std::printf("ERROR: Expected component type %u to be present\n", (unsigned int)type);
        std::exit(1);
    }
    bool Entity::hasComponent(components::ComponentType type){
        for(components::Component* comp : this->__components){
            if(comp->getComponentType() == type){
                return true;
            }
        }
        return false;
    }
    void Entity::draw(){
        for(components::Component* component : this->__components){
            if(component->getComponentType() == components::ComponentType::Drawable){
                reinterpret_cast<components::Drawable*>(component)->draw(this->__renderer);
            }
        }
    }
};