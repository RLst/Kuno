#pragma once
#include <cassert>

//#define SCREEN_WIDTH 1280
//#define SCREEN_HEIGHT 720

#define WORLD_WIDTH			10		//Tiles along X axis
#define WORLD_DEPTH			10		//Tiles along Y axis

#define CART_TILE_WIDTH		128		//In this case, the tiles in this world (orthogonal)
#define CART_TILE_HEIGHT	128		//is 128x128

#define ISO_TILE_WIDTH		255		//px; Width of isometric tile; Must change according to assets
#define ISO_TILE_HEIGHT		148		//px; Height of isometric tile; Must change according to assets
const float TILE_RATIO = (float)ISO_TILE_WIDTH / (float)ISO_TILE_HEIGHT;	//Used for Iso<>Cart conversions

namespace pkr {

	int Random(int min, int max);		//int RNG

	template <typename T>
	T Clamp(const T& value, const T& min, const T& max)
	{
		if (value < min)
			return min;
		else if (value > max)
			return max;
		//Else it is already clamped OR the min/max values are invalid :P
		return value;
	}

}




//// RANDOM TRASH BIN ////


/*
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
*/

/*
void OLDCODE1()
{
//for (int indexA = 0; indexA < m_groundLayer.size(); ++indexA) {
//	for (int indexB = 0; indexB < m_groundLayer.size(); ++indexB) {
//		auto tileA = m_groundLayer[indexA];
//		auto tileB = m_groundLayer[indexB];
//		//	}

//		//}

//		//for (auto tileA : m_groundLayer) {
//		//	for (auto tileB : m_groundLayer) {

//		//Get working ID to access
//		//int workingID = tileA->ID;

//		////Find equivalent/parallel tile in main layer if it exists
//		//Tile* ParallelMainTile;
//		////Get tileB's ID
//		//for (auto t : m_groundLayer) {
//		//	int groundTileID = t->ID;
//		//	int
//		//}
//		//StaticObject* ParallelObject;

//		//// Skip if they're both the same node ////
//		if (tileA == tileB) continue;

//		//// Skip if the subject tile (tileA) has an object on it ////
//		if (m_mainLayer[indexA]->access == eTileAccess::INACCESSIBLE)
//			continue;

//		//bool skip = false;
//		////Loop through main layer until a matching id is found
//		//for (auto mainTile : m_mainLayer) {
//		//	if (mainTile->ID == tileA->ID) {
//		//		if (mainTile->access == eTileAccess::INACCESSIBLE) {
//		//			skip = true;		//TileA has an object on it
//		//			break;				//Match found so get out
//		//		}
//		//	}
//		//}
//		//if (skip = true) continue;	//Break out and skip connecting this tile

//		//// Skip if the target tile (tileB) has an object on it ////
//		if (m_mainLayer[indexB]->access == eTileAccess::INACCESSIBLE)
//			continue;


//		//Loop through main layer until a matching id is found
//		//for (auto mainTile : m_mainLayer) {
//		//	if (mainTile->ID == tileB->ID) {
//		//		if (mainTile->access == eTileAccess::INACCESSIBLE) {
//		//			skip = true;		//TileA has an object on it
//		//			break;				//Match found so get out
//		//		}
//		//	}
//		//}
//		//if (skip = true) continue;	//Break out and skip connecting this tile


//		//// Do the connection ////

//		//Find the distance between the two tiles
//		float distanceBetween = tileA->cPos.distance(tileB->cPos);

//		//If they're within range then connect
//		if (distanceBetween < connectRadius) {
//			//// Take into account tile's accessibility and terrain ////
//			//Set the edge cost based on the terrain
//			//auto terrainCost = tileB->terrain;

//			float cost = 1.0f;	//Default cost to 1

//								//ground layer
//			switch (tileB->terrain) {
//			case NA:
//				cost = INFINITY;
//				break;
//			case SMOOTH_FLOOR:
//				cost = 0.5f;
//				break;
//			case GRASS:
//				cost = 1.0f;
//				break;
//			case DIRT:
//				cost = 1.3f;
//				break;
//			case GRAVEL:
//				cost = 2.0f;
//				break;
//			case WATER:
//				cost = 5.0f;
//				break;
//			default:
//				assert(false);		//Invalid
//			}

//			pf::Node::connect(tileA, tileB, cost);	//This should also connect tiles both ways
//		}
//	}
//}

}
*/


////Skip if ground tile OR main layer tile not ACCESSIBLE
//if (tileB->access == INACCESSIBLE) continue;
////if (tileB->access == INACCESSIBLE) ||					//Ground layer
////	m_mainLayer[tileB->ID]->access == INACCESSIBLE)		//Main layer tile/object

////Find the tile (REALLY DUMB; should use binary tree or something)
//int EquivMainTileID = 0;
//for (auto mainTile : m_mainLayer) {
//	if (mainTile->ID == tileB->ID) {	//Found the tile
//		EquivMainTileID = mainTile->ID;

//			//EquivMainTileID = m_mainLayer.size()-1;
//		break;
//	}
//}
//if (EquivMainTileID < m_mainLayer.size())
//{
//	if (m_mainLayer[EquivMainTileID]->access == INACCESSIBLE)
//		continue;
//}


	//////////////////////////////////////////////////////////////////////////////////////
	//TEST leafs
	//eResult tAttackSequence::execute(Agent * agent, float deltaTime)
	//{
	//	//If condition node returns success then get the list of enemies found in range
	//	
	//	//////////////////////
	//	//GIVE UP!!!
	//	//////////////////////

	//	return eResult::SUCCESS;
	//}
	//tEnemiesCloseCondition::tEnemiesCloseCondition(std::vector<Agent*> listOfEnemies, float range) :
	//	m_enemies(listOfEnemies), m_range(range) {}
	//eResult tEnemiesCloseCondition::execute(Agent * agent, float deltaTime)
	//{
	//	m_enemyFoundInRange.clear();		//Clear found enemies
	//	bool successfullyFoundEnemiesInRange = false;		//Clear found flag 

	//	//Return success if an enemy is within range
	//	for (auto enemy : m_enemies) {
	//		if (pkr::Vector2::distance(agent->getPos(), enemy->getPos()) < m_range) {
	//			//Retrieve the enemy that is in range
	//			m_enemyFoundInRange.push_back(enemy);
	//			successfullyFoundEnemiesInRange = true;
	//		}
	//	}

	//	//Return success if found
	//	if (successfullyFoundEnemiesInRange)
	//			return eResult::SUCCESS;
	//	else 
	//		return eResult::FAILURE;
	//}

	//eResult tAttackAction::execute(Agent * agent, float deltaTime)
	//{
	//	//For each enemy within range of agent
	//	for (auto enemy : m_enemiesInRange) {

	//		//Deal damage to enemy
	//		//enemy.health -= m_damageToApply;
	//	}
	//	return eResult::SUCCESS;
	//}
	//////////////////////////////////////////////////////////////////////////////////////////

	////////////// TESTS /////////////////////
	////Composites
	//class tAttackSequence : public Sequence
	//{
	//private:
	//	std::vector<Agent*>	m_enemiesInRange;
	//public:
	//	tAttackSequence() { m_enemiesInRange.clear(); }
	//	~tAttackSequence() {}
	//	
	//	eResult execute(Agent* agent, float deltaTime) override;
	//};
	//class tEnemiesCloseCondition : public iBehaviour
	//{
	//private:
	//	std::vector<Agent*> m_enemies;
	//	float		m_range;
	//	std::vector<Agent*>	m_enemyFoundInRange;		//How do you relay this information to AttackAction?
	//public:
	//	//This class will need to take in a list of enemy agents
	//	tEnemiesCloseCondition(std::vector<Agent*> listOfEnemies, float range);
	//	//void setEnemyList(std::vector<Agent*> listOfEnemies);
	//	//std::vector<Agent*> getEnemyList() const;
	//	eResult execute(Agent* agent, float deltaTime) override;
	//};
	//class tAttackAction : public iBehaviour
	//{
	//private:
	//	std::vector<Agent*> m_enemiesInRange;
	//	Agent*		m_enemyInRange;
	//	int			m_damageToApply;
	//	float		m_range;
	//public:
	//	eResult execute(Agent* agent, float deltaTime) override;
	//};
//
//void Camera::testViewportToCanvas(aie::Renderer2D * renderer)
//{
//	aie::Input* input = aie::Input::getInstance();
//
//	//Get mouse position in window coords
//	float windowX = input->getMouseX();
//	float windowY = input->getMouseY();
//
//	//Transform from window coords to canvas coords
//	pkr::Vector2 canvas = ViewportToCanvas(windowX, windowY);
//
//	renderer->setRenderColour(0.25f, 1, 0.25f);
//	renderer->drawCircle(canvas.x, canvas.y, 50.0f);
//
//	//// DEBUG ////
//	//ImGui::Begin("WindowToCanvas(test)");
//	//ImGui::Text("Before > X: %f, Y: %f", windowX, windowY);
//	//ImGui::Text("After > X: %f, Y: %f", canvas.x, canvas.y);
//	//ImGui::End();
//	////////////////
//
//}
