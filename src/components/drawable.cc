#include <components/drawable.h>
#include <cstdio>
#include <cstdlib>
#include <common.h>

namespace chainGrid::components{
    Drawable::Drawable(glm::u8vec4 color, rendering::RenderType polyType) :Component(ComponentType::Drawable){
        this->color = color;
        this->transform = nullptr;
        this->polyType = polyType;
    }
    Drawable::~Drawable(){}
    void Drawable::update(){}
    void Drawable::linkTransform(Transform* transform){
        this->transform = transform;
    }
    void Drawable::draw(rendering::Renderer* renderer){
        if(this->transform == nullptr){
            std::printf("ERROR: No transform linked\n");
            std::exit(1);
        }
        glm::vec2 topLeft = chainGrid::convertToScreenCoords(glm::vec2(this->transform->getPos())*this->transform->getScale());
        glm::vec2 bottomRight = chainGrid::convertToScreenCoords((glm::vec2(this->transform->getPos())*this->transform->getScale())+(glm::vec2(this->transform->getSize())*this->transform->getScale()));
        // glm::mat4 mp = chainGrid::getMP(this->transform);
        glm::mat4 mp(1.0f);
        switch(polyType){
            case rendering::RenderType::Primitive: {
                renderer->renderQuad(topLeft, bottomRight, mp, this->color);
            } break;
            case rendering::RenderType::None:
            default: {
                std::printf("ERROR: Attempted to draw invalid polygon type\n");
                std::exit(1);
            } break;
        }
    }
};