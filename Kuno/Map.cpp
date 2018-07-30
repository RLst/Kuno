#include "Map.h"
#include <Texture.h>
#include "imgui/imgui.h"
#include "GameDefines.h"
#include "Tile.h"
#include <pkr/Vector2.h>

#include "KunoApp.h"

namespace pf {
	Map::~Map()
	{
		//Ground layer
		for (auto &t : m_groundLayer) {
			delete t;
			t = nullptr;
		}

		//Main layer
		for (auto &t : m_mainLayer) {
			delete t;
			t = nullptr;
		}

		//Object layer
		for (auto &so : m_objectLayer) {
			delete so;
			so = nullptr;
		}

	}

	Map::Map(int mapWidth, int mapDepth, pkr::Vector2 mapOffset) :
		m_width(mapWidth),
		m_depth(mapDepth),
		m_mapOffset(mapOffset)
	{
		buildTestMap(m_width, m_depth);
	}

	void Map::buildTestMap(int width, int depth)
	{
		//Call texture manager
		auto TM = KunoApp::Instance()->TextureManager();

		//Ground layer
		for (int row = 0; row < depth; ++row) {
			for (int col = 0; col < width; ++col) {
				//Create and insert new tile into vector
				Tile* newTile = new Tile();		//IMPORTANT!!! This must be created on the heap, NOT the stack!!!

				//Randomize tiles + determine other parameters
				switch (pkr::Random(0, 4)) {
				case 0:	//Floor
					//newTile.m_texOffset = { 0,0 };		//Set this later
					newTile->tex = TM->getTexture("Floor");
					newTile->type = eTileType::ACCESSIBLE;
					break;
				case 1:	//Slab
					//newTile.m_texOffset = { 0,0 };		//Set this later
					newTile->tex = TM->getTexture("Slab");
					newTile->type = eTileType::ACCESSIBLE;
					break;
				case 2: //HugeBlock
					//newTile.m_texOffset = { 0,0 };		//Set this later
					newTile->tex = TM->getTexture("HugeBlock");
					newTile->type = eTileType::INACCESSIBLE;
					break;
				case 3: //Column
					//newTile.m_texOffset = { 0,0 };		//Set this later
					newTile->tex = TM->getTexture("Column");
					newTile->type = eTileType::INACCESSIBLE;
					break;
				case 4:	//ColumnBlocks
					//newTile.m_texOffset = { 0,0 };		//Set this later
					newTile->tex = TM->getTexture("ColumnBlocks");
					newTile->type = eTileType::INACCESSIBLE;
					break;
				case 5:	//SmallBlock
					//newTile.m_texOffset = { 0,0 };		//Set this later
					newTile->tex = TM->getTexture("SmallBlock");
					newTile->type = eTileType::INACCESSIBLE;
					break;
				case 6:	//LargeBlock
					//newTile.m_texOffset = { 0,0 };		//Set this later
					newTile->tex = TM->getTexture("LargeBlock");
					newTile->type = eTileType::INACCESSIBLE;
					break;
				default:
					assert(false);		//Something went wrong!
				}

				//Determine position of new tile
				newTile->posCart = m_mapOffset + pkr::Vector2(col * CART_TILE_HEIGHT, row * CART_TILE_WIDTH);

				//Insert tile into ground layer
				m_groundLayer.push_back(newTile);
			}
		}

	}

	void Map::draw(aie::Renderer2D * renderer)
	{
		auto app = KunoApp::Instance();

		//Draw tiles and walls
		for (auto &t : m_groundLayer) 
		{
			//Convert cartesian to isometric
			t->posIso = app->CoordConverter()->CartesianToIsometric(t->posCart);

			//Calculate render depth
			auto depth = app->DepthSorter()->getSortDepth(t->posIso.y);

			//Draw tile
			if (t->onMouseOver())
				renderer->setRenderColour(0.6f, 0.6f, 0.6f);
			else
				renderer->setRenderColour(1, 1, 1);
			renderer->drawSprite(t->tex, t->posIso.x, t->posIso.y, 0, 0, 0, depth);
		}

		//for (auto t : m_mainLayer) {

		//}

		////Draw static objects
		//for (auto obj : m_objectLayer) {

		//}

		//for (int row = 0; row < m_width; ++row) {
		//	for (int col = 0; col < m_depth; ++col) {
		//		auto thisTile = m_tile_array[row][col];
		//		pkr::Vector2 isoPos, cartPos;
		//		//Get cartesian coords
		//		cartPos.x = col * CART_TILE_WIDTH;
		//		cartPos.y = row * CART_TILE_HEIGHT;
		//		//Convert to isometric
		//		//isoPos = KunoApp::CoordConverter.CartesianToIsometric(cartPos);
		//		isoPos = KunoApp::Instance()->CoordConverter()->CartesianToIsometric(cartPos);
		//		//// DRAW THE TILE ////
		//		//Find final tile positions
		//		pkr::Vector2 tilePos = isoPos + m_mapOffset;
		//		//Calculate the depth
		//		//float depth = KunoApp::DepthSorter.getSortDepth(tilePos.y);
		//		float depth = KunoApp::Instance()->DepthSorter()->getSortDepth(tilePos.y);
		//		renderer->setRenderColour(1, 1, 1);
		//		renderer->drawSprite(
		//			thisTile->getTexture(),				//Texture*
		//			tilePos.x,							//X
		//			tilePos.y,							//Y
		//			0,									//Width
		//			0,									//Height
		//			0,									//Rotation
		//			depth,								//Depth
		//			0.5f,								//Xorigin
		//			0.35f);								//Yorigin
		//		//Xorigin: 0.5f, Yorigin: 0.325f, seems to work OK
		//		//// DEBUG ////
		//		//Draw a debug point
		//		//renderer->setRenderColour(1, 0.75f, 0);
		//		//renderer->drawCircle(isoPos.x, isoPos.y, 5);
		//		///////////////
		//	}
		//}

	}
}