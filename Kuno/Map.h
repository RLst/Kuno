//////////////////
//// Tony Le ////
// 2 Aug 2018 //
///////////////


#pragma once
#include <vector>
#include <pkr\Vector3.h>
#include "PF.h"

namespace aie {
	class Renderer2D;
}

namespace pf {

class Tile;
class StaticObject;

//typedef std::vector<Tile*> TileList;
//typedef std::vector<pkr::Vector2*> PointList;		//More accurate list of waypoints

class Map /*: public Graph*/
{
	//A map contains a grid of tiles
	//A grid is 
	//The map draws the tile according to the tile's offset and height etc

private:
	pkr::Vector2		m_mapOffset = { 0, 0 };	//Default starts at 0,0
	int					m_width = 0;			//Columns
	int					m_depth = 0;			//Rows

	std::vector<Tile*>	m_tiles;				//Container of tiles

	//Tile tinting on mouse over
	Tile*				m_tileMouseOver;		//The tile the mouse is over

	//Test out pathfinding
	Path				m_path;
	Tile*				m_pathStart = nullptr;
	Tile*				m_pathEnd = nullptr;

public:

	Map() = default;
	~Map();			//Delete everything in the layers

	Map(int mapWidth, int mapDepth, pkr::Vector2 mapOffset);

	//Create maps
	void				buildRandomMap(int width, int depth);
	void				connectNodesByDistance(float connectRadius);	//Also take into account tile's terrain and accessibility
	void				buildKunoMap();									//Build game map from raw data (maybe this should be in Game.cpp)
	//void				loadMap();	//From file? Implement later
	//void				addTile(Tile* tile);

	//Find tile
	Tile*				findTileFromCpos(pkr::Vector2 &cPos, float searchRadius = 75.f);	//Get the nearest tile using an CARTESIAN coord
	Tile*				findTileFromIpos(pkr::Vector2 &iPos, float searchRadius = 75.f);	//Get the nearest tile using an ISOMETRIC coord

	Path				getAStarPath(Tile* startTile, Tile* endTile) const;

	//Core
	void				update(float deltaTime);					//Handles mouse over tiles etc
	void				draw(aie::Renderer2D* renderer);			//Only draw tiles, walls and static objects

private:
	Map(const Map &map);	//Prevent copy constructor
};

}