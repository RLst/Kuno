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

		//// Ground layer ////
		int ID = 0;		//Tile ID
		for (int row = 0; row < depth; ++row) 
		{
			for (int col = 0; col < width; ++col) 
			{
				++ID;
				ID = m_groundLayer.size() + 1;

				//Create new tile
				Tile* newTile = new Tile();		//IMPORTANT!!! This must be created on the heap, NOT the stack!!!

				//Sets
				newTile->ID = ID;
				newTile->cPos = m_mapOffset + pkr::Vector2(static_cast<float>(col * CART_TILE_HEIGHT), static_cast<float>(row * CART_TILE_WIDTH));

				//Randomize tiles and set other tile properties
				switch (pkr::Random(0, 1))
				{
					//Floor
				case 0:
					newTile->tex = TM->getTexture("Floor");
					newTile->dsOffset = pkr::Vector2(0, 75.0f);
					newTile->terrain = SMOOTH_FLOOR;
					newTile->access = ACCESSIBLE;
					//newTile = new Tile(Tpos,
					//	TM->getTexture("Floor"),
					//	pkr::Vector2(0.0f, 75.0f),
					//	eTileTerrain::SMOOTH_FLOOR);
					break;

					//Slab
				case 1:
					newTile->tex = TM->getTexture("Slab");
					newTile->dsOffset = pkr::Vector2(0, 75.0f);
					newTile->terrain = SMOOTH_FLOOR;
					newTile->access = ACCESSIBLE;
					break;
				default:
					assert(false);		//Something went wrong!
				}

				//Insert tile into layer only if it is valid
				if (newTile->tex != nullptr)
					m_groundLayer.push_back(newTile);
			}
		}

		//// Main layer ////
		ID = 0;
		for (int row = 0; row < depth; ++row) 
		{
			for (int col = 0; col < width; ++col) 
			{
				ID = m_mainLayer.size() + 1;

				auto randomize = pkr::Random(0, 15);	//Not all tiles will get filled
				if (randomize < 5) {	//Only create a tile where necessary to avoid fragmentation

					//Create new tile
					Tile* newTile = new Tile();		//IMPORTANT!!! This must be created on the heap, NOT the stack!!!

					//Sets
					newTile->ID = ID;
					newTile->cPos = m_mapOffset + pkr::Vector2(static_cast<float>(col * CART_TILE_HEIGHT), static_cast<float>(row * CART_TILE_WIDTH));

					switch (randomize) {
					case 0: //HugeBlock
						newTile->tex = TM->getTexture("HugeBlock");
						newTile->dsOffset = pkr::Vector2(0, 75.0f);		//Isometric back bottom corner
						newTile->terrain = GRASS;						//Cost = 1.0f
						newTile->access = INACCESSIBLE;
						break;
					//case 1: //Column
					//	newTile->tex = TM->getTexture("Column");
					//	newTile->dsOffset = pkr::Vector2(0, 19.f);		//Isometric back bottom corner
					//	newTile->terrain = GRASS;						//Cost = 1.0f
					//	newTile->access = INACCESSIBLE;
					//	break;
					//case 2:	//ColumnBlocks
					//	newTile->tex = TM->getTexture("ColumnBlocks");
					//	newTile->dsOffset = pkr::Vector2(0, 19.f);		//Isometric back bottom corner
					//	newTile->terrain = GRASS;						//Cost = 1.0f
					//	newTile->access = INACCESSIBLE;
					//	break;
					//case 3:	//SmallBlock
					//	newTile->tex = TM->getTexture("SmallBlock");
					//	newTile->dsOffset = pkr::Vector2(0, 19.f);		//Isometric back bottom corner
					//	newTile->terrain = GRASS;						//Cost = 1.0f
					//	newTile->access = INACCESSIBLE;
					//	break;
					//case 4:	//LargeBlock
					//	newTile->tex = TM->getTexture("LargeBlock");
					//	newTile->dsOffset = pkr::Vector2(0, 39.f);		//Isometric back bottom corner
					//	newTile->terrain = GRASS;						//Cost = 1.0f
					//	newTile->access = INACCESSIBLE;
					//	break;
					}

					//Insert tile into main layer
					m_mainLayer.push_back(newTile);
				}
			}
		}

	}

	void Map::connectNodesByDistance(float connectRadius)
	{
		for (auto tileA : m_groundLayer) {
			for (auto tileB : m_groundLayer) {
				
				//Get working ID to access 
				//int workingID = tileA->ID;

				//Find equivalent tile in main layer if it exists
				Tile* ParallelMainTile;
				StaticObject* ParallelObject;


				//Skip if they're both the same node
				if (tileA == tileB) continue;

				//Skip if ground tile OR main layer tile not ACCESSIBLE
				if (tileB->access == INACCESSIBLE) continue;
				//if (tileB->access == INACCESSIBLE) ||					//Ground layer
				//	m_mainLayer[tileB->ID]->access == INACCESSIBLE)		//Main layer tile/object

				//Find the tile (REALLY DUMB; should use binary tree or something)
				int EquivMainTileID = 0;
				for (auto mainTile : m_mainLayer) {
					if (mainTile->ID == tileB->ID) {	//Found the tile
						EquivMainTileID = mainTile->ID;

							//EquivMainTileID = m_mainLayer.size()-1;
						break;
					}
				}
				if (EquivMainTileID < m_mainLayer.size())
				{
					if (m_mainLayer[EquivMainTileID]->access == INACCESSIBLE)
						continue;
				}

				//Find the distance between the two tiles
				float distanceBetween = tileA->cPos.distance(tileB->cPos);

				//If they're within range then connect
				if (distanceBetween < connectRadius) {
					//// Take into account tile's accessibility and terrain ////
					//Set the edge cost based on the terrain
					//auto terrainCost = tileB->terrain;

					float cost = 1.0f;	//Default cost to 1

					//ground layer
					switch (tileB->terrain) {
					case NA:
						cost = INFINITY;
						break;
					case SMOOTH_FLOOR:
						cost = 0.5f;
						break;
					case GRASS:
						cost = 1.0f;
						break;
					case DIRT:
						cost = 1.3f;
						break;
					case GRAVEL:
						cost = 2.0f;
						break;
					case WATER:
						cost = 5.0f;
						break;
					default:
						assert(false);		//Invalid
					}

					pf::Node::connect(tileA, tileB, cost);	//This should also connect tiles both ways
				}
			}
		}

	}

	void Map::draw(aie::Renderer2D * renderer)
	{
		auto app = KunoApp::Instance();

		//Draw the ground tile layerr
		for (auto t : m_groundLayer) 
		{
			//Convert cartesian to isometric
			t->iPos = app->CoordConverter()->CartesianToIsometric(t->cPos);

			//Calculate render depth
			auto depth = app->DepthSorter()->getSortDepth(t->iPos.y);

			//Set colour
			if (t->onMouseOver())	renderer->setRenderColour(0.3f, 0.3f, 0.3f);
			else	renderer->setRenderColour(1, 1, 1);
			
			//Draw tile
			t->draw(renderer);

			//// DEBUG ////
			//Draw all the node/tile connections
			static int temp = 0;
			ImGui::Begin("Draw edge");
			for (auto c : t->connections) {
				pkr::Vector2 start = t->iPos;
				pkr::Vector2 end = c->target->iPos;
				renderer->setRenderColour(0, 0, 0);
				renderer->drawLine(start.x, start.y, end.x, end.y, 1.5f, 0.01f);
				ImGui::Text("Start > x: %.1f, y: %.1f", start.x, start.y);
				ImGui::Text("End > x: %.1f, y: %.1f", end.x, end.y);
				//temp++;
				//if (temp++)
			}
			ImGui::End();

			////Draw the cPos of the tile (should be the tile's isometric centre)
			//renderer->setRenderColour(0, 0, 0);
			//auto fPos = t->iPos;		//Final position
			//renderer->drawBox(fPos.x, fPos.y, 3, 3, 0, 0);
			////Draw the depth sort offset of the tile (!!! MIGHT NOT NEED THIS IF I BUILD AN ADVANCE DEPTH SORTING ALGORITHM)
			//renderer->setRenderColour(0, 0, 1);
			//renderer->drawBox(t->iPos.x + t->dsOffset.x, t->iPos.y + t->dsOffset.y, 3, 3, 0, 0);
			/////////////////
		}

		//Draw the main tile layer
		for (auto t : m_mainLayer) {
			//Convert cartesian to isometric
			t->iPos = app->CoordConverter()->CartesianToIsometric(t->cPos);

			//Calculate render depth
			auto depth = app->DepthSorter()->getSortDepth(t->iPos.y);

			//Set render colours
			if (t->onMouseOver())	renderer->setRenderColour(0.6f, 0.6f, 0.6f);
			else	renderer->setRenderColour(1, 1, 1);

			//Draw tile
			t->draw(renderer);

			////// DEBUG ////
			////Draw the cPos of the tile (should be the tile's isometric centre)
			//renderer->setRenderColour(0, 0, 0);
			//auto fPos = t->iPos;		//Final position
			//renderer->drawBox(fPos.x, fPos.y, 5, 5, 0, 0);
			////Draw the depth sort offset of the tile (!!! MIGHT NOT NEED THIS IF I BUILD AN ADVANCE DEPTH SORTING ALGORITHM)
			//renderer->setRenderColour(0, 0, 1);
			//renderer->drawBox(t->iPos.x + t->dsOffset.x, t->iPos.y + t->dsOffset.y, 5, 5, 0, 0);
			/////////////////
		}

		//Draw static objects
		for (auto obj : m_objectLayer) {

		}
	}
}