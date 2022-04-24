#include "Teleport.h"

#include "Player.h"

Teleport::Teleport(unsigned int x, unsigned int y, Board* board) : BoardObject(x, y, c, board) {
    this->classname = "Teleport";
    this->moveInto = false;
    this->interactWith = true;

	this->c = '*';
    this->color = 0x03;

    // this->board = board;
    this->board->addToBoard(this);
}

Teleport::~Teleport() {
    this->moveInto = false;

    this->tp_set = false;
    this->dynamic = false;

    this->dest_x = 0;
    this->dest_y = 0;
    this->dest_board = nullptr;
}

void Teleport::setDestination(unsigned int dest_x, unsigned int dest_y, Board* dest_board, bool dynamic) {
	if (dest_x != 0 && dest_y != 0) {
		this->dest_x = dest_x;
		this->dest_y = dest_y;
	}
    this->dest_board = dest_board;
    
	this->tp_set = true;
    this->dynamic = dynamic;
}

void Teleport::unsetDestination() {
    if (this->tp_set) {
        this->moveInto = false;

        this->tp_set = false;
        this->dynamic = false;

        this->dest_x = 0;
		this->dest_y = 0;
        this->dest_board = nullptr;
    }
}

void Teleport::onTouchEvent(Player* player) {
    if (tp_set && !dynamic) {
        if (dest_board != board) {
            this->board->deleteFromBoard(player, false);
            this->dest_board->addToBoard(player);
        }

        this->game->set_current_board(dest_board);
        player->set_pos(this->dest_x, this->dest_y);
    } else if (tp_set && dynamic) {
        if (this->dest_x+player->get_dirx() >= 0 && this->dest_x+player->get_dirx() < board->get_width() 
            && this->dest_y+player->get_diry() >= 0 && this->dest_y+player->get_diry() < board->get_height()) {
            if (dest_board != board) {
                this->board->deleteFromBoard(player, false);
                this->dest_board->addToBoard(player);
            }
            
            this->game->set_current_board(dest_board);
            player->set_pos(this->dest_x+player->get_dirx(), this->dest_y+player->get_diry());
        }
    }
}