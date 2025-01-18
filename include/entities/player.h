#if !defined(_CHAINGRID_ENTITIES_PLAYER_H_)
#define _CHAINGRID_ENTITIES_PLAYER_H_
#include <cstdint>
#include "entity.h"

namespace chainGrid::entities{
    class Player : public Entity{
        public:
            Player(glm::u64vec2 initPos, GLFWwindow* window, rendering::Renderer* renderer);
            ~Player();
            void update(std::vector<Entity*> _entities) override;
        private:
            void handleInput();
            void onNoCollision();
            void onCollision(Entity* entity);
            glm::u64vec2 newPos, oldPos;
    };
};

#endif // _CHAINGRID_ENTITIES_PLAYER_H_
