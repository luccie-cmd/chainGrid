#include <entities/player.h>
#include <components/drawable.h>
#include <components/collision2d.h>
#include <common.h>

namespace chainGrid::entities{
    Player::Player(glm::u64vec2 initPos, GLFWwindow* window, rendering::Renderer* renderer) :Entity(EntityType::Player, initPos, window, renderer){
        components::Transform* transform = reinterpret_cast<components::Transform*>(this->getComponent(components::ComponentType::Transform));
        components::Drawable* drawable = new components::Drawable(glm::u8vec4(255), rendering::RenderType::Primitive);
        drawable->linkTransform(transform);
        this->addComponent(drawable);
        components::Collision2D* collision = new components::Collision2D();
        collision->linkTransform(transform);
        collision->addOnNoCollision([this]() { this->onNoCollision(); });
        collision->addOnCollision([this](Entity* entity) { this->onCollision(entity); });
        collision->addIgnoredType(EntityType::Player);
        this->addComponent(collision);
    }
    Player::~Player(){}
    void Player::handleInput(){
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
        this->oldPos = transform->getPos();
        transform->setTmpPos(this->newPos);
    }
    void Player::onNoCollision(){}
    void Player::onCollision(Entity* entity){
        if(entity->getType() == EntityType::Wall){
            components::Transform* transform = reinterpret_cast<components::Transform*>(this->getComponent(components::ComponentType::Transform));
            transform->setTmpPos(this->oldPos);
            transform->update({});
        }
    }
    void Player::update(std::vector<Entity*> _entities){
        this->handleInput();
        for(components::Component* component : this->__components){
            component->update(_entities);
        }
    }
};