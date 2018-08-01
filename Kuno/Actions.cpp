#include "Actions.h"
#include "AI.h"
#include "Agent.h"
#include "pkr/Vector2.h"

namespace ai {
	BasicController::BasicController(aie::Input * input, float lSpeedMax) :
		m_input(input), m_lSpeedMax(lSpeedMax)
	{}

	eResult BasicController::execute(Agent * agent, float deltaTime)
	{
		//Mouse controls
		//int mouseX = input->getMouseX();
		//int mouseY = input->getMouseY();

		//Keyboard controls
		if (m_input->isKeyDown(aie::INPUT_KEY_W))
		{
			agent->moveIso(pkr::Vector2(0.0f, m_lSpeedMax * deltaTime));
		}
		if (m_input->isKeyDown(aie::INPUT_KEY_S))
		{
			agent->moveIso(pkr::Vector2(0.0f, -m_lSpeedMax * deltaTime));
		}
		if (m_input->isKeyDown(aie::INPUT_KEY_A))
		{
			agent->moveIso(pkr::Vector2(-m_lSpeedMax * deltaTime, 0.0f));
		}
		if (m_input->isKeyDown(aie::INPUT_KEY_D))
		{
			agent->moveIso(pkr::Vector2(m_lSpeedMax * deltaTime, 0.0f));
		}
		//agent->rotation = -mouseX * deltaTime;

		return eResult::SUCCESS;
	}

	//// SEEK ////
	SeekAction::SeekAction(Agent * target, float lSpeedMax) :
		m_target(target), m_lSpeedMax(lSpeedMax) {}

	eResult SeekAction::execute(Agent * agent, float deltaTime)
	{	//Seek vector = Target position - Agent position
		//Find the normalised seek vector towards target
		pkr::Vector2 nrmSeekVector = pkr::Vector2::normalise(m_target->getPos() - agent->getPos());

		//Apply max force towards target
		agent->move(nrmSeekVector * m_lSpeedMax * deltaTime);

		return eResult::SUCCESS;
	}

	//// PATROL ////
	PatrolAction::PatrolAction(Agent * pathObject)
	{
		//SeekAction* pathFollower = new SeekAction(pathObject);
	}

	eResult PatrolAction::execute(Agent * agent, float deltaTime)
	{
		SeekAction* followPath = new SeekAction(agent, m_maxForce);

		//Get a new point from path agent/object
		

		//Seek towards the new point

		return eResult();
	}
}