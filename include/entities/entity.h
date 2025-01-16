#if !defined(_CHAINGRID_ENTITIES_ENTITY_H_)
#define _CHAINGRID_ENTITIES_ENTITY_H_
#include <cstdint>
#include <glm/glm.hpp>
#include <vector>
#include <components/component.h>
#include <GLFW/glfw3.h>
#include <rendering/types.h>
#include <rendering/renderer.h>

namespace chainGrid::entities{
    enum struct EntityType{
        Player,
        Wall,
        None,
    };
    class Entity{
        public:
            Entity(EntityType type, glm::u64vec2 initPos, GLFWwindow* window, rendering::Renderer* renderer, bool hasCollision);
            virtual ~Entity() = 0;
            virtual void update(std::vector<Entity*> _entities){
                (void)_entities;
            }
            void draw();
            void addComponent(components::Component* component);
            void addComponent(components::ComponentType component);
            void removeComponent(components::ComponentType type);
            bool hasComponent(components::ComponentType type);
            bool hasColission();
            components::Component* getComponent(components::ComponentType type);
            EntityType getType();
        protected:
            bool __hasColission;
            EntityType __type;
            GLFWwindow* __window;
            std::vector<components::Component*> __components;
            rendering::Renderer* __renderer;
    };
};

#endif // _CHAINGRID_ENTITIES_ENTITY_H_
