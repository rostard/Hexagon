//
// Created by rostard on 15.10.18.
//

#include "Font.h"

#include <ft2build.h>
#include FT_FREETYPE_H
#include "../Texture.h"
#include "../Sprite.h"

void cpyFragment(unsigned char *dst, int dstWidth, unsigned char *src, int srcWidth, int srcHeight, int x, int y) {
    for(int i = 0; i<srcHeight; i++){
        memcpy(dst+(y+i)*dstWidth+x, src + i*srcWidth, static_cast<size_t>(srcWidth));
    }
}

void flipyAxis(unsigned char* src, int srcWidth, int srcHeight){
    auto * buf = new unsigned char[srcWidth];
    for(int i = 0; i < srcHeight/2; i++){
        memcpy(buf, src + i * srcWidth, static_cast<size_t>(srcWidth));
        memcpy(src + i * srcWidth, src + (srcHeight - i - 1) * srcWidth, static_cast<size_t>(srcWidth));
        memcpy(src + (srcHeight - i - 1) * srcWidth, buf, static_cast<size_t>(srcWidth));
    }
    delete[] buf;
}

Font::Font(const std::string &filename, unsigned int size): size(size) {
    loadFromTrueType(filename, size);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}


void Font::RenderText(const std::string& text, vec2 pos, GLfloat scale, vec3 color)
{
    vec2 offset = pos;
    // Iterate through all characters
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        glyphs[*c].sprite->getShader()->use();
        glyphs[*c].sprite->getShader()->setUniform2f("offset", offset);
        glyphs[*c].sprite->setColor(color);
        glyphs[*c].sprite->render();
        offset.x += glyphs[*c].advance;
    }
}


void Font::loadFromTrueType(const std::string &filename, unsigned int fontSize) {
    glyphs.reserve(numOfGlyphs);

    FT_Library ft_library;
    if(FT_Init_FreeType(&ft_library)){
        std::cerr << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
    }

    FT_Face face;
    if(FT_New_Face(ft_library, ("res/fonts/"+filename).c_str(), 0, &face)){
        std::cerr << "ERROR::FREETYPE: Failed to load font" << std::endl;
    }

    FT_Set_Pixel_Sizes(face, 0, fontSize);

    int glyphSize = static_cast<int>(face->size->metrics.height >> 6);
    int mapSideSize = static_cast<int>(ceil(sqrt(numOfGlyphs)));
    uint mapSize = 1;
    while(glyphSize * mapSideSize > mapSize){
        mapSize *= 2;
    }
    auto bakedFont = new unsigned char[mapSize*mapSize];

    for (GLubyte c = 0; c < numOfGlyphs; c++)
    {
        // Load character glyph
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }
        glyphs[c].size={(float)face->glyph->bitmap.width, (float)face->glyph->bitmap.rows};
        glyphs[c].bearing={(float)face->glyph->bitmap_left, (float)face->glyph->bitmap_top};
        glyphs[c].advance = (GLuint)(face->glyph->advance.x) >> 6;

        cpyFragment(bakedFont, mapSize, face->glyph->bitmap.buffer, face->glyph->bitmap.width, face->glyph->bitmap.rows,
                    (c % mapSideSize) * glyphSize, c / mapSideSize * glyphSize);
    }
    FT_Done_Face(face);
    FT_Done_FreeType(ft_library);

    flipyAxis(bakedFont, mapSize, mapSize);
    fontTexture = new Texture(bakedFont, mapSize, mapSize, GL_RED, GL_RED);
    delete[] bakedFont;
    //setting needed texCoords for each glyph
    float step = (float)glyphSize / mapSize;
    for (GLubyte c = 0; c < numOfGlyphs; c++) {
        float xpos = glyphs[c].bearing.x + glyphs[c].size.x / 2.0f;
        float ypos = glyphs[c].bearing.y - glyphs[c].size.y / 2.0f - size;
        auto sprite = new Sprite(fontTexture, glyphs[c].size/2 , {xpos, ypos}, angleToMat(0), Shader::GetFontShader());

        int x = c % mapSideSize;
        int y = c / mapSideSize;

        float stepx = glyphs[c].size.x / mapSize;
        float stepy = glyphs[c].size.y / mapSize;

        float texCoords[] = { step*x,       1 - step * y - stepy,
                              step*x,       1 - step * y,
                              step*x+stepx, 1 - step * y,
                              step*x,       1 - step * y - stepy,
                              step*x+stepx, 1 - step * y,
                              step*x+stepx, 1 - step * y - stepy};

        sprite->setNewTexCoords(texCoords);
        glyphs[c].sprite = sprite;
    }
}

Font::~Font() {
    for(int i = 0; i <numOfGlyphs; i++){
        delete(glyphs[i].sprite);
    }
    delete fontTexture;
}
