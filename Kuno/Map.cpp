#include "Map.h"
#include "Tile.h"
#include "GameDefines.h"

namespace PF {

	Map::Map(int mapWidth, int mapDepth, Tile*** tileArray, pkr::Vector3 offset) :
		m_width(mapWidth),
		m_depth(mapDepth),
		m_tiles(tileArray), 
		m_offset(offset)
	{}

	Map::~Map()
	{
		//Don't need to delete tiles; Array of tiles are already being deleted in KunoApp.cpp
	}

	void Map::draw(aie::Renderer2D * renderer)
	{
		////VERSION 1: Draw tiles by using the tile's draw function
		//for (auto tile : m_tileArray) {
		//	tile->draw(renderer);
		//}
		//VERSION 2: Draw tiles by using the tile's properties
		//Advantages:
		//1. Be able to offset the map easier? Unless the tiles are sprite object parent to map
		//for (auto tile : m_tileArray) {
		//	//Draw tiles using the tile's properties
		//	float x = tile->pos_tmp.x + tile.offset.x;
		//	float y = tile->pos_tmp.y + tile.offset.y;
		//	//tile->X = 
		//}

		//auto thisTile = m_tileArray;
		//VERSION 3: Draw tiles by map's offset
		for (int row = 0; row < m_width; ++row) {
			for (int col = 0; col < m_depth; ++col) {
				//thisTile++;
				auto thisTile = m_tiles[row][col];
				pkr::Vector2 isoPos, cartPos;

				//Get cartesian coords
				cartPos.x = col * tmpCARTESIAN_WIDTH;
				cartPos.y = row * tmpCARTESIAN_HEIGHT;

				//Convert to isometric
				isoPos = CartesianToIsometric(cartPos);

				//Adjust for height of tile if needed

				//Draw the tile
				renderer->drawSprite(
					m_tiles[row][col]->getTexture(), 
					isoPos.x + m_offset.x, 
					isoPos.y + m_offset.y);

				//renderer->drawSprite((***thisTile).getTexture(), isoPos.x, isoPos.y);
			}
		}


	}

	//These are Right Down render order I believe
	pkr::Vector2 Map::IsometricToCartesian(const pkr::Vector2 & isometric)
	{
		pkr::Vector2 cartesian;
		cartesian.x = (2.0f * isometric.y - isometric.x) / 2.0f;
		cartesian.y = (2.0f * isometric.y + isometric.x) / 2.0f;
		return cartesian;
	}

	pkr::Vector2 Map::CartesianToIsometric(const pkr::Vector2 & cartesian)
	{
		pkr::Vector2 isometric;
		isometric.x = (2.0f * cartesian.y + cartesian.x) / 2.0f;
		isometric.y = (2.0f * cartesian.y + cartesian.x) / 2.0f;
		return isometric;

		//isometric.x = (cartesian.x - cartesian.y) * ISO_TILE_WIDTH / 2.0f + m_offset.x;
		//isometric.y = (cartesian.x + cartesian.y) * ISO_TILE_HEIGHT / 3.0f + m_offset.y;
	}

	//These are Right Down render order I believe
	//pkr::Vector2 Map::IsometricToCartesian(const pkr::Vector2 & isometric)
	//{
	//	pkr::Vector2 cartesian;
	//	cartesian.x = (2.0f * isometric.y + isometric.x) / 2.0f;
	//	cartesian.y = (2.0f * isometric.y - isometric.x) / 2.0f;
	//	return cartesian;
	//}
	//pkr::Vector2 Map::CartesianToIsometric(const pkr::Vector2 & cartesian)
	//{
	//	pkr::Vector2 isometric;
	//	isometric.x = (2.0f * cartesian.y + cartesian.x) / 2.0f;
	//	isometric.y = (2.0f * cartesian.y - cartesian.x) / 2.0f;
	//	return isometric;
	//}
}
