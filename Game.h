#pragma once

#include <string>

#include "Utilities.h"

class Board;
class BoardObject;
class Player;

class Game {
    private:
        std::string game_name;

        HWND consoleWindow; // console window handle
        HANDLE handle; // handles changes made to command prompt
        
        COORD coord; // coordinates
        CONSOLE_CURSOR_INFO consoleCursorInfo; // console cursor options

        std::vector<Board*> boards = {};
        Board* current_board = nullptr;
    
    public:
        Game() = default;
    
        Game(const std::string& game_name);

        ~Game();
        
        HANDLE get_handle() { return this->handle; }

        void setTitle(const std::string& game_name);
        void setCursorVisibility(bool show_cursor);
        void resizeWindow(int width, int height);
        void moveWindow(int x, int y);
        void moveWindowCenter();
        void setConsoleBufferSize(int x, int y);
        void maxemizeWindow(bool maxemize);
        void resizeableWindow(bool can_resize);
        void disableInput(bool disable);

        Board* get_current_board() { return this->current_board; };
        void set_current_board(Board *board);
        
        void showBoard();
        
        Board* getBoardByName(const std::string& name);
        std::vector<Board*> getAllBoards();
        std::vector<BoardObject*> getAllBoardObjects();
        
        void addBoard(Board* board) { boards.push_back(board); }
        
        void debug(bool debug_mode, Player *player);
};