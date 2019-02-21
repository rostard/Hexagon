//
// Created by rostard on 14.02.19.
//

#include "HexField.h"
#include "Texture.h"

#include <queue>

void HexField::render() {
    for(auto &row : hexagons){
        for(auto &hex : row){
            hex->render();
        }
    }

}


HexField::HexField(int x_pos, int y_pos, int size, int side) : side(side){
    auto hexagonShape = new Texture("hexagon.png", GL_RGBA, GL_RGBA);

    for(int i = 0; i < side; i++){
        std::vector<Hexagon*> row;
        for(int j = 0; j < side; j++){
            float hex_size = float(size) / side;

            float eps = 4.f;
            float x = x_pos + j * hex_size * 1.5f + j*eps * 1.154700538f;
            float y = y_pos + i * hex_size * 0.865f * 2+ (j%2) * (hex_size * 0.865f + 0.5f * eps) + i*eps;
            Hexagon * sprite = new Hexagon(hexagonShape, {hex_size, 0.865f * hex_size}, {x, y}, {1, 0, 0, 1});

            row.push_back(sprite);
        }
        hexagons.push_back(row);
    }
}

HexField::~HexField() {
    for(auto &row : hexagons){
        for(auto &hex : row){
            delete hex;
        }
    }
}

bool HexField::dirtWon() {
    return checkWinner(DIRT);
}

bool HexField::waterWon() {
    return checkWinner(WATER);
}

bool HexField::checkWinner(HexState candidate) {
    std::vector<char> row(side, false);
    std::vector<std::vector<char>> reachable(side, row);

    std::queue<std::pair<int, int>> q;
    if(candidate == DIRT){
        for(int i = 0; i < side; i++){
            if(hexagons[i][0]->getState() == DIRT){
                q.push(std::make_pair(i, 0));
                reachable[i][0]= true;
            }
        }
    }
    else if(candidate == WATER){
        for(int i = 0; i < side; i++){
            if(hexagons[0][i]->getState() == WATER){
                q.push(std::make_pair(0, i));
                reachable[0][i]= true;
            }
        }
    }

    while(!q.empty()){
        auto coord = q.front();
        int i = coord.first;
        int j = coord.second;

        if (candidate == DIRT && j == side - 1) {
            return true;
        } else {
            if (candidate == WATER && i == side - 1)return true;
        }
        q.pop();

        if(i + 1 < side && hexagons[i+1][j]->getState() == candidate && !reachable[i+1][j]){
            q.push({i+1, j});
            reachable[i+1][j] = true;
        }
        if(i > 0 && hexagons[i-1][j]->getState() == candidate && !reachable[i-1][j]){
            q.push({i-1, j});
            reachable[i-1][j] = true;
        }
        if(j + 1 < side && hexagons[i][j+1]->getState() == candidate && !reachable[i][j+1]){
            q.push({i, j+1});
            reachable[i][j+1] = true;
        }
        if(j > 0 && hexagons[i][j-1]->getState() == candidate && !reachable[i][j-1]){
            q.push({i, j-1});
            reachable[i][j-1] = true;
        }
        if(!(j%2) && i>0 && j>0 && hexagons[i-1][j-1]->getState() == candidate && !reachable[i-1][j-1]){
            q.push({i-1, j-1});
            reachable[i-1][j-1] = true;
        }
        if(!(j%2) && i>0 && j+1<side && hexagons[i-1][j+1]->getState() == candidate && !reachable[i-1][j+1]){
            q.push({i-1, j+1});
            reachable[i-1][j+1] = true;
        }
        if((j%2) && i+1 < side && j>0 && hexagons[i+1][j-1]->getState() == candidate && !reachable[i+1][j-1]){
            q.push({i+1, j-1});
            reachable[i+1][j-1] = true;
        }
        if((j%2) && i+1 < side && j+1<side && hexagons[i+1][j+1]->getState() == candidate && !reachable[i+1][j+1]){
            q.push({i+1, j+1});
            reachable[i+1][j+1] = true;
        }


    }
    return false;
}
