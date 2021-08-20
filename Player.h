#pragma once
#include <iostream>

#include "Item.h"
#include "Maze.h"
#include "RandomNumberGenerator.h"
#include "PlayerData.h"

class Player
{
public:
	Player(const RandomNumberGenerator&);

	//Encapsulation Functions
	const std::string& GetName() { return _playerName; }

	Item& GetSnakeHead() { return _snake[0]; }
	void SetSnake(const std::vector<Item>&);
	const size_t GetSnakeLength() { return _snake.size(); }

	const int GetPlayer() { return _data._player; }
	const int GetScore() { return _data._score; }
	void IncrementScore(const int s) { _data._score += s; }

	const bool GetPlayerStatus() { return _data._playerDead; }
	void SetPlayerStatus(const bool s) { _data._playerDead = s; }

	const bool GetInvincibleStatus() { return _data._invincible; }
	void SetInvincibleStatus(const bool s) { _data._invincible = s; }
	void IncrementInvincibleMoves();

	//Initialize Functions
	void InputName(const int, const int);
	void SetSnakeCoordinates(const int, const int, Maze&);

	//Update Functions
	void IncreaseSnake();
	void MoveSnake(const std::pair<int, int>&, Maze&);

	//Render Functions
	void DisplayPlayerInformation(int&, void(*)(int, int));

private:
	void CreateSnake();


	static int _playerCount;
	std::string _playerName;
	std::vector<Item> _snake;
	RandomNumberGenerator _rng;
	PlayerData _data;
};
