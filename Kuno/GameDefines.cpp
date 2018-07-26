#include "GameDefines.h"
#include <random>

int Random(int min, int max)
{
	return min + (rand() % (max - min + 1));
}
