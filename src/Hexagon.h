//
// Created by rostard on 18.02.19.
//

#ifndef INC_2DPROJECT_HEXAGON_H
#define INC_2DPROJECT_HEXAGON_H


#include "ClickableSprite.h"

enum HexState{
    EMPTY,
    DIRT,
    WATER
};

class Hexagon : public ClickableSprite {
public:
    Hexagon(Texture *texture, const vec2 &scale, const vec2 &pos, const mat2 &rot, Shader *shader = nullptr);

    void render();

    HexState getState() const;

    void setState(HexState state);

private:
    HexState state = EMPTY;
};


#endif //INC_2DPROJECT_HEXAGON_H
