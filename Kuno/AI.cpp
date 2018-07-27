#include "AI.h"
#include "Agent.h"
#include <pkr\Vector2.h>
#include <Renderer2D.h>

namespace ai {
	//Composites
	aComposite::~aComposite()
	{
		//Delete all children
		for (auto &child : m_childBehaviours) {
			delete child;
			child = nullptr;
		}
	}
	void aComposite::addChild(iBehaviour * behaviour)
	{
		m_childBehaviours.push_back(behaviour);
	}
	eResult Selector::execute(Agent * agent, float deltaTime)
	{
		//OR node; Returns SUCCESS if any child returns SUCCESS
		for (auto child : m_childBehaviours) {
			if (child->execute(agent, deltaTime) == eResult::SUCCESS)
				return eResult::SUCCESS;
		}
		return eResult::FAILURE;
	}

	eResult Sequence::execute(Agent * agent, float deltaTime)
	{
		//AND node; Returns SUCCESS only if ALL children return SUCCESS
		for (auto child : m_childBehaviours) {
			if (child->execute(agent, deltaTime) == eResult::FAILURE)
				return eResult::FAILURE;
		}
		return eResult::SUCCESS;
	}

	//Decorators
	eResult NotDecorator::execute(Agent * agent, float deltaTime)
	{
		//Get result of child...
		eResult result = m_child->execute(agent, deltaTime);

		//Invert
		switch (result) {
		case eResult::SUCCESS:
			return FAILURE; break;
		case eResult::FAILURE:
			return SUCCESS; break;
		default:	//Else return whatever result is
			return result;
		}
	}

	eResult TimeoutDecorator::execute(Agent * agent, float deltaTime)
	{
		m_timeout -= deltaTime;
		if (m_timeout > 0)
			return eResult::FAILURE;
		m_timeout = m_duration;
		//Returns result of child unless it times out
		return m_child->execute(agent, deltaTime);
	}
	////////////////////////////////////////////////////////////////////////////////////////////
	eResult BasicController::execute(Agent * agent, float deltaTime)
	{
		//Mouse controls
		//int mouseX = input->getMouseX();
		//int mouseY = input->getMouseY();

		//Keyboard controls
		if (m_input->isKeyDown(aie::INPUT_KEY_W || aie::INPUT_KEY_UP))
		{
			agent->addForce(pkr::Vector2(0.0f, m_maxForce));
		}
		if (m_input->isKeyDown(aie::INPUT_KEY_S))
		{
			agent->addForce(pkr::Vector2(0.0f, -m_maxForce));
		}
		if (m_input->isKeyDown(aie::INPUT_KEY_A))
		{
			agent->addForce(pkr::Vector2(-m_maxForce, 0.0f));
		}
		if (m_input->isKeyDown(aie::INPUT_KEY_D))
		{
			agent->addForce(pkr::Vector2(m_maxForce, 0.0f));
		}
		//agent->rotation = -mouseX * deltaTime;

		return eResult::SUCCESS;
	}




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


	PatrolAction::PatrolAction(Agent * pathObject)
	{
		SeekAction* pathFollower = new SeekAction(pathObject);
		


	}

	eResult PatrolAction::execute(Agent * agent, float deltaTime)
	{
		SeekAction* followPath = new SeekAction(agent, m_maxForce);

		//Get a new point from path agent/object
		

		//Seek towards the new point

		return eResult();
	}

}