//
// Created by rostard on 15.10.18.
//

#ifndef INC_2DPROJECT_BITMAPFONT_H
#define INC_2DPROJECT_BITMAPFONT_H

#include <string>
#include <vector>
#include "../Shader.h"

class Sprite;
class Texture;

struct Glyph{
    Sprite* sprite;  // ID handle of the glyph texture
    vec2    size;       // Size of glyph
    vec2    bearing;    // Offset from baseline to left/top of glyph
    GLuint  advance;
};

class Font {
public:
    Font(const std::string &filename, unsigned int size = 100);

    virtual ~Font();

    void RenderText(const std::string& text, vec2 pos, GLfloat scale, vec3 color);
private:
    Texture* fontTexture = nullptr;
    void loadFromTrueType(const std::string& filename, unsigned int fontSize=100);
    std::vector<Glyph> glyphs;
    const unsigned int numOfGlyphs = 255;
    unsigned int size;
};


#endif //INC_2DPROJECT_BITMAPFONT_H
