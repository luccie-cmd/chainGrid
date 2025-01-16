#if !defined(_CHAINGRID_RENDERING_VBO_H_)
#define _CHAINGRID_RENDERING_VBO_H_
#include <GLFW/glfw3.h>

namespace chainGrid::rendering{
    class Vbo{
        public:
            Vbo(GLenum target, GLboolean staticDraw);
            ~Vbo();
            void bind();
            void unbind();
            void setSubBuffer(GLintptr offset, GLsizeiptr size, const GLvoid* data);
            void setBuffer(GLvoid* data, GLsizeiptr size);
        private:
            GLenum type;
            GLboolean staticDraw;
            GLuint handle;
    };
};

#endif // _CHAINGRID_RENDERING_VBO_H_
