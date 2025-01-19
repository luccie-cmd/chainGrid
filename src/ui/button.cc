#include <ui/button.h>
#include <common.h>

namespace chainGrid::ui{
    Button::Button(glm::u64vec2 pos, glm::u16vec2 size, glm::u8vec4 color, glm::u8vec4 textColor, std::string text, rendering::Renderer* renderer, buttonClickProto buttonClick, ...) :Element(ElementType::Button, renderer){
        va_start(this->onClickArgs, buttonClick);
        this->pos = pos;
        this->size = size;
        this->color = color;
        this->text = text;
        this->textColor = textColor;
        this->onClick = buttonClick;
    }
    Button::~Button(){
        va_end(this->onClickArgs);
    }
    void Button::render(){
        this->__renderer->renderQuad(this->pos, this->pos+glm::u64vec2(this->size), this->color);
        this->__renderer->renderText(glm::u64vec2(this->pos.x+(this->size.y/2), this->pos.y+45), this->textColor, this->text);
    }
    void Button::update(GLFWwindow* window){
        static bool mousePress = false;
        if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && !mousePress){
            glm::f64vec2 cursorPos;
            glfwGetCursorPos(window, &cursorPos.x, &cursorPos.y);
            glm::u64vec2 u64CursorPos = glm::u64vec2(cursorPos);
            if(AABBu64vec2(this->pos, this->size, u64CursorPos, glm::u64vec2(3))){
                this->onClick(this->onClickArgs);
            }
            mousePress = true;
        } else if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE){
            mousePress = false;
        }
    }
};