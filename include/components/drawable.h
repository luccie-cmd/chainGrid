#if !defined(_CHAINGRID_COMPONENTS_DRAWABLE_H_)
#define _CHAINGRID_COMPONENTS_DRAWABLE_H_
#include "component.h"
#include <glm/glm.hpp>
#include "transform.h"
#include <rendering/types.h>
#include <rendering/renderer.h>

namespace chainGrid::components{
    class Drawable : public Component{
        public:
            Drawable(glm::u8vec4 color, rendering::RenderType polyType);
            ~Drawable();
            void update();
            void draw(rendering::Renderer* renderer);
            void linkTransform(Transform* transform);
            Transform* getTransform();
        private:
            glm::u8vec4 color;
            Transform* transform;
            rendering::RenderType polyType;
    };
};

#endif // _CHAINGRID_COMPONENTS_DRAWABLE_H_
