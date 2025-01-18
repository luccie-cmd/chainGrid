#include <cstdio>
#include <GLFW/glfw3.h>
#include <entities/player.h>
#include <entities/wall.h>
#include <common.h>
#include <rendering/renderer.h>
#include <thirdparty/toml.hpp>
#include <ui/text.h>
#include <csignal>
#include <execinfo.h>
#include <rendering/opengl/renderer.h>
#include <chrono>
#include <iostream>

uint64_t maxFps = 0;
std::vector<chainGrid::entities::Entity*> entities;
std::vector<chainGrid::ui::Element*> uiElements;
GLFWwindow* window = nullptr;
toml::v3::ex::parse_result config;
chainGrid::rendering::Renderer* renderer;
enum struct RenderType{
    TitleScreen,
    LevelSelect,
    Level,
} renderType;

void render(){
    renderer->beginDraw();
    if(renderType == RenderType::Level){
#ifdef OPENGL_RENDERER
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
#endif
        for(size_t y = 1; y < GRID_HEIGHT-2; ++y){
            for(size_t x = 1; x < GRID_WIDTH-2; ++x){
                renderer->renderQuad(chainGrid::normalizeCoordinates(chainGrid::convertFromGridToScreen(glm::u64vec2(x, y))), chainGrid::normalizeCoordinates(chainGrid::convertFromGridToScreen(glm::u64vec2(x+1, y+1))), glm::u8vec4(50));
            }
        }
#ifdef OPENGL_RENDERER
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
#endif
    }
    for(chainGrid::entities::Entity* entity : entities){
        entity->draw();
    }
    for(chainGrid::ui::Element* element : uiElements){
        element->render();
    }
    renderer->endDraw();
}

void update(){
    for(chainGrid::entities::Entity* entity : entities){
        entity->update(entities);
    }
    for(chainGrid::ui::Element* element : uiElements){
        element->update(window);
    }
}

void fillBorderWalls(){
    for(size_t y = 0; y < GRID_HEIGHT-1; ++y){
        entities.push_back(new chainGrid::entities::Wall(glm::u64vec2(0,            y), window, renderer));
        entities.push_back(new chainGrid::entities::Wall(glm::u64vec2(GRID_WIDTH-2, y), window, renderer));
    }
    for(size_t x = 1; x < GRID_WIDTH-2; ++x){
        entities.push_back(new chainGrid::entities::Wall(glm::u64vec2(x,             0), window, renderer));
        entities.push_back(new chainGrid::entities::Wall(glm::u64vec2(x, GRID_HEIGHT-2), window, renderer));
    }
}

void loadLevel(unsigned int level){
    entities.clear();
    uiElements.clear();
    fillBorderWalls();
    switch(level){}
    entities.push_back(new chainGrid::entities::Player(glm::u64vec2(1, 7), window, renderer));
    renderType = RenderType::Level;
}

void titleScreenButtonHandler(){
    entities.clear();
    uiElements.clear();
    renderType = RenderType::LevelSelect;
}

void loadTitleScreen(){
    entities.clear();
    uiElements.clear();
    uiElements.push_back(new chainGrid::ui::Text(glm::u64vec2((chainGrid::getScreenCoords().x/2)-(chainGrid::getScreenCoords().x/9), 100), "Chaingrid", renderer));
    renderType = RenderType::TitleScreen;
}

void commonExit(){
    if(renderer){
        delete renderer;
    }
    if(window){
        glfwDestroyWindow(window);
    }
    glfwTerminate();
}

void init(){
    config = toml::parse_file("./config.toml");
    maxFps = static_cast<uint64_t>(config["settings"]["max_fps"].value_or(0));
#ifdef OPENGL_RENDERER
    renderer = new chainGrid::rendering::OpenGLRenderer;
#endif
    if(renderer == nullptr){
        commonExit();
        std::printf("ERROR: No rendering backend\n");
        std::exit(1);
    }
    renderer->init(window);
    loadTitleScreen();
    // loadLevel(0);
}

void quitHandler(int sig){
    commonExit();
    std::printf("HAHA you fucked something up, code %u, good luck finding out what the fuck went wrong\n", sig);
    void* callstack[128];
    int frames = backtrace(callstack, 128);
    char** strs = backtrace_symbols(callstack, frames);
    std::printf("Stack trace\n");
    for(int i = 0; i < frames; ++i){
        std::printf("- %s\n", strs[i]);
    }
    std::exit(1);
}

int main(){
    signal(SIGSEGV, quitHandler);
    if(!glfwInit()){
        std::printf("ERROR: Failed to init GLFW\n");
        return 1;
    }
    GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
    if(!primaryMonitor){
        commonExit();
        std::printf("ERROR: Failed to get primary window\n");
        return 1;
    }
    int windowWidth, windowHeight;
    glfwGetMonitorWorkarea(primaryMonitor, nullptr, nullptr, &windowWidth, &windowHeight);
    chainGrid::setScreenSize(glm::u16vec2(windowWidth, windowHeight));
#if defined(OPENGL_RENDERER)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#elif defined(VULKAN_RENDERER)
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
#endif
    window = glfwCreateWindow(windowWidth, windowHeight, "Chain Grid", primaryMonitor, NULL);
    if(!window){
        commonExit();
        std::printf("ERROR: Unable to create window\n");
        std::exit(1);
    }
    init();
    std::printf("Max FPS: %lu\n", maxFps);
    float last_time = glfwGetTime();
    float accumulated_time = 0.0f;
    const float FRAME_TIME = 1/maxFps;
    while(!glfwWindowShouldClose(window)){
        float current_time = glfwGetTime();
        float dt = current_time - last_time;
        last_time = current_time;
        accumulated_time += dt;
        if (accumulated_time >= FRAME_TIME){
            accumulated_time = 0.0f;
            update();
            render();
        }
        glfwPollEvents();
    }
    renderer->shutDown();
    commonExit();
    return 0;
}