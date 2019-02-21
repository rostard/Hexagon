//
// Created by rostard on 21.02.19.
//

#include "Game.h"

HexState Game::player = DIRT;

HexState Game::getPlayer() {
    return player;
}

void Game::setPlayer(HexState player) {
    Game::player = player;
}
