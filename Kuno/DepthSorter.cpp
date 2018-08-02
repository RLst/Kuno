//////////////////
//// Tony Le ////
// 2 Aug 2018 //
///////////////


#include "DepthSorter.h"
#include "GameDefines.h"
#include <Texture.h>
#include "Agent.h"

namespace util {
	void DepthSorter::calcDepthIterator()
	{
		auto totalDepthSlices = abs(m_minYpos) + abs(m_maxYpos);
		m_depthIterator = (m_maxSortDepth - m_minSortDepth) / totalDepthSlices;
	}

	DepthSorter::DepthSorter(float minYpos, float maxYpos, float minSortDepth, float maxSortDepth) :
	m_minYpos(minYpos),
	m_maxYpos(maxYpos),
	m_minSortDepth(minSortDepth),
	m_maxSortDepth(maxSortDepth)
{
	calcDepthIterator();
}

float DepthSorter::getSortDepth(float spriteYpos)
{
	//Note: spriteYpos is the point at the base of the sprite object 
	//ie. Corresponds to the BACK CORNER of a tile/block/column OR feet of a character

	//Adjust limits for Y range
	if (spriteYpos < m_minYpos) {
		m_minYpos = spriteYpos;	
		calcDepthIterator();	//Recalc depth iterator
	}
	else if (spriteYpos > m_maxYpos) {
		m_maxYpos = spriteYpos;
		calcDepthIterator();	//Recalc depth iterator
	}
	
	//Dealt with sprites that are out of range
	//spriteYpos = pkr::Clamp(spriteYpos, m_minYpos, m_maxYpos);	//In this case just clamp

	//Add nearestYpos to spriteYpos
	spriteYpos += abs(m_minYpos);

	//Multiply spriteYpos by depthIterator to find the correct depth
	float sortedDepth = m_minSortDepth + (spriteYpos * m_depthIterator);

	return sortedDepth;
}

float DepthSorter::getSortDepth(ai::Agent * agent)
{
	//Get agent's isometric y position and then pass through first getSortDepth
	float agentYpos = agent->getPos().y;

	return getSortDepth(agentYpos);		//Hopefully the agent's Y position corresponds to it's sprite Y position too
}

}
