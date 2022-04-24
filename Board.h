#pragma once

#include <vector>
#include <string>

class Game;

class BoardObject;

class Board {
    private:
        Game *game;

        const int BOARD_LIMIT_MIN = 2;
        const int BOARD_LIMIT_MAX = 100;

        std::string name = "nullBoard";

        int width;
        int height;

        char board[100][100] = {};
        std::vector<BoardObject*> board_objects = {};
    public:
        Board(unsigned int width, unsigned int height, Game* game);

        Board(const std::string& name, unsigned int width, unsigned int height, Game* game);

        std::string get_name() { return this->name; }
        void set_name(std::string name) { this->name = name; }

        int get_width() { return this->width; }
        int get_height() { return this->height; }

        void render();
        void draw();

        bool hasBoardObjects();

        void addToBoard(BoardObject* board_object);
        void deleteFromBoard(BoardObject* board_object, bool delete_object_in_memory);

        std::vector<BoardObject*> getBoardObjects();
        BoardObject* getBoardObjectById(int id);
        std::vector<BoardObject*> getBoardObjectsByClassname(std::string classname);
        BoardObject* getBoardObjectByCoords(int x, int y);

        friend class Game;
};
