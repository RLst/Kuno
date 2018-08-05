//////////////////
//// Tony Le ////
// 2 Aug 2018 //
///////////////


#include "Actions.h"
#include "AI.h"
#include "Agent.h"
#include "pkr/Vector2.h"
#include "KunoApp.h"
#include "Tile.h"

namespace ai {
	namespace action {

	KeyboardControl::KeyboardControl(aie::Input * input, float lSpeedMax) :
		m_input(input), m_maxForce(lSpeedMax)
	{}

	eResult KeyboardControl::execute(Agent * agent, float deltaTime)
	{
		//Mouse controls
		//int mouseX = input->getMouseX();
		//int mouseY = input->getMouseY();

		//Keyboard controls
		if (m_input->isKeyDown(aie::INPUT_KEY_UP))
		{
			agent->moveOnCanvas(pkr::Vector2(0.0f, m_maxForce), deltaTime );
		}
		if (m_input->isKeyDown(aie::INPUT_KEY_DOWN))
		{
			agent->moveOnCanvas(pkr::Vector2(0.0f, -m_maxForce), deltaTime );
		}
		if (m_input->isKeyDown(aie::INPUT_KEY_LEFT))
		{
			agent->moveOnCanvas(pkr::Vector2(-m_maxForce, 0.0f), deltaTime );
		}
		if (m_input->isKeyDown(aie::INPUT_KEY_RIGHT))
		{
			agent->moveOnCanvas(pkr::Vector2(m_maxForce, 0.0f), deltaTime );
		}

		return eResult::SUCCESS;
	}

	//// Seek ////
	Seek::Seek(Agent * target, float maxForce) :
		m_target(target), m_maxForce(maxForce) {}

	//SeekAction::SeekAction(pkr::Vector2 destination, float maxLspeed) :
	//	m_destination(destination), m_maxLspeed(maxLspeed) {}

	eResult Seek::execute(Agent * agent, float deltaTime)
	{	//Seek vector = Target position - Agent position
		//Find the normalised seek vector towards target

		pkr::Vector2 SeekDirection = pkr::Vector2::normalise(m_target->getPos() - agent->getPos());

		//Apply max force towards target
		agent->move(SeekDirection * m_maxForce, deltaTime);
		//agent->move(nrmSeekVector - agent.getVel() * m_maxLspeed, deltaTime);

		return eResult::SUCCESS;
	}

	//// Patrol ////
	Patrol::Patrol(Agent * pathObject, float maxForce)
	{
		//SeekAction* pathFollower = new SeekAction(pathObject);
	}

	eResult Patrol::execute(Agent * agent, float deltaTime)
	{
		Seek* followPath = new Seek(agent, m_maxForce);

		//Get a new point from path agent/object
		

		//Seek towards the new point

		return eResult();
	}

	//// Mouse Controller ////
	MouseControl::MouseControl(aie::Input * input, float maxForce) :
		m_input(input), m_maxForce(maxForce) {}
	
	eResult MouseControl::execute(Agent * agent, float deltaTime)	//MESSY
	{
		//Get GameApp
		auto app = KunoApp::Instance();

		//Get current cartesian mouse position
		auto mView = pkr::Vector2(m_input->getMouseX(), m_input->getMouseY());
		auto mCanvas = app->CoordConverter()->ViewportToCanvas(mView);
		auto mWorld = app->CoordConverter()->CanvasToWorld(mCanvas);

		//(CONDITION) Retrieve new destination if any (later make this retrieve a new waypoint/node)
		if (m_input->wasMouseButtonReleased(aie::INPUT_MOUSE_BUTTON_LEFT)) {
			m_dest = mWorld;	//(ACTION)
		}

		//(CONDITION) If the agent is not at the target position, then move towards it
		if (pkr::Vector2::distance(agent->getPos(), m_dest) > m_arriveThreshold) {
			//(ACTION) Seek towards target
			auto seek = pkr::Vector2::normalise(m_dest - agent->getPos()) * m_maxForce;
			agent->move(seek, deltaTime);
			return RUNNING;
		}
		//if (pkr::Vector2::distance(agent->getPos(), m_destination) > m_arriveThreshold) {
		//	//(ACTION) Seek towards target
		//	auto seek = pkr::Vector2::normalise(m_destination - agent->getPos()) * m_maxForce;
		//	agent->move(seek, deltaTime);
		//	return RUNNING;
		//}
		//Else; Agent has arrived, stop moving. Success
		else {
			return SUCCESS;
		}

	}

	eResult Attack::execute(Agent * agent, float deltaTime)
	{
		return eResult();
	}

}
}
