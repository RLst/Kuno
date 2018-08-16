//////////////////
//// Tony Le ////
// 2 Aug 2018 //
///////////////


#include "GameDefines.h"

namespace pkr {

	int Random(int min, int max)
	{
		//C
		return min + (rand() % (max - min + 1)); 

		//C++
		//std::default_random_engine DRE;
		//std::uniform_int_distribution<int> result(min, max);
		//return result(DRE);
	}

	float Random(float min, float max)
	{
		//C
		float multiplier = (float)rand() / (float)RAND_MAX;
		float diff = max - min;
		return min + multiplier * diff;

		//C++
		//std::default_random_engine DRE;
		//std::uniform_real_distribution<float> result(min, max);
		//return result(DRE);
	}

}