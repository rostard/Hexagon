//
// Created by rostard on 14.02.19.
//

#ifndef INC_2DPROJECT_HEXFIELD_H
#define INC_2DPROJECT_HEXFIELD_H

#include <vector>
#include "ClickableSprite.h"
#include "Hexagon.h"

class HexField {
public:
    HexField(int x_pos, int y_pos, int size, int side);

    virtual ~HexField();

    void render();

    bool dirtWon();
    bool waterWon();
private:
    bool checkWinner(HexState candidate);

    int side;
    std::vector<std::vector<Hexagon*>> hexagons;
};


#endif //INC_2DPROJECT_HEXFIELD_H
