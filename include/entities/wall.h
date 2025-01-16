#if !defined(_CHAINGRID_ENTITIES_WALL_H_)
#define _CHAINGRID_ENTITIES_WALL_H_
#include <cstdint>
#include "entity.h"

namespace chainGrid::entities{
    class Wall : public Entity{
        public:
            Wall(glm::u64vec2 initPos, GLFWwindow* window, rendering::Renderer* renderer);
            ~Wall();
    };
};

#endif // _CHAINGRID_ENTITIES_WALL_H_
