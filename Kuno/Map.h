#pragma once
#include <vector>
#include <Vector3.h>
#include "PF.h"

namespace aie {
	class Renderer2D;
}

namespace pf {

class Tile;
class StaticObject;

//typedef std::vector<Tile*> TileList;
//typedef std::vector<pkr::Vector2*> PointList;		//More accurate list of waypoints

enum eLayerType {	//Also holds the depth setting
	BACKGROUND = 0,
	GROUND = 1,
	OBJECT = 10,
	WALLS = 10,
	ROOF = 100,
};

class Map : public Graph
{
	//A map contains a grid of tiles
	//A grid is 
	//The map draws the tile according to the tile's offset and height etc

private:
	pkr::Vector2	m_mapOffset;
	int				m_width;			//Columns
	int				m_depth;			//Rows
	int				m_tileWidthpx;
	int				m_tileHeightpx;

	//Tile container
	Tile***			m_tile_array;		//Pointer to the 2D array of tiles
	std::vector<Tile*>	m_tiles;

	//Static object container
	std::vector<StaticObject*> m_staticObjects;

public:
	Map() = default;
	~Map() = default;	//Tile array already being deleted in KunoApp.cpp

	//Constructor using pointer to array of tiles
	Map(int mapWidth, int mapDepth, Tile*** tileArray, pkr::Vector2 offset = { 0,0 });
	
	//Constructor using vector of Tile*; Add tiles afterwards
	Map(int mapWidth, int mapDepth, pkr::Vector2 mapOffset);

	void			addTile(Tile* tile);
	void			buildMap();
	//void			loadMap();	//From file? Implement later

	//Core
	void			draw(aie::Renderer2D* renderer);			//Only draw tiles, walls and static objects

private:
	Map(const Map &map);	//Prevent copy constructor
};

}