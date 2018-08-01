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
		for (int row = 0; row < depth; ++row) 
		{
			for (int col = 0; col < width; ++col) 
			{
				//Init temps
				eTileAccess		Ttype;
				aie::Texture*	Ttex = nullptr;
				pkr::Vector2	TtexOffset;
				pkr::Vector2	Tpos;

				//Create and insert new tile into vector
				Tile* newTile = new Tile();		//IMPORTANT!!! This must be created on the heap, NOT the stack!!!

				//Determine position of new tile
				Tpos = m_mapOffset + pkr::Vector2(float(col * CART_TILE_HEIGHT), float(row * CART_TILE_WIDTH));

				//Randomize tiles + determine other parameters
				switch (pkr::Random(0, 0))		//0-9: Floor tiles, 10-20: Main tiles
				{
					//Floor
				case 0:
					newTile = new Tile(Tpos,
						TM->getTexture("Floor"),
						pkr::Vector2(0.0f, -75.0f),
						eTileTerrain::SMOOTH_FLOOR);
					break;

					//Slab
				case 1:
					newTile = new Tile(Tpos,
						TM->getTexture("Slab"),
						pkr::Vector2(0.0f, -95.0f),
						eTileTerrain::SMOOTH_FLOOR);
					break;
				default:
					assert(false);		//Something went wrong!
				}

				//Insert tile into layer only if it is valid
				if (newTile->tex != nullptr)
					m_groundLayer.push_back(newTile);
				else
					delete newTile;		//FRAGMENTATION! BAD CODE!!!
			}
		}

		//// Main layer ////
		for (int row = 0; row < depth; ++row) 
		{
			for (int col = 0; col < width; ++col) 
			{
				//Init temps
				eTileAccess		Ttype;
				aie::Texture*	Ttex = nullptr;
				pkr::Vector2	TtexOffset;
				pkr::Vector2	Tpos;

				//Create and insert new tile into vector
				Tile* newTile = new Tile();		//IMPORTANT!!! This must be created on the heap, NOT the stack!!!

				//Determine position of new tile
				Tpos = m_mapOffset + pkr::Vector2(float(col * CART_TILE_HEIGHT), float(row * CART_TILE_WIDTH));

				//Randomize tiles + determine other parameters
				switch (pkr::Random(0, 14))		//0-9: Floor tiles, 10-20: Main tiles
				{		
				case 10: //HugeBlock
					newTile = new Tile(Tpos,
						TM->getTexture("HugeBlock"),
						pkr::Vector2(0.0f, -75.0f),
						eTileTerrain::GRASS,	//cost = 1.0f
						eTileAccess::INACCESSIBLE);
					break;
				case 11: //Column
					newTile = new Tile(Tpos,
						TM->getTexture("Column"),
						pkr::Vector2(0.0f, -19.0f),
						eTileTerrain::GRASS,	//cost = 1.0f
						eTileAccess::INACCESSIBLE);
					break;
				case 12:	//ColumnBlocks
					newTile = new Tile(Tpos,
						TM->getTexture("ColumnBlocks"),
						pkr::Vector2(0.0f, -19.0f),
						eTileTerrain::GRASS,	//cost = 1.0f
						eTileAccess::INACCESSIBLE);
					break;
				case 13:	//SmallBlock
					newTile = new Tile(Tpos,
						TM->getTexture("SmallBlock"),
						pkr::Vector2(0.0f, -19.0f),
						eTileTerrain::GRASS,	//cost = 1.0f
						eTileAccess::INACCESSIBLE);
					break;
				case 14:	//LargeBlock
					newTile = new Tile(Tpos,
						TM->getTexture("LargeBlock"),
						pkr::Vector2(0.0f, -39.0f),
						eTileTerrain::GRASS,	//cost = 1.0f
						eTileAccess::INACCESSIBLE);
					break;
				}

				//Insert tile into layer only if it is valid
				if (newTile->tex != nullptr)
					m_mainLayer.push_back(newTile);
				else
					delete newTile;		//FRAGMENTATION! BAD CODE!!!
			}
		}

	}

	void Map::connectNodesByDistance(float connectRadius)
	{
		for (auto tileA : m_groundLayer) {
			for (auto tileB : m_groundLayer) {
				//Skip if they're both the same node
				if (tileA == tileB) continue;

				//Skip if tileB is not ACCESSIBLE
				if (tileB->access == eTileAccess::INACCESSIBLE) continue;

				//Find the distance between the two tiles
				float distance = tileA->cPos.distance(tileB->cPos);

				//If they're within range then connect
				if (distance < connectRadius) {
					//Set the traversal cost based on the terrain
					//auto terrainCost = tileB->terrain;
					float cost = 1.0f;
					switch (tileB->terrain) {
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

			//Draw tile
			if (t->onMouseOver())
				renderer->setRenderColour(0.6f, 0.6f, 0.6f);
			else
				renderer->setRenderColour(1, 1, 1);
			//renderer->drawSprite(t->tex, t->iPos.x + t->depthSortOffset.x, t->iPos.y + t->depthSortOffset.y, 0, 0, 0, depth, 0,0);
			t->draw(renderer);

			//// DEBUG ////
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

			//Draw tile
			if (t->onMouseOver())
				renderer->setRenderColour(0.6f, 0.6f, 0.6f);
			else
				renderer->setRenderColour(1, 1, 1);
			//renderer->drawSprite(t->tex, t->iPos.x + t->depthSortOffset.x, t->iPos.y + t->depthSortOffset.y, 0, 0, 0, depth, 0, 0);
			t->draw(renderer);

			//// DEBUG ////
			//Draw the cPos of the tile (should be the tile's isometric centre)
			renderer->setRenderColour(0, 0, 0);
			auto fPos = t->iPos;		//Final position
			renderer->drawBox(fPos.x, fPos.y, 3, 3, 0, 0);

			//Draw the depth sort offset of the tile (!!! MIGHT NOT NEED THIS IF I BUILD AN ADVANCE DEPTH SORTING ALGORITHM)
			renderer->setRenderColour(0, 0, 1);
			renderer->drawBox(t->iPos.x + t->dsOffset.x, t->iPos.y + t->dsOffset.y, 3, 3, 0, 0);
			///////////////
		}

		//Draw static objects
		for (auto obj : m_objectLayer) {

		}
	}
}