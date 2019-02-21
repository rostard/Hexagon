//
// Created by rostard on 10.02.19.
//

#ifndef INC_2DPROJECT_CLICKABLESPRITE_H
#define INC_2DPROJECT_CLICKABLESPRITE_H


#include <set>
#include <unordered_map>
#include "Sprite.h"

class Framebuffer;

class ClickableSprite;

void nothing(ClickableSprite*);

class ClickableSprite : public Sprite {
public:
    ClickableSprite(Texture *texture, const vec2 &scale, const vec2 &pos, const mat2 &rot, Shader *shader = nullptr);

    virtual ~ClickableSprite();

    void render() override;
    void onClick();
    void onHover();
    void onHoverOff();
    void setOnClick(void(*fnc)(ClickableSprite*));
    void setOnHover(void(*fnc)(ClickableSprite*));
    void setOnHoverOff(void(*fnc)(ClickableSprite*));

    static void setPickFramebuffer(Framebuffer* framebuffer);
    static ClickableSprite* getByIndex(int index);
private:

    Shader *pickShader = nullptr;
    int index;
    void(*onClickFcn)(ClickableSprite*) = nothing;
    void(*onHoverFcn)(ClickableSprite*) = nothing;
    void(*onHoverOffFcn)(ClickableSprite*) = nothing;

    static int last_index;
    static std::unordered_map<int, ClickableSprite*> reserved;
    static Framebuffer* pickFramebuffer;
};



#endif //INC_2DPROJECT_CLICKABLESPRITE_H
