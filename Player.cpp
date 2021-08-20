#include "Player.h"

int Player::_playerCount = -1;

Player::Player(const RandomNumberGenerator& r)
	:_rng(r)
{
	CreateSnake();
	_playerCount++;
	_data._player = _playerCount;
}

void Player::InputName(const int maxSize, const int player)
{
	do
	{
		printf("Enter Player %d's Name (Max %d Characters): ", player, maxSize);
		std::cin >> _playerName;

	} while (_playerName.size() > maxSize);
}

void Player::CreateSnake()
{
	const int maxSize = 3;
	Item head(GC::HEAD, { 0,0 });
	_snake.push_back(head);

	for (int i = 0; i < maxSize; i++)
	{
		Item tail(GC::TAIL, { 0,0 });
		_snake.push_back(tail);
	}
}

inline void Player::SetSnake(const std::vector<Item>& newSnake) 
{ 
	_snake = newSnake;
}

void Player::SetSnakeCoordinates(const int h, const int w, Maze& m)
{
	int randX = _rng.random(w);			//Width
	int randY = _rng.random(h);			//Height

	while (!m.AvailableSpaceCheck(randX, randY))
	{
		randX = _rng.random(w);
		randY = _rng.random(h);
	}

	//Set position of the head
	_snake[0].SetPosition(randY, randX);

	//Place tail underneath head at start
	for (int i = 1; i < _snake.size(); i++)
		_snake[i].SetPosition(randY, randX);

	//Add snake to maze
	m.AssignElementInMaze(randX, randY, _snake[0].GetSymbol());

}

void Player::MoveSnake(const std::pair<int, int>& newPos, Maze& m)
{
	m.AssignElementInMaze(_snake[_snake.size() - 1].GetPosition(), GC::TUNNEL);

	//Move snake tail
	for (size_t i(_snake.size() - 1); i >= 1; --i)
	{
		_snake[i].SetPosition(_snake[i - 1].GetPosition());
	}

	//Move snake head
	_snake[0].SetPosition(newPos);

	//Changes maze based on position changes for the snake
	for (Item& it : _snake)
		m.AssignElementInMaze(it.GetPosition(), it.GetSymbol());
}

void Player::IncreaseSnake()
{
	Item newTail(GC::TAIL, _snake[_snake.size() - 1].GetPosition());
	_snake.push_back(newTail);
}

void Player::IncrementInvincibleMoves()
{
	if (_data._invincibleMoves < 20)
		_data._invincibleMoves++;
	else
	{
		_data._invincibleMoves = 0;
		_data._invincible = false;
	}
}

void Player::DisplayPlayerInformation(int& y, void(*ptr)(int, int))
{
	(*ptr)(80, y);		//Calls gotoxy function in ConsoleUtils.cpp

	printf("Player %d Name: %8s", _data._player+1, _playerName.c_str());
	y++;

	(*ptr)(80, y);
	printf("Player %d Score: %7d", _data._player+1, _data._score);
	y += 2;
}
