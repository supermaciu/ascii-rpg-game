#pragma once

#include <string>

class Board;
class Player;

class BoardObject {
    protected:
        //BoardObject
        std::string classname = "nullBoardObject";

        unsigned int x;
        unsigned int y;

        char c = '?';
        int color = 0x07; // 0x, 0 -> black, 7 -> console white
        
        unsigned int id;
        static unsigned int ID;
        
        bool moveInto = false;
        bool interactWith = false;

        Board* board;

        //Entity
        std::string name;

        int level = -1;
        int health = -1;
        int max_health = -1;
        int damage = -1;

        void setStats(const std::string& name, int level, int health, int damage) {
            this->name = name;
            this->level = level;
            this->health = health;
            this->max_health = health;
            this->damage = damage;
        }

    public:
        BoardObject(unsigned int x, unsigned int y);

        //BoardObject
        std::string get_classname() { return classname; }

        int get_id() { return id; }

        int get_x() { return x; }
        int get_y() { return y; }
        void set_pos(int x, int y);

        char get_char() { return c; }
        void set_char(char c) { this->c = c; }

        int get_color() { return color; }
        void set_color(int color) { this->color = color; }

        Board* get_board() { return board; }
        void set_board(Board* board) { this->board = board; }
        
        bool get_moveInto() { return moveInto; }
        void set_moveInto(bool canMoveInto) { this->moveInto = canMoveInto; }

        bool get_interactWith() { return interactWith; }
        void set_interactWith(bool canBeInteractedWith) { this->interactWith = canBeInteractedWith; }
        
        virtual void onEnterEvent(Player* player) {};
        virtual void onTouchEvent(Player* player) {};

        //Entity
        std::string get_name() { return name; }
        void set_name(const std::string& name) { this->name = name; }

        int get_level() { return level; }
        void set_level(int level) { this->level = level; }

        int get_health() { return health; }
        int& R_get_health() { return health; }
        void set_health(int health) { this->health = health; }

        int get_max_health() { return max_health; }
        int& R_get_max_health() { return max_health; }
        void set_max_health(int max_health) { this->max_health = max_health; }

        int get_damage() { return damage; }
        void set_damage(int damage) { this->damage = damage; }

};

class Void : public BoardObject {
    public:
        Void(unsigned int x, unsigned int y);
};

class Pickup : public BoardObject {
    public:
        Pickup(unsigned int x, unsigned int y);

        void onEnterEvent(Player* player) override;
};
