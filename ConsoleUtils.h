 #ifndef ConsoleUtilsH
#define ConsoleUtilsH

#include <windows.h>
#include <string>
#include "Constants.h"

//colour constants for translation
const WORD clBlack = 0;
const WORD clRed = 9;
const WORD clGreen = 10;
const WORD clBlue = 11;
const WORD clYellow = 14;
const WORD clWhite = 15;

//-------------
//clear the screen, and reset cursor to (0, 0)
void clrscr();

//move the text cursor to position (x, y)
void gotoxy(int x, int y);
void gotoxy(const std::pair<int, int>&);

//select a background colour from the colour constants list
void selectBackColour(int colour);

//select a text colour from the colour constants list
void selectTextColour(const char c);

//select the text attributes
void selectAttributes();

#endif