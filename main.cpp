#include <conio.h>
#include "Game.h"

int GetKey()
{
	int keyPressed = _getch();
	while (keyPressed == 224)
		keyPressed = _getch();
	return keyPressed;
}

int main()
{
	Game _game;
	_game.Initialize();

	int key;

	//Game Loop
	do
	{
		//Render before checking for input
		_game.Render();

		//Read input
		key = toupper(GetKey());

		_game.Update(key);

	} while (key != GC::QUIT && !_game._endProgramFlag);

	_game.Render();

	return EXIT_SUCCESS;
}
