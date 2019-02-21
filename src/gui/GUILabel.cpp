//
// Created by rostard on 22.10.18.
//

#include "GUILabel.h"

GUILabel::GUILabel(const vec2 &pos, const vec2 &scale, const std::string &text, const std::string &font,
                   vec3 color, Texture *texture) : GUIObject(pos, scale, texture), text(text), color(color) {
    this->font = new Font(font + ".ttf");
}

void GUILabel::render() {
    background->render();
    font->RenderText(text, background->getPos(), 1, color);
}

GUILabel::~GUILabel() {
    delete font;

}
