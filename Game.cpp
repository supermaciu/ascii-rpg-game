#include "Game.h"

#include "BoardObject.h"
#include "Board.h"
#include "Player.h"

#include <iostream>
#include <cstdlib>
#include <string>
#include <cwchar>

Game Game::instance;

Game::~Game() {
    if (debug_mode) {
        system("cls");
        setConsoleBufferSize(get_console_width(), 500);

        for (Board* b : boards) {
            if (b->hasBoardObjects()) {
                std::cout << b->get_name() << ":" << std::endl;

                for (BoardObject* bo : b->getBoardObjects()) {
                    std::cout << "[" << get_current_time() << "]" << " Deleting (" << bo->get_id() << ") ";
                    
                    SetConsoleTextAttribute(handle, bo->get_color());
                    std::cout << bo->get_classname();
                    SetConsoleTextAttribute(handle, 0x07);
                    
                    std::cout << " from " 
                        << bo->get_board()->get_name() << " with address " << bo << std::endl;
                    current_board->deleteFromBoard(bo, true); // has delete in it
                }
            }
        }
        
        std::cout << std::endl << "Boards:" << std::endl;
        
        for (Board* b : boards) {
            std::cout << "[" << get_current_time() << "]"  << " Deleting (" << b << ") " << b->get_name() << std::endl;
            delete b;
        }

        std::cout << std::endl << std::endl << "Done!" << std::endl;

        system("pause");
        exit(0);
    }
}

void Game::IsetTitle(const std::string& game_name) {
    std::string str(game_name);
    SetConsoleTitle(str.c_str());
}

void Game::IsetCursorVisibility(bool show_cursor) {
    handle = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleCursorInfo(handle, &consoleCursorInfo);

    consoleCursorInfo.bVisible = show_cursor;
    consoleCursorInfo.dwSize = 100;
    SetConsoleCursorInfo(handle, &consoleCursorInfo);
}

void Game::IresizeWindow(int width, int height) {
    consoleWindow = GetConsoleWindow();
	RECT console_rect;

	GetWindowRect(consoleWindow, &console_rect);

	MoveWindow(consoleWindow, console_rect.left, console_rect.top, width, height, TRUE);
}

void Game::ImoveWindow(int x, int y) {
    consoleWindow = GetConsoleWindow();
    RECT rectClient, rectWindow;
    
    GetClientRect(consoleWindow, &rectClient);
    GetWindowRect(consoleWindow, &rectWindow);
    
    MoveWindow(consoleWindow, x, y, rectClient.right - rectClient.left, rectClient.bottom - rectClient.top, TRUE);
}

void Game::ImoveWindowCenter() {
    consoleWindow = GetConsoleWindow();
    RECT rectClient, rectWindow;
    
    GetClientRect(consoleWindow, &rectClient);
    GetWindowRect(consoleWindow, &rectWindow);
    
    int screenx, screeny, posx, posy;
    screenx = GetSystemMetrics(SM_CXSCREEN);
    screeny = GetSystemMetrics(SM_CYSCREEN);
    
    int sizex = 600, sizey = 200;
    
    posx = screenx / 2 - (rectWindow.right - rectWindow.left) / 2;
    posy = screeny / 2 - (rectWindow.bottom - rectWindow.top) / 2;
    
    MoveWindow(consoleWindow, posx, posy, rectClient.right - rectClient.left, rectClient.bottom - rectClient.top, TRUE);
    //MoveWindow(consoleWindow, posx, posy, (rectClient.right - rectClient.left) + sizex, (rectClient.bottom - rectClient.top), TRUE);
}

void Game::IsetConsoleBufferSize(int x, int y) {
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	
	if (x <= 0 or y <= 0) {
		coord.X = get_console_width();
    	coord.Y = get_console_height();
	} else {
		coord.X = x;
    	coord.Y = y;
	}
    
    SetConsoleScreenBufferSize(handle, coord); // deletes scrollbar / shortens the buffer
}

void Game::ImaxemizeWindow(bool maxemize) {
	if (maxemize) {
		consoleWindow = GetConsoleWindow();
		ShowWindow(consoleWindow, SW_MAXIMIZE); // maxemizes console window
	} else {
		consoleWindow = GetConsoleWindow();
		ShowWindow(consoleWindow, SW_NORMAL); // maxemizes console window
	}
}

void Game::IresizeableWindow(bool can_resize) {
	if (!can_resize) {
		consoleWindow = GetConsoleWindow();
	    SetWindowLong(consoleWindow, GWL_STYLE,
		GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX); // makes window non resizable
	} else {
		consoleWindow = GetConsoleWindow();
	    SetWindowLong(consoleWindow, GWL_STYLE,
		GetWindowLong(consoleWindow, GWL_STYLE)); // makes window resizable
	}
}

void Game::IdisableInput(bool disable) {
	consoleWindow = GetConsoleWindow();
	
	if (disable) {
		EnableWindow(consoleWindow, false);
	} else {
		EnableWindow(consoleWindow, true);
	}
}

void Game::Iset_current_board(Board *board) {
    if (board == current_board) {
        return;
    }

    current_board = board;
}

void Game::IshowBoard() {
    current_board->render();
    system("cls");
    current_board->draw();
}

void Game::Idebug(Player* player) {
    if (!debug_mode) return;

    int dx = 4, dy = 3;

    if (debug_mode) {
        setCursor(dx, dy);
        std::cout << player->get_classname() << ": ";

        setCursor(dx+1, dy+1);
        std::cout << "Board: " << current_board->get_name();

        setCursor(dx+1, dy+2);
        std::cout << "x, y: " << player->get_x() << ", " << player->get_y();

        setCursor(dx+1, dy+3);
        std::cout << "kill count: " << player->kill_count;

        dy += 5;
        
        int s = (current_board->getBoardObjects().size() >= 5) ? 5 : current_board->getBoardObjects().size();
        for (int i = 0; i != s; i++) {
            setCursor(dx, dy+i*4);
            std::cout << current_board->getBoardObjects()[i]->get_id() << " : "
                << current_board->getBoardObjects()[i]->get_classname() << ": ";

            setCursor(dx+1, dy+i*4+1);
            std::cout << "Board: " << current_board->getBoardObjects()[i]->get_board()->get_name();

            setCursor(dx+1, dy+i*4+2);
            std::cout << "x: " << current_board->getBoardObjects()[i]->get_x();

            setCursor(dx+1, dy+i*4+3);
            std::cout << "y: " << current_board->getBoardObjects()[i]->get_y();
        }

        dy -= 5;

        setCursor(1, 1);
        std::cout << "current board: (" << current_board->get_id() << ") " << current_board->get_name();

        setCursor(1, get_console_height()-1);
        std::cout << "prev_move: " << player->get_prev_move() << " - " << int(player->get_prev_move());

        setCursor(20, get_console_height()-1);
        std::cout << "prev_x: " << player->get_prev_x() << " prev_y: " << player->get_prev_y();

        setCursor(1, get_console_height());
        std::cout << "move: " << player->move << " - " << int(player->move);

        setCursor(22, get_console_height());
        std::cout << "dirx: " << player->get_dirx() << " diry: " << player->get_diry();

        std::vector<std::vector<int> > infoPos = {
            {(get_console_width()/2-20-current_board->get_width()*2), (get_console_height()/2)},
            {(get_console_width()/2+current_board->get_width()*2), (get_console_height()/2)},
            {(get_console_width()/2-5), (get_console_height()/2-current_board->get_height())},
            {(get_console_width()/2-5), (get_console_height()/2+current_board->get_height())}
        };

        std::vector<BoardObject*> playerSurrounds = {
            current_board->getBoardObjectByCoords(player->get_x()-1, player->get_y()),
            current_board->getBoardObjectByCoords(player->get_x()+1, player->get_y()),
            current_board->getBoardObjectByCoords(player->get_x(), player->get_y()-1),
            current_board->getBoardObjectByCoords(player->get_x(), player->get_y()+1)
        };

        for (int i = 0; i < playerSurrounds.size(); i++) {
            BoardObject* bo = playerSurrounds[i];

            if (bo == nullptr) continue;

            setCursor(infoPos[i][0], infoPos[i][1]);
            std::cout << "[" << bo->get_id() << "]" << " : "
                << bo->get_name() << " (" << bo->get_classname() << ")" << ": ";
                
            setCursor(infoPos[i][0], infoPos[i][1]+1);
			std::cout << "c: " << bo->get_char();
			
			setCursor(infoPos[i][0], infoPos[i][1]+2);
			std::cout << "get_moveInto: " << bo->get_moveInto();

            setCursor(infoPos[i][0], infoPos[i][1]+3);
			std::cout << "get_interactWith: " << bo->get_interactWith();
        }
    }
}

std::vector<Board*> Game::IgetAllBoards() {
	return boards;
}

Board* Game::IgetBoardById(int id) {
    for (Board* board : boards) {
        if (board->get_id() == id) {
            return board;
        }
    }

    return nullptr;
}

std::vector<BoardObject*> Game::IgetAllBoardObjects() {
    std::vector<BoardObject*> bos = {};

    for (Board* board : getAllBoards()) {
        for (BoardObject* bo : board->getBoardObjects()) {
            bos.push_back(bo);
        }
    }

    return bos;
}

void Game::ImenuExitGame() {
    system("cls");
    std::string str = "Are you sure? (y/n)";
    setCursor(get_console_width()/2-str.size()/2, get_console_height()/2);
    
    for (char c : str) {
        std::cout << c;
        Sleep(10);
    }
    
    char move = getch();
    
    if (move == 'e' || move == 'E' || move == 'y' || move == 'Y' || move == 13) {
        exit(0);
    }
}