#include "Map.h"
#include "Tile.h"
#include "GameDefines.h"
#include <Texture.h>

#include "imgui/imgui.h"

#include <ctime>

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
		

		//VERSION 3: Draw tiles by map's offset

		//// DEBUG: to find the proper tile offsets? //////
		//static float cartWidth = -127;
		//static float cartHeight = -127;
		//ImGui::Begin("Map::Tile width adjustment");
		//ImGui::SliderFloat("CartWidth", &cartWidth, -256, 256);
		//ImGui::SliderFloat("CartHeight", &cartHeight, -256, 256);
		//ImGui::End();
		////////////

		//auto thisTile = m_tileArray;
		float mapDrawStartTime = time(NULL);

		for (int row = 0; row < m_width; ++row) {
			for (int col = 0; col < m_depth; ++col) {
				//thisTile++;
				auto thisTile = m_tiles[row][col];
				pkr::Vector2 isoPos, cartPos;

				//Get cartesian coords
				cartPos.x = col * CART_TILE_WIDTH;
				cartPos.y = row * CART_TILE_HEIGHT;
				//cartPos.x = col * cartWidth;
				//cartPos.y = row * cartHeight;

				//Convert to isometric
				isoPos = CartesianToIsometric(cartPos);

				//Adjust for height of tile if needed
				//float tmpDifY = ISO_TILE_HEIGHT - (float)thisTile->getTexture()->getHeight();

				// account for the difference in height in the texture
				// and keep the bottoms aligned
				//float dify = TILE_HEIGHT -
				//	(float)thisTile->getTexture()->getHeight();

				//Draw the tile
				renderer->setRenderColour(1, 1, 1);
				renderer->drawSprite(
					thisTile->getTexture(),					//Texture*
					isoPos.x + m_offset.x,					//X
					isoPos.y + m_offset.y,					//Y
					0,						
					0,
					0,
					10,										//Depth
					0.0f,									//Xorigin
					0.0f);									//Yorigin


				//// DEBUG ////
				//Draw a debug point
				//renderer->setRenderColour(1, 0, 0);
				//renderer->drawCircle(isoPos.x, isoPos.y, 5);
				///////////////

				//renderer->drawSprite((***thisTile).getTexture(), isoPos.x, isoPos.y);
			}
		}

		//// DEBUG ////
		float mapDrawEndTime = time(NULL);
		ImGui::Begin("Map Draw Duration");
		ImGui::Text("%f",mapDrawEndTime - mapDrawStartTime);
		ImGui::End();
		//////////////
	}

	//These are Right Down render order I believe
	pkr::Vector2 Map::IsometricToCartesian(const pkr::Vector2 & isometric)
	{
		static float tileRatio = (float)ISO_TILE_WIDTH / (float)ISO_TILE_HEIGHT;
		pkr::Vector2 cartesian;
		cartesian.x = (tileRatio * isometric.y + isometric.x) / tileRatio;
		cartesian.y = (tileRatio * isometric.y - isometric.x) / tileRatio;
		return cartesian;
		//cartesian.x = (2.0f * isometric.y - isometric.x) / 2.0f;
		//cartesian.y = (2.0f * isometric.y + isometric.x) / 2.0f;
	}

	pkr::Vector2 Map::CartesianToIsometric(const pkr::Vector2 & cartesian)
	{

		static float tileRatio = (float)ISO_TILE_WIDTH / (float)ISO_TILE_HEIGHT;
		pkr::Vector2 isometric = { 0,0 };
		isometric.x = cartesian.x - cartesian.y;
		isometric.y = (cartesian.x + cartesian.y) / tileRatio;			
		return isometric;
		//isometric.x = (2.0f * cartesian.y - cartesian.x) / 2.0f;
		//isometric.y = (2.0f * cartesian.y + cartesian.x) / 2.0f;
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
