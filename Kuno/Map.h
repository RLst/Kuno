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
	void				buildKunoMap();									//Build game map from raw data (maybe this should be in Game.cpp)
	void				connectNodesByDistance(float connectRadius);	//Also take into account tile's terrain and accessibility
	//void				loadMap();	//From file? Implement later

	//// Find Tile ////
	//Get the nearest tile using a CARTESIAN coord; 
	//Agents use this
	Tile*				findTileFromPos(const pkr::Vector2 &cPos, float searchRadius = 100.f);
	
	//Get the nearest tile using an ISOMETRIC coord; 
	//Mouse uses this; use this to find the tile under the mouse cursor
	Tile*				findTileFromCanvasPos(const pkr::Vector2 &iPos, float searchRadius = 100.f);	
	
	//Clamps
	pkr::Vector2		clampWithinMapRetWORLD(const pkr::Vector2 &Wpos);			//Returns a clamped WORLD position 
	Tile*				clampwithinMapRetTILE(const pkr::Vector2 &Wpos);			//Returns the nearest tile after clamping

	//Pathfinding
	Path				getDjikstraPath(Tile* start, Tile* end) const;
	Path				getAStarPath(Tile* start, Tile* end) const;
	Path				getPath() const { return m_path; }

	//Core
	void				update(float deltaTime);					//Handles mouse over tiles etc
	void				draw(aie::Renderer2D* renderer);			//Only draw tiles, walls and static objects

private:
	Map(const Map &map);	//Prevent copy constructor
};

}