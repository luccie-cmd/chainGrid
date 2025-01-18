#if defined(OPENGL_RENDERER)
#include <rendering/opengl/renderer.h>
#include <rendering/opengl/shader.h>
#include <rendering/opengl/vao.h>
#include <rendering/opengl/vbo.h>
#include <rendering/opengl/error.h>
#include <common.h>
#include <glm/gtc/matrix_transform.hpp>

namespace chainGrid::rendering{
    OpenGLRenderer::OpenGLRenderer(){
        this->__window = nullptr;
        this->shaders.fill(nullptr);
        this->vaos.fill(nullptr);
        this->characters.clear();
    }
    OpenGLRenderer::~OpenGLRenderer(){}
    Character* OpenGLRenderer::loadChar(FT_Face face){
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );
        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        Character* character = new Character;
        character->textureID = texture;
        character->size = glm::u64vec2(face->glyph->bitmap.width, face->glyph->bitmap.rows);
        character->bearing = glm::u64vec2(face->glyph->bitmap_left, face->glyph->bitmap_top);
        character->advance = face->glyph->advance.x;
        glBindTexture(GL_TEXTURE_2D, 0);
        return character;
    }
    static void debugCallbackFunction(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam){
        (void)userParam;
        if(severity != GL_DEBUG_SEVERITY_NOTIFICATION || type == GL_DEBUG_TYPE_PERFORMANCE){
            std::printf("Source: 0x%x\n", source);
            std::printf("Type: 0x%x\n", type);
            std::printf("ID: %u\n", id);
            std::printf("Severity: 0x%x\n", severity);
            std::printf("Length:: %u\n", length);
            std::printf("Message: `%s`\n", message);
            checkGlError();
        }
    }
    void OpenGLRenderer::init(GLFWwindow* window) {
        this->__window = window;
        glfwMakeContextCurrent(this->__window);
        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(debugCallbackFunction, nullptr);
        glEnable(GL_CULL_FACE);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        this->loadCharacters();
    }
    void OpenGLRenderer::shutDown(){}
    void OpenGLRenderer::beginDraw(){
        glClearColor(0.1, 0.1, 0.1, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    void OpenGLRenderer::endDraw(){
        glfwSwapBuffers(this->__window);
    }
    void OpenGLRenderer::renderQuad(glm::vec2 topLeft, glm::vec2 bottomRight, glm::u8vec4 color){
        if(this->shaders.at((std::size_t)RenderType::Primitive) == nullptr){
            this->shaders.at((std::size_t)RenderType::Primitive) = new Shader(RenderType::Primitive);
        }
        Shader* shader = this->shaders.at((std::size_t)RenderType::Primitive);
        shader->bind();
        GLfloat vertices[4][6] = {
            topLeft.x,     topLeft.y,     (color.r/255.0f), (color.g/255.0f), (color.b/255.0f), (color.a/255.0f),
            topLeft.x,     bottomRight.y, (color.r/255.0f), (color.g/255.0f), (color.b/255.0f), (color.a/255.0f),
            bottomRight.x, topLeft.y,     (color.r/255.0f), (color.g/255.0f), (color.b/255.0f), (color.a/255.0f),
            bottomRight.x, bottomRight.y, (color.r/255.0f), (color.g/255.0f), (color.b/255.0f), (color.a/255.0f),
        };
        if(this->vaos.at((std::size_t)RenderType::Primitive) == nullptr){
            this->vaos.at((std::size_t)RenderType::Primitive) = new Vao;
        }
        Vao* vao = this->vaos.at((std::size_t)RenderType::Primitive);
        vao->bind();
        Vbo* vbo = new Vbo(GL_ARRAY_BUFFER, GL_TRUE);
        vbo->bind();
        vbo->setBuffer(vertices, sizeof(vertices));
        vao->setAttr(0, 2, GL_FLOAT, 6*sizeof(GLfloat), nullptr);
        vao->setAttr(1, 4, GL_FLOAT, 6*sizeof(GLfloat), reinterpret_cast<void*>(2*sizeof(GLfloat)));
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        vbo->unbind();
        vao->unbind();
        shader->unbind();
        delete vbo;
    }
    void OpenGLRenderer::renderText(glm::u64vec2 pos, glm::u8vec4 color, std::string text){
        (void)color;
        if(this->shaders.at((std::size_t)RenderType::Text) == nullptr){
            this->shaders.at((std::size_t)RenderType::Text) = new Shader(RenderType::Text);
        }
        Shader* shader = this->shaders.at((std::size_t)RenderType::Text);
        if(this->vaos.at((std::size_t)RenderType::Text) == nullptr){
            this->vaos.at((std::size_t)RenderType::Text) = new Vao;
        }
        Vao* vao = this->vaos.at((std::size_t)RenderType::Text);
        Vbo* vbo = new Vbo(GL_ARRAY_BUFFER, GL_FALSE);
        vao->bind();
        vbo->bind();
        vbo->setBuffer(nullptr, sizeof(GLfloat)*6*4);
        vao->setAttr(0, 4, GL_FLOAT, 4 * sizeof(GLfloat), nullptr);
        vbo->unbind();
        vao->unbind();
        shader->bind();
        glm::vec4 normalizedColor = glm::vec4(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f);
        shader->uniform("textColor", normalizedColor);
        shader->uniform("text", glm::i32vec1(0));
        glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(getScreenCoords().x), 0.0f, static_cast<float>(getScreenCoords().y));
        shader->uniform("proj", projection);
        glActiveTexture(GL_TEXTURE0);
        vao->bind();
        for(char c : text){
            Character *ch = this->characters[c];
            float xpos = pos.x + ch->bearing.x;
            float ypos = (getScreenCoords().y - pos.y) - (ch->size.y - ch->bearing.y);
            float w = ch->size.x;
            float h = ch->size.y;
            GLfloat vertices[6][4] = {
                {xpos,     ypos + h,   0.0f, 0.0f},
                {xpos,     ypos,       0.0f, 1.0f},
                {xpos + w, ypos,       1.0f, 1.0f},
                {xpos,     ypos + h,   0.0f, 0.0f},
                {xpos + w, ypos,       1.0f, 1.0f},
                {xpos + w, ypos + h,   1.0f, 0.0f} 
            };
            glBindTexture(GL_TEXTURE_2D, ch->textureID);
            vbo->bind();
            vbo->setSubBuffer(0, sizeof(vertices), vertices);
            vbo->unbind();
            glDrawArrays(GL_TRIANGLES, 0, 6);
            pos.x += (ch->advance >> 6);
        }
        glBindTexture(GL_TEXTURE_2D, 0);
        delete vbo;
        vao->unbind();
        shader->unbind(); 
    }
};

#endif