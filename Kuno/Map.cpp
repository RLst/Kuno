#include "Map.h"
#include "Tile.h"
#include "GameDefines.h"
#include <Texture.h>

#include "imgui/imgui.h"

#include "KunoApp.h"

namespace pf {

	Map::Map(int mapWidth, int mapDepth, Tile*** tileArray, pkr::Vector2 offset) :
		m_width(mapWidth),
		m_depth(mapDepth),
		m_tile_array(tileArray), 
		m_mapOffset(offset)
	{}

	Map::Map(int mapWidth, int mapDepth, pkr::Vector2 mapOffset) :
		m_width(mapWidth),
		m_depth(mapDepth),
		m_mapOffset(mapOffset)
	{}

	void Map::draw(aie::Renderer2D * renderer)
	{
		//Draw tiles and walls
		for (auto tile : m_tiles) {



		}

		//Draw static objects
		for (auto obj : m_staticObjects) {

		}

		for (int row = 0; row < m_width; ++row) {
			for (int col = 0; col < m_depth; ++col) {
				auto thisTile = m_tile_array[row][col];
				pkr::Vector2 isoPos, cartPos;

				//Get cartesian coords
				cartPos.x = col * CART_TILE_WIDTH;
				cartPos.y = row * CART_TILE_HEIGHT;

				//Convert to isometric
				//isoPos = KunoApp::CoordConverter.CartesianToIsometric(cartPos);
				isoPos = KunoApp::Instance()->CoordConverter()->CartesianToIsometric(cartPos);

				//// DRAW THE TILE ////
				//Find final tile positions
				pkr::Vector2 tilePos = isoPos + m_mapOffset;
				//Calculate the depth
				//float depth = KunoApp::DepthSorter.getSortDepth(tilePos.y);
				float depth = KunoApp::Instance()->DepthSorter()->getSortDepth(tilePos.y);
				renderer->setRenderColour(1, 1, 1);
				renderer->drawSprite(
					thisTile->getTexture(),				//Texture*
					tilePos.x,							//X
					tilePos.y,							//Y
					0,									//Width
					0,									//Height
					0,									//Rotation
					depth,								//Depth
					0.5f,								//Xorigin
					0.35f);								//Yorigin
				//Xorigin: 0.5f, Yorigin: 0.325f, seems to work OK

				//// DEBUG ////
				//Draw a debug point
				//renderer->setRenderColour(1, 0.75f, 0);
				//renderer->drawCircle(isoPos.x, isoPos.y, 5);
				///////////////
			}
		}
	}
}