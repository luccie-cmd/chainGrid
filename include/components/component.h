#if !defined(_CHAINGRID_COMPONENTS_COMPONENT_H_)
#define _CHAINGRID_COMPONENTS_COMPONENT_H_

namespace chainGrid::components{
    enum struct ComponentType{
        Invalid,
        Transform,
        Drawable,
    };
    class Component{
        public:
            Component(ComponentType type);
            virtual ~Component();
            virtual void update() = 0;
            ComponentType getComponentType();
        protected:
            ComponentType __type;
    };
};

#endif // _CHAINGRID_COMPONENTS_COMPONENT_H_
