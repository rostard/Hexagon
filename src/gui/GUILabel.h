//
// Created by rostard on 22.10.18.
//

#ifndef INC_2DPROJECT_GUILABEL_H
#define INC_2DPROJECT_GUILABEL_H


#include "GUIObject.h"
#include "Font.h"

class GUILabel : public GUIObject {
public:
    GUILabel(const vec2 &pos, const vec2 &scale, const std::string& text, const std::string& font = "arial", vec3 color = {1, 1, 1}, Texture *texture = nullptr);

    virtual ~GUILabel();

    void render() override;

private:
    vec3 color;
    Font* font;
    std::string text;
};


#endif //INC_2DPROJECT_GUILABEL_H
