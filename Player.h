#pragma once

#include <string>

#include "BoardObject.h"
#include "Board.h"

#include "Teleport.h"

class Player : public BoardObject {
    public:
        char move;
        int kill_count = 0;
    private:
        int dirx = 0;
        int diry = 0;

        int prev_x;
        int prev_y;
        char prev_move;
    public:
        Player(unsigned int x, unsigned int y);

		//Overridden BoardObject functions
		void set_pos(int x, int y);
		
		//Player functions
        int get_dirx() { return dirx; }
        int get_diry() { return diry; }

        int get_prev_x() { return prev_x; }
        int get_prev_y() { return prev_y; }
        char get_prev_move() { return prev_move; }

		bool canMoveInto(int x, int y);
        bool canMoveInto(BoardObject* bo);

        void movementHandler(char move);
        void checkOnEnterEvents();
        void checkOnTouchEvents();
        void eventsHandler(char move);
};
