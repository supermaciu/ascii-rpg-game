#pragma once

#include <vector>
#include <string>

class Game;

class BoardObject;

class Board {
    private:
        unsigned int id;
        static unsigned int ID;

        const int BOARD_LIMIT_MIN = 2;
        const int BOARD_LIMIT_MAX = 100;

        std::string name = "nullBoard";

        int width;
        int height;

        char board[100][100] = {};
        int board_color = 0x07;

        std::vector<BoardObject*> board_objects = {};
    public:
        Board(unsigned int width, unsigned int height);

        Board(const std::string& name, unsigned int width, unsigned int height);

        int get_id() { return this->id; }

        std::string get_name() { return this->name; }
        void set_name(std::string name) { this->name = name; }

        int get_width() { return this->width; }
        int get_height() { return this->height; }

        void set_color(int color) { board_color = color; }

        void render();
        void draw();

        bool hasBoardObjects();

        void addToBoard(BoardObject* board_object);
        void deleteFromBoard(BoardObject* board_object, bool delete_object_in_memory);

        std::vector<BoardObject*> getBoardObjects();
        BoardObject* getBoardObjectById(int id);
        std::vector<BoardObject*> getBoardObjectsByClassname(std::string classname);
        BoardObject* getBoardObjectByCoords(int x, int y);
};
