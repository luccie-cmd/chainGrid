#if defined(OPENGL_RENDERER)
#include <rendering/opengl/shader.h>
#include <glm/gtc/type_ptr.hpp>
#include <cstdio>
#include <cstdlib>
#include <common.h>
#include <iostream>
#include <rendering/opengl/error.h>

namespace chainGrid::rendering{
    static void checkCompileErrors(GLuint shader, std::string type) {
        GLint success;
        GLchar infoLog[1024];
        if (type != "PROGRAM") {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            checkGlError();
            if (!success) {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n";
                std::exit(1);
            }
        } else {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            checkGlError();
            if (!success) {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cerr << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n";
                std::exit(1);
            }
        }
    }
    Shader::Shader(RenderType type){
        this->program = glCreateProgram();
        switch(type){
            case RenderType::Primitive: {
                this->vertexShader = this->loadSubShader(GL_VERTEX_SHADER, readfile("./assets/shaders/opengl/primitive.vert"));
                this->fragmentShader = this->loadSubShader(GL_FRAGMENT_SHADER, readfile("./assets/shaders/opengl/primitive.frag"));
            } break;
            case RenderType::Text: {
                this->vertexShader = this->loadSubShader(GL_VERTEX_SHADER, readfile("./assets/shaders/opengl/text.vert"));
                this->fragmentShader = this->loadSubShader(GL_FRAGMENT_SHADER, readfile("./assets/shaders/opengl/text.frag"));
            } break;
            case RenderType::None:
            default: {
                std::printf("ERROR: Invalid render type passed to shader\n");
                std::exit(1);
            } break;
        }
        glAttachShader(this->program, this->vertexShader);
        glAttachShader(this->program, this->fragmentShader);
        glLinkProgram(this->program);
        checkCompileErrors(this->program, "PROGRAM");
        glDeleteShader(this->vertexShader);
        glDeleteShader(this->fragmentShader);
    }
    void Shader::bind(){
        glUseProgram(this->program);
    }
    void Shader::unbind(){
        glUseProgram(0);
    }
    void Shader::uniform(const char* name, glm::mat4 mat4){
        GLint loc = this->getUniformLoc(name);
        glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mat4));
    }
    void Shader::uniform(const char* name, glm::vec4 vec4){
        GLint loc = this->getUniformLoc(name);
        glUniform4fv(loc, 1, glm::value_ptr(vec4));
    }
    void Shader::uniform(const char* name, glm::i32vec1 vec1){
        GLint loc = this->getUniformLoc(name);
        glUniform1i(loc, vec1.x);
    }
    GLint Shader::getUniformLoc(const char* name){
        GLint loc = glGetUniformLocation(this->program, name);
        if(loc == -1){
            std::printf("ERROR: No uniform with name `%s`\n", name);
            std::printf("NOTE: Possible uniforms:\n");
            GLint count;
            glGetProgramiv(this->program, GL_ACTIVE_UNIFORMS, &count);
            std::printf("Active Uniforms: %d\n", count);
            const GLsizei bufSize = 16;
            GLchar name[bufSize];
            GLsizei length;
            GLint size;
            GLenum type;
            for (GLint i = 0; i < count; i++){
                glGetActiveUniform(program, (GLuint)i, bufSize, &length, &size, &type, name);
                printf("Uniform #%d Type: %u Name: %s\n", i, type, name);
            }
            std::exit(1);
        }
        return loc;
    }
    Shader::~Shader(){
        glDeleteProgram(this->program);
    }
    GLuint Shader::loadSubShader(GLenum type, std::string data){
        GLuint shader = glCreateShader(type);
        const char* csrc = data.c_str();
        glShaderSource(shader, 1, &csrc, nullptr);
        glCompileShader(shader);
        checkCompileErrors(shader, "SHADER");
        return shader;
    }
};

#endif