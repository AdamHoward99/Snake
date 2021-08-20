#pragma once
#include <string>
#include <vector>
#include <unordered_map>

#include "Maze.h"
#include "Player.h"
#include "RandomNumberGenerator.h"

#define NAMEMAXSIZE 8

class Game
{
public:
	Game();
	~Game();

	const void Initialize();
	void Update(const int);
	const void Render();


	int _endProgramFlag = 0;

private:
	//Initialize Functions
	const void GetMode();
	void InitializePlayers(const int);
	void InitializeItems();
	Item CreateItem(const char, const int, const int);

	//Update Functions
	void MoveMouse();
	void MoveMongoose();
	const bool GameEnd();
	std::pair<int, int> SetKeyDirection(const int, const int);

	//Render Functions
	const void DisplayTitleInformation(int&);
	const void DisplayQuitInformation(const int);


	Maze _maze;
	std::vector<Player> _players;
	std::unordered_map<std::string, Item> _items;
	RandomNumberGenerator _rng;
};