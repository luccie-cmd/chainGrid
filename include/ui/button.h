#if !defined(_CHAINGRID_UI_BUTTON_H_)
#define _CHAINGRID_UI_BUTTON_H_
#include "element.h"
#include <cstdarg>
#include <functional>

namespace chainGrid::ui{
    using buttonClickProto = std::function<void(std::va_list)>;
    class Button : public Element{
        public:
            Button(glm::u64vec2 pos, glm::u16vec2 size, glm::u8vec4 color, glm::u8vec4 textColor, std::string text, rendering::Renderer* renderer, buttonClickProto buttonClick, ...);
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
            std::va_list onClickArgs;
    };
};

#endif // _CHAINGRID_UI_BUTTON_H_
