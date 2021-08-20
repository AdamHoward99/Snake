#pragma once
#include <stdlib.h>
#include <ctime>

class RandomNumberGenerator
{
public:
	void seed() {
		srand(static_cast<unsigned>(time(0)));
	}

	int random(int max) {
		if (max <= 0)
			exit(EXIT_FAILURE);

		return (rand() % max) + 1;
	}
};