#pragma once

#include <Texture.h>

namespace ai {
	class Agent;
}

namespace util {

class DepthSorter
{
	//This class will auto sort the z buffer depth based on a sprite's origin Y position
	//That way you don't have to draw stuff in order to depth sort it ie:
	//The map can be drawn seperately from other game objects and agents

private:
	float		m_nearestYpos, m_furthestYpos;
	float		m_minDepth, m_maxDepth;
	float		m_totalDepthSegments;
	float		m_depthIterator;

public:
	DepthSorter(float nearestYpos, float furthestYpos, float minDepth = 1.0f, float maxDepth = 100.0f);
	~DepthSorter() = default;

	float		getSortDepth(float spriteYpos) const;		//Sorts the z-depth based on sprite Y position
	float		getSortDepth(ai::Agent *agent) const;			//Gets the agent Y position then pass through getSortDepth()
};

}
