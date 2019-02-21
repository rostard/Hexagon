//
// Created by rostard on 25.09.18.
//

#include "Sprite.h"
#include "ConfigManager.h"
#include "Texture.h"
#include "Framebuffer.h"

Sprite::Sprite(Texture *texture, const vec2 &scale, const vec2 &pos, const mat2 &rot, Shader *shader) : texture(
        texture), scale(scale), pos(pos), rot(rot), shader(shader) {
        float positions[] = { -1, -1,
                              -1, 1,
                              1, 1,
                              -1, -1,
                              1, 1,
                              1, -1 };
        float texCoords[] = { 0, 0,
                              0, 1,
                              1, 1,
                              0, 0,
                              1, 1,
                              1, 0 };

        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(positions) + sizeof(texCoords), nullptr, GL_STATIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(positions), positions);
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(positions), sizeof(texCoords), texCoords);


        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), nullptr);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), (void*)(sizeof(positions)));

    if(shader== nullptr){
        this->shader = Shader::GetSpriteShader();
    }
    this->shader->setWindowSize(ConfigManager::getFloat("window_width"), ConfigManager::getFloat("window_height"));
    if(texture == nullptr){
        default_texture = true;
        this->texture = new Texture(ConfigManager::getString("default_texture"));
    }
}


Sprite::~Sprite() {
    if(default_texture)delete(this->texture);
}



void Sprite::render() {
    shader->use();

    shader->setUniformMat2("rot", rot);
    shader->setUniform2f("pos", pos);
    shader->setUniform2f("scale", scale);
    shader->setUniform3f("color", color);
//    shader->setU

    texture->bind(0);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

const vec2 &Sprite::getScale() const {
    return scale;
}

void Sprite::setScale(const vec2 &scale) {
    Sprite::scale = scale;
}

const vec2 &Sprite::getPos() const {
    return pos;
}

void Sprite::setPos(const vec2 &pos) {
    Sprite::pos = pos;
}

const mat2 &Sprite::getRot() const {
    return rot;
}

void Sprite::setRot(const mat2 &rot) {
    Sprite::rot = rot;
}

Shader *Sprite::getShader() const {
    return shader;
}

void Sprite::setShader(Shader *shader) {
    Sprite::shader = shader;
}

const vec3 &Sprite::getColor() const {
    return color;
}

void Sprite::setColor(const vec3 &color) {
    Sprite::color = color;
}

void Sprite::setNewTexCoords(float* texCoords) {
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(float) * 2 * 6, sizeof(float) * 2 * 6, texCoords);
}

