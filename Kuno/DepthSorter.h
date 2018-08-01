#pragma once

#include <Texture.h>

namespace ai {
	class Agent;
}

namespace util {

//This auto sorts the z buffer depth based on a sprite's origin Y position
//That way you don't have to draw stuff in correct order to depth sort it ie:
//The map can be drawn seperately from other game objects and agents
class DepthSorter
{

private:
	float		m_minYpos, m_maxYpos;
	float		m_minSortDepth, m_maxSortDepth;
	float		m_depthIterator;

	friend class KunoApp;		//For debugging only

	void		calcDepthIterator();

public:
	DepthSorter(float minYpos, float maxYpos, float minSortDepth = 1.0f, float maxSortDepth = 100.0f);
	~DepthSorter() = default;

	float		getSortDepth(float spriteYpos);			//Sorts the z-depth based on sprite Y position 	ie. corresponds to the isometric BACK CORNER of a tile/block/column OR feet of a character
	float		getSortDepth(ai::Agent *agent);			//Gets the agent Y position then pass through getSortDepth()

	float		getSortDepthByMapDiagonal(float spriteYpos) const;		//Advance depth sorting algorithm 
	float		getSortDepthByMapDiagonal(ai::Agent *agent) const;		//for near perfect depth sorting
};

}
