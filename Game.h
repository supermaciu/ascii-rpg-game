#pragma once

#include <string>

#include "Utilities.h"

class Board;
class BoardObject;
class Player;

//Singleton class
class Game {
    protected:
    	Game() = default;

        ~Game();
        
        static Game instance;
        
        std::string game_name;

        HWND consoleWindow; // console window handle
        HANDLE handle; // handles changes made to command prompt
        
        COORD coord; // coordinates
        CONSOLE_CURSOR_INFO consoleCursorInfo; // console cursor options

        std::vector<Board*> boards = {};
        Board* current_board = nullptr;

        bool debug_mode = false;

        void IsetTitle(const std::string& game_name);
        void IsetCursorVisibility(bool show_cursor);
        void IresizeWindow(int width, int height);
        void ImoveWindow(int x, int y);
        void ImoveWindowCenter();
        void IsetConsoleBufferSize(int x, int y);
        void ImaxemizeWindow(bool maxemize);
        void IresizeableWindow(bool can_resize);
        void IdisableInput(bool disable);

        Board* Iget_current_board() { return current_board; };
        void Iset_current_board(Board *board);
        
        void IshowBoard();
        
        Board* IgetBoardById(int id);
        std::vector<Board*> IgetAllBoards();
        std::vector<BoardObject*> IgetAllBoardObjects();
        
        void IaddBoard(Board* board) { boards.push_back(board); }
        
        bool IgetDebugMode() { return debug_mode; }
        void IsetDebugMode(bool set) { debug_mode = set; }
        
        void Idebug(Player *player);

        void ImenuExitGame();
    
    public:
    	Game(Game &other) = delete;
    	void operator=(const Game&) = delete;
    	
    	static Game& Get() { return instance; }
    	
        static HANDLE& get_handle() { return Get().handle; }

        static void setTitle(const std::string& game_name) { Get().IsetTitle(game_name); }
        static void setCursorVisibility(bool show_cursor) { Get().IsetCursorVisibility(show_cursor); }
        static void resizeWindow(int width, int height) { Get().IresizeWindow(width, height); }
        static void moveWindow(int x, int y) { Get().ImoveWindow(x, y); }
        static void moveWindowCenter() { Get().ImoveWindowCenter(); }
        static void setConsoleBufferSize(int x, int y) { Get().IsetConsoleBufferSize(x, y); }
        static void maxemizeWindow(bool maxemize) { Get().ImaxemizeWindow(maxemize); }
        static void resizeableWindow(bool can_resize) { Get().IresizeableWindow(can_resize); }
        static void disableInput(bool disable) { Get().IdisableInput(disable); }

        static Board* get_current_board() { return Get().Iget_current_board(); }
        static void set_current_board(Board *board) { Get().Iset_current_board(board); }
        
        static void showBoard() { Get().IshowBoard(); }
        
        static std::vector<Board*> getAllBoards() { return Get().IgetAllBoards(); }
        static Board* getBoardById(int id) { return Get().IgetBoardById(id); }
        static std::vector<BoardObject*> getAllBoardObjects() { return Get().IgetAllBoardObjects(); }
        
        static void addBoard(Board* board) { Get().IaddBoard(board); }

        static bool getDebugMode() { return Get().IgetDebugMode(); }
        static void setDebugMode(bool set) { Get().IsetDebugMode(set); }
        
        static void debug(Player *player) { Get().Idebug(player); }

        static void menuExitGame() { Get().ImenuExitGame(); };
};
