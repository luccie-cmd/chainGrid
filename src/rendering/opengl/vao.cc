#if defined(OPENGL_RENDERER)
#include <rendering/opengl/vao.h>
#include <cstdio>
#include <cstdlib>
#include <rendering/opengl/error.h>

namespace chainGrid::rendering{
    Vao::Vao(){
        glGenVertexArrays(1, &this->handle);
    }
    Vao::~Vao(){
        glDeleteVertexArrays(1, &this->handle);
    }
    void Vao::bind(){
        if(this->handle == 0){
            std::printf("Unable to bind 0 handle\n");
            std::exit(1);
        }
        glBindVertexArray(this->handle);
    }
    void Vao::unbind(){
        glBindVertexArray(0);
    }
    void Vao::setAttr(GLuint index, GLint size, GLenum type, GLsizei stride, const void *pointer){
        glEnableVertexAttribArray(index);
        switch (type) {
            case GL_BYTE:
            case GL_UNSIGNED_BYTE:
            case GL_SHORT:
            case GL_UNSIGNED_SHORT:
            case GL_INT:
            case GL_UNSIGNED_INT:
            case GL_INT_2_10_10_10_REV:
            case GL_UNSIGNED_INT_2_10_10_10_REV:
                glVertexAttribIPointer(index, size, type, stride, pointer);
                break;
            default:
                glVertexAttribPointer(index, size, type, GL_FALSE, stride, pointer);
                break;
        }
    }
};

#endif