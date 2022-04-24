#include "Player.h"

#include "Game.h"
#include "Board.h"
#include "Enemy.h"

Player::Player(unsigned int x, unsigned int y, Board* board) : BoardObject(x, y, c, board) {
    this->classname = "Player";
    
    this->c = '@';
    this->color = 0x02;
    
    this->board->addToBoard(this);
}

void Player::set_pos(int x, int y) {
	BoardObject* bo = this->board->getBoardObjectByCoords(x, y);
	if (bo != nullptr) {
		bo->onEnterEvent((Player*)this);
	}
	
	this->x = x;
	this->y = y;
}

void Player::movementHandler(char move) {
    this->prev_x = this->x;
    this->prev_y = this->y;
    this->prev_move = this->move;

    this->move = move;

    this->dirx = 0;
    this->diry = 0;

    if ((move == 'a' || move == 75) && x>0) {
        this->dirx = -1;
        if (canMoveInto(x-1, y)) x -= 1;
    } else if ((move == 'd' || move == 77) && x+1<board->get_width()) {
        this->dirx = 1;
        if (canMoveInto(x+1, y)) x += 1;
    } else if ((move == 'w' || move == 72) && y>0) {
        this->diry = -1;
        if (canMoveInto(x, y-1)) y -= 1;
    } else if ((move == 's' || move == 80) && y+1<board->get_height()) {
        this->diry = 1;
        if (canMoveInto(x, y+1)) y += 1;
    }

    if (move == 'e') {
         bool t = true;
         for (int x = 0; x < board->get_width(); x++) {
             for (int y = 0; y < board->get_height(); y++) {
                 for (BoardObject *p_bo : board->getBoardObjects()) {
                     if (x == p_bo->get_x() && y == p_bo->get_y()) {
                         t = false;
                     }
                 }

                 if (t) {
                     Enemy* enemy = new Enemy(x, y, board);
                 }
                 t = true;
             }
         }
    } else if (move == 'c') {
        std::vector<BoardObject*> bos = board->getBoardObjects();

        if (!bos.empty()) {
            for (BoardObject* bo : bos) {
                if (bo->get_classname() == "Enemy" || bo->get_classname() == "Teleport" && (bo == t1 || bo == t2)) {
                    board->deleteFromBoard(bo, true);
                }
            }
        }
    } else if (move == 't') {
        if (!this->t1) {
            int x, y;

            std::cout << std::endl << "t1 (teleports to t2):" << std::endl;
            std::cout << "x: ";
            std::cin >> x;
            std::cout << "y: ";
            std::cin >> y;

            if (this->t1) {
                this->board->deleteFromBoard(t1, true);
            }

            this->t1 = new Teleport(x, y, this->board);
        } else if (this->t1) {
            if (this->t2) {
                t2->get_board()->deleteFromBoard(t2, true);
            }

            int x, y;

            std::cout << std::endl << "t2 (teleports to t1):" << std::endl;
            std::cout << "dx: ";
            std::cin >> x;
            std::cout << "dy: ";
            std::cin >> y;

            this->t2 = new Teleport(x, y, this->board);
            t2->setDestination(t1->get_x(), t1->get_y(), t1->get_board(), true);

            t1->setDestination(t2->get_x(), t2->get_y(), t2->get_board(), true);
        }
    }
}

bool Player::canMoveInto(int x, int y) {
	BoardObject* bo = this->board->getBoardObjectByCoords(x, y);
	
	if (bo == nullptr) {
		return true;
	}
	
	return bo->get_moveInto();
}

bool Player::canMoveInto(BoardObject* bo) {
    if (bo == nullptr) {
		return true;
	}
	
	return bo->get_moveInto();
}

// TODO: more optimized -> can check in current players position / near player
void Player::checkOnEnterEvents() {
	for (BoardObject *p_bo : board->getBoardObjects()) {
        if (p_bo != this && this->get_x() == p_bo->get_x() && this->get_y() == p_bo->get_y()) {
            p_bo->onEnterEvent(this);
        }
    }
}

// void Player::checkOnTouchEvents() {
//     for (BoardObject *p_bo : board->getBoardObjects()) {
//         if (p_bo != this
//             && ((this->get_x() == p_bo->get_x()-1 && this->get_y() == p_bo->get_y() && (this->dirx == 1 && this->diry == 0))
//             || (this->get_x() == p_bo->get_x()+1 && this->get_y() == p_bo->get_y() && (this->dirx == -1 && this->diry == 0))
//             || (this->get_x() == p_bo->get_x() && this->get_y() == p_bo->get_y()-1 && (this->dirx == 0 && this->diry == 1))
//             || (this->get_x() == p_bo->get_x() && this->get_y() == p_bo->get_y()+1 && (this->dirx == 0 && this->diry == -1)))
//             && (this->x == this->prev_x && this->y == this->prev_y)
//             && (p_bo->get_interactWith())) {
//             p_bo->onTouchEvent(this);
//         }
//     }
// }

void Player::checkOnTouchEvents() {
    for (BoardObject *p_bo : board->getBoardObjects()) {
        if (p_bo != this
            && ((this->get_x() == p_bo->get_x()-1 && this->get_y() == p_bo->get_y() && (this->dirx == 1 && this->diry == 0))
            || (this->get_x() == p_bo->get_x()+1 && this->get_y() == p_bo->get_y() && (this->dirx == -1 && this->diry == 0))
            || (this->get_x() == p_bo->get_x() && this->get_y() == p_bo->get_y()-1 && (this->dirx == 0 && this->diry == 1))
            || (this->get_x() == p_bo->get_x() && this->get_y() == p_bo->get_y()+1 && (this->dirx == 0 && this->diry == -1)))
            && (this->x == this->prev_x && this->y == this->prev_y)
            && (p_bo->get_interactWith())) {
            p_bo->onTouchEvent(this);
        }
    }
}

void Player::eventsHandler(char move) {
    if (board != nullptr) {
        movementHandler(move);
        checkOnEnterEvents();
        checkOnTouchEvents();
    }
}
