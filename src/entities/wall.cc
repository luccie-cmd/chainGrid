#include <entities/wall.h>
#include <components/drawable.h>

namespace chainGrid::entities{
    Wall::Wall(glm::u64vec2 initPos, GLFWwindow* window, rendering::Renderer* renderer) :Entity(EntityType::Wall, initPos, window, renderer, true){
        components::Drawable* drawable = new components::Drawable(glm::u8vec4(75), rendering::RenderType::Primitive);
        for(components::Component* component : this->__components){
            if(component->getComponentType() == components::ComponentType::Transform){
                drawable->linkTransform(reinterpret_cast<components::Transform*>(component));
            }
        }
        this->addComponent(drawable);
    }
    Wall::~Wall(){}
};