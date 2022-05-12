#pragma once

#include <string>

#include "BoardObject.h"
//has to be included -> Teleport is a derived class
class Board;

class Teleport : public BoardObject {
    private:
        unsigned int dest_x = 0;
        unsigned int dest_y = 0;
        Board* dest_board = nullptr;

        bool tp_set = false;
        bool dynamic = false;
	public:
        Teleport(unsigned int x, unsigned int y);

        ~Teleport();

        bool is_set() { return tp_set; }
        
        void setDestination(unsigned int x2, unsigned int y2, Board* board2, bool dynamic=false);
        void unsetDestination();

        Board* get_dest_board() { return dest_board; }

		void onTouchEvent(Player* player) override;
};