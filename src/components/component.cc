#include <components/component.h>

namespace chainGrid::components{
    Component::Component(ComponentType type){
        this->__type = type;
    }
    Component::~Component(){}
    ComponentType Component::getComponentType(){
        return this->__type;
    }
};