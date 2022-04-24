#pragma once

#include <string>

#include "Game.h"

class Board;
class Player;

class BoardObject {
    protected:
    	Game *game;
    	
        unsigned int x;
        unsigned int y;

        char c;
        int color = 0x07; // 0x, 0 -> black, 7 -> console white
        
        unsigned int id;
        static unsigned int ID;

        std::string classname = "nullBoardObject";
        
        bool moveInto= false;
        bool interactWith = false;

        Board* board;

    public:
        BoardObject(unsigned int x, unsigned int y, char c, Board* board);

        std::string get_classname() { return this->classname; }

        int get_id() { return this->id; }

        int get_x() { return this->x; }
        int get_y() { return this->y; }
        void set_pos(int x, int y);

        char get_char() { return this->c; }
        void set_char(char c) { this->c = c; }

        int get_color() { return this->color; }
        void set_color(int color) { this->color = color; }

        Board* get_board() { return this->board; }
        void set_board(Board* board) { this->board = board; }
        
        bool get_moveInto() { return this->moveInto; }
        void set_moveInto(bool canMoveInto) { this->moveInto = canMoveInto; }

        bool get_interactWith() { return this->interactWith; }
        void set_interactWith(bool canBeInteractedWith) { this->interactWith = canBeInteractedWith; }
        
        virtual void onEnterEvent(Player* player) {};
        virtual void onTouchEvent(Player* player) {};
        
        friend class Game;
        friend class Board;
};

class Void : public BoardObject {
    public:
        Void(unsigned int x, unsigned int y, Board* board);
};
