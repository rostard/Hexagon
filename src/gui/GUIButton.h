//
// Created by rostard on 30.09.18.
//

#ifndef INC_2DPROJECT_GUIBUTTON_H
#define INC_2DPROJECT_GUIBUTTON_H


#include "GUIObject.h"

class GUIButton : public GUIObject{
public:
    GUIButton(const vec2 &pos, const vec2 &scale, Texture *texture = nullptr);
};


#endif //INC_2DPROJECT_GUIBUTTON_H
