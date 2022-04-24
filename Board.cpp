#include "Board.h"
#include "BoardObject.h"

#include "Utilities.h"

Board::Board(unsigned int width, unsigned int height, Game* game) {
    this->width = (width < BOARD_LIMIT_MIN) ? BOARD_LIMIT_MIN : ((width > BOARD_LIMIT_MAX) ? BOARD_LIMIT_MAX : width);
    this->height = (height < BOARD_LIMIT_MIN) ? BOARD_LIMIT_MIN : ((height > BOARD_LIMIT_MAX) ? BOARD_LIMIT_MAX : height);

    this->game = game;
    this->game->addBoard(this);
}

Board::Board(const std::string& name, unsigned int width, unsigned int height, Game* game) {
    this->name = name;

    this->width = (width < BOARD_LIMIT_MIN) ? BOARD_LIMIT_MIN : ((width > BOARD_LIMIT_MAX) ? BOARD_LIMIT_MAX : width);
    this->height = (height < BOARD_LIMIT_MIN) ? BOARD_LIMIT_MIN : ((height > BOARD_LIMIT_MAX) ? BOARD_LIMIT_MAX : height);

    this->game = game;
    this->game->addBoard(this);
}

void Board::render() {
    // bool render_board_objects = false;

    // if (!this->board_objects.empty()) {
    //     render_board_objects = true;
    // }

    // for (int x = 0; x < this->width; x++) {
    //     for (int y = 0; y < this->height; y++) {
    //         this->board[x][y] = '_';

    //         if (render_board_objects) {
    //             for (BoardObject *p_bo : this->board_objects) {
    //                 if (p_bo->get_x() == x && p_bo->get_y() == y && this->board[x][y] != '@') { // more constants -> Utilities.h
    //                     this->board[x][y] = p_bo->get_char();
    //                 }
    //             }
    //         }
    //     }
    // }

    for (int x = 0; x < this->width; x++) {
        for (int y = 0; y < this->height; y++) {
            this->board[x][y] = '_';

            for (BoardObject *p_bo : this->board_objects) {
                if (p_bo->get_x() == x && p_bo->get_y() == y && this->board[x][y] != '@') { // more constants -> Utilities.h
                    this->board[x][y] = p_bo->get_char();
                }
            }
        }
    }
}

void Board::draw() {
    for (int x = 0; x < this->width; x++) {
        for (int y = 0; y < this->height; y++) {
            setCursor((get_console_width()/2 - width) + 2 * x, (get_console_height()/2 - height/2) + y);

            BoardObject* bo = this->getBoardObjectByCoords(x, y);
            if (bo != nullptr) {
                SetConsoleTextAttribute(this->game->get_handle(), bo->get_color());
            } else {
                SetConsoleTextAttribute(this->game->get_handle(), 0x07);
            }
			    
            std::cout << this->board[x][y];
        }
    }

    SetConsoleTextAttribute(this->game->get_handle(), 0x07);
}

bool Board::hasBoardObjects() {
	return !this->board_objects.empty();
}

void Board::deleteFromBoard(BoardObject* board_object, bool delete_object_in_memory) {
    if (board_object != nullptr) {
        this->board_objects.erase(std::remove(this->board_objects.begin(), this->board_objects.end(), board_object), this->board_objects.end());
        board_object->set_board(nullptr);

        if (delete_object_in_memory) {
            delete board_object;
            board_object = nullptr;
        }
    }
}

void Board::addToBoard(BoardObject* board_object) {
    if (board_object != nullptr) {
        for (BoardObject *p_bo : this->board_objects) {
            if (board_object->get_board() == p_bo->get_board() && board_object->get_x() == p_bo->get_x() && board_object->get_y() == p_bo->get_y()) {
                deleteFromBoard(p_bo, false);
                p_bo = board_object;
            }
        }
    }

    this->board_objects.push_back(board_object);

    board_object->game = this->game;
    board_object->board = this;
}

std::vector<BoardObject*> Board::getBoardObjects() {
    return this->board_objects;
}

BoardObject* Board::getBoardObjectById(int id) {
    for (BoardObject *p_bo : this->board_objects) {
        if (p_bo->get_id() == id) {
            return p_bo;
        }
    }

    return nullptr;
}

std::vector<BoardObject*> Board::getBoardObjectsByClassname(std::string classname) {
    std::vector<BoardObject*> bos = {};

    for (BoardObject *p_bo : this->board_objects) {
        if (p_bo->get_classname() == classname) {
            bos.push_back(p_bo);
        }
    }

    return bos;
}

BoardObject* Board::getBoardObjectByCoords(int x, int y) {
	for (BoardObject *p_bo : this->board_objects) {
        if (p_bo->get_x() == x && p_bo->get_y() == y) {
            return p_bo;
        }
    }
    
    return nullptr;
}
