//////////////////
//// Tony Le ////
// 2 Aug 2018 //
///////////////


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

	//Sort depth by diagonal
	/*
	Requirements:
	* Tile map height in pixels
	* Map grid size (rows and columns)
	* Start point of map

	How to:
	* Find the point of the map that is the furthest away from the camera
	* Calculate how many diagonals the map will have: rows + columns - 1
	1x1 = 1 horizontal diagonal ... rows + columns - 1
	2x2 = 3 horizontal diagonals
	3x3 = 5 diagonals
	3x2 = 4 diagonals
	FIGURED IT OUT!!!: number of diagonals in a grid = rows + columns - 1


	* Figure out which diagonal the sprite/agent is on (y pos)
		* Get y pos of object/agent
	*/
};

}
