#include "HUD.h"

#include <iostream>
#include <conio.h>
#include <functional>

#include "Utilities.h"
#include "Game.h"

//Menu functions
Menu::Menu(const std::string& title, const std::vector<MenuFunctionAlias>& options)
    : title(title), options(options) {
    centered = true;
}

Menu::Menu(const std::string& title, int posx, int posy, const std::vector<MenuFunctionAlias>& options)
    : title(title), posx(posx), posy(posy), options(options) {
    centered = false;
}

void Menu::show() {
    if (!saveCursorPosition) {
        choice = 0;
    }

    system("cls");
	
    int offx;

    bool running = true;
    while (running) {
    	setCursor(get_console_width()/2-title.size()/2-3, get_console_height()*0.3);
		std::cout << "-= " << title << " =-";
    	
        if (centered) {
            for (int i = 0; i < options.size(); i++) {
                posx = options[i].alias.size() / 2;
                setCursor((get_console_width()/2-posx), (get_console_height()/2-options.size()+i));

                if (i == choice) SetConsoleTextAttribute(Game::get_handle(), 0x70);
                std::cout << options[i].alias;
                if (i == choice) SetConsoleTextAttribute(Game::get_handle(), 0x07);
            }

            //Cursor
            SetConsoleTextAttribute(Game::get_handle(), cursor_color);
            offx = options[choice].alias.size() / 2;
            setCursor((get_console_width()/2-offx-2), (get_console_height()/2-options.size()+choice));
            std::cout << cursor;
            setCursor((get_console_width()/2+offx+2), (get_console_height()/2-options.size()+choice));
            std::cout << cursor;
            SetConsoleTextAttribute(Game::get_handle(), 0x07);
        } else {
            for (int i = 0; i < options.size(); i++) {
                setCursor(posx, posy+i);
                std::cout << options[i].alias;
            }

            //Cursor
            SetConsoleTextAttribute(Game::get_handle(), cursor_color);
            setCursor((posx-2), (posy+choice));
            std::cout << cursor;
            setCursor((posx+options[choice].alias.size()+2), (posy+choice));
            std::cout << cursor;
            SetConsoleTextAttribute(Game::get_handle(), 0x07);
        }

        move = getch();

        if (move == -32) {
            move = getch();
        }

        if (move == 'w' || move == 72) {
            choice--;
            if (choice < 0) choice = options.size()-1;
        } else if (move == 's' || move == 80) {
            choice++;
            if (choice > options.size()-1) choice = 0;
        } else if (move == 'e' || move == 13) {
            if (options[choice].function != nullptr && options[choice].menu == nullptr) {
            	options[choice].function();
			} else if (options[choice].function == nullptr && options[choice].menu != nullptr) {
                options[choice].menu->show();
            } else if (options[choice].function == nullptr && options[choice].menu == nullptr) {
				break;
			}
        } else if (move == 27 && canESC) {
            break;
        }

        system("cls");
    }
}
