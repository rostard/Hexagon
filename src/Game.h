//
// Created by rostard on 21.02.19.
//

#ifndef INC_2DPROJECT_GAME_H
#define INC_2DPROJECT_GAME_H

#include "Hexagon.h"

class Game {
public:
    static HexState getPlayer();

    static void setPlayer(HexState player);

private:
    static HexState player;
};


#endif //INC_2DPROJECT_GAME_H
