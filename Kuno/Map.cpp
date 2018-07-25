#include "Map.h"
#include "Tile.h"

namespace PF {

	Map::Map(int mapWidth, int mapHeight)
	{
		//Create an array of tiles on the heap
		for (int col = 0; col < mapWidth; ++col) {
			m_tiles = new Tile**[mapWidth];
			for (int row = 0; row < mapHeight; ++row) {
				m_tiles[col] = new Tile*[mapHeight];
			}
		}
	}

	Map::~Map()
	{
		//Delete tiles
		for (auto &tile : m_tiles) {
			delete tile;
			tile = nullptr;
		}
	}
	void Map::draw(aie::Renderer2D * renderer)
	{
		//VERSION 1: Draw tiles by using the tile's draw function
		for (auto tile : m_tiles) {
			tile->draw(renderer);
		}


		//VERSION 2: Draw tiles by using the tile's properties
		//Advantages:
		//1. Be able to offset the map easier? Unless the tiles are sprite object parent to map
		for (auto tile : m_tiles) {
			//Draw tiles using the tile's properties
			float x = tile->pos_tmp.x + tile.offset.x;
			float y = tile->pos_tmp.y + tile.offset.y;

			//tile->X = 
		}

	}

}
