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

#ifdef _DEBUG
//ImGui::Begin("tMouseSetDesiredPos");
//ImGui::Text("desiredPos> x: %.2f, y: %.2f", desiredPos.x, desiredPos.y);
//ImGui::End();
#endif // _DEBUG

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

			//TRY implementing CheckNotMoving behaviour inside 
			//the move behaviours to simplify it a bit
			if (agent->m_isMoving)
			{
				//If the agent is moving then let the agent move/followPath
				return eResult::FAILURE;	//Should branch out to Pathfinding branch
			}
			else {
				//Set the agent's desired position
				agent->m_isMoving = true;		//set to moving
				agent->setDesiredPos(m_target->pos);
				return eResult::SUCCESS;
			}
		}
		}
		/////////////////////////////////////////////////////////////////////////////////////////////////
		Idle::Idle(float minIdleTime, float maxIdleTime) :
			m_minTime(minIdleTime), m_maxTime(maxIdleTime), m_duration(0)	{}
		eResult Idle::execute(Agent * agent, float deltaTime)
		{
			//If the current idle time is 0 then start timing
			if (m_duration <= 0) {
				//Set random finished time
				m_timeout = pkr::Random(m_minTime, m_maxTime);
				m_duration += deltaTime;
				return RUNNING;		//Return running
			}
			//If the current idle time is past max idle time
			else if (m_duration > m_maxTime) {
				//Reset and return success
				m_duration = NULL;
				m_timeout = NULL;
				return SUCCESS;
			}
			else {
				//Still counting down
				return RUNNING;
			}
		}
		/////////////////////////////////////////////////////////////////////////////////////////////////
		eResult Attack::execute(Agent * agent, float deltaTime)
		{
			//This agent attacks the target agent
			m_target->takeDamage(agent->getAttack());
			return eResult::SUCCESS;
		}
		/////////////////////////////////////////////////////////////////////////////////////////////////
		eResult FollowPath::execute(Agent * agent, float deltaTime)
		{
			//If a path exists then follow it, return running/success?
			return agent->followPath(deltaTime);
		}
		/////////////////////////////////////////////////////////////////////////////////////////////////
		Flee::Flee(Agent * target, float fleeRange) :
			m_target(target), m_fleeRange(fleeRange) {}
		eResult Flee::execute(Agent * agent, float deltaTime)
		{
			//Set the desired path to where the target is.... but reversed
			auto fleeVec = pkr::Vector2::normalise(agent->pos - m_target->pos) /** agent->getSpeed()*/;
			auto fleePos = agent->pos + fleeVec;
			agent->setDesiredPos(fleePos);
			return eResult::SUCCESS;
		}
		/////////////////////////////////////////////////////////////////////////////////////////////////
		eResult UpdateState::execute(Agent * agent, float deltaTime)
		{
			//Just change the agent's state to the desired state
			agent->state = m_desiredState;
			return eResult::SUCCESS;
		}
		/////////////////////////////////////////////////////////////////////////////////////////////////
		eResult UpdateLastSeen::execute(Agent * agent, float deltaTime)
		{		
			agent->setLastSeen(m_target->pos);
			return eResult::SUCCESS;
		}
		/////////////////////////////////////////////////////////////////////////////////////////////////
		eResult ClearLastSeen::execute(Agent * agent, float deltaTime)
		{
			agent->clearLastSeen();
			return eResult::SUCCESS;
		}
		/////////////////////////////////////////////////////////////////////////////////////////////////
		eResult CalculatePath::execute(Agent * agent, float deltaTime)
		{
			//Get desired world position from agent
			auto desiredPos = agent->getDesiredPos();

			//// Find the correct destination and starting tiles ////
			//DESTINATION TILE
			desiredPos = m_map->clampWithinMapRetWORLD(desiredPos);		//Restrict desiredPos within the bounds of the map
			auto endTile = m_map->findTileFromPos(desiredPos);

			//This ensures endTile will be valid ie. NOT a untraversable tile
			float searchRadius = 120.f; 
			while (!endTile->objects.empty()) {
				endTile = m_map->findTileFromPos(desiredPos, searchRadius);
				searchRadius += 20.0f;
				if (searchRadius > 2000.0f)
					assert(false);		//Search area getting too large;
			}

			//START TILE
			pf::Path desiredPath;
			pf::Tile* startTile = m_map->findTileFromPos(agent->pos);
			if (!startTile->objects.empty()) {	//If agent is on an untraversable tile
				//Expand the search until a traversable tile is found
				float searchRadius = 120.f;
				do 	{
					startTile = m_map->findTileFromPos(agent->pos, searchRadius);
					searchRadius += 20.0f;
					if (searchRadius > 2000.0f)
						assert(false);		//Search area getting too large;
				} while (!startTile->objects.empty());
				//The path should move the agent out from the untraversable tile
				desiredPath = m_map->getAStarPath(startTile, endTile);
			}
			else { //Else the agent is on a traversable tile
				desiredPath = m_map->getAStarPath(startTile, endTile);
				//Set the first waypoint to the agent's current position so that
				//it doesn't move back to the tile centre
				desiredPath[0] = agent->pos;
			}

			//Set the agent's path
			agent->setPath(desiredPath);

#ifdef _DEBUG
////DEBUG
//ImGui::Begin("UpdatePath");
//ImGui::Text("desiredPos > x: %.2f, y: %.2f", desiredPos.x, desiredPos.y);
////ImGui::Text("endPos > x: %.2f, y: %.2f", endPos.x, endPos.y);
//ImGui::Text("endTile: %p", endTile);
//ImGui::Text("startTile: %p", startTile);
//ImGui::Text("desiredPath >");
//for (int i = 0; i < desiredPath.size(); ++i) {
//	ImGui::Text("%d: x: %.2f, y: %.2f", i, desiredPath[i].x, desiredPath[i].y);
//}
//ImGui::End();
#endif
			return eResult::SUCCESS;
		}

	}
}













/*
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
*/