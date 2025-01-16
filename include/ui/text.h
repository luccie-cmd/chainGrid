#if !defined(_CHAINGRID_UI_TEXT_H_)
#define _CHAINGRID_UI_TEXT_H_
#include "element.h"
#include <glm/vec2.hpp>
#include <string>

namespace chainGrid::ui{
    class Text : public Element{
        public:
            Text(glm::u64vec2 pos, std::string text, rendering::Renderer* renderer);
            ~Text();
            void render() override;
        private:
            glm::u64vec2 _pos;
            std::string _text;
    };
};

#endif // _CHAINGRID_UI_TEXT_H_
