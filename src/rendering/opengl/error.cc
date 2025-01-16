#if defined(OPENGL_RENDERER)
#include <rendering/opengl/error.h>
#include <GLFW/glfw3.h>
#include <cstdio>
#include <cstdlib>

namespace chainGrid::rendering{
    void checkGlError(){
        GLenum err = glGetError();
        bool bErr = false;
        while(err != GL_NO_ERROR){
            std::printf("GL ERROR: 0x%x\n", err);
            bErr = true;
            err = glGetError();
        }
        if(bErr){
            std::exit(1);
        }
    }
};

#endif