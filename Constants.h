#pragma once
#include <vector>

namespace GC
{
	const unsigned char
		//Game Specific Chars
		HEAD = 'O',
		MOUSE = '@',
		PILL = '+',
		MONGOOSE = 'M',
		TAIL = 'o',
		TUNNEL = ' ',
		WALL = '#',

		//Menu Chars
		QUIT = 'Q';

	//Input Keys
	const std::vector<std::vector<unsigned int>> 
		PLAYER_INPUTS = { {72, 80, 75, 77}, {87, 83, 65, 68} };

};