#pragma once
#include <vector>

namespace aie {
	class Renderer2D;
}

namespace PF {

class Tile;

class Map
	//A map contains a grid of tiles
	//The map draws the tile
{
private:
	int					width;
	int					height;
	std::vector<Tile*>	m_tiles;

public:
	Map(int mapWidth, int mapHeight);
	~Map();

	void	addTile(int xIndex, int yIndex, Tile* tile);
	void	draw(aie::Renderer2D* renderer);
};

}
