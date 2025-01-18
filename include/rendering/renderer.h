#if !defined(_CHAINGRID_RENDERING_RENDERER_H_)
#define _CHAINGRID_RENDERING_RENDERER_H_
#include <glm/glm.hpp>
#include "types.h"
#include <GLFW/glfw3.h>
#include <map>
#include <string>
#include <ft2build.h>
#include FT_FREETYPE_H

namespace chainGrid::rendering{
    struct Character{
        union {
#if defined(OPENGL_RENDERER)
            uint32_t textureID;
#elif defined(VULKAN_RENDERER)
            struct {
                VkImage image;
                VkImageView imageView;
                VkSampler sampler;
            } vulkanTexture;
#else
#error "No rendering backend specified"
#endif
        };
        glm::u32vec2 size;
        glm::u32vec2 bearing;
        uint32_t advance;
    };
    class Renderer{
        public:
            virtual ~Renderer() = default;
            virtual void init(GLFWwindow* window) = 0;
            virtual void shutDown() = 0;
            virtual void beginDraw() = 0;
            virtual void endDraw() = 0;
            virtual void renderQuad(glm::vec2 topLeft, glm::vec2 bottomRight, glm::u8vec4 color) = 0;
            virtual void renderText(glm::u64vec2 topLeft, glm::u8vec4 color, std::string text) = 0;
        protected:
            virtual Character* loadChar(FT_Face face) = 0;
            void loadCharacters();
            std::map<char, Character*> characters;
            GLFWwindow* __window;
    };
};

#endif // _CHAINGRID_RENDERING_RENDERER_H_
