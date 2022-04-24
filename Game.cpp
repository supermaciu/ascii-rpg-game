#include "Game.h"

#include "BoardObject.h"
#include "Board.h"
#include "Player.h"

#include <iostream>
#include <cstdlib>
#include <string>
#include <cwchar>

Game::Game(const std::string& game_name) {
    this->game_name = game_name;

    std::string str(game_name);
    SetConsoleTitle(str.c_str());
}

Game::~Game() {
    system("cls");
    this->setConsoleBufferSize(get_console_width(), 500);

    for (Board* b : this->boards) {
        if (b->hasBoardObjects()) {
            std::cout << b->get_name() << ":" << std::endl;

            for (BoardObject* bo : b->getBoardObjects()) {
                std::cout << " Deleting (" << bo->get_id() << ") ";
                
                SetConsoleTextAttribute(this->handle, bo->get_color());
                std::cout << bo->get_classname();
                SetConsoleTextAttribute(this->handle, 0x07);
                
                std::cout << " from " 
					<< bo->get_board()->get_name() << " with address " << bo << std::endl;
                this->current_board->deleteFromBoard(bo, true); // has delete in it
            }
        }
    }
    
    std::cout << std::endl << "boards:" << std::endl;
    
    for (Board* b : this->boards) {
    	std::cout << "Deleting (" << b << ") " << b->get_name() << std::endl;
        delete b;
    }

	std::cout << std::endl << std::endl << "Done!" << std::endl;

    system("pause");
}

void Game::setTitle(const std::string& game_name) {
    std::string str(game_name);
    SetConsoleTitle(str.c_str());
}

void Game::setCursorVisibility(bool show_cursor) {
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &this->consoleCursorInfo);
    this->consoleCursorInfo.bVisible = show_cursor;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &this->consoleCursorInfo);
}

void Game::resizeWindow(int width, int height) {
    this->consoleWindow = GetConsoleWindow();
	RECT console_rect;

	GetWindowRect(consoleWindow, &console_rect);

	MoveWindow(consoleWindow, console_rect.left, console_rect.top, width, height, TRUE);
}

void Game::moveWindow(int x, int y) {
    this->consoleWindow = GetConsoleWindow();
    RECT rectClient, rectWindow;
    
    GetClientRect(consoleWindow, &rectClient);
    GetWindowRect(consoleWindow, &rectWindow);
    
    MoveWindow(consoleWindow, x, y, rectClient.right - rectClient.left, rectClient.bottom - rectClient.top, TRUE);
}

void Game::moveWindowCenter() {
    this->consoleWindow = GetConsoleWindow();
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

void Game::setConsoleBufferSize(int x, int y) {
	this->handle = GetStdHandle(STD_OUTPUT_HANDLE);
	
	if (x <= 0 or y <= 0) {
		this->coord.X = get_console_width();
    	this->coord.Y = get_console_height();
	} else {
		this->coord.X = x;
    	this->coord.Y = y;
	}
    
    SetConsoleScreenBufferSize(this->handle, this->coord); // deletes scrollbar / shortens the buffer
}

void Game::maxemizeWindow(bool maxemize) {
	if (maxemize) {
		this->consoleWindow = GetConsoleWindow();
		ShowWindow(consoleWindow, SW_MAXIMIZE); // maxemizes console window
	} else {
		this->consoleWindow = GetConsoleWindow();
		ShowWindow(consoleWindow, SW_NORMAL); // maxemizes console window
	}
}

void Game::resizeableWindow(bool can_resize) {
	if (!can_resize) {
		this->consoleWindow = GetConsoleWindow();
	    SetWindowLong(this->consoleWindow, GWL_STYLE,
		GetWindowLong(this->consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX); // makes window non resizable
	} else {
		this->consoleWindow = GetConsoleWindow();
	    SetWindowLong(this->consoleWindow, GWL_STYLE,
		GetWindowLong(this->consoleWindow, GWL_STYLE)); // makes window resizable
	}
}

void Game::disableInput(bool disable) {
	this->consoleWindow = GetConsoleWindow();
	
	if (disable) {
		EnableWindow(this->consoleWindow, false);
	} else {
		EnableWindow(this->consoleWindow, true);
	}
}

void Game::set_current_board(Board *board) {
    if (board == this->current_board) {
        return;
    }

    this->current_board = board;
    this->current_board->game = this;
    // add board to boards?
}

void Game::showBoard() {
    this->current_board->render();

    system("cls"); // clipping
    this->current_board->draw();
}

void Game::debug(bool debug_mode, Player* player) {
    int dx = 4, dy = 3;

    if (debug_mode) {
        setCursor(dx, dy);
        std::cout << player->get_classname() << ": ";

        setCursor(dx+1, dy+1);
        std::cout << "Board: " << this->current_board->get_name();

        setCursor(dx+1, dy+2);
        std::cout << "x, y: " << player->get_x() << ", " << player->get_y();

        setCursor(dx+1, dy+3);
        std::cout << "kill count: " << player->kill_count;

        dy += 5;
        
        int s = (this->current_board->getBoardObjects().size() >= 5) ? 5 : this->current_board->getBoardObjects().size();
        for (int i = 0; i != s; i++) {
            setCursor(dx, dy+i*4);
            std::cout << this->current_board->getBoardObjects()[i]->get_id() << " : "
                << this->current_board->getBoardObjects()[i]->get_classname() << ": ";

            setCursor(dx+1, dy+i*4+1);
            std::cout << "Board: " << this->current_board->getBoardObjects()[i]->get_board()->get_name();

            setCursor(dx+1, dy+i*4+2);
            std::cout << "x: " << this->current_board->getBoardObjects()[i]->get_x();

            setCursor(dx+1, dy+i*4+3);
            std::cout << "y: " << this->current_board->getBoardObjects()[i]->get_y();
        }

        dy -= 5;

//        setCursor(get_console_width()/2+20,get_console_height()/2-1);
//        std::cout << "Info by id (1): " << this->current_board->getBoardObjectById(1)->get_x()
//            << " " << this->current_board->getBoardObjectById(1)->get_y();
//
//        setCursor(get_console_width()/2+20,get_console_height()/2);
//        std::cout << "Info by classname (Enemy count): " << this->current_board->getBoardObjectsByClassname("Enemy").size();

        setCursor(1, 1);
        std::cout << "current board: " << this->current_board->get_name();

        setCursor(1, get_console_height()-1);
        std::cout << "prev_move: " << player->get_prev_move() << " - " << int(player->get_prev_move());

        setCursor(20, get_console_height()-1);
        std::cout << "prev_x: " << player->get_prev_x() << " prev_y: " << player->get_prev_y();

        setCursor(1, get_console_height());
        std::cout << "move: " << player->move << " - " << int(player->move);

        setCursor(22, get_console_height());
        std::cout << "dirx: " << player->get_dirx() << " diry: " << player->get_diry();

		int midx = get_console_width()/2;
		int midy = get_console_height()/2;
		
		BoardObject* bo_x1 = this->current_board->getBoardObjectByCoords(player->get_x()-1, player->get_y());
		BoardObject* bo_x2 = this->current_board->getBoardObjectByCoords(player->get_x()+1, player->get_y());
		BoardObject* bo_y1 = this->current_board->getBoardObjectByCoords(player->get_x(), player->get_y()-1);
		BoardObject* bo_y2 = this->current_board->getBoardObjectByCoords(player->get_x(), player->get_y()+1);

		if (bo_x1 != nullptr) {
			setCursor(midx-14-this->current_board->get_width()*2, midy);
			std::cout << bo_x1->get_id() << " : "
                << bo_x1->get_classname() << ": ";
                
            setCursor(midx-14-this->current_board->get_width()*2, midy+1);
			std::cout << "c: " << bo_x1->get_char();
			
			setCursor(midx-14-this->current_board->get_width()*2, midy+2);
			std::cout << "get_moveInto: " << bo_x1->get_moveInto();

            setCursor(midx-14-this->current_board->get_width()*2, midy+3);
			std::cout << "get_interactWith: " << bo_x1->get_interactWith();
		} 
		if (bo_x2 != nullptr) {
			setCursor(midx-5+this->current_board->get_width()*2, midy);
			std::cout << bo_x2->get_id() << " : "
                << bo_x2->get_classname() << ": ";
            
            setCursor(midx-5+this->current_board->get_width()*2, midy+1);
			std::cout << "c: " << bo_x2->get_char();
			
			setCursor(midx-5+this->current_board->get_width()*2, midy+2);
			std::cout << "get_moveInto: " << bo_x2->get_moveInto();

            setCursor(midx-5+this->current_board->get_width()*2, midy+3);
			std::cout << "get_interactWith: " << bo_x2->get_interactWith();
		}
		if (bo_y1 != nullptr) {
			setCursor(midx-5, midy-this->current_board->get_height());
			std::cout << bo_y1->get_id() << " : "
                << bo_y1->get_classname() << ": ";
            
            setCursor(midx-5, midy-this->current_board->get_height()+1);
			std::cout << "c: " << bo_y1->get_char();
			
			setCursor(midx-5, midy-this->current_board->get_height()+2);
			std::cout << "get_moveInto: " << bo_y1->get_moveInto();

            setCursor(midx-5, midy-this->current_board->get_height()+3);
			std::cout << "get_interactWith: " << bo_y1->get_interactWith();
		}
		if (bo_y2 != nullptr) {
			setCursor(midx-5, midy+this->current_board->get_height());
			std::cout << bo_y2->get_id() << " : "
                << bo_y2->get_classname() << ": ";
                
            setCursor(midx-5, midy+this->current_board->get_height()+1);
			std::cout << "c: " << bo_y2->get_char();
			
			setCursor(midx-5, midy+this->current_board->get_height()+2);
			std::cout << "get_moveInto: " << bo_y2->get_moveInto();

            setCursor(midx-5, midy+this->current_board->get_height()+3);
			std::cout << "get_interactWith: " << bo_y2->get_interactWith();
		}
    }
}

std::vector<Board*> Game::getAllBoards() {
	return this->boards;
}

Board* Game::getBoardByName(const std::string& name) {
    for (Board* board : this->getAllBoards()) {
        if (board->get_name() == name) {
            return board;
        }
    }

    return nullptr;
}

std::vector<BoardObject*> Game::getAllBoardObjects() {
    std::vector<BoardObject*> bos = {};

    // for (Board* b : this->getAllBoards()) {
    //     bos.insert(b->getBoardObjects().begin(), b->getBoardObjects().begin(), b->getBoardObjects().end());
    // }

    for (Board* board : this->getAllBoards()) {
        for (BoardObject* bo : board->getBoardObjects()) {
            bos.push_back(bo);
        }
    }

    // for (int i = 0; i < bos.size()-1; i++) {
    //     for (int j = 0; j < bos.size()-1; j++) {
    //         if (bos[j]->get_id() > bos[j+1]->get_id()) {
    //             std::swap(bos[j], bos[j+1]);
    //         }
    //     }
    // }

    return bos;
}