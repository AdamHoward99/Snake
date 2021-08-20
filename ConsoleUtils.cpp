#include "ConsoleUtils.h"

WORD backColour = 0;
WORD textColour = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
WORD textAttributes = backColour | textColour;

//-------------
//clear the screen, and reset cursor to (0, 0)
void clrscr()
{
	//from web-site
	COORD coordScreen = { 0, 0 }; 
	DWORD cCharsWritten; 
	CONSOLE_SCREEN_BUFFER_INFO csbi; 
	DWORD dwConSize; 
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 
	GetConsoleScreenBufferInfo(hConsole, &csbi); 
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y; 
	FillConsoleOutputCharacter(hConsole, TEXT(' '), dwConSize, coordScreen, &cCharsWritten); 
	GetConsoleScreenBufferInfo(hConsole, &csbi); 
	FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, 	coordScreen, &cCharsWritten); 
	SetConsoleCursorPosition(hConsole, coordScreen); 
}

//-------------
//move the text cursor to position (x, y)
void gotoxy(int x, int y)
{
	//from web-site
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//move the text cursor to position (x, y)
void gotoxy(const std::pair<int, int>& pos)
{
	COORD coord;
	coord.X = pos.second;
	coord.Y = pos.first;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), clRed);
}

//-------------
//select a background colour from the colour constants list
void selectBackColour(int colour)
{
	void selectAttributes();
	switch (colour)
	{
		case clBlack: backColour = 0; break;
		case clRed: backColour = BACKGROUND_INTENSITY | BACKGROUND_RED; break;
		case clGreen: backColour = BACKGROUND_INTENSITY | BACKGROUND_GREEN; break;
		case clYellow: backColour = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN; break;
		default: backColour = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
	}
	selectAttributes();
}

//-------------
//select a text colour from the colour constants list
void selectTextColour(const char c)
{
	void selectAttributes();
	switch (c)
	{
	case GC::HEAD: textColour = FOREGROUND_INTENSITY | FOREGROUND_RED; break;
	case GC::TAIL: textColour = FOREGROUND_INTENSITY | FOREGROUND_GREEN; break;
	case GC::MOUSE: textColour = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN; break;
	case GC::PILL: textColour = FOREGROUND_INTENSITY | FOREGROUND_BLUE; break;
	default: textColour = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE; break;
	}

	selectAttributes();
}

//-------------
//select the text attributes
void selectAttributes()
{
	textAttributes = backColour | textColour;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), textAttributes);
}
