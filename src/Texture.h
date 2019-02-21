//
// Created by rostard on 25.09.18.
//

#ifndef INC_2DPROJECT_TEXTURE_H
#define INC_2DPROJECT_TEXTURE_H


#include <string>
#include <glad/glad.h>
#include <unordered_map>

class Texture {
public:
    Texture(const std::string& name, GLenum FORMAT = GL_RGB, int INTERNAL_FORMAT = GL_RGB,
            int WRAP_S = GL_CLAMP_TO_EDGE, int WRAP_T = GL_CLAMP_TO_EDGE,
            int MIN_F = GL_LINEAR, int MAG_F = GL_LINEAR);
    Texture(unsigned char* data, uint width, uint height, GLenum FORMAT, int INTERNAL_FORMAT,
            int WRAP_S = GL_CLAMP_TO_EDGE, int WRAP_T = GL_CLAMP_TO_EDGE,
            int MIN_F = GL_LINEAR, int MAG_F = GL_LINEAR);

    virtual ~Texture();

    void bind(unsigned int slot);

    static uint genTextureId(uint width, uint height, void *data, GLenum FORMAT, int INTERNAL_FORMAT,
                             int WRAP_S = GL_CLAMP_TO_EDGE, int WRAP_T = GL_CLAMP_TO_EDGE,
                             int MIN_F = GL_LINEAR, int MAG_F = GL_LINEAR);
private:
    unsigned int id;
    std::string name;

    static std::unordered_map<std::string, int> counters;

};


#endif //INC_2DPROJECT_TEXTURE_H
