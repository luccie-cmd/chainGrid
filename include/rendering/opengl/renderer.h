#if !defined(_CHAINGRID_RENDERING_OPENGL_RENDERER_H_)
#define _CHAINGRID_RENDERING_OPENGL_RENDERER_H_
#include <rendering/renderer.h>
#include "shader.h"
#include "vao.h"
#include <array>

namespace chainGrid::rendering{
    class OpenGLRenderer : public Renderer{
        public:
            OpenGLRenderer();
            ~OpenGLRenderer() override;
            void init(GLFWwindow* window) override;
            void shutDown() override;
            void beginDraw() override;
            void endDraw() override;
            void renderQuad(glm::u64vec2 topLeft, glm::u64vec2 bottomRight, glm::u8vec4 color) override;
            void renderText(glm::u64vec2 topLeft, glm::u8vec4 color, std::string text) override;
        private:
            Character* loadChar(FT_Face face) override;
            std::array<Shader*, (std::size_t)(RenderType::None)> shaders;
            std::array<Vao*, (std::size_t)(RenderType::None)> vaos;
    };
};

#endif // _CHAINGRID_RENDERING_RENDERER_H_
