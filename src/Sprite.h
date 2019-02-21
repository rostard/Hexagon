//
// Created by rostard on 25.09.18.
//

#ifndef INC_2DPROJECT_SPRITE_H
#define INC_2DPROJECT_SPRITE_H


#include "Shader.h"
//#include "Texture.h"

class Framebuffer;
class Texture;

class Sprite {
public:

    Sprite(Texture *texture, const vec2 &scale, const vec2 &pos, const mat2 &rot, Shader *shader = nullptr);
    virtual ~Sprite();

    const vec2 &getScale() const;

    void setScale(const vec2 &scale);

    const vec2 &getPos() const;

    void setPos(const vec2 &pos);

    const mat2 &getRot() const;

    void setRot(const mat2 &rot);

    const vec3 &getColor() const;

    void setColor(const vec3 &color);

    Shader *getShader() const;

    void setShader(Shader *shader);

    virtual void render();

    void setNewTexCoords(float* texCoords);

protected:
    Texture* texture = nullptr;
    vec2 scale = {10, 10};
    vec2 pos = {0, 0};
    mat2 rot = angleToMat(0);
    vec3 color = {1, 1, 1};
    Shader *shader = nullptr;

    bool default_texture = false;

    unsigned int VAO, VBO;
};


#endif //INC_2DPROJECT_SPRITE_H
