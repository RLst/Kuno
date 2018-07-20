#include "AI.h"

#include <pkr\Vector2.h>
#include <Renderer2D.h>

namespace AI {
	//Composites
	Composite::~Composite()
	{
		//Delete all children
		for (auto &child : m_childBehaviours) {
			delete child;
			child = nullptr;
		}
	}
	void Composite::addChild(iBehaviour * behaviour)
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


	//////////////////////////////////////////////////////////////////////////////////////////////////
	//Agent
	Agent::Agent(const Agent & other) :
		m_behaviours(other.m_behaviours),
		m_maxForce(other.m_maxForce),
		m_force(other.m_force),
		m_accel(other.m_accel),
		m_vel(other.m_vel),
		m_pos(other.m_pos),
		m_size(other.m_size),
		m_colour(other.m_colour),
		m_texture(other.m_texture)	{}

	Agent::Agent( float maxForce, const pkr::Vector2 & startingPos) :
		m_maxForce(maxForce),
		m_pos(startingPos) {}

	Agent::Agent(float size, const pkr::Vector3 & colour, const pkr::Vector2 & startingPos) :
		m_size(size),
		m_colour(colour),
		m_pos(startingPos) {}

	Agent::Agent(aie::Texture * texture, const pkr::Vector2 & startingPos) :
		m_texture(texture),
		m_pos(startingPos) {}

	Agent::~Agent()
	{
		for (auto &behaviour : m_behaviours) {
			delete behaviour;			//Do the behaviours have to be deleted?
			behaviour = nullptr;
		}
		if (m_texture != nullptr) delete m_texture;
	}

	void Agent::addBehaviour(iBehaviour * behaviour)
	{
		m_behaviours.push_back(behaviour);
	}

	void Agent::addForce(const pkr::Vector2 & force)
	{
		m_force += force;
	}

	void Agent::update(float deltaTime)
	{
		//Execute all behaviours
		for (auto behaviour : m_behaviours) {
			behaviour->execute(this, deltaTime);
		}
	}

	void Agent::draw(aie::Renderer2D * renderer)
	{
		//Draw agent as a coloured circle
		renderer->setRenderColour(m_colour.r, m_colour.g, m_colour.b);
		renderer->drawCircle(m_pos.x, m_pos.y, m_size);
	}
	////////////////////////////////////////////////////////////////////////////////////////
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

	SeekAction::SeekAction(Agent * target, float maxSpeed) :
		m_target(target), m_maxForce(maxSpeed) {}

	eResult SeekAction::execute(Agent * agent, float deltaTime)
		//Seek vector = Target position - Agent position
	{
		//Find the normalised seek vector towards target
		pkr::Vector2 nrmSeekVector = pkr::Vector2::normalise(m_target->getPos() - agent->getPos());

		//Apply max force towards target
		agent->addForce(nrmSeekVector * m_maxForce);
		
		return eResult::SUCCESS;
	}





}