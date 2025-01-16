#include <entities/player.h>
#include <components/drawable.h>
#include <common.h>

namespace chainGrid::entities{
    Player::Player(glm::u64vec2 initPos, GLFWwindow* window, rendering::Renderer* renderer) :Entity(EntityType::Player, initPos, window, renderer, true){
        components::Drawable* drawable = new components::Drawable(glm::u8vec4(255), rendering::RenderType::Primitive);
        for(components::Component* component : this->__components){
            if(component->getComponentType() == components::ComponentType::Transform){
                drawable->linkTransform(reinterpret_cast<components::Transform*>(component));
            }
        }
        this->addComponent(drawable);
    }
    Player::~Player(){}
    void Player::handleInput(std::vector<Entity*> _entities){
        static bool lastLeftState = false;
        static bool lastRightState = false;
        static bool lastUpState = false;
        static bool lastDownState = false;
        components::Transform* transform = reinterpret_cast<components::Transform*>(this->getComponent(components::ComponentType::Transform));
        this->newPos = transform->getPos();
        if(glfwGetKey(this->__window, GLFW_KEY_LEFT) == GLFW_PRESS && lastLeftState == false){
            lastLeftState = true;
            this->newPos -= glm::u64vec2((1*GRID_BLOCK_SIZE)+GRID_LINE_SIZE, 0);
        } else if(glfwGetKey(this->__window, GLFW_KEY_LEFT) == GLFW_RELEASE){
            lastLeftState = false;
        }
        if(glfwGetKey(this->__window, GLFW_KEY_RIGHT) == GLFW_PRESS && lastRightState == false){
            lastRightState = true;
            this->newPos += glm::u64vec2((1*GRID_BLOCK_SIZE)+GRID_LINE_SIZE, 0);
        } else if(glfwGetKey(this->__window, GLFW_KEY_RIGHT) == GLFW_RELEASE){
            lastRightState = false;
        }
        if(glfwGetKey(this->__window, GLFW_KEY_UP) == GLFW_PRESS && lastUpState == false){
            lastUpState = true;
            this->newPos -= glm::u64vec2(0, (1*GRID_BLOCK_SIZE)+GRID_LINE_SIZE);
        } else if(glfwGetKey(this->__window, GLFW_KEY_UP) == GLFW_RELEASE){
            lastUpState = false;
        }
        if(glfwGetKey(this->__window, GLFW_KEY_DOWN) == GLFW_PRESS && lastDownState == false){
            lastDownState = true;
            this->newPos += glm::u64vec2(0, (1*GRID_BLOCK_SIZE)+GRID_LINE_SIZE);
        } else if(glfwGetKey(this->__window, GLFW_KEY_DOWN) == GLFW_RELEASE){
            lastDownState = false;
        }
        if(!this->collidesWith(_entities)){
            transform->setTmpPos(this->newPos);
        }
    }
    bool Player::collidesWith(std::vector<Entity*> _entities){
        for(Entity* entity : _entities){
            if(entity->hasColission()){
                if(reinterpret_cast<components::Transform*>(entity->getComponent(components::ComponentType::Transform))->getPos() == this->newPos){
                    return true;
                }
            }
        }
        return false;
    }
    void Player::update(std::vector<Entity*> _entities){
        this->handleInput(_entities);
        for(components::Component* component : this->__components){
            component->update();
        }
    }
};