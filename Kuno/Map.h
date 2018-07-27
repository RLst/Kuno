#pragma once
#include <vector>
#include <Vector3.h>
#include "PF.h"

namespace aie {
	class Renderer2D;
}

namespace pf {

class Tile;
class Layer;
class PropertySet;

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
	pkr::Vector3	m_mapOffset;
	int				m_width;			//Columns
	int				m_depth;			//Rows
	int				m_tileWidthpx;
	int				m_tileHeightpx;

	//Tile container
	Tile***			m_tiles;		//Pointer to the 2D array of tiles
	//std::vector<Tile*>	m_tiles;

public:
	pkr::Vector2	IsoToCart(const pkr::Vector2 &iso);
	pkr::Vector2	CartToIso(const pkr::Vector2 &cart);

	//Constructor
	Map(int mapWidth, int mapDepth, Tile*** tileArray, pkr::Vector3 offset = pkr::Vector3());
	
	//Destructor
	~Map();

	//void	loadMap();	//From file? Implement later
	//void	addTile(int xIndex, int yIndex, Tile* tile);

	void			draw(aie::Renderer2D* renderer);

	//Need to separate these out?
	void			drawTiles();
	void			drawAgents();
	void			drawObjects();

private:
	Map(const Map &map);	//Prevent copy constructor
};

}