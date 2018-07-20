#include "AI.h"

#include <pkr\Vector2.h>
#include <Renderer2D.h>

namespace AI {

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

	Agent::Agent(const Agent & other) :
		m_behaviours(other.m_behaviours),
		m_pos(other.m_pos),
		m_size(other.m_size),
		m_colour(other.m_colour)
	{}

	Agent::Agent(const pkr::Vector2 & pos, float size, const pkr::Vector3 & colour) :
		m_pos(pos), m_size(size), m_colour(colour)
	{}

	Agent::~Agent()
	{
		for (auto &behaviour : m_behaviours) {
			delete behaviour;			//Do the behaviours have to be deleted?
			behaviour = nullptr;
		}
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

	eResult tEnemiesCloseCondition::execute(Agent * agent, float deltaTime)
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