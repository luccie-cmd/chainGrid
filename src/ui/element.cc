#include <ui/element.h>

namespace chainGrid::ui{
    Element::Element(ElementType type, rendering::Renderer* renderer){
        this->__type = type;
        this->__renderer = renderer;
    }
};