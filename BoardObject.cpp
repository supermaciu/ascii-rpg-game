#include "BoardObject.h"

#include "Board.h"
#include "Player.h"

BoardObject::BoardObject(unsigned int x, unsigned int y) {
	this->x = x;
    this->y = y;

    ID++;
    this->id = ID;
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

Void::Void(unsigned int x, unsigned int y)
	: BoardObject(x, y) {
    this->classname = "Void";
    this->moveInto = false;
    
	this->c = ' ';
	this->color = 0x08;
}

Pickup::Pickup(unsigned int x, unsigned int y)
	: BoardObject(x, y) {
	this->classname = "Pickup";
	this->moveInto = true;

	this->c = '#';
	this->color = 0x0f;
}

void Pickup::onEnterEvent(Player* player) {
	player->set_health(player->get_max_health());
	board->deleteFromBoard(this, true);
}