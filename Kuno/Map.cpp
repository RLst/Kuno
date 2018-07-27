#include "Map.h"
#include "Tile.h"
#include "GameDefines.h"
#include <Texture.h>

#include "imgui/imgui.h"

#include "KunoApp.h"

namespace pf {

	Map::Map(int mapWidth, int mapDepth, Tile*** tileArray, pkr::Vector3 offset) :
		m_width(mapWidth),
		m_depth(mapDepth),
		m_tiles(tileArray), 
		m_mapOffset(offset)
	{}

	Map::~Map()
	{
		//Don't need to delete tiles; Array of tiles are already being deleted in KunoApp.cpp
	}

	void Map::draw(aie::Renderer2D * renderer)
	{
		//// DEBUG: to find the proper tile offsets? //////
		//static float cartWidth = -127;
		//static float cartHeight = -127;
		//ImGui::Begin("Map::Tile width adjustment");
		//ImGui::SliderFloat("CartWidth", &cartWidth, -256, 256);
		//ImGui::SliderFloat("CartHeight", &cartHeight, -256, 256);
		//ImGui::End();
		////////////

		for (int row = 0; row < m_width; ++row) {
			for (int col = 0; col < m_depth; ++col) {
				auto thisTile = m_tiles[row][col];
				pkr::Vector2 isoPos, cartPos;

				//Get cartesian coords
				cartPos.x = col * CART_TILE_WIDTH;
				cartPos.y = row * CART_TILE_HEIGHT;
				//cartPos.x = col * cartWidth;
				//cartPos.y = row * cartHeight;

				//Convert to isometric
				isoPos = KunoApp::getInstance()->getCoordConverter()->CartesianToIsometric(cartPos);
				//isoPos = CartToIso(cartPos);

				//Adjust for height of tile if needed
				//float tmpDifY = ISO_TILE_HEIGHT - (float)thisTile->getTexture()->getHeight();

				// account for the difference in height in the texture
				// and keep the bottoms aligned
				//float dify = TILE_HEIGHT -
				//	(float)thisTile->getTexture()->getHeight();

				//// DRAW THE TILE ////
				//Find final tile positions
				pkr::Vector2 tilePos = isoPos + m_mapOffset;
				//Calculate the depth
				float depth = KunoApp::getInstance()->getDepthSorter()->getSortDepth(tilePos.y);
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
					0.4f);								//Yorigin
				//Xorigin: 0.5f, Yorigin: 0.4f, seems to work OK

				//// DEBUG ////
				//Draw a debug point
				//renderer->setRenderColour(1, 0.75f, 0);
				//renderer->drawCircle(isoPos.x, isoPos.y, 5);
				///////////////
			}
		}
	}
}