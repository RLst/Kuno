#pragma once

#include <Texture.h>

namespace Util {

class DepthSorter
{
	//This class will auto sort the z buffer depth based on a sprite's origin Y position
	//That way you don't have to draw stuff in order to depth sort it ie:
	//The map can be drawn seperately from other game objects and agents

private:
	float		m_nearestYpos, m_furthestYpos;
	float		m_minDepth, m_maxDepth;
	float		m_totalDepthSegments;
	float		m_depthIteration;

public:
	DepthSorter();
	DepthSorter(float nearestYpos, float furthestYpos, float minDepth = 1.0f, float maxDepth = 100.0f);
	~DepthSorter();

	float		getSortDepth(float spriteYpos) const;
	float		getSortDepth(aie::Texture* tex) const;


};

}
