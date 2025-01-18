#if !defined(_CHAINGRID_COMPONENTS_COMPONENT_H_)
#define _CHAINGRID_COMPONENTS_COMPONENT_H_
#include <vector>
namespace chainGrid {
namespace entities {
    class Entity;
}
}


namespace chainGrid::components{
    enum struct ComponentType : int{
        Invalid,
        Transform,
        Drawable,
        Collision2D,
    };
    class Component{
        public:
            Component(ComponentType type);
            virtual ~Component();
            virtual void update(std::vector<entities::Entity*> _entities){
                (void)_entities;
            };
            ComponentType getComponentType();
        protected:
            ComponentType __type;
    };
};

#endif // _CHAINGRID_COMPONENTS_COMPONENT_H_
