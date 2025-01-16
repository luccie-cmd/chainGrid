#if !defined(_CHAINGRID_RENDERING_SHADER_H_)
#define _CHAINGRID_RENDERING_SHADER_H_
#include <GLFW/glfw3.h>
#include <rendering/types.h>
#include <glm/glm.hpp>
#include <string>

namespace chainGrid::rendering{
    class Shader{
        public:
            Shader(RenderType polyType);
            ~Shader();
            void bind();
            void unbind();
            void uniform(const char* name, glm::mat4 mat4);
            void uniform(const char* name, glm::vec4 vec4);
            void uniform(const char* name, glm::i32vec1 vec1);
        private:
            GLint getUniformLoc(const char* name);
            GLuint loadSubShader(GLenum type, std::string data);
            GLuint fragmentShader;
            GLuint vertexShader;
            GLuint program;
    };
};

#endif // _CHAINGRID_RENDERING_SHADER_H_