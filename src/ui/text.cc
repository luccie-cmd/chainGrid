#include <ui/text.h>
#include <common.h>

namespace chainGrid::ui{
    Text::Text(glm::u64vec2 pos, std::string text, rendering::Renderer* renderer) :Element(ElementType::Text, renderer){
        this->_pos = pos;
        this->_text = text;
    }
    void Text::render(){
        this->__renderer->renderText(this->_pos, glm::u8vec4(255), this->_text);
    }
};