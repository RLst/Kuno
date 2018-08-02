//////////////////
//// Tony Le ////
// 2 Aug 2018 //
///////////////


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
	pkr::Vector2		m_mapOffset = { 0, 0 };	//Default starts at 0,0
	int					m_width = 0;			//Columns
	int					m_depth = 0;			//Rows

	std::vector<Tile*>	m_tiles;				//Container of tiles

public:
	Map() = default;
	~Map();			//Delete everything in the layers

	Map(int mapWidth, int mapDepth, pkr::Vector2 mapOffset);

	//Setups
	void				buildTestMap(int width, int depth);
	void				connectNodesByDistance(float connectRadius);	//Also take into account tile's terrain and accessibility

	void				buildKunoMap();				//Build game map raw

	//void				loadMap();					//From file? Implement later
	//void				addTile(Tile* tile);
	
	//Core	
	void				draw(aie::Renderer2D* renderer);	//Only draw tiles, walls and static objects

private:
	Map(const Map &map);	//Prevent copy constructor
};

}