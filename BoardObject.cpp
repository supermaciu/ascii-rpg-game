#include "BoardObject.h"
#include "Board.h"

BoardObject::BoardObject(unsigned int x, unsigned int y, char c, Board* board) {
	this->x = (x >= board->get_width() ? board->get_width()-1 : x);
    this->y = (y >= board->get_height() ? board->get_height()-1 : y);

    this->c = c;

    this->board = board;

    ID++;
    id = ID;
}

void BoardObject::set_pos(int x, int y) {
	BoardObject* bo = this->board->getBoardObjectByCoords(x, y);
	if (bo != nullptr) {
		this->board->deleteFromBoard(bo, true);
	}
	
	this->x = x;
	this->y = y;
}

unsigned int BoardObject::ID = 0;

Void::Void(unsigned int x, unsigned int y, Board* board)
	: BoardObject(x, y, c, board) {
    this->classname = "Void";
    this->moveInto = false;
    
	this->c = ' ';
	this->color = 0x08;

	this->board->addToBoard(this);
}
