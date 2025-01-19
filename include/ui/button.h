#if !defined(_CHAINGRID_UI_BUTTON_H_)
#define _CHAINGRID_UI_BUTTON_H_
#include "element.h"
#include <cstdarg>
#include <functional>
#include <typeindex>
#include <any>

namespace chainGrid::ui{
    using buttonClickProto = std::function<void(std::vector<std::any>)>;
    class Button : public Element{
        public:
            Button(glm::u64vec2 pos, glm::u16vec2 size, glm::u8vec4 color, glm::u8vec4 textColor, std::string text, rendering::Renderer* renderer, std::vector<std::type_index> types, buttonClickProto buttonClick, ...);
            ~Button();
            void render() override;
            void update(GLFWwindow* window) override;
        private:
            buttonClickProto onClick;
            glm::u64vec2 pos;
            glm::u16vec2 size;
            glm::u8vec4 color;
            glm::u8vec4 textColor;
            std::string text;
            std::vector<std::type_index> types;
            std::vector<std::any> onClickArgs;
    };
};

#endif // _CHAINGRID_UI_BUTTON_H_
