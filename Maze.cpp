#include "Maze.h"

Maze::Maze()
{
	_mapNames.push_back("Error.txt");
	_mapNames.push_back("Map1.txt");
	_mapNames.push_back("Map2.txt");
}

Maze::~Maze()
{}

void Maze::Initialize()
{
	if (_map < 1 || _map > 2)
		exit(EXIT_FAILURE);

	std::string c;
	std::ifstream input_file(_mapNames[_map]);		//Get appropriate map name based on which map has been selected

	if (!input_file.is_open())
		exit(EXIT_FAILURE);

	while (std::getline(input_file, c))
	{
		std::vector<char> row;

		for (char &ch : c)
		{
			if (ch == '.')
				ch = ' ';
			row.push_back(ch);
		}

		_maze.push_back(row);
	}

	_height = (int)_maze.size();
	_width = (int)_maze[0].size();

	Render();			//Render initial maze frame
}

const void Maze::RenderPadding()
{
	printf("%50c", ' ');
}

const void Maze::Render()
{
	char* mazePtr;
	for (int y = 0; y < _maze.size(); y++)
	{
		mazePtr = &_maze[y][0];
		RenderPadding();
		for (int x = 0; x < _maze[0].size(); x++)
		{
			selectTextColour(*mazePtr);
			printf("%c", *mazePtr);
			*mazePtr++;
		}
		printf("\n");
	}
	
	_prevMazeFrame = _maze;		//Set previous frame as current
}

const void Maze::UpdateFrame()
{
	char* currMaze, *prevMaze;
	for (int y = 0; y < _height; y++)
	{
		currMaze = &_maze[y][0];
		prevMaze = &_prevMazeFrame[y][0];

		for (int x = 0; x < _width; x++)
		{
			//Instead of clearing screen, compares current maze frame with previous and overwrites specific positions
			if (*currMaze == *prevMaze)		
				goto label;

			gotoxy(x + 50, y);
			selectTextColour(*currMaze);
			printf("%c", *currMaze);

			label:
			*currMaze++;
			*prevMaze++;
		}
	}
	
	selectTextColour(clWhite);
	_prevMazeFrame = _maze;
}

const WORD Maze::GetColour(const char c)
{
	switch (c)
	{
	case GC::HEAD:
		return clRed;
		break;

	case GC::TAIL:
		return clGreen;
		break;
		
	case GC::MOUSE:
		return clYellow;
		break;

	case GC::PILL:
		return clBlue;
		break;

	default:
		return clWhite;
		break;
	}
}

