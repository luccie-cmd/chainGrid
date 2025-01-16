#if defined(OPENGL_RENDERER)
#include <rendering/opengl/vbo.h>
#include <rendering/opengl/error.h>

namespace chainGrid::rendering{
    Vbo::Vbo(GLenum target, GLboolean staticDraw){
        this->type = target;
        this->staticDraw = staticDraw;
        glGenBuffers(1, &this->handle);
    }
    Vbo::~Vbo(){
        glDeleteBuffers(1, &this->handle);
    }
    void Vbo::bind(){
        glBindBuffer(this->type, this->handle);
    }
    void Vbo::unbind(){
        glBindBuffer(this->type, 0);
    }
    void Vbo::setBuffer(void* data, GLsizeiptr size){
        glBufferData(this->type, size, data, this->staticDraw ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);
    }
    void Vbo::setSubBuffer(GLintptr offset, GLsizeiptr size, const GLvoid* data){
        glBufferSubData(this->type, offset, size, data);
    }
};

#endif