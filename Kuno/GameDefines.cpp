//////////////////
//// Tony Le ////
// 2 Aug 2018 //
///////////////


#include "GameDefines.h"
#include <random>

namespace pkr {

	int Random(int min, int max)
	{
		return min + (rand() % (max - min + 1));
	}

}