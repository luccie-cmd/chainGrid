#include <ui/text.h>
#include <common.h>

namespace chainGrid::ui{
    Text::Text(glm::u64vec2 pos, std::string text, rendering::Renderer* renderer) :Element(ElementType::Text, renderer){
        this->_pos = pos;
        this->_text = text;
    }
    Text::~Text(){}
    void Text::render(){
        this->__renderer->renderText(convertToScreenCoords(this->_pos), glm::u8vec4(255), this->_text);
        // this->__renderer->renderQuad(glm::vec2(convertToScreenCoords(this->_pos)), glm::vec2(convertToScreenCoords(this->_pos+(this->_text.size()*10))), glm::mat4(1), glm::u8vec4(255));
    }
};