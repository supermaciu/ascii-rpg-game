#include <iostream>
#include <thread>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <string>
#include <cstdlib>
#include <time.h>
#include <functional>

#include "Utilities.h"

#include "Game.h"
#include "HUD.h"
#include "Sequence.h"
#include "BoardObject.h"
#include "Board.h"
#include "Player.h"
#include "Enemy.h"
#include "Teleport.h"

// TODO: file reader, txt to board setup

int main() { //int argc, char *argv[]

    srand(time(NULL));
	
    //Initialization
    char move;
	int width = get_screen_width() * 0.85;
	int height = get_screen_height() * 0.85;
	
    //Config
    Game::setTitle("A-scimitar");
    Game::resizeWindow(width, height);
    Game::moveWindowCenter();
    Game::setConsoleBufferSize(0, 0);
    Game::resizeableWindow(false);
    Game::setCursorVisibility(false);

    Game::setDebugMode(false);
	
	/*
		Menus
		nullptr - come back to game
		[](){} - do nothing
		
		std::function<void()> - pointer to a void function that has no arguments
		{std::string, std::function<void()>} = MenuFuncionAlias(std::string, std::function<void()>)
	*/

	//Start options
	std::vector<MenuFunctionAlias> startOptionsMFAs = {
		{"DEVELOPER MODE", []{ Game::setDebugMode(!Game::getDebugMode());}},
		{"GO BACK", nullptr}
	};

	Menu startOptions("OPTIONS", startOptionsMFAs);

	//Start menu
	std::vector<MenuFunctionAlias> startMenuMFAs = {
		{"START", nullptr},
		{"OPTIONS", &startOptions}, // pointer to menu object (to call show() member function)
		{"EXIT / QUIT", Game::menuExitGame} // or a void function
	};

	Menu startMenu("A-scimitar", startMenuMFAs);
	startMenu.setCanESC(false);
	startMenu.setSaveCursorPosition(true);
	
	//Paused menu options
	std::vector<MenuFunctionAlias> pauseMenuMFAs = {
		{"UNPAUSE", nullptr},
		{"OPTIONS", &startOptions},
		{"EXIT / QUIT", Game::menuExitGame}
	};

	Menu pauseMenu("PAUSED", pauseMenuMFAs);
	startMenu.setSaveCursorPosition(true);
	
	//Start menu sequence
	startMenu.show();


    // TODO: loading data, options, gamemode, etc.


    //Game
    Board* forest = new Board("Forest", 25, 10);
	forest->set_color(0x02);
    Game::set_current_board(forest);

	Board* cave = new Board("Cave", 9, 9);

    Player* player = new Player(1, 1);
    forest->addToBoard(player);

    Teleport* t1 = new Teleport(8, 1);
	forest->addToBoard(t1);
	t1->setDestination(4, 8, cave, true);

	Teleport* t2 = new Teleport(4, 8);
	cave->addToBoard(t2);
	t2->setDestination(8, 1, forest, true);

	Spider* spd1 = new Spider(3, 3);
	forest->addToBoard(spd1);

	Spider* spd2 = new Spider(5, 5);
	forest->addToBoard(spd2);

	Spider* spd3 = new Spider(7, 2);
	forest->addToBoard(spd3);

	Pickup* medics = new Pickup(4, 3);
	cave->addToBoard(medics);

	Teleport* t3 = new Teleport(3, 7);
	forest->addToBoard(t3);
	t3->setDestination(8, 7, forest, true);

	Teleport* t4 = new Teleport(8, 7);
	forest->addToBoard(t4);
	t4->setDestination(3, 7, forest, true);

	//HUDs
	HUD<int> playerHealthHUD(10, 5, "Health", player->R_get_health(), player->R_get_max_health(), true);

	Game::showBoard();
	playerHealthHUD.show();

	// FIX: why does health HUD not show with this and any stringstream
	// std::stringstream stream;
	// stream << "-= " << Game::get_current_board()->get_name() << " =-";
	// std::string str = stream.str();

	// setCursor(get_console_width()/2-str.size()/2, get_console_height()*0.2);
	// std::cout << str;

    while (&Game::Get()) {
    	move = getch();

        if (move == -32) {
            move = getch();
        }
        
        if (move == 27) {
        	pauseMenu.show();
		}
    
        player->eventsHandler(move);
		
		if (Game::getDebugMode() == true) {
			playerHealthHUD.hide();
		} else {
			playerHealthHUD.unhide();
		}
		
		//Display
		Game::showBoard();
		playerHealthHUD.show();

		// setCursor(get_console_width()/2-str.size()/2, get_console_height()*0.2);
		// std::cout << str;

        //Debug
        Game::debug(player);
    }

    return 0;
}
