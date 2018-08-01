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
				//Create and insert new tile into vector
				Tile* newTile = new Tile();		//IMPORTANT!!! This must be created on the heap, NOT the stack!!!

				//Randomize tiles + determine other parameters
				switch (pkr::Random(0, 1)) 
				{
				case 0:	//Floor
					newTile->tex = TM->getTexture("Floor");
					newTile->depthSortOffset = { -(newTile->tex->getWidth() / 2.0f), -130 };		//Set this later
					newTile->type = eTileType::ACCESSIBLE;
					break;
				case 1:	//Slab
					newTile->tex = TM->getTexture("Slab");
					newTile->depthSortOffset = { -(newTile->tex->getWidth()/2.0f), -190 };		//Set this later
					newTile->type = eTileType::ACCESSIBLE;
					break;
				default:
					assert(false);		//Something went wrong!
				}

				//Determine position of new tile
				newTile->cPos = m_mapOffset + pkr::Vector2(float(col * CART_TILE_HEIGHT), float(row * CART_TILE_WIDTH));

				//Insert tile into ground layer
				m_groundLayer.push_back(newTile);
			}
		}

		//// Main layer ////
		for (int row = 0; row < depth; ++row) 
		{
			for (int col = 0; col < width; ++col) 
			{
				//Init temps
				eTileType		Ttype;
				aie::Texture*	Ttex = nullptr;
				pkr::Vector2	TtexOffset;
				pkr::Vector2	Tpos;

				//Create and insert new tile into vector
				Tile* newTile = new Tile();		//IMPORTANT!!! This must be created on the heap, NOT the stack!!!

				//Determine position of new tile
				Tpos = m_mapOffset + pkr::Vector2(float(col * CART_TILE_HEIGHT), float(row * CART_TILE_WIDTH));

				//Randomize tiles + determine other parameters
				switch (pkr::Random(0, 25))			//Some kept blank
				{		
				case 2: //HugeBlock
					newTile = new Tile(Tpos,
						TM->getTexture("HugeBlock"),
						pkr::Vector2(10.0f, 10.0f),		//Raw
						eTileType::INACCESSIBLE);
					break;
				case 3: //Column
					newTile = new Tile(Tpos,
						TM->getTexture("Column"),
						pkr::Vector2(5.0f, 5.0f),		//Raw
						eTileType::INACCESSIBLE);
					break;
				case 4:	//ColumnBlocks
					newTile = new Tile(Tpos,
						TM->getTexture("ColumnBlocks"),
						pkr::Vector2(2.5f, 2.5f),		//Raw
						eTileType::INACCESSIBLE);
					break;
				case 5:	//SmallBlock
					newTile = new Tile(Tpos,
						TM->getTexture("SmallBlock"),
						pkr::Vector2(7.5f, 7.5f),		//Raw
						eTileType::INACCESSIBLE);
					break;
				case 6:	//LargeBlock
					newTile = new Tile(Tpos,
						TM->getTexture("LargeBlock"),
						pkr::Vector2(0.f, 0.0f),		//Raw
						eTileType::INACCESSIBLE);
					break;
				//default:
				//	//do nothing
				}

				//Insert tile into layer only if it is valid
				if (newTile->tex != nullptr)
					m_mainLayer.push_back(newTile);
				else
					delete newTile;		//FRAGMENTATION! BAD CODE!!!
			}
		}

	}

	void Map::draw(aie::Renderer2D * renderer)
	{
		auto app = KunoApp::Instance();

		//Draw the bottom ground layerr
		for (auto &t : m_groundLayer) 
		{
			//Convert cartesian to isometric
			t->iPos = app->CoordConverter()->CartesianToIsometric(t->cPos);

			//Calculate render depth
			auto depth = app->DepthSorter()->getSortDepth(t->iPos.y);

			//Draw tile
			//if (t->onMouseOver())
			//	renderer->setRenderColour(0.6f, 0.6f, 0.6f);
			//else
				renderer->setRenderColour(1, 1, 1);
			//renderer->drawSprite(t->tex, t->iPos.x + t->depthSortOffset.x, t->iPos.y + t->depthSortOffset.y, 0, 0, 0, depth, 0,0);
				t->draw(renderer);

			//// DEBUG ////
			renderer->setRenderColour(0, 0, 0);
			auto fPos = t->iPos;		//Final position
			renderer->drawBox(fPos.x, fPos.y, 5, 5, 0, 0);
			///////////////
		}

		for (auto t : m_mainLayer) {
			//Convert cartesian to isometric
			t->iPos = app->CoordConverter()->CartesianToIsometric(t->cPos);

			//Calculate render depth
			auto depth = app->DepthSorter()->getSortDepth(t->iPos.y);

			//Draw tile
			//if (t->onMouseOver())
			//	renderer->setRenderColour(0.6f, 0.6f, 0.6f);
			//else
				renderer->setRenderColour(1, 1, 1);
			//renderer->drawSprite(t->tex, t->iPos.x + t->depthSortOffset.x, t->iPos.y + t->depthSortOffset.y, 0, 0, 0, depth, 0, 0);
			t->draw(renderer);
		}

		//Draw static objects
		for (auto obj : m_objectLayer) {

		}
	}
}