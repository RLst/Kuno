//////////////////
//// Tony Le ////
// 2 Aug 2018 //
///////////////


#include "Actions.h"
#include "AI.h"
#include "Agent.h"
#include "pkr/Vector2.h"
#include "KunoApp.h"

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

	//// Seek ////
	SeekAction::SeekAction(Agent * target, float lSpeedMax) :
		m_target(target), m_maxLspeed(lSpeedMax) {}

	//SeekAction::SeekAction(pkr::Vector2 destination, float maxLspeed) :
	//	m_destination(destination), m_maxLspeed(maxLspeed) {}

	eResult SeekAction::execute(Agent * agent, float deltaTime)
	{	//Seek vector = Target position - Agent position
		//Find the normalised seek vector towards target
		pkr::Vector2 nrmSeekVector = pkr::Vector2::normalise(m_target->getPos() - agent->getPos());

		//Apply max force towards target
		agent->move(nrmSeekVector * m_maxLspeed * deltaTime);

		return eResult::SUCCESS;
	}

	//// Patrol ////
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

	//// Mouse Controller ////
	MouseController::MouseController(aie::Input * input, float maxSpeed) :
		m_input(input), m_lSpeedMax(maxSpeed) {}
	
	eResult MouseController::execute(Agent * agent, float deltaTime)
	{
		//Retrieve new destination if any (later make this retrieve a new waypoint/node)
		if (m_input->wasMouseButtonReleased(aie::INPUT_MOUSE_BUTTON_LEFT)) {
			//Convert from viewport to isometric
			int mousex, mousey; m_input->getMouseXY(&mousex, &mousey);
			m_destination = KunoApp::Instance()->CoordConverter()->ViewportToCartesian(mousex, mousey);
		}

		//If the agent is not at the target position, then move towards it
		if (pkr::Vector2::distance(agent->getPos(), m_destination) > m_arriveThreshold) {
			//Seek towards target
			auto seek = pkr::Vector2::normalise(m_destination - agent->getPos());
			agent->move(seek * m_lSpeedMax * deltaTime);
			return RUNNING;
		}
		//Else; Agent has arrived, stop moving. Success
		else {
			return SUCCESS;
		}
	}
}