#pragma once
#include <cassert>

//#define SCREEN_WIDTH 1280
//#define SCREEN_HEIGHT 720

#define WORLD_WIDTH			20		//Tiles along X axis
#define WORLD_DEPTH			20		//Tiles along Y axis

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
