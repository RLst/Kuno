#include "DepthSorter.h"

namespace Util {


DepthSorter::DepthSorter()
{
}

DepthSorter::DepthSorter(float nearestYpos, float furthestYpos, float minDepth, float maxDepth) :
	m_nearestYpos(nearestYpos),
	m_furthestYpos(furthestYpos),
	m_minDepth(minDepth),
	m_maxDepth(maxDepth)
{
	//Calculate iterations
	float		m_totalDepthSegments = abs(m_nearestYpos) + abs(m_furthestYpos);
	float		m_depthIteration = (m_maxDepth - m_minDepth) / m_totalDepthSegments;
}

DepthSorter::~DepthSorter()
{
}

float DepthSorter::getSortDepth(float spriteYpos) const
{
	//
	return 0.0f;
}

}
