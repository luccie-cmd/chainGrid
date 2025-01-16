#if !defined(_CHAINGRID_COMPONENTS_TRANSFORM_H_)
#define _CHAINGRID_COMPONENTS_TRANSFORM_H_
#include "component.h"
#include <glm/glm.hpp>

namespace chainGrid::components{
    class Transform : public Component{
        public:
            Transform(glm::u64vec2 initPos, glm::u16vec2 initRotation, glm::vec2 initScale, glm::u16vec2 initSize);
            ~Transform();
            void setTmpPos(glm::u64vec2 newPos);
            void setTmpRotation(glm::u16vec2 newRotation);
            void setTmpScale(glm::vec2 newScale);
            void setTmpSize(glm::u16vec2 newSize);
            glm::u64vec2 getPos();
            glm::u16vec2 getRotation();
            glm::vec2 getScale();
            glm::u16vec2 getSize();
            void update();
        private:
            glm::u64vec2 tmpPos;
            glm::u16vec2 tmpRotation;
            glm::vec2 tmpScale;
            glm::u16vec2 tmpSize;
            glm::u64vec2 pos;
            glm::u16vec2 rotation;
            glm::vec2 scale;
            glm::u16vec2 size;
    };
};

#endif // _CHAINGRID_COMPONENTS_TRANSFORM_H_
