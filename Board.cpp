#include "Board.h"

#include "Game.h"
#include "BoardObject.h"

#include "Utilities.h"

Board::Board(unsigned int width, unsigned int height) {
    this->width = (width < BOARD_LIMIT_MIN) ? BOARD_LIMIT_MIN : ((width > BOARD_LIMIT_MAX) ? BOARD_LIMIT_MAX : width);
    this->height = (height < BOARD_LIMIT_MIN) ? BOARD_LIMIT_MIN : ((height > BOARD_LIMIT_MAX) ? BOARD_LIMIT_MAX : height);

    Game::addBoard(this);

    ID++;
    this->id = ID;
}

Board::Board(const std::string& name, unsigned int width, unsigned int height) {
    this->name = name;

    this->width = (width < BOARD_LIMIT_MIN) ? BOARD_LIMIT_MIN : ((width > BOARD_LIMIT_MAX) ? BOARD_LIMIT_MAX : width);
    this->height = (height < BOARD_LIMIT_MIN) ? BOARD_LIMIT_MIN : ((height > BOARD_LIMIT_MAX) ? BOARD_LIMIT_MAX : height);

    Game::addBoard(this);

    ID++;
    this->id = ID;
}

unsigned int Board::ID = 0;

void Board::render() {
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            board[x][y] = '_';

            for (BoardObject *bo : board_objects) {
                if (bo->get_x() == x && bo->get_y() == y && board[x][y] != '@') { // more constants -> Utilities.h
                    board[x][y] = bo->get_char();
                }
            }
        }
    }
}

void Board::draw() {
    setCursor((get_console_width()/2 - width), (get_console_height()/2 - height/2)-1);
    std::cout << name;

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            setCursor((get_console_width()/2 - width) + 2 * x, (get_console_height()/2 - height/2) + y);

            BoardObject* bo = getBoardObjectByCoords(x, y);
            if (bo != nullptr) {
                SetConsoleTextAttribute(Game::get_handle(), bo->get_color());
            } else {
                SetConsoleTextAttribute(Game::get_handle(), board_color);
            }
			    
            std::cout << board[x][y];
        }
    }

    SetConsoleTextAttribute(Game::get_handle(), 0x07);
}

bool Board::hasBoardObjects() {
	return !this->board_objects.empty();
}

void Board::deleteFromBoard(BoardObject* board_object, bool delete_object_in_memory) {
    if (board_object != nullptr) {
        board_objects.erase(std::remove(this->board_objects.begin(), this->board_objects.end(), board_object), this->board_objects.end());
        board_object->set_board(nullptr);

        if (delete_object_in_memory) {
            delete board_object;
            board_object = nullptr;
        }
    }
}

void Board::addToBoard(BoardObject* board_object) {
    if (board_object != nullptr) {
        for (BoardObject *bo : board_objects) {
            if (board_object->get_board() == bo->get_board() && board_object->get_x() == bo->get_x() && board_object->get_y() == bo->get_y()) {
                deleteFromBoard(bo, false);
                bo = board_object;
            }
        }
    }

    board_objects.push_back(board_object);

    board_object->set_board(this);
}

std::vector<BoardObject*> Board::getBoardObjects() {
    return board_objects;
}

BoardObject* Board::getBoardObjectById(int id) {
    for (BoardObject *bo : board_objects) {
        if (bo->get_id() == id) {
            return bo;
        }
    }

    return nullptr;
}

std::vector<BoardObject*> Board::getBoardObjectsByClassname(std::string classname) {
    std::vector<BoardObject*> bos = {};

    for (BoardObject *bo : board_objects) {
        if (bo->get_classname() == classname) {
            bos.push_back(bo);
        }
    }

    return bos;
}

BoardObject* Board::getBoardObjectByCoords(int x, int y) {
	for (BoardObject *bo : board_objects) {
        if (bo->get_x() == x && bo->get_y() == y) {
            return bo;
        }
    }
    
    return nullptr;
}
