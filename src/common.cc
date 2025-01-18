#include <common.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include <fstream>

namespace chainGrid{
    static glm::u16vec2 screenSize;
    void setScreenSize(glm::u16vec2 size){
        screenSize = size;
    }
    glm::u16vec2 getScreenCoords(){
        return screenSize;
    }
    glm::vec2 normalizeCoordinates(glm::vec2 coords){
        glm::vec2 ret;
        ret.x = ((float)coords.x / (float)screenSize.x) * 2.0f - 1.0f;
        ret.y = 1.0f - ((float)coords.y / (float)screenSize.y) * 2.0f;
        return ret;
    }
    glm::vec2 normalizeCoordinates(glm::u64vec2 coords){
        glm::vec2 ret;
        ret.x = ((float)coords.x / (float)screenSize.x) * 2.0f - 1.0f;
        ret.y = 1.0f - ((float)coords.y / (float)screenSize.y) * 2.0f;
        return ret;
    }
    glm::mat4 getMP(components::Transform* transform){
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(normalizeCoordinates(transform->getPos()*glm::u64vec2(transform->getSize())), 0.0f));
        model = glm::rotate(model, glm::radians((float)transform->getRotation().x), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(model, glm::vec3(transform->getScale().x, transform->getScale().y, 1.0f));
        glm::mat4 projection = glm::ortho(0.0f, (float)screenSize.x, (float)screenSize.y, 0.0f, -1.0f, 1.0f);
        return projection * model;
    }
    std::string readfile(std::string path){
        std::ifstream *file = new std::ifstream(path, std::ios::in | std::ios::binary);
        file->seekg(0, std::ios::end);
        std::size_t fileSize = file->tellg();
        file->seekg(0, std::ios::beg);
        std::string fileContents(fileSize, '\0');
        file->read(&fileContents[0], fileSize);
        delete file;
        return fileContents;
    }
    glm::u64vec2 convertFromGridToScreen(glm::u64vec2 grid){
        glm::u64vec2 gridBlock = grid*glm::u64vec2(GRID_BLOCK_SIZE);
        glm::u64vec2 offset = glm::u64vec2(GRID_OFFSET)*glm::u64vec2(glm::u16vec2(GRID_BLOCK_SIZE));
        glm::u64vec2 ret = gridBlock+offset+glm::u64vec2(GRID_LINE_SIZE*grid.x, GRID_LINE_SIZE*grid.y);
        return ret;
    }
};