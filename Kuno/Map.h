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

class Map
{
	//A map contains a grid of tiles
	//A grid is 
	//The map draws the tile according to the tile's offset and height etc

private:
	//pkr::Vector2		m_mapCoffset = { 0, 0 };	//MAP SHOULD ALWAYS START AT 0,0!!! Default starts at 0,0
	int					m_width = 0;			//Columns
	int					m_depth = 0;			//Rows

	std::vector<Tile*>	m_tiles;				//Container of tiles

	//Tile tinting on mouse over
	Tile*				m_tileMouseOver;		//The tile the mouse is over

	//Test out pathfinding
	bool				m_drawConnections = true;
	bool				m_useAstar = true;
	Path				m_path;
	Tile*				m_pathStart = nullptr;
	Tile*				m_pathEnd = nullptr;

public:

	Map() = default;
	~Map();			//Delete everything in the layers

	Map(int mapWidth, int mapDepth);

	//Create maps
	void				buildRandomMap(int width, int depth);
	void				connectNodesByDistance(float connectRadius);	//Also take into account tile's terrain and accessibility
	void				buildKunoMap();									//Build game map from raw data (maybe this should be in Game.cpp)
	//void				loadMap();	//From file? Implement later
	//void				addTile(Tile* tile);

	//Find tile
	Tile*				findTileFromPos(pkr::Vector2 &cPos, float searchRadius = 100.f);	//Get the nearest tile using an CARTESIAN coord
	Tile*				findTileFromCanvasPos(pkr::Vector2 &iPos, float searchRadius = 100.f);	//Get the nearest tile using an ISOMETRIC coord

	Path				getDjikstraPath(Tile* startTile, Tile* endTile) const;
	Path				getAStarPath(Tile* startTile, Tile* endTile) const;

	//Accessors
	Path				getPath() const { return m_path; }

	//Core
	void				update(float deltaTime);					//Handles mouse over tiles etc
	void				draw(aie::Renderer2D* renderer);			//Only draw tiles, walls and static objects

private:
	Map(const Map &map);	//Prevent copy constructor
};

}