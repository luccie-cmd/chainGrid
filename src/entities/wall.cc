#include <entities/wall.h>
#include <components/drawable.h>
#include <components/collision2d.h>

namespace chainGrid::entities{
    Wall::Wall(glm::u64vec2 initPos, GLFWwindow* window, rendering::Renderer* renderer) :Entity(EntityType::Wall, initPos, window, renderer){
        components::Transform* transform = reinterpret_cast<components::Transform*>(this->getComponent(components::ComponentType::Transform));
        components::Drawable* drawable = new components::Drawable(glm::u8vec4(75), rendering::RenderType::Primitive);
        components::Collision2D* collision = new components::Collision2D();
        drawable->linkTransform(transform);
        collision->linkTransform(transform);
        this->addComponent(drawable);
        this->addComponent(collision);
    }
    Wall::~Wall(){}
};