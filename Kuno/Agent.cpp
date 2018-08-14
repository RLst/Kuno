//////////////////
//// Tony Le ////
// 2 Aug 2018 //
///////////////

#include "Agent.h"
#include <pkr\Vector2.h>
#include "AI.h"
#include "KunoApp.h"

#include "imgui.h"

namespace ai {

	Agent::Agent(float circleSize, const pkr::Vector3 & colour, const pkr::Vector2 & startingPos) :
		m_size(circleSize),
		m_colour(colour),
		pos(startingPos) {}

	Agent::~Agent()
	{
		//Behaviours
		//for (auto behaviour : m_behaviours) {
		//	if (behaviour != nullptr)
		//		delete behaviour;			//Do the behaviours have to be deleted?
		//	//behaviour = nullptr;
		//}
	}

	void Agent::addBehaviour(iBehaviour * behaviour)
	{
		m_behaviours.push_back(behaviour);
	}

	void Agent::move(const pkr::Vector2 & speed, float deltaTime)
	{
		//accel = force / mass;
		//vel = vel + accel * deltaTime;
		//pos = pos + vel * deltaTime;

		pos += speed * deltaTime;
	}

	void Agent::moveOnCanvas(const pkr::Vector2 & speed, float deltaTime)
	{
		pos += KunoApp::Instance()->CoordConverter()->CanvasToWorld(speed) * deltaTime;
	}

	void Agent::seek(const pkr::Vector2 & target, float deltaTime)
	{
		auto seekVec = pkr::Vector2::normalise(target - pos) * getSpeed();		//Get speed auto adjusts for agent's state ie. NORMAL = walk, ALERT = run
		move(seekVec, deltaTime);
	}

	eResult Agent::followPath(float deltaTime)
	{
		//If there is an available path
		if (m_path.isAvailable()) 
		{
			////// ONLY THE FIRST WAYPOINT ////
			//if (m_path.index == 0 && m_path.size() > 1) {
			//	//Skip the first waypoint and go directly to the second waypoint
			//	//that way the agent doesn't return back to the centre of the it's on
			//	//because that looks jerky
			//	//PROBLEM1: If the agent goes through a unconnected zone it gets stuck
			//	//TRY: 
			//	m_path.next();
			//	//seek(m_path[1], deltaTime);
			//	return SUCCESS;
			//}

			//// END OF PATH REACHED ////
			if (m_path.endReached())
			{
				//Reset and return success
				this->m_isMoving = false;
				m_path.reset();
				return SUCCESS;
			}

			//// A WAYPOINT REACHED ////
			if (pkr::Vector2::distance(pos, m_path.getWaypoint()) < m_path.radius)
			{
				//Increment current waypoint index and return running
				m_path.next();
				return SUCCESS;
				//return RUNNING;
			}
			else
			{
				//The agent is in between waypoints (PROBABLY)
				//so move agent towards next waypoint
				seek(m_path.getWaypoint(), deltaTime);
				return SUCCESS;
				//return RUNNING;
			}
		}
		//Path not available
		return FAILURE;
	}


	float Agent::getSpeed() const
	{
		switch (state) {
		case eState::NORMAL:
			return m_walkSpeed; break;
		case eState::STEALTH:
			return m_sneakSpeed; break;
		case eState::PATROL:
			return m_walkSpeed; break;
		case eState::SUSPICIOUS:
			return m_walkSpeed; break;
		case eState::ALERT:
			return m_runSpeed; break;
		default:
			return m_maxSpeed; //Temp
		}
	}

	void Agent::setLastSeen(pkr::Vector2 lastSeenPos)
	{
		m_lastSeenPos = lastSeenPos;
		m_lastSeenAvail = true;		//Automatically sets last seen flag
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
		auto app = KunoApp::Instance();
		m_cPos = app->CoordConverter()->WorldToCanvas(pos);			//Convert agents coords to isometric
		auto depth = app->DepthSorter()->getSortDepth(m_cPos.y);					//Sort drawing depth of agent

		renderer->setRenderColour(m_colour.r, m_colour.g, m_colour.b);
		renderer->drawCircle(m_cPos.x, m_cPos.y + m_size, m_size, depth);	//By default draw agent as a coloured circle

#ifdef _DEBUG
		ImGui::Begin("DEBUG: Agent");
		ImGui::Text("pos > x:%.2f, y:%.2f", pos.x, pos.y);
		ImGui::Text("health > %.0f", m_health);
		ImGui::Text("lastSeen > x:%.0f, y:%.0f", m_lastSeenPos.x, m_lastSeenPos.y);
		ImGui::Text("desiredPos > x:%.2f, y:%.2f", m_desiredPos.x, m_desiredPos.y);
		ImGui::Text("state > ", state);
		ImGui::End();
#endif // _DEBUG

	}

}