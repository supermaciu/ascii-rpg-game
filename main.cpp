#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>
#include <time.h>
#include <algorithm>

#include "Utilities.h"

#include "Game.h"
#include "BoardObject.h"
#include "Board.h"
#include "Player.h"
#include "Enemy.h"
#include "Teleport.h"

// TODO: optimize 
// TODO: file reader, txt to board setup
// FIX: why does it take so much time to compile
// TODO: Board function to move a BoardObject to another board
// TODO: optimize Board.cpp coloring
// IDEA: console window widens on inventory open on the right side / slowly
// TODO: threading / doing things while waiting on input
// TODO: make Game class a singleton

int main() {

    //Init
    srand(time(NULL));
    bool running = true;
    bool debug_mode = true;

    //Game / Config
    Game game;
    game.setTitle("ascii-rpg-game");
    game.setCursorVisibility(false);
    game.resizeWindow(get_screen_width()*0.85, get_screen_height()*0.8);
    game.moveWindowCenter();
    game.setConsoleBufferSize(0, 0);
    //game.maxemizeWindow(true);
    game.resizeableWindow(false);
    //game.resizeableWindow(true); // not working
    //game.disableInput(true);

    Board* board = new Board("board1", 10, 10, &game);
    game.set_current_board(board);

    Player* player = new Player(1, 1, board);

	//Board 2
	Board* board2 = new Board("board2", 15, 5, &game);

    Board* board3 = new Board("sklep", 8, 8, &game);

    // TODO: shop template
	
    Teleport* t1 = new Teleport(3, 3, board);
    t1->setDestination(0, 0, board2);

    Teleport* t2 = new Teleport(3, 3, board2);
    t2->setDestination(0, 0, board);

    Teleport* t3 = new Teleport(5, 3, board);
    t3->setDestination(0, 0, board);

    Teleport* t4 = new Teleport(1, 8, board);
    t4->setDestination(0, 0, board3);
    
    for (int i = 0; i < board->get_width(); i++) {
    	Void* v = new Void(i, 5, board);
	}

    //Input
    char move;

    //Initial board draw
    player->eventsHandler(move);
    game.showBoard();

    while (running) {
        move = getch();

        if (move == -32) {
            move = getch();
        }

        if (move == 3 || move == 27) {
            running = false;
        } else if (move == 9) {
            if (debug_mode == false) {
                debug_mode = true;
            } else {
                debug_mode = false;
            }
        }

        player->eventsHandler(move);

        game.showBoard();

        //Debug
        game.debug(debug_mode, player);

        Sleep(1);
    }

    return 0;
}