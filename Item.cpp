#include "Item.h"

Item::Item()
{}

Item::Item(const char sym)
{
	_symbol = sym;
}

Item::Item(const char sym, const int x, const int y)
{
	_symbol = sym;
	_position.first = x;
	_position.second = y;
}

Item::Item(const char sym, const std::pair<int, int>& pos)
{
	_symbol = sym;
	_position = pos;
}

Item::~Item()
{}

void Item::SetPosition(const int x, const int y)
{
	_position.first = x;
	_position.second = y;
}

void Item::SetPosition(const std::pair<int, int>& coords)
{
	_position = coords;
}

const std::pair<int, int>& Item::GetPosition()
{
	return _position;
}
