#include <ui/button.h>
#include <common.h>
#include <typeindex>

namespace chainGrid::ui{
    Button::Button(glm::u64vec2 pos, glm::u16vec2 size, glm::u8vec4 color, glm::u8vec4 textColor, std::string text, rendering::Renderer* renderer, std::vector<std::type_index> types, buttonClickProto buttonClick, ...) :Element(ElementType::Button, renderer){
        this->types = types;
        this->pos = pos;
        this->size = size;
        this->color = color;
        this->text = text;
        this->textColor = textColor;
        this->onClick = buttonClick;
        va_list args;
        va_start(args, buttonClick);
        for(size_t i = 0; i < this->types.size(); ++i){
            if(this->types.at(i) == typeid(uint64_t)){
                this->onClickArgs.push_back(va_arg(args, uint64_t));
            } else{
                std::printf("TODO: Support more types within Button::Button() attempted type: `%s`\n", this->types.at(i).name());
                std::exit(1);
            }
        }
        va_end(args);
    }
    Button::~Button(){}
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