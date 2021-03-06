//////////////////
//// Tony Le ////
// 2 Aug 2018 //
///////////////

#pragma once
#include <vector>
#include <pkr\math\Vector3.h>
#include "PF.h"
#include "GameDefines.h"

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
	Path				m_path;
	Tile*				m_pathStart = nullptr;
	Tile*				m_pathEnd = nullptr;

public:
	bool				useAstar = true;
public:

	Map() = default;
	~Map();			//Delete everything in the layers

	Map(int mapWidth, int mapDepth);

	//Create maps
	//void				buildRandomMap(int width, int depth);
	void				buildKunoMap();									//Build game map from raw data (maybe this should be in Game.cpp)
	void				connectNodesByDistance(float connectRadius);	//Also take into account tile's terrain and accessibility
	float				getTerrainCost(const pf::Tile * tile);
	//void				loadMap();	//From file? Implement later

	//Tiles
	Tile*				findTileFromPos(const pkr::Vector2 &pos);	//Get the nearest tile using a CARTESIAN coord; Agents use this
	Tile*				findTileFromCanvasPos(const pkr::Vector2 &cPos);	//Get the nearest tile using an ISOMETRIC coord; Mouse uses this; use this to find the tile under the mouse cursor
	std::vector<Tile*>	getTiles() const { return m_tiles; }

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