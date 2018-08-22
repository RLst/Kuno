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
#include "Map.h"
#include <Input.h>

#include "imgui.h"
#include <iostream>

namespace ai {
	namespace action {
		/////////////////////////////////////////////////////////////////////////////////////////////////
		tKeyboardControl::tKeyboardControl(aie::Input * input, float lSpeedMax) :
			m_input(input), m_maxForce(lSpeedMax)
		{}

		eResult tKeyboardControl::execute(Agent * agent, float deltaTime)
		{
			//Keyboard controls
			if (m_input->isKeyDown(aie::INPUT_KEY_UP))
			{
				agent->moveOnCanvas(pkr::Vector2(0.0f, m_maxForce), deltaTime);
			}
			if (m_input->isKeyDown(aie::INPUT_KEY_DOWN))
			{
				agent->moveOnCanvas(pkr::Vector2(0.0f, -m_maxForce), deltaTime);
			}
			if (m_input->isKeyDown(aie::INPUT_KEY_LEFT))
			{
				agent->moveOnCanvas(pkr::Vector2(-m_maxForce, 0.0f), deltaTime);
			}
			if (m_input->isKeyDown(aie::INPUT_KEY_RIGHT))
			{
				agent->moveOnCanvas(pkr::Vector2(m_maxForce, 0.0f), deltaTime);
			}

			return eResult::SUCCESS;
		}
		/////////////////////////////////////////////////////////////////////////////////////////////////
		tMouseControl::tMouseControl(aie::Input * input, float maxForce) :
			m_input(input), m_maxSpeed(maxForce) {}
		eResult tMouseControl::execute(Agent * agent, float deltaTime)	//MESSY
		{
			//Get GameApp
			auto app = KunoApp::Instance();

			//Get current cartesian mouse position
			auto mView = pkr::Vector2((float)m_input->getMouseX(), (float)m_input->getMouseY());
			auto mCanvas = app->CoordConverter()->ViewportToCanvas(mView);
			auto mWorld = app->CoordConverter()->CanvasToWorld(mCanvas);

			//(CONDITION) Retrieve new destination if any (later make this retrieve a new waypoint/node)
			if (m_input->wasMouseButtonReleased(aie::INPUT_MOUSE_BUTTON_LEFT)) {
				m_dest = mWorld;	//(ACTION)
			}

			//(CONDITION) If the agent is not at the target position, then move towards it
			if (pkr::Vector2::distance(agent->pos, m_dest) > m_arriveThreshold) {
				//(ACTION) Seek towards target
				auto seek = pkr::Vector2::normalise(m_dest - agent->pos) * m_maxSpeed;
				agent->move(seek, deltaTime);
				return eResult::RUNNING;
			}
			//Else; Agent has arrived, stop moving. Success
			else {
				return eResult::SUCCESS;
			}
		}
		/////////////////////////////////////////////////////////////////////////////////////////////////
		tMouseSetDesiredPos::tMouseSetDesiredPos(aie::Input * input) :
			m_input(input) 	{}
		eResult tMouseSetDesiredPos::execute(Agent * agent, float deltaTime)
		{
			auto cc = KunoApp::Instance()->CoordConverter();
				//Set agent desired pos to where the mouse is clicked
				auto mView = pkr::Vector2((float)m_input->getMouseX(), (float)m_input->getMouseY());
				auto mCanvas = cc->ViewportToCanvas(mView);
				auto desiredPos = cc->CanvasToWorld(mCanvas);

			if (m_input->wasMouseButtonPressed(aie::INPUT_MOUSE_BUTTON_LEFT)) {
				agent->setDesiredPos(desiredPos);
				return eResult::SUCCESS;
			}
			return FAILURE;
		}
		/////////////////////////////////////////////////////////////////////////////////////////////////
		Seek::Seek(Agent * target, float arriveRadius) :
			m_target(target), m_arriveRadius(arriveRadius)	{}
		eResult Seek::execute(Agent * agent, float deltaTime)
		{	//Seek vector = Target position - Agent position
			std::cout << "Seek" << std::endl;

			//TRY implementing CheckNotMoving behaviour inside 
			//the move behaviours to simplify it a bit
			if (agent->isMoving())
			{
				//If the agent is moving then let the agent move/followPath
				return eResult::FAILURE;	//Should branch out to Pathfinding branch
			}
			else {
				//Set the agent's desired position
				agent->setDesiredPos(m_target->pos);
				return eResult::SUCCESS;
			}
		}
		/////////////////////////////////////////////////////////////////////////////////////////////////
		Flee::Flee(Agent * target) :
			m_target(target){}
		eResult Flee::execute(Agent * agent, float deltaTime)
		{
			std::cout << "Flee" << std::endl;

			if (agent->isMoving())	{
				//If the agent is moving then let the agent move/followPath
				return eResult::FAILURE;	//Should branch out to Pathfinding branch
			}
			else {
				//Set the desired path to where the target is.... but reversed
				auto fleeVec = pkr::Vector2::normalise(agent->pos - m_target->pos) * agent->getSpeed();
				auto fleePos = agent->pos + fleeVec;
				agent->setDesiredPos(fleePos);
				return eResult::SUCCESS;
			}
		}
		/////////////////////////////////////////////////////////////////////////////////////////////////
		Idle::Idle(float minIdleTime, float maxIdleTime) :
			m_minTime(minIdleTime), m_maxTime(maxIdleTime), m_idleTime(0)	{}
		eResult Idle::execute(Agent * agent, float deltaTime)
		{
			std::cout << "Idle: " << std::endl;

			//If first run then setup
			if (m_idleTime <= 0) {
				//Set random finished time
				m_reset = pkr::Random(m_minTime, m_maxTime);
				m_idleTime += deltaTime;
				return RUNNING;		//Return running
			}
			//If the current idle time is past max idle time
			else if (m_idleTime > m_reset) {
				//Reset and return success
				m_idleTime = 0;
				return SUCCESS;
			}
			else {
				//Still counting down
				m_idleTime += deltaTime;
				std::cout << m_idleTime << " / " << m_reset << std::endl;
				return RUNNING;
			}
		}
		/////////////////////////////////////////////////////////////////////////////////////////////////
		eResult Attack::execute(Agent * agent, float deltaTime)
		{
			std::cout << "Attack" << std::endl;

			//This agent attacks the target agent
			m_target->takeDamage(agent->getAttack());
			return eResult::SUCCESS;
		}
		/////////////////////////////////////////////////////////////////////////////////////////////////
		eResult FollowPath::execute(Agent * agent, float deltaTime)
		{
			std::cout << "FollowPath: ";

			//If a path exists then follow it, return running/success?
			return agent->followPath(deltaTime);	//eResult RETURNED HERE
		}
		/////////////////////////////////////////////////////////////////////////////////////////////////
		eResult UpdateState::execute(Agent * agent, float deltaTime)
		{
			std::cout << "UpdateState: " << static_cast<int>(m_desiredState) << std::endl;

			//Just change the agent's state to the desired state
			agent->state = m_desiredState;
			return eResult::SUCCESS;
		}
		/////////////////////////////////////////////////////////////////////////////////////////////////
		eResult UpdateLastSeen::execute(Agent * agent, float deltaTime)
		{		
			std::cout << "SetLastSeen > x: " << m_target->pos.x << ",y: " << m_target->pos.y << std::endl;
			
			agent->setLastSeen(m_target->pos);
			return eResult::SUCCESS;
		}
		/////////////////////////////////////////////////////////////////////////////////////////////////
		eResult ClearLastSeen::execute(Agent * agent, float deltaTime)
		{
			std::cout << "ClearLastSeen" << std::endl;
			agent->clearLastSeen();
			return eResult::SUCCESS;
		}
		/////////////////////////////////////////////////////////////////////////////////////////////////
		eResult CalculatePath::execute(Agent * agent, float deltaTime)
		{
			std::cout << "CalculatePath: ";

			if (agent->isMoving()) {

				//// Find the correct destination and starting tiles ////
				//DESTINATION TILE
				auto endPos = m_map->clampWithinMapRetWORLD(agent->getDesiredPos());		//Restrict desiredPos within the bounds of the map
				auto endTile = m_map->findTileFromPos(endPos);

				//START TILE
				auto startPos = m_map->clampWithinMapRetWORLD(agent->pos);
				auto startTile = m_map->findTileFromPos(startPos);

				pf::Path desiredPath;
				if (!startTile->objects.empty()) {	//If agent is on a untraversable tile
					//... this path should move the agent out from the untraversable tile
					desiredPath = m_map->getAStarPath(startTile, endTile);
				}
				else {	//If agent is ona  traversable tile
					//Set the first waypoint to the agent's current position so that
					//it doesn't move back to the tile centre
					desiredPath = m_map->getAStarPath(startTile, endTile);
					desiredPath[0] = agent->pos;
				}

				//Set the agent's path
				agent->setPath(desiredPath);
				std::cout << "SUCCESS" << std::endl;
				return SUCCESS;
			}
			else {
				std::cout << "FAILURE" << std::endl;
				return FAILURE;
			}
			return eResult::SUCCESS;
		}

		eResult ReturnToPost::execute(Agent * agent, float deltaTime)
		{
			std::cout << "ReturnToPost: ";

			//If patrol path is empty return failure
			if (agent->isMoving()) {
				//Exit branch so that pathfinding can run?
				//1. Path can be calculated
				//2. Path can be followed
				std::cout << "FAILURE" << std::endl;
				return FAILURE;
			}
			else {
				if (agent->patrolPath().isAvailable()) {	//Failsafe check

					//If the agent is already back at his post then don't pathfind (MESSY/CLUNKY)
					if (pkr::Vector2::distance(agent->pos, agent->patrolPath().at(0)) > m_postRadius) {		//If not yet at the post 
						agent->setDesiredPos(agent->patrolPath().at(0));	//Move towards it
						std::cout << "SUCCESS" << std::endl;
						return SUCCESS;
					}
				}
				//assert(false);
				std::cout << "FAILURE: No patrol route/guard" << std::endl;
				return FAILURE;
			}
		}

		eResult Inspect::execute(Agent * agent, float deltaTime)
		{
			std::cout << "Inspect: ";

			if (agent->isMoving()) {
				//Exit branch so that:
				//1. Path can be calculated
				//2. Path can be followed
				std::cout << "FAILURE" << std::endl;
				return FAILURE;
			}
			else {
				//Move and set desired pos
				agent->setDesiredPos(agent->getLastSeen());
				std::cout << "SUCCESS" << std::endl;
				return SUCCESS;
			}
		}

}
}


