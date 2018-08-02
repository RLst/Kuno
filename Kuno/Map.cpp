#include "Map.h"
#include <Texture.h>
#include "imgui/imgui.h"
#include "GameDefines.h"
#include "Tile.h"
#include <pkr/Vector2.h>
#include "StaticObject.h"

#include "KunoApp.h"

//Debug
#include <iostream>

namespace pf {
	Map::~Map()
	{
		//Tiles
		for (auto &t : m_tiles) {
			delete t;
			t = nullptr;
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

		/////////////////////
		//// NEW SYSTEM ////
		///////////////////

		//ONE LAYER FITS ALL!
		int ID = 0;			//Not sure if this is needed anymore
		for (int row = 0; row < depth; ++row)
		{
			for (int col = 0; col < width; ++col)
			{
				++ID;

				Tile* newTile = new Tile();

				//// Position tile ////
				//newTile->ID = ID;
				newTile->cPos = m_mapOffset + pkr::Vector2(static_cast<float>(col * CART_TILE_HEIGHT), static_cast<float>(row * CART_TILE_WIDTH));

				//// Set the base //// (The ground/floor)
				switch (pkr::Random(0, 0))
				{
				case 0:	//Floor
					newTile->tex = TM->getTexture("Floor");
					newTile->dsOffset = pkr::Vector2(0, 75.0f);
					newTile->terrain = SMOOTH_FLOOR;
					newTile->access = TRAVERSABLE;
					break;					
				case 1:	//Slab
					newTile->tex = TM->getTexture("Slab");
					newTile->dsOffset = pkr::Vector2(0, 75.0f);
					newTile->terrain = SMOOTH_FLOOR;
					newTile->access = TRAVERSABLE;
					break;
				case 2:	//Grass

				default:
					assert(false);		//Something went wrong!
				}

				//// Add any objects that may be on this tile ////
				int random = pkr::Random(0, 15);
				if (random < 4) //Object will definitely be created
				{
					StaticObject* newObject = new StaticObject();		//Create empty object and set properties below
					switch (random)
					{
					case 0: //HugeBlock
						newObject->tex = TM->getTexture("HugeBlock");
						newObject->cPos = newTile->cPos;
						newObject->dsOffset = pkr::Vector2(0, 75.0f);
						newTile->objects.push_back(newObject);				//Add onto the tile

						//newTile->objects.push_back(new StaticObject())
						//newTile->tex = TM->getTexture("HugeBlock");
						//newTile->dsOffset = pkr::Vector2(0, 75.0f);		//Isometric back bottom corner
						//newTile->terrain = GRASS;						//Cost = 1.0f
						//newTile->access = INACCESSIBLE;
						break;
					case 1: //Column
						newObject->tex = TM->getTexture("Column");
						newObject->cPos = newTile->cPos;
						newObject->dsOffset = pkr::Vector2(0, 19.f);
						newTile->objects.push_back(newObject);				//Add onto the tile
						break;
					case 2:	//ColumnBlocks
						newObject->tex = TM->getTexture("ColumnBlocks");
						newObject->cPos = newTile->cPos;
						newObject->dsOffset = pkr::Vector2(0, 19.f);
						newTile->objects.push_back(newObject);				//Add onto the tile
						break;
					case 3:	//SmallBlock
						newObject->tex = TM->getTexture("SmallBlock");
						newObject->cPos = newTile->cPos;
						newObject->dsOffset = pkr::Vector2(0, 19.f);
						newTile->objects.push_back(newObject);				//Add onto the tile
						break;
					case 4:	//LargeBlock
						newObject->tex = TM->getTexture("LargeBlock");
						newObject->cPos = newTile->cPos;
						newObject->dsOffset = pkr::Vector2(0, 39.f);
						newTile->objects.push_back(newObject);				//Add onto the tile
						break;
					default:
						assert(false);

						//ELSE don't add any objects
					}
				}
				//Insert new tile into tile container
				m_tiles.push_back(newTile);

			}	//Cols
		}	//Rows

	}

	/*
	void Map::buildTestMapOld(int width, int depth)
	{
		//Call texture manager
		auto TM = KunoApp::Instance()->TextureManager();

		///////////////////
		//// OLD CODE ////
		/////////////////

		//// Ground layer ////
		int ID = 0;		//Tile ID
		for (int row = 0; row < depth; ++row) 
		{
			for (int col = 0; col < width; ++col) 
			{
				++ID;
				//ID = m_groundLayer.size();

				//Create new tile
				Tile* newTile = new Tile();		//IMPORTANT!!! This must be created on the heap, NOT the stack!!!

				//Sets
				//newTile->ID = ID;
				newTile->cPos = m_mapOffset + pkr::Vector2(static_cast<float>(col * CART_TILE_HEIGHT), static_cast<float>(row * CART_TILE_WIDTH));

				//Randomize tiles and set other tile properties
				switch (pkr::Random(0, 1))
				{
					//Floor
				case 0:
					newTile->tex = TM->getTexture("Floor");
					newTile->dsOffset = pkr::Vector2(0, 75.0f);
					newTile->terrain = SMOOTH_FLOOR;
					newTile->access = TRAVERSABLE;
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
					newTile->access = TRAVERSABLE;
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
				++ID;	//shoudl be the same as ground layer size at the end; = m_mainLayer.size() + 1;
					
				auto randomize = pkr::Random(0, 15);	//Not all tiles will get filled
				if (randomize < 5) {	//Only create a tile where necessary to avoid fragmentation

					//Create new tile
					Tile* newTile = new Tile();		//IMPORTANT!!! This must be created on the heap, NOT the stack!!!

					//Sets
					//newTile->ID = ID;
					newTile->cPos = m_mapOffset + pkr::Vector2(static_cast<float>(col * CART_TILE_HEIGHT), static_cast<float>(row * CART_TILE_WIDTH));

					switch (randomize) {
					case 0: //HugeBlock
						newTile->tex = TM->getTexture("HugeBlock");
						newTile->dsOffset = pkr::Vector2(0, 75.0f);		//Isometric back bottom corner
						newTile->terrain = GRASS;						//Cost = 1.0f
						newTile->access = UNTRAVERSABLE;
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
		// DEBUG ////
		std::cout << "ID: " << ID << std::endl;
		std::cin.get();
	}
	*/

	void Map::connectNodesByDistance(float connectRadius)
	{

		for (auto t1 : m_tiles)
		{
			for (auto t2 : m_tiles)
			{
				//// Skip if they're both the same node ////
				if (t1 == t2) continue;

				//// Skip if the subject tile (t1) has an object on it ie: untraversable ////
				if (!t1->objects.empty()) continue;

				//// Skip if the target tile (t2) has an object on it ie: can't traverse to this tile ////
				if (!t2->objects.empty()) continue;

				//// Find the distance between the two tiles ////
				float distanceBetween = t1->cPos.distance(t2->cPos);

				//If they're within range then connect taking into account terrain
				if (distanceBetween < connectRadius) {
					//Set the edge cost based on the terrain
					float cost = 1.0f;
					switch (t2->terrain) {
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

					//// FINALLY CONNECT THE TILES UP ////
					pf::Node::connect(t1, t2, cost);	//This should also connect tiles both ways
				}

			}
		}

	}



	void Map::draw(aie::Renderer2D * renderer)
	{
		auto app = KunoApp::Instance();

		for (auto t : m_tiles) 
		{
			//Convert cartesian to isometric, readying the sprite for drawing
			t->iPos = app->CoordConverter()->CartesianToIsometric(t->cPos);

			//Calculate render depth
			auto depth = app->DepthSorter()->getSortDepth(t->iPos.y);

			//Set colour
			if (t->onMouseOver())	renderer->setRenderColour(0.3f, 0.3f, 0.3f);
			else	renderer->setRenderColour(1, 1, 1);

			//Draw tile including any objects it has
			t->draw(renderer);

			//// DEBUG ////
			//Draw the paths; all the node/tile connections
			static int temp = 0;
			ImGui::Begin("Draw edge");
			for (auto c : t->connections) {
				pkr::Vector2 start = t->iPos;
				pkr::Vector2 end = c->target->iPos;
				renderer->setRenderColour(0, 0, 0);
				renderer->drawLine(start.x, start.y, end.x, end.y, 2.f, 0.01f);
				ImGui::Text("Start > x: %.1f, y: %.1f", start.x, start.y);
				ImGui::Text("End > x: %.1f, y: %.1f", end.x, end.y);
			}
			ImGui::End();
		}

	}
}