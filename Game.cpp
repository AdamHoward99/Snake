#include "Game.h"

Game::Game()
{}

Game::~Game()
{}

std::pair<int, int> operator +(const std::pair<int, int> A, const std::pair<int, int> B)		//Overload Operator for pair<int, int> addition
{
	return { A.first + B.first, A.second + B.second };
}

const void Game::GetMode()
{
	int mode = 0;
	//Get Integer value representing game mode (1 = single player, 2 = multiplayer)
	while (mode != 1 && mode != 2)
	{
		printf("Enter Game Mode (1 for single player, 2 for 2-player): ");
		scanf_s("%d", &mode); 

		//Input Validation
		std::cin.clear();
		std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
	}

	_maze.SetMap(mode);
	InitializePlayers(mode);
}

void Game::InitializePlayers(const int amountOfPlayers)
{
	if (amountOfPlayers > 2)
		exit(EXIT_FAILURE);

	for (int i = 0; i < amountOfPlayers; i++)
	{
		Player newPlayer(_rng);
		newPlayer.InputName(NAMEMAXSIZE, (i + 1));
		_players.emplace_back(newPlayer);
	}

	gotoxy(0, 0);
}

const void Game::Initialize()
{
	GetMode();
	_maze.Initialize();
	InitializeItems();
}

void Game::Update(const int key)
{
	for (Player& p : _players)
	{
		std::pair<int, int> nextMove = SetKeyDirection(key, p.GetPlayer());

		if (nextMove.first == 0 && nextMove.second == 0)		//No key movement detected for this player
			continue;

		const std::pair<int, int> nextPosition = p.GetSnakeHead().GetPosition() + nextMove;

		switch (_maze.GetElementFromMaze(nextPosition))
		{
		case GC::MOUSE:
			p.IncrementScore(1000);
			p.IncreaseSnake();
			MoveMouse();
		case GC::TUNNEL:
			if (p.GetInvincibleStatus())			//Player is currently invincible
			{
				p.IncrementInvincibleMoves();
			}
			p.IncrementScore(10);
			p.MoveSnake(nextPosition, _maze);
			MoveMongoose();
			break;

		case GC::WALL:
		case GC::MONGOOSE:
		case GC::TAIL:
		case GC::HEAD:
			if(!p.GetInvincibleStatus())
				p.SetPlayerStatus(true);
			break;

		case GC::PILL:
			p.MoveSnake(nextPosition, _maze);
			p.SetInvincibleStatus(true);
			break;

		default:
			exit(EXIT_FAILURE);
			break;
		}

	}

}

const void Game::Render()
{
	_maze.UpdateFrame();

	int y = 4;

	DisplayTitleInformation(y);

	//Function pointer to gotoxy()
	void(*funcPtr)(int, int);
	funcPtr = &gotoxy;

	//Render player information
	for (Player& p : _players)
		p.DisplayPlayerInformation(y, funcPtr);

	DisplayQuitInformation(y);
	y++;
	gotoxy(80, y);
	
	//Display win information
	if (GameEnd())
	{
		if (_players.size() > 1)
		{
			std::string winnerName;

			for (Player &p : _players)
				if (!p.GetPlayerStatus())
					winnerName = p.GetName();

			printf("%s has won!!!", winnerName.c_str());
		}
		else
			printf("You Died...");

		_endProgramFlag = 1;
	}


}

void Game::InitializeItems()
{
	const int h = _maze.GetHeight() - 2;
	const int w = _maze.GetWidth() - 2;

	_rng.seed();

	//Get random coordinates for snake
	for (Player &p : _players)
		p.SetSnakeCoordinates(h, w, _maze);

	//Initialize Items
	_items.insert({ "mouse", CreateItem(GC::MOUSE, h, w) });
	_items.insert({ "pill", CreateItem(GC::PILL, h, w) });
	_items.insert({ "mongoose", CreateItem(GC::MONGOOSE, h, w) });

}

Item Game::CreateItem(const char c, const int h, const int w)
{
	Item newItem(c);

	int randX = _rng.random(w);
	int randY = _rng.random(h);

	while (!_maze.AvailableSpaceCheck(randX, randY))
	{
		randX = _rng.random(w);
		randY = _rng.random(h);
	}

	newItem.SetPosition(randY, randX);

	_maze.AssignElementInMaze(randX, randY, c);

	return newItem;
}

std::pair<int, int> Game::SetKeyDirection(const int key, const int p)
{
	std::pair<int, int> pos = { 0,0 };

	if (key == GC::PLAYER_INPUTS[p][0])		//UP Input
		return { -1, 0 };

	else if (key == GC::PLAYER_INPUTS[p][1])	//Down input
		return { 1, 0 };

	else if (key == GC::PLAYER_INPUTS[p][2])	//Left input
		return { 0, -1 };

	else if (key == GC::PLAYER_INPUTS[p][3])	//Right input
		return { 0, 1 };

	return pos;
}

void Game::MoveMongoose()
{
	int move = rand() % 5;		//Chooses random movement for mongoose

	std::pair<int, int> mongoosePos = _items["mongoose"].GetPosition();
	std::pair<int, int> potentialPos;

	switch (move)
	{
	case 1:
		potentialPos = mongoosePos + std::pair<int, int>{-1, 0};	//Up direction
		break;

	case 2:
		potentialPos = mongoosePos + std::pair<int, int>{1, 0};		//Down direction
		break;

	case 3:
		potentialPos = mongoosePos + std::pair<int, int>{0, -1};	//Left direction
		break;

	case 4:
		potentialPos = mongoosePos + std::pair<int, int>{0, 1};		//Right direction
		break;

	default:
		potentialPos = mongoosePos;
		break;
	}

	const char c = _maze.GetElementFromMaze(potentialPos);

	switch (c)
	{
	case GC::HEAD:
		for (Player &p : _players)			//Find which player it collided with
		{
			if (potentialPos == p.GetSnakeHead().GetPosition())
				p.SetPlayerStatus(true);
		}
	case GC::TUNNEL:
		_maze.AssignElementInMaze(mongoosePos, GC::TUNNEL);		//Clear previous space of mongoose from the maze
		_items["mongoose"].SetPosition(potentialPos);
		_maze.AssignElementInMaze(potentialPos, GC::MONGOOSE);	//Set mongoose in new position in maze
		break;

	default:
		break;
	}

}

void Game::MoveMouse()
{
	const int h = _maze.GetHeight() - 2;
	const int w = _maze.GetWidth() - 2;
	std::pair<int, int> newPos = { _rng.random(h), _rng.random(w) };

	while (_maze.GetElementFromMaze(newPos) != GC::TUNNEL)
	{
		newPos = { _rng.random(h), _rng.random(w) };
	}

	_items["mouse"].SetPosition(newPos);
	_maze.AssignElementInMaze(newPos, GC::MOUSE);

}

const bool Game::GameEnd()
{
	for (Player& p : _players)
	{
		if (p.GetPlayerStatus())
			return true;
	}

	return false;
}

const void Game::DisplayTitleInformation(int& y)
{
	gotoxy(80, y);
	selectBackColour(clRed);
	printf("SNAKE GAME %zu PLAYER(S) ", _players.size());
	y++;
}

const void Game::DisplayQuitInformation(const int y)
{
	gotoxy(80, y);
	printf("Q Key to quit the game.");
	selectBackColour(clBlack);
}
