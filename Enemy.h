#pragma once

#include <string>

#include "BoardObject.h"
class Board;

class Enemy : public BoardObject {
    public:
        Enemy(unsigned int x, unsigned int y);
        
        void onTouchEvent(Player* player) override;
};

class Spider : public Enemy {
    public:
        Spider(unsigned int x, unsigned int y);
};