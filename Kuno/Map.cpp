//////////////////
//// Tony Le ////
// 2 Aug 2018 //
///////////////


#include "Map.h"
#include <Texture.h>
#include <imgui.h>
#include "GameDefines.h"
#include "Tile.h"
#include <pkr\math\Vector2.h>
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

	Map::Map(int mapWidth, int mapDepth) :
		m_width(mapWidth),
		m_depth(mapDepth)
	{
		//buildRandomMap(m_width, m_depth);
		buildKunoMap();
	}

	void Map::buildKunoMap()
	{

		//MAP DATA ARRAY
		const short width = 20;
		const short depth = 20;

		//This must be done otherwise they'll be out of range errors
		m_width = width;
		m_depth = depth;

		short mapData[width][depth] =
		{
			{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
			{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
			{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
			{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
			{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
			{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
			{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
			{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
			{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
			{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
			{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1 },
			{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 4, 1, 1, 0, 1 },
			{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 4, 1, 1, 0, 1 },
			{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 5, 6, 6, 4, 4, 1, 1, 0, 1 },
			{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 5, 6, 1, 1, 1, 1, 1, 0, 1 },
			{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 5, 1, 1, 1, 1, 1, 1, 0, 1 },
			{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 5, 1, 1, 1, 1, 1, 1, 0, 1 },
			{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1 },
			{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		};
		//	{ 5, 1, 0, 0, 6, 5, 1, 0, 1, 5, 1, 1 },
		//	{ 5, 1, 0, 0, 6, 5, 1, 0, 1, 5, 1, 1 },
		//	{ 5, 1, 0, 0, 0, 0, 0, 0, 1, 5, 1, 1 },
		//	{ 5, 1, 0, 0, 6, 5, 1, 1, 1, 5, 1, 1 },
		//	{ 5, 5, 0, 0, 6, 5, 5, 5, 5, 5, 1, 1 },
		//	{ 1, 5, 0, 0, 5, 5, 1, 1, 1, 1, 1, 1 },
		//	{ 1, 5, 0, 0, 5, 1, 1, 1, 1, 1, 2, 2 },
		//	{ 6, 5, 0, 0, 5, 1, 1, 1, 1, 2, 2, 2 },
		//	{ 6, 6, 0, 0, 1, 1, 1, 2, 2, 3, 3, 3 },
		//	{ 6, 1, 0, 0, 1, 1, 1, 2, 3, 3, 3, 4 },
		//	{ 1, 0, 0, 1, 1, 1, 2, 3, 3, 3, 4, 4 },
		//	{ 0, 0, 1, 1, 1, 1, 2, 3, 3, 4, 4, 4 }
		//};

		//Call texture manager
		auto tm = KunoApp::Instance()->TextureManager();

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
				//StaticObject * newObject = new StaticObject();		//Used to set tile untraversable

				//// Position tile ////
				newTile->ID = ID;
				newTile->pos = pkr::Vector2(static_cast<float>(col * CART_TILE_HEIGHT), static_cast<float>(row * CART_TILE_WIDTH));

				switch (mapData[row][col])
				{
				case 0:	//PATH
					newTile->tex = tm->getTexture("Path");
					newTile->dsOffset = pkr::Vector2(0, 58.0f);
					newTile->terrain = PATH;
					newTile->access = TRAVERSABLE;
					break;
				case 1:	//GRASS
					newTile->tex = tm->getTexture("Grass");
					newTile->dsOffset = pkr::Vector2(0, 58.0f);
					newTile->terrain = GRASS;
					newTile->access = TRAVERSABLE;
					break;
				case 3: //DIRT
					newTile->tex = tm->getTexture("Dirt");
					newTile->dsOffset = pkr::Vector2(0, 58.0f);
					newTile->terrain = DIRT;
					newTile->access = TRAVERSABLE;
					break;
				case 4:	//SAND
					newTile->tex = tm->getTexture("Sand");
					newTile->dsOffset = pkr::Vector2(0, 58.0f);
					newTile->terrain = SAND;
					newTile->access = TRAVERSABLE;
					break;
				case 5:	//WATER
					newTile->tex = tm->getTexture("Water");
					newTile->dsOffset = pkr::Vector2(0, 58.0f);
					newTile->terrain = WATER;
					newTile->access = TRAVERSABLE;
					break;
				case 6:	//DEEPWATER
					newTile->objects.push_back(new StaticObject());		//An empty static object makes this tile untraversable
					newTile->tex = tm->getTexture("DeepWater");
					newTile->dsOffset = pkr::Vector2(0, 58.0f);
					newTile->terrain = WATER;
					newTile->access = UNTRAVERSABLE;
					break;
				case 7:	//WALL
					newTile->objects.push_back(new StaticObject());		//An empty static object makes this tile untraversable
					newTile->tex = tm->getTexture("Wall");
					newTile->dsOffset = pkr::Vector2(0, 35.0f);
					newTile->terrain = NA;
					newTile->access = UNTRAVERSABLE;
					break;

				default:
					assert(false);		//Something went wrong!
				}

				//Insert new tile into tile container
				m_tiles.push_back(newTile);

			}	//Cols
		}	//Rows
	}

	/*
	void Map::buildRandomMap(int width, int depth)
	{
		m_width = width;
		m_depth = depth;

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
				newTile->pos = pkr::Vector2(static_cast<float>(col * CART_TILE_HEIGHT), static_cast<float>(row * CART_TILE_WIDTH));

				//// Set the base //// (The ground/floor)
				switch (pkr::Random(0, TILE_TERRAIN_COUNT))
				{
				case 0:
					newTile->tex = TM->getTexture("Floor");		//Parsing by string is slow but this only happens once each tile
					newTile->dsOffset = pkr::Vector2(0, 58.0f);
					newTile->terrain = SMOOTH_FLOOR;
					newTile->access = TRAVERSABLE;
					break;
				case 1:
					newTile->tex = TM->getTexture("FloorGrassRound");
					newTile->dsOffset = pkr::Vector2(0, 58.0f);
					newTile->terrain = GRASS;
					newTile->access = TRAVERSABLE;
					break;
				case 2:
					newTile->tex = TM->getTexture("Slab");
					newTile->dsOffset = pkr::Vector2(0, 58.0f);
					newTile->terrain = DIRT;
					newTile->access = TRAVERSABLE;
					break;
				case 3:
					newTile->tex = TM->getTexture("SmallBlock");
					newTile->dsOffset = pkr::Vector2(0, 58.0f);
					newTile->terrain = WATER;
					newTile->access = TRAVERSABLE;
					break;
				case 4:	
					newTile->tex = TM->getTexture("LargeBlock");
					newTile->dsOffset = pkr::Vector2(0, 58.0f);
					newTile->terrain = WATER;
					newTile->access = TRAVERSABLE;
					break;
				case 5:	
					newTile->tex = TM->getTexture("HugeBlock");
					newTile->dsOffset = pkr::Vector2(0, 58.0f);
					newTile->terrain = eTileTerrain::NA;
					newTile->access = eTileTraversable::UNTRAVERSABLE;
					break;

				default:
					assert(false);		//Something bad happened!
				}

				//// Add any objects that may be on this tile ////
				//int random = pkr::Random(4, 20);
				int random = NULL;
				if (random <= 5) //Object will definitely be created
				{
					StaticObject* newObject = new StaticObject();		//Create empty object and set properties below
					switch (random)
					{
					case 1: //Column
						newObject->tex = TM->getTexture("Column");
						newObject->pos = newTile->pos;
						newObject->dsOffset = pkr::Vector2(0, 19.f);
						newTile->objects.push_back(newObject);				//Add onto the tile
						break;
					case 2:	//ColumnBlocks
						newObject->tex = TM->getTexture("ColumnBlocks");
						newObject->pos = newTile->pos;
						newObject->dsOffset = pkr::Vector2(0, 19.f);
						newTile->objects.push_back(newObject);				//Add onto the tile
						break;
					case 3:	//SmallBlock
						newObject->tex = TM->getTexture("SmallBlock");
						newObject->pos = newTile->pos;
						newObject->dsOffset = pkr::Vector2(0, 19.f);
						newTile->objects.push_back(newObject);				//Add onto the tile
						break;
					case 4:	//LargeBlock
						newObject->tex = TM->getTexture("LargeBlock");
						newObject->pos = newTile->pos;
						newObject->dsOffset = pkr::Vector2(0, 39.f);
						newTile->objects.push_back(newObject);				//Add onto the tile
						break;
					case 5: //HugeBlock
						newObject->tex = TM->getTexture("HugeBlock");
						newObject->pos = newTile->pos;
						newObject->dsOffset = pkr::Vector2(0, 75.0f);
						newTile->objects.push_back(newObject);				//Add onto the tile
						break;
						//ELSE don't add any objects
					}
				}
				//Insert new tile into tile container
				m_tiles.push_back(newTile);

			}	//Cols
		}	//Rows

	}
	*/

	void Map::connectNodesByDistance(float connectRadius)
	{
		//Connect up nodes wi
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
				float distanceBetween = t1->pos.distance(t2->pos);

				//If they're within range then connect taking into account terrain
				if (distanceBetween < connectRadius) {

					//THIS SETS THE EDGE COST (ie. HOW DIFFICULT IT IS TO TRAVERSE ACROSS THESE TERRAINS)
					float cost = 1.0f;
					switch (t2->terrain) {
					case NA:			cost = INFINITY;	break;
					case PATH:			cost = 0.8f;		break;
					case GRASS:			cost = 1.0f;		break;
					case DIRT:			cost = 1.3f;		break;
					case SAND:			cost = 2.0f;		break;
					case GRAVEL:		cost = 3.0f;		break;
					case WATER:			cost = 4.0f;		break;
					case DEEPWATER:		cost = 5.0f;		break;
					default:
						assert(false);		//Invalid
					}

					//// FINALLY CONNECT THE TILES UP ////
					pf::Node::connect(t1, t2, cost);	//!!!This should also connect tiles both ways
				}

			}
		}

	}

	Tile * Map::findTileFromPos(const pkr::Vector2 & pos)
	{
		//Just return the closest tile (use distancesquare for efficiency)
		if (!m_tiles.empty()) {
			//Go through all tiles and find the closest one
			Tile* closestTile; float closestDist = INFINITY; float distance;
			for (auto t : m_tiles) {
				//Get the distance
				distance = pkr::Vector2::distanceSqr(t->pos, pos);

				//if the distance is lower than current distance then save dist and Tile*
				if (distance < closestDist) {
					closestDist = distance;
					closestTile = t;
				}
			}
			return closestTile;		//This should be the tile closest to input position
		}
		return nullptr;		//Failsafe: return null if no tiles are available
	}


	Tile * Map::findTileFromCanvasPos(const pkr::Vector2 & cPos)
	{
		//Just return the closest tile (use distancesquare for efficiency)
		if (!m_tiles.empty()) {
			//Go through all tiles and find the closest one
			Tile* closestTile; float closestDist = INFINITY; float distance;
			for (auto t : m_tiles) {
				//Get the distance
				distance = pkr::Vector2::distanceSqr(t->cPos, cPos);

				//if the distance is lower than current distance then save dist and Tile*
				if (distance < closestDist) {
					closestDist = distance;
					closestTile = t;
				}
			}
			return closestTile;		//This should be the tile closest to input position

		}
		return nullptr;		//Failsafe: return null if no tiles are available
	}

	pkr::Vector2 Map::clampWithinMapRetWORLD(const pkr::Vector2 & pos)
	{
		auto clamped = pos;

		//// Simple clamp ////
		clamped.x = pkr::Clamp(clamped.x, 0.0f, static_cast<float>(CART_TILE_WIDTH * (m_width - 1)));		//BUGGY
		clamped.y = pkr::Clamp(clamped.y, 0.0f, static_cast<float>(CART_TILE_HEIGHT * (m_depth - 1)));	//BUGGY		

		return clamped;
	}

	Tile * Map::clampwithinMapRetTILE(const pkr::Vector2 & Wpos)
	{
		auto clamped = clampWithinMapRetWORLD(Wpos);
		auto clampedTile = findTileFromPos(clamped);
		return clampedTile;
	}

	Path Map::getDjikstraPath(Tile * start, Tile * end) const
	{
		//Inits
		Node*		currentTile;
		NodeList	openList;
		NodeList	closedList;

		//Set all parents to null and G scores to infinity
		for (auto t : m_tiles) {
			t->parent = nullptr;
			t->G = INFINITY;
		}

		//Clear and push start node onto open list
		end->parent = nullptr;		//This will act as the root; will be used when tracing back
		end->G = 0;				//0 because there's no traversal yet
		openList.push_back(end);

		//Slight optimization; Stop once you get to the node you're looking for
		//Downside: Might not always find the shortest parth
		//for (auto o : openList) {
		//	if (currentTile == o) {	//Not sure if this is right
		//		endTile = static_cast<Tile*>(currentTile);
		//	}
		//}

		//While queue is not empty
		while (!openList.empty())
		{
			//Sort open list based on the F score
			openList.sort(pf::Node::compareGscore);		//Sort takes in a function object

			currentTile = openList.front();				//Get current work node of the end of the queue
			openList.pop_front();						//Remove node from the queue
			closedList.push_back(currentTile);			//Current node is now traversed (mark it as traversed)

			if (currentTile == start) break;			//Goal node found so break out

			for (auto c : currentTile->connections) {		//[Loop through it's edges]

				if (c == nullptr) continue;			//What's the purpose of this?

													//Determine if this tile is in any of the lists
				bool inClosedList = std::find(closedList.begin(), closedList.end(), c->target) != closedList.end();
				bool inOpenedList = std::find(openList.begin(), openList.end(), c->target) != openList.end();

				//Calculate G score
				float gScore = currentTile->G + c->cost;

				if (!inClosedList) {	//inClosedList == false
										//Not already traversed, set score
					c->target->G = gScore;
					c->target->parent = currentTile;
				}
				else {	//inClosedList == true
					//Already traversed, check if we now have a lower score
					if (gScore < c->target->G) {
						c->target->G = gScore;
						c->target->parent = currentTile;
					}
				}

				if (!inOpenedList && !inClosedList) {
					//Probably a fail safe
					//If not in any lists (ie. first run), ad to priority queue
					openList.push_back(static_cast<Tile*>(c->target));		//Node* -> Tile*
				}
			}
		}

		//Return the solution
		Path DjikstraSolution;
		auto workTile = start;
		while (workTile != nullptr) {
			DjikstraSolution.push_back(workTile->pos);
			workTile = static_cast<Tile*>(workTile->parent);
		}
		return DjikstraSolution;
	}

	Path Map::getAStarPath(Tile * start, Tile * end) const
	{
		//Failsafes; Return if the input tiles are invalid
		if (start == nullptr) return pf::Path();
		if (end == nullptr) return pf::Path();

		//Inits
		Node*		currentNode;
		NodeList	openList;
		NodeList	closedList;

		//Set all parents to null and G scores to infinity
		for (auto t : m_tiles) {
			t->parent = nullptr;
			t->G = INFINITY;
			t->F = INFINITY;
		}

		//Clear and push start node onto open list
		end->parent = nullptr;		//This will act as the root; will be used when tracing back
		end->G = 0;				//0 because there's no traversal yet
		openList.push_back(end);

		//While queue is not empty
		while (!openList.empty())
		{
			//Sort open list based on the F score
			openList.sort(pf::Node::compareFscore);		//Sort takes in a function object

			//if (currentNode == start) break;			//Goal node found so break out

			currentNode = openList.front();				//Get current work node of the end of the queue
			openList.pop_front();						//Remove node from the queue
			closedList.push_back(currentNode);			//Current node is now traversed (mark it as traversed)

			for (auto neighbour : currentNode->connections) {		//[Loop through it's edges]

				if (neighbour == nullptr) continue;			//What's the purpose of this?

				//Determine if this tile is in any of the lists
				bool inClosedList = std::find(closedList.begin(), closedList.end(), neighbour->target) != closedList.end();
				bool inOpenedList = std::find(openList.begin(), openList.end(), neighbour->target) != openList.end();

				//Ignore the neighbour that is already evaluated
				if (inClosedList)
					continue;

				//The distance from start to a neighbour
				float tentativeGscore = currentNode->G + neighbour->cost;
				float hScore = pkr::Vector2::distance(neighbour->target->pos, start->pos);
				//float tentativeGscore = currentNode->G + pkr::Vector2::distance(currentNode->pos, neighbour->target->pos);

				//Discover a new node
				if (!inOpenedList) {
					openList.push_back(neighbour->target);
				}
				else if (tentativeGscore >= neighbour->target->G) {
					continue;		//This is not a better path
				}

				//This is the best path until now. Record it!
				neighbour->target->parent = currentNode;
				neighbour->target->G = tentativeGscore;
				neighbour->target->F = neighbour->target->G + hScore;
			}
		}

		//Return the solution
		Path AstarSolution;
		auto workNode = start;
		while (workNode != nullptr) {
			AstarSolution.push_back(workNode->pos);
			//AstarSolution.insert(AstarSolution.begin(), workNode->pos);		//If path needs to be reversed
			workNode = static_cast<Tile*>(workNode->parent);
		}
		return AstarSolution;
	}

	void Map::update(float deltaTime)
	{
		auto CoordConverter = KunoApp::Instance()->CoordConverter();
		aie::Input* input = aie::Input::getInstance();

		//// Get Tile that is being mouse over on ////
		auto mView = pkr::Vector2((float)input->getMouseX(), (float)input->getMouseY());
		auto mCanvas = CoordConverter->ViewportToCanvas(mView);
		m_tileMouseOver = findTileFromCanvasPos(mCanvas);		//UPDATE! Totally know why it works... NOTE SURE WHY THIS WORKS

		//// Get Start of path (left click) ////
		if (input->wasMouseButtonPressed(aie::INPUT_MOUSE_BUTTON_LEFT))
			if (m_tileMouseOver != nullptr && m_tileMouseOver != m_pathEnd)	//The mouse is actually over a tile
				m_pathStart = m_tileMouseOver;
			else
				m_pathStart = nullptr;

		//// Get End of path (right click) ////
		if (input->wasMouseButtonPressed(aie::INPUT_MOUSE_BUTTON_RIGHT))
			if (m_tileMouseOver != nullptr && m_tileMouseOver != m_pathStart)	//The mouse is actually over a tile
				m_pathEnd = m_tileMouseOver;
			else
				m_pathEnd = nullptr;

		//// If there are start and end nodes then try to A* ////
		if (m_pathStart != nullptr && m_pathEnd != nullptr) {
			if (m_useAstar)
				m_path = getAStarPath(m_pathStart, m_pathEnd);
			else
				m_path = getDjikstraPath(m_pathStart, m_pathEnd);
		}
		else {
			m_path.clear();
		}

		//// Swap between pathing algorithms ////
		if (input->wasKeyPressed(aie::INPUT_KEY_SPACE))
			m_useAstar = !m_useAstar;
		//Toggle connection draws
		if (input->wasKeyPressed(aie::INPUT_KEY_C))
			m_drawConnections = !m_drawConnections;
	}

	void Map::draw(aie::Renderer2D * renderer)
	{
		auto app = KunoApp::Instance();

		for (auto t : m_tiles)
		{
			//Convert cartesian to isometric, readying the sprite for drawing
			t->cPos = app->CoordConverter()->WorldToCanvas(t->pos);

			//Calculate render depth
			auto depth = app->DepthSorter()->getSortDepth(t->cPos.y);

			//Set tile colour
			if (t == m_tileMouseOver)		renderer->setRenderColour(0.75f, 0.75f, 0.75f);			//Mouse over
			else if (t == m_pathStart)		renderer->setRenderColour(0.35f, 0.7f, 0.35f);			//Start
			else if (t == m_pathEnd)		renderer->setRenderColour(0.7f, 0.35f, 0.35f);			//End
			//else if (t->terrain == GRASS)	renderer->setRenderColour(0, 0.6f, 0);
			//else if (t->terrain == DIRT)	renderer->setRenderColour(0.7f, 0.35f, 0.65f);
			//else if (t->terrain == GRAVEL)	renderer->setRenderColour(0.65f, 0.65f, 0.65f);
			//else if (t->terrain == WATER)	renderer->setRenderColour(0.2f, 0.4f, 1);
			else							renderer->setRenderColour(1, 1, 1);

			//Draw tile including any objects it has
			t->draw(renderer);

#ifdef _DEBUG
			//// DEBUG ////
			//Draw the paths; all the node/tile connections
			ImGui::Begin("Map's tile connections");
			if (m_drawConnections)
			{
				int index = 0;
				for (auto c : t->connections)
				{
					{
						//Canvas coords
						pkr::Vector2 start = t->cPos;
						pkr::Vector2 end = c->target->cPos;

						//Set line color based on terrain cost
						float maxCost = 4.0f;
						// (c->cost / maxCost)
						renderer->setRenderColour((c->cost / maxCost), 0, 0);
						renderer->drawLine(start.x, start.y, end.x, end.y, 2.f, 0.2f);

						//World coords
						start = t->pos;
						end = c->target->pos;

						//Print debugs
						ImGui::Text("Edge: %d, x1: %.1f, y1: %.1f, x2: %.1f, y2: %.1f", index, start.x, start.y, end.x, end.y);
					} ++index;
				}
			}
			ImGui::End();
#endif

		}

#ifdef _DEBUG
		//Draw the test map A* pathfinding
		ImGui::Begin("Map's path");

		//Toggle between pathfinding algorithms
		const char* pathalgorithm;
		pathalgorithm = (m_useAstar) ? "A* Search" : "Dijkstra Search";
		ImGui::TextColored({ 1,0.5f,0,1 }, pathalgorithm);	ImGui::SameLine; ImGui::Text("Press space to toggle");

		//Print path waypoints
		renderer->setRenderColour(0.90f, 0, 0);
		if (!m_path.empty()) {
			//Loop through all sets of waypoints and draw the path (isometrically)
			for (int i = 0; i < m_path.size() - 1; ++i) {
				auto start = app->CoordConverter()->WorldToCanvas(m_path[i]);
				auto end = app->CoordConverter()->WorldToCanvas(m_path[i + 1]);
				renderer->drawLine(start.x, start.y, end.x, end.y, 6.f, 0.3f);
				ImGui::Text("%d > x: %.2f, y: %.2f", i, start.x, start.y);
			}
		}
		ImGui::End();
#endif // _DEBUG
	}
}