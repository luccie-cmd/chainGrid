#if !defined(_CHAINGRID_RENDERING_VAO_H_)
#define _CHAINGRID_RENDERING_VAO_H_
#include <GLFW/glfw3.h>

namespace chainGrid::rendering{
    class Vao{
        public:
            Vao();
            ~Vao();
            void bind();
            void unbind();
            void setAttr(GLuint index, GLint size, GLenum type, GLsizei stride, const void *pointer);
        private:
            GLuint handle;
    };
};

#endif // _CHAINGRID_RENDERING_VAO_H_
