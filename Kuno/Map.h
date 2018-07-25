#pragma once
#include <vector>

namespace aie {
	class Renderer2D;
}

namespace PF {

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

class Map
{
	//A map contains a grid of tiles
	//A grid is 
	//The map draws the tile according to the tile's offset and height etc

private:
	int				m_width;
	int				m_height;
	int				m_tileWidth;
	int				m_tileHeight;

	//Tile container
	//std::vector<Tile*>		m_tiles;
	Tile***			m_tiles;	//How to make a set array in c++??

	//Layer container
	std::vector<Layer*>		m_layers;

	//Object container?

	//Other
	bool			hasError;
	unsigned char	errorCode;
	std::string		errorText;

	PropertySet		m_properties;



	//void	addTile(int xIndex, int yIndex, Tile* tile);
public:
	Map(int mapWidth, int mapHeight);
	~Map();

	void	loadMap();
	void	draw(aie::Renderer2D* renderer);

private:
	Map(const Map &map);	//Prevent copy constructor
};

}


//


