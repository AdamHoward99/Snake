#pragma once
#include "Constants.h"

class Item
{
public:
	Item();
	Item(const char);
	Item(const char, const int, const int);
	Item(const char, const std::pair<int, int>&);
	~Item();

	void SetPosition(const int x, const int y);
	void SetPosition(const std::pair<int, int>& coordinates);

	const std::pair<int, int>& GetPosition();
	const char GetSymbol() { return _symbol; }

private:
	std::pair<int, int> _position;
	char _symbol;
};