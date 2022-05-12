#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <functional>

#include "Utilities.h"

//HUD class
template <typename T>
class HUD {
    private:
        int posx;
        int posy;
        std::string name;

        T& value;
        T& max_value;

        bool visualize;
        bool hidden;
    public:
        HUD(int posx, int posy, const std::string& name, T& value)
            : posx(posx), posy(posy), name(name), value(value) {}

        HUD(int posx, int posy, const std::string& name, T& value, T& max_value, bool visualize)
            : posx(posx), posy(posy), name(name), value(value), max_value(max_value), visualize(visualize) {}
        
        const std::string& get_name() { return name; }
        void set_name(const std::string& name) { this->name = name; }

        T get_value() { return value; }
        void set_value(T& value) { this->value = value; }
        T get_max_value() { return max_value; }

        void hide() { hidden = true; }
        void unhide() { hidden = false; }

        void displayName() {
            setCursor(posx, posy);
            std::cout << name;
        }

        void displayValue() {
            setCursor(posx, posy);
            std::cout << value;
        }

        void show() {
            if (hidden) return;

            if (!visualize) {
                setCursor(posx, posy);
                std::cout << name << ": " << value;
            } else if (visualize) {
                setCursor(posx, posy);
                std::cout << name << ":";

                //Drawing the box
                setCursor(posx, posy+1);
                std::cout << "+" << std::string(14, '-') << "+";

                int count;
                setCursor(posx, posy+2);
                count = int(float(value)/float(max_value)*14);
                std::cout << "|" << std::string(count, char(219)) << std::string((14-count), char(176)) << "|";

                setCursor(posx, posy+3);
                count = int(float(value)/float(max_value)*14);
                std::cout << "|" << std::string(count, char(219)) << std::string((14-count), char(176)) << "|";
                std::stringstream stream;
                stream << value << "/" << max_value;
                std::string s = stream.str();
                setCursor((posx+14/2)-s.size()/2, posy+3);
                std::cout << s;

                setCursor(posx, posy+4);
                count = int(float(value)/float(max_value)*14);
                std::cout << "|" << std::string(count, char(219)) << std::string((14-count), char(176)) << "|";

                setCursor(posx, posy+5);
                std::cout << "+" << std::string(14, '-') << "+";
            }
        }
};

//Menu class
class Menu;

struct MenuFunctionAlias {
    std::string alias;
    std::function<void()> function = nullptr;
    Menu* menu = nullptr;

    MenuFunctionAlias(const std::string& alias, const std::function<void()>& function)
        : alias(alias), function(function) {}
    
    MenuFunctionAlias(const std::string& alias, Menu* menu)
        : alias(alias), menu(menu) {}
};

class Menu {
    private:
        char move;
        bool centered;

        int choice = 0;

        bool canESC = true;
        bool saveCursorPosition = false;

        std::string title;
        
        int posx;
        int posy;

        char cursor = '@';
        int cursor_color = 0x0e;

        std::vector<MenuFunctionAlias> options;
    
    public:
        Menu(const std::string& title, const std::vector<MenuFunctionAlias>& options);

        Menu(const std::string& title, int posx, int posy, const std::vector<MenuFunctionAlias>& options);

		void setCanESC(bool set) { this->canESC = set; }
        void setSaveCursorPosition(bool set) { this->saveCursorPosition = set; }

        void show();
};