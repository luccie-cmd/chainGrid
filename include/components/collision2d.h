#if !defined(_CHAINGRID_COMPONENTS_COLLISION2D_H_)
#define _CHAINGRID_COMPONENTS_COLLISION2D_H_
#include "component.h"
#include "transform.h"
#include <entities/entity.h>
#include <functional>

namespace chainGrid::components{
    using onCollisionPrototype = std::function<void(entities::Entity*)>;
    using onNoCollisionPrototype = std::function<void()>;
    class Collision2D : public Component{
        public:
            Collision2D(Transform* transform);
            Collision2D();
            ~Collision2D();
            void addOnCollision(onCollisionPrototype onCollision);
            void addOnNoCollision(onNoCollisionPrototype onNoCollision);
            void addIgnoredType(entities::EntityType ignoredType);
            void linkTransform(Transform* transform);
            void update(std::vector<entities::Entity*> _entities) override;
        private:
            std::vector<entities::EntityType> ignoredTypes;
            onNoCollisionPrototype onNoCollision;
            onCollisionPrototype onCollision;
            Transform* transform;
    };
};

#endif // _CHAINGRID_COMPONENTS_COLLISION2D_H_
