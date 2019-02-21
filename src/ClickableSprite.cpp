//
// Created by rostard on 10.02.19.
//

#include "ClickableSprite.h"
#include "Texture.h"
#include "Framebuffer.h"
#include "ConfigManager.h"

std::unordered_map<int, ClickableSprite*> ClickableSprite::reserved;
Framebuffer* ClickableSprite::pickFramebuffer = nullptr;
int ClickableSprite::last_index = 0;

ClickableSprite::ClickableSprite(Texture *texture, const vec2 &scale, const vec2 &pos, const mat2 &rot, Shader *shader)
        : Sprite(texture, scale, pos, rot, shader) {
    index = last_index++;
    reserved[index] = this;

    if(pickShader== nullptr){
        this->pickShader = Shader::GetPickShader();
    }
    this->pickShader->setWindowSize(ConfigManager::getFloat("window_width"), ConfigManager::getFloat("window_height"));
}

ClickableSprite::~ClickableSprite() {
    reserved.erase(index);
}


void ClickableSprite::render() {
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

    pickFramebuffer->bind();
    pickShader->use();
    pickShader->setUniformMat2("rot", rot);
    pickShader->setUniform2f("pos", pos);
    pickShader->setUniform2f("scale", scale);
    pickShader->setUniform1i("index", index);
    glDrawArrays(GL_TRIANGLES, 0, 6);

}

void ClickableSprite::onHover() {
    if(onHoverFcn)onHoverFcn(this);
}

void ClickableSprite::onHoverOff() {
    if(onHoverOffFcn)onHoverOffFcn(this);
}

void ClickableSprite::onClick() {
    if(onClickFcn)onClickFcn(this);
}

void ClickableSprite::setOnClick(void (*fnc)(ClickableSprite*)) {
    onClickFcn = fnc;
}

void ClickableSprite::setOnHover(void (*fnc)(ClickableSprite*)) {
    onHoverFcn = fnc;
}

void ClickableSprite::setOnHoverOff(void (*fnc)(ClickableSprite*)) {
    onHoverOffFcn = fnc;
}

void ClickableSprite::setPickFramebuffer(Framebuffer *framebuffer) {
    pickFramebuffer = framebuffer;
}

ClickableSprite *ClickableSprite::getByIndex(int index) {
    return reserved.at(index);
}


void nothing(ClickableSprite *) {}