//
// Created by rostard on 30.09.18.
//

#ifndef INC_2DPROJECT_GUIOBJECT_H
#define INC_2DPROJECT_GUIOBJECT_H


#include <vector>
#include "../ClickableSprite.h"

class GUIObject {
public:
    GUIObject();
    GUIObject(vec2 pos, vec2 scale, Texture* texture = nullptr);

    virtual ~GUIObject();

    void addChild(GUIObject* child);
    virtual void render();

    void setOnClick(void(*fnc)(ClickableSprite*));
    void setOnHover(void(*fnc)(ClickableSprite*));
    void setOnHoverOff(void(*fnc)(ClickableSprite*));

protected:
    ClickableSprite* background;
private:
    std::vector<GUIObject*> children;
};


#endif //INC_2DPROJECT_GUIOBJECT_H
