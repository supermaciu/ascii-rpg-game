#include "Enemy.h"
#include "Player.h"

#include <iostream>
#include <conio.h>

//Enemy
Enemy::Enemy(unsigned int x, unsigned int y) : BoardObject(x, y) {
    this->classname = "Enemy";
    this->interactWith = true;
    
    this->c = '!';
    this->color = 0x04;
}

void Enemy::onTouchEvent(Player* player) {
    system("cls");
    std::cout << player->get_name() << " vs " << name << std::endl;
    std::cout << std::endl << "Press anything to destroy your opponent!";
    getch();

    player->set_health(player->get_health()-1);

    board->deleteFromBoard(this, true);
    player->kill_count++;
}

//Spider
Spider::Spider(unsigned int x, unsigned int y) : Enemy(x, y) {
    this->c = '^';
    this->color = 0x08;

    setStats("Spider", 1, 3, 1);
}