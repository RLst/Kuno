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
		m_target(target), m_maxSpeed(maxForce) 
	{
		m_dest = m_target->getPos();
	}

	Seek::Seek(pkr::Vector2 destination, float maxSpeed) :
		m_dest(destination), m_maxSpeed(maxSpeed) {}

	eResult Seek::execute(Agent * agent, float deltaTime)
	{	//Seek vector = Target position - Agent position
		//Find the normalised seek vector towards target

		pkr::Vector2 seekVec = pkr::Vector2::normalise(m_dest - agent->getPos());

		//Apply max force towards target
		agent->move(seekVec * m_maxSpeed, deltaTime);
		//agent->move(nrmSeekVector - agent.getVel() * m_maxLspeed, deltaTime);

		return eResult::SUCCESS;
	}

	//// Patrol ////
	PatrolPath::PatrolPath(Agent * pathObject, float maxForce)
	{
		//SeekAction* pathFollower = new SeekAction(pathObject);
	}

	eResult PatrolPath::execute(Agent * agent, float deltaTime)
	{
		Seek* followPath = new Seek(agent, m_maxForce);

		//Get a new point from path agent/object
		

		//Seek towards the new point

		return eResult();
	}

	//// Mouse Controller ////
	MouseControl::MouseControl(aie::Input * input, float maxForce) :
		m_input(input), m_maxSpeed(maxForce) {}
	
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
			auto seek = pkr::Vector2::normalise(m_dest - agent->getPos()) * m_maxSpeed;
			agent->move(seek, deltaTime);
			return RUNNING;
		}
		//Else; Agent has arrived, stop moving. Success
		else {
			return SUCCESS;
		}

	}

	eResult Attack::execute(Agent * agent, float deltaTime)
	{
		return eResult();
	}



	//////////////////////////////////////////////////////////////////////////////////////
	SeekAndArrive::SeekAndArrive(Agent * target, float maxSpeed) :
		m_target(target), m_maxSpeed(maxSpeed)	
	{
		m_dest = m_target->getPos();
	}

	SeekAndArrive::SeekAndArrive(pkr::Vector2 destination, float maxSpeed) :
		m_dest(destination), m_maxSpeed(maxSpeed) {}

	eResult SeekAndArrive::execute(Agent * agent, float deltaTime)
	{
		//Get current seek destination if target agent is set
		if (m_target != nullptr)
			m_dest = m_target->getPos();

		//auto seek = m_dest - agent->getPos();				//Get the seek vector
		//auto distance = pkr::Vector2::magnitude(seek);		//Get the distance from destination
		//seek.normalise();
		//seek *= m_maxSpeed;
		auto seek = pkr::Vector2::normalise(m_dest - agent->getPos());
		auto distance = pkr::Vector2::distance(m_dest, agent->getPos());

		//If within arrive zone...
		if (distance < m_slowZone) {
			agent->move(seek * (distance / m_slowZone), deltaTime);		//Slow down accordingly
			return RUNNING;
		}
		else {
			agent->move(seek * m_maxSpeed, deltaTime);					//Otherwise go full speed
			return RUNNING;
		}
		if (distance <= m_arriveZone) {
			return SUCCESS;
		}
	}

	FollowPath::FollowPath() : m_currentWaypoint(0), m_pathRadius(20.0f)	//Raw
	{}

	eResult FollowPath::execute(Agent * agent, float deltaTime)
	{
		//Try using the agent's member path
		//How do you get a path from here?
		auto map = KunoApp::Instance()->getMap();
		agent->setPath(&map->getPath());

		//If there is an available path
		if (!agent->getPath()->empty()) {
			//If the agent has reached the end of the path
			if (m_currentWaypoint > agent->getPath()->size()) {
				m_currentWaypoint = 0;	//Reset waypoint
				return eResult::SUCCESS;
			}
			else {
				auto waypoint = agent->getPath()->at(m_currentWaypoint);	//Get target waypoint

				//Seek towards it
				if (pkr::Vector2::distance(waypoint, agent->getPos()) > m_pathRadius) {
					agent->seek(waypoint, deltaTime);
					return eResult::RUNNING;
				}
				else { //Target reached, next waypoint
					++m_currentWaypoint;
					return eResult::RUNNING;
				}
			}
		}
		else	//Path unavailable; FAIL!
			return eResult::FAILURE;
	}

}
}
