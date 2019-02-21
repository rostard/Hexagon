//
// Created by rostard on 30.09.18.
//

#include "GUIObject.h"

GUIObject::GUIObject() : background(nullptr){

}

void GUIObject::addChild(GUIObject *child) {
    children.push_back(child);
}

GUIObject::GUIObject(vec2 pos, vec2 scale, Texture *texture) {
    background = new ClickableSprite(texture, scale, pos, {1, 0, 0, 1});
}

void GUIObject::render() {
    if(background){
        background->render();
    }
    for(auto i: children){
        i->render();
    }
}

GUIObject::~GUIObject() {
    for(auto i: children){
        delete(i);
    }
    delete background;
}

void GUIObject::setOnClick(void (*fnc)(ClickableSprite *)) {
    background->setOnClick(fnc);
}

void GUIObject::setOnHover(void (*fnc)(ClickableSprite *)) {
    background->setOnHover(fnc);
}

void GUIObject::setOnHoverOff(void (*fnc)(ClickableSprite *)) {
    background->setOnHoverOff(fnc);
}
