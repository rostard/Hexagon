//
// Created by rostard on 18.02.19.
//

#include "Hexagon.h"
#include "Game.h"

void fade(ClickableSprite* sprite){
    if(((Hexagon*)sprite)->getState() == EMPTY){
        if(Game::getPlayer() == DIRT){
            sprite->setColor({0.1, 0.5, 0.1});
        }
        else if(Game::getPlayer() == WATER){
            sprite->setColor({0.1, 0.1, 0.5});
        }
    }

}
void fadeOff(ClickableSprite* sprite){
    if(((Hexagon*)sprite)->getState() == EMPTY){
        sprite->setColor({1.0, 1.0, 1.0});
    }

}

void click(ClickableSprite* sprite){
    if(((Hexagon*)sprite)->getState() != EMPTY)return;
    if(Game::getPlayer() == DIRT){
        sprite->setColor({0.1, 1.0, 0.1});
        ((Hexagon*)sprite)->setState(DIRT);
        Game::setPlayer(WATER);
    }
    else if (Game::getPlayer() == WATER){
        sprite->setColor({0.1, 0.1, 1.0});
        ((Hexagon*)sprite)->setState(WATER);
        Game::setPlayer(DIRT);
    }

}

Hexagon::Hexagon(Texture *texture, const vec2 &scale, const vec2 &pos, const mat2 &rot, Shader *shader)
        : ClickableSprite(texture, scale, pos, rot, shader) {
    setOnHover(fade);
    setOnHoverOff(fadeOff);
    setOnClick(click);
}

void Hexagon::render() {
    ClickableSprite::render();
}

HexState Hexagon::getState() const {
    return state;
}

void Hexagon::setState(HexState state) {
    Hexagon::state = state;
}
