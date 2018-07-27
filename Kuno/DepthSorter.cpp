#include "DepthSorter.h"
#include "GameDefines.h"
#include <Texture.h>
#include "Agent.h"

namespace util {

DepthSorter::DepthSorter(float nearestYpos, float furthestYpos, float minDepth, float maxDepth) :
	m_nearestYpos(nearestYpos),
	m_furthestYpos(furthestYpos),
	m_minDepth(minDepth),
	m_maxDepth(maxDepth)
{
	//Calculate iterations
	m_totalDepthSegments = abs(m_nearestYpos) + abs(m_furthestYpos);
	m_depthIterator = (m_maxDepth - m_minDepth) / m_totalDepthSegments;
}

float DepthSorter::getSortDepth(float spriteYpos) const
{
	//Note: spriteYpos is the point at the base of the sprite object 
	//ie. Corresponds to the front corner of a tile OR feet of a character

	//Dealt with sprites that are out of range
	spriteYpos = pkr::Clamp(spriteYpos, m_nearestYpos, m_furthestYpos);	//In this case just clamp

	//Add nearestYpos to spriteYpos
	spriteYpos += m_nearestYpos;

	//Multiply spriteYpos by depthIterator to find the correct depth
	float sortedDepth = spriteYpos * m_depthIterator;

	return sortedDepth;
}

float DepthSorter::getSortDepth(ai::Agent * agent) const
{
	//Get agent's isometric y position and then pass through first getSortDepth
	float agentYpos = agent->getPos().y;

	return getSortDepth(agentYpos);		//Hopefully the agent's Y position corresponds to it's sprite Y position too
}

//float DepthSorter::getSortDepth(aie::Texture * tex) const
//{
//	//Get sprite Y position then process as usual
//	spriteYpos = tex.
//
//	//Dealt with sprites that are out of range
//	spriteYpos = Clamp(spriteYpos, m_nearestYpos, m_furthestYpos);	//In this case just clamp
//
//																	//Add nearestYpos to spriteYpos
//	spriteYpos += m_nearestYpos;
//
//	//Multiply spriteYpos by depthIterator to find the correct depth
//	float correctDepth = spriteYpos * m_depthIterator;
//
//	return correctDepth;
//	return 0.0f;
//}



}
