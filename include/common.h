#if !defined(_CHAINGRID_COMMON_H_)
#define _CHAINGRID_COMMON_H_
#include <glm/glm.hpp>
#include "components/transform.h"
#include <string>
#define GRID_BLOCK_SIZE 64
#define GRID_WIDTH      28
#define GRID_HEIGHT     16
#define GRID_OFFSET     1
#define GRID_LINE_SIZE  2

namespace chainGrid{
    glm::vec2 convertToScreenCoords(glm::u8vec2 coords);
    glm::vec2 convertToScreenCoords(glm::u16vec2 coords);
    glm::vec2 convertToScreenCoords(glm::u64vec2 coords);
    glm::vec2 convertToScreenCoords(glm::vec2 coords);
    glm::u64vec2 convertFromGridToScreen(glm::u64vec2 coords);
    void setScreenSize(glm::u16vec2 screenSize);
    glm::mat4 getMP(components::Transform* transform);
    std::string readfile(std::string path);
};

#endif // _CHAINGRID_COMMON_H_