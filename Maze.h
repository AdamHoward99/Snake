#pragma once
#include <vector>
#include <fstream>

#include "Constants.h"
#include "ConsoleUtils.h"

class Maze
{
public:
	Maze();
	~Maze();

	//Encapsulation Functions
	const int GetMap() { return _map; }
	void SetMap(const int val) { _map = val; }

	const int GetHeight() { return _height; }
	const int GetWidth() { return _width; }

	//Inlined Functions
	void AssignElementInMaze(const int x, const int y, const char c)	//Adds new char to maze without passing full maze vector
	{	_maze[y][x] = c;	}

	void AssignElementInMaze(const std::pair<int, int>& pos, const char c)
	{	_maze[pos.first][pos.second] = c;	}

	const char GetElementFromMaze(const std::pair<int, int>& pos)
	{	return _maze[pos.first][pos.second];	}

	const bool AvailableSpaceCheck(const int x, const int y)		//Returns if space is available to put a char, e.g not a wall
	{	return (_maze[y][x] == ' ');	}

	void Initialize();
	const void UpdateFrame();
	const void Render();

private:
	const void RenderPadding();
	const WORD GetColour(const char);


	int _height, _width, _map;
	std::vector<std::string> _mapNames;
	std::vector<std::vector<char>> _maze;
	std::vector<std::vector<char>> _prevMazeFrame;
};