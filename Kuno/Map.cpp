//////////////////
//// Tony Le ////
// 2 Aug 2018 //
///////////////


#include "Map.h"
#include <Texture.h>
#include <imgui.h>
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

	Map::Map(int mapWidth, int mapDepth) :
		m_width(mapWidth),
		m_depth(mapDepth)
	{
		buildRandomMap(m_width, m_depth);
	}

	void Map::buildRandomMap(int width, int depth)
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
				newTile->pos = pkr::Vector2(static_cast<float>(col * CART_TILE_HEIGHT), static_cast<float>(row * CART_TILE_WIDTH));

				//// Set the base //// (The ground/floor)
				switch (pkr::Random(0, 5))
				{
				case 0:	//Floor
					newTile->tex = TM->getTexture("Floor");
					newTile->dsOffset = pkr::Vector2(0, 75.0f);
					newTile->terrain = SMOOTH_FLOOR;
					newTile->access = TRAVERSABLE;
					break;					
				case 1:	//Grass
					newTile->tex = TM->getTexture("Floor");
					newTile->dsOffset = pkr::Vector2(0, 75.0f);
					newTile->terrain = GRASS;
					newTile->access = TRAVERSABLE;
					break;
				case 2:	//DIRT
					newTile->tex = TM->getTexture("Floor");
					newTile->dsOffset = pkr::Vector2(0, 75.0f);
					newTile->terrain = DIRT;
					newTile->access = TRAVERSABLE;
					break;
				case 3:	//GRAVEL
					newTile->tex = TM->getTexture("Floor");
					newTile->dsOffset = pkr::Vector2(0, 75.0f);
					newTile->terrain = GRAVEL;
					newTile->access = TRAVERSABLE;
					break;
				case 4:	//WATER
					newTile->tex = TM->getTexture("Floor");
					newTile->dsOffset = pkr::Vector2(0, 75.0f);
					newTile->terrain = WATER;
					newTile->access = TRAVERSABLE;
					break;
				case 5:	//Slab
					newTile->tex = TM->getTexture("Slab");
					newTile->dsOffset = pkr::Vector2(0, 75.0f);
					newTile->terrain = SMOOTH_FLOOR;
					newTile->access = TRAVERSABLE;
					break;

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
						newObject->pos = newTile->pos;
						newObject->dsOffset = pkr::Vector2(0, 75.0f);
						newTile->objects.push_back(newObject);				//Add onto the tile
						break;
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
						//ELSE don't add any objects
					}
				}
				//Insert new tile into tile container
				m_tiles.push_back(newTile);

			}	//Cols
		}	//Rows

	}


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


	Tile * Map::findTileFromPos(const pkr::Vector2 & cPos, float searchRadius)
	{
		for (auto t : m_tiles) {
			//Return tile that is within range of search position
			if (pkr::Vector2::distance(t->pos, cPos) < searchRadius)
				return t;
		}
		return nullptr;		//Tile not found; return null
	}

	Tile * Map::findTileFromCanvasPos(const pkr::Vector2 & iPos, float searchRadius)
	{
		for (auto t : m_tiles) {
			//Return tile that is within range of search position
			if (pkr::Vector2::distance(t->cPos, iPos) < searchRadius)
				return t;
		}
		return nullptr;		//Tile not found; return null
	}

	Path Map::getDjikstraPath(Tile * startTile, Tile * endTile) const
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
		startTile->parent = nullptr;		//This will act as the root; will be used when tracing back
		startTile->G = 0;				//0 because there's no traversal yet
		openList.push_back(startTile);

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

			if (currentTile == endTile) break;			//Goal node found so break out

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
		auto workTile = endTile;
		while (workTile != nullptr) {
			DjikstraSolution.push_back(workTile->pos);
			workTile = static_cast<Tile*>(workTile->parent);
		}
		return DjikstraSolution;
	}

	Path Map::getAStarPath(Tile * startNode, Tile * endNode) const
	{
		//Inits
		Node*		currentNode;
		NodeList	openList;
		NodeList	closedList;

		//Set all parents to null and G scores to infinity
		for (auto t : m_tiles ) {
			t->parent = nullptr;
			t->G = INFINITY;
			t->F = INFINITY;
		}

		//Clear and push start node onto open list
		startNode->parent = nullptr;		//This will act as the root; will be used when tracing back
		startNode->G = 0;				//0 because there's no traversal yet
		openList.push_back(startNode);

		//Slight optimization; Stop once you get to the node you're looking for
		//Downside: Might not always find the shortest parth
		//for (auto it = openList.begin(); it != openList.end(); it++) {
		//	if (currentNode == *it) {
		//		endNode = node;
		//		break;
		//	}
		//}

		//While queue is not empty
		while (!openList.empty())
		{
			//Sort open list based on the F score
			openList.sort(pf::Node::compareFscore);		//Sort takes in a function object

			currentNode = openList.front();				//Get current work node of the end of the queue
			openList.pop_front();						//Remove node from the queue
			closedList.push_back(currentNode);			//Current node is now traversed (mark it as traversed)

			if (currentNode == endNode) break;			//Goal node found so break out

			for (auto c : currentNode->connections) {		//[Loop through it's edges]
				
				if (c == nullptr) continue;			//What's the purpose of this?

				//Determine if this tile is in any of the lists
				bool inClosedList = std::find(closedList.begin(), closedList.end(), c->target) != closedList.end();
				bool inOpenedList = std::find(openList.begin(), openList.end(), c->target) != openList.end();

				//Calculate G score
				float gScore = currentNode->G + c->cost;
				float hScore = pkr::Vector2::distance(currentNode->pos, endNode->pos);
				float fScore = gScore + hScore;

				if (!inClosedList) {	//inClosedList == false; Not already traversed, set score
					c->target->G = gScore;
					c->target->H = hScore;
					c->target->F = fScore;
					c->target->parent = currentNode;
				}
				else {					//inClosedList == true; Already traversed, check if we now have a lower score
					if (gScore < c->target->G) {
						c->target->G = gScore;
						c->target->H = hScore;
						c->target->F = fScore;
						c->target->parent = currentNode;
					}
				}

				if (!inOpenedList && !inClosedList) {	//If not in any lists (ie. first run), ad to priority queue
					//Probably a fail safe
					openList.push_back(static_cast<Tile*>(c->target));		//Node* -> Tile*
				}
			}
		}

		//Return the solution
		Path AstarSolution;
		auto workNode = endNode;
		while (workNode != nullptr) {
			AstarSolution.insert(AstarSolution.begin(), workNode->pos);		//Push to the front instead; FollowAgent() starts from the rear
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

		//// DEBUG //// 
		//Swap between pathing algorithms
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
			ImGui::Begin("Path connections");
			if (m_drawConnections) 
			{
				int index = 0;
				for (auto c : t->connections) 
				{	{
						//Canvas coords
						pkr::Vector2 start = t->cPos;
						pkr::Vector2 end = c->target->cPos;
						//Set line color based on terrain cost
						if (c->cost == 0.5f) {
							renderer->setRenderColour(0, 0, 0);
						}
						else if (c->cost == 1.0f) {
							renderer->setRenderColour(0, 0.60f, 0);
						}
						else if (c->cost == 1.3f) {
							renderer->setRenderColour(0.7f, 0.35f, 0.1f);
						}
						else if (c->cost == 2.0f) {
							renderer->setRenderColour(0.65f, 0.65f, 0.65f);
						}
						else if (c->cost == 5.0f) {
							renderer->setRenderColour(0.2f, 0.4f, 1.0f);
						}
						renderer->drawLine(start.x, start.y, end.x, end.y, 2.f, 0.2f);

						//World coords
						start = t->pos;
						end = c->target->pos;

						//Print debugs
						ImGui::Text("Edge: %d, x1: %.1f, y1: %.1f, x2: %.1f, y2: %.1f", index, start.x, start.y, end.x, end.y);
				} ++index; 	}
			}
			ImGui::End();

		}
		//Draw the test map A* pathfinding
		ImGui::Begin("Map's Path");
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
		////////////
		//// DEBUG ///
		ImGui::Begin("Pathfinding Method");
		ImGui::Text("Press space bar to toggle between methods");
		const char* buttonText;
		if (m_useAstar) buttonText = "A* Search";
		else buttonText = "Dijkstra Search";
		if (ImGui::Button(buttonText))
			m_useAstar = !m_useAstar;
		ImGui::End();
#endif
	}
}