#pragma once

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>
#include <time.h>
#include <algorithm>

inline void setCursor(int x, int y) {
	COORD c;
	
	c.X = x - 1;
	c.Y = y - 1;
	
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

inline int get_screen_width() {
	RECT desktop;
	HWND hDesktop = GetDesktopWindow();

	GetWindowRect(hDesktop, &desktop);

	return desktop.right;
}

inline int get_screen_height() {
	RECT desktop;
	HWND hDesktop = GetDesktopWindow();

	GetWindowRect(hDesktop, &desktop);

	return desktop.bottom;
}

inline int get_console_width() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int console_width = csbi.srWindow.Right - csbi.srWindow.Left + 1;

	return console_width;
}

inline int get_console_height() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int console_height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

	return console_height;
}