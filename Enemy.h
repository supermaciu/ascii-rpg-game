#pragma once

#include <string>

#include "BoardObject.h"
class Board;

class Enemy : public BoardObject {
    public:
        Enemy(unsigned int x, unsigned int y, Board* board);
        
        void onEnterEvent(Player* player) override;
};
