//
// Created by rostard on 25.09.18.
//

#include <glad/glad.h>
#include <iostream>
#include "Texture.h"
#include "dependencies/stb_image.h"

std::unordered_map<std::string, int> Texture::counters;

Texture::Texture(const std::string &name, GLenum FORMAT, int INTERNAL_FORMAT,
                 int WRAP_S, int WRAP_T, int MIN_F, int MAG_F): name(name){
    int width, height, channels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(("res/textures/"+name).c_str(), &width, &height, &channels, 0);

    if(!data){
        std::cerr<<"Error loading texture: " << name << std::endl;
        return;
    }
    id = genTextureId(width, height, data, FORMAT, INTERNAL_FORMAT, WRAP_S, WRAP_T, MIN_F, MAG_F);

    if(counters.find(name) != counters.end()) counters[name] += 1;
    else counters[name] = 0;


    stbi_image_free(data);
}

Texture::Texture(unsigned char *data, uint width, uint height, GLenum FORMAT, int INTERNAL_FORMAT,
                 int WRAP_S, int WRAP_T, int MIN_F, int MAG_F) {

    name = std::string((char*)data);
    name.resize(16);

    id = genTextureId(width, height, data, FORMAT, INTERNAL_FORMAT, WRAP_S, WRAP_T, MIN_F, MAG_F);

    if(counters.find(name) != counters.end()) counters[name] += 1;
    else counters[name] = 0;
}

void Texture::bind(unsigned int slot) {
    glActiveTexture(slot);
    glBindTexture(GL_TEXTURE_2D, id);
}

Texture::~Texture() {
    if(--counters[name] == 0){
        glDeleteTextures(1, &id);
    }
}

uint Texture::genTextureId(uint width, uint height, void *data, GLenum FORMAT, int INTERNAL_FORMAT, int WRAP_S,
                           int WRAP_T,
                           int MIN_F, int MAG_F) {
    uint ret;
    glGenTextures(1, &ret);
    glBindTexture(GL_TEXTURE_2D, ret);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, WRAP_S);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, WRAP_T);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, MAG_F);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, MIN_F);

    glTexImage2D(GL_TEXTURE_2D, 0, INTERNAL_FORMAT, width, height, 0, FORMAT, GL_UNSIGNED_BYTE, data);
//    glGenerateMipmap(GL_TEXTURE_2D);

    return ret;
}

