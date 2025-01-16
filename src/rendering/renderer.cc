#include <rendering/renderer.h>
#include <utility>
#include <cassert>
#include <iostream>

namespace chainGrid::rendering{
    void Renderer::loadCharacters(){
        FT_Library ft;
        if (FT_Init_FreeType(&ft)){
            std::printf("ERROR: Could not init FreeType Library\n");
            std::exit(1);
        }
        FT_Face face;
        if (FT_New_Face(ft, "./assets/fonts/JetBrainsMono-SemiBold.ttf", 0, &face)){
            std::printf("ERROR: Failed to load font\n");  
            std::exit(1);
        }
        FT_Set_Pixel_Sizes(face, 0, 48);
        for(uint8_t c = 0; c < 127; ++c){
            if(FT_Load_Char(face, c, FT_LOAD_RENDER)){
                std::printf("ERROR: Failed to load character `%c`\n", (char)c);
            }
            Character* character = this->loadChar(face);
            this->characters.insert({(char)c, character});
        }
        FT_Done_Face(face);
        FT_Done_FreeType(ft);
    }
};