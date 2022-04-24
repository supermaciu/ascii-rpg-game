#include "Enemy.h"
#include "Player.h"

Enemy::Enemy(unsigned int x, unsigned int y, Board* board) : BoardObject(x, y, c, board) {
    this->classname = "Enemy";
    this->moveInto = true;
    
    // this->x = x;
    // this->y = y;
    this->c = '!';
    this->color = 0x04;

    // this->board = board;
    this->board->addToBoard(this);
}

void Enemy::onEnterEvent(Player* player) {
    this->board->deleteFromBoard(this, true);
    player->kill_count++;
}
