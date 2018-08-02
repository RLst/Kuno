//////////////////
//// Tony Le ////
// 2 Aug 2018 //
///////////////

#include "Agent.h"
#include <Vector2.h>
#include "AI.h"
#include "KunoApp.h"

namespace ai {

	//Agent::Agent(const Agent & other) :		//Copy constructor
	//	m_behaviours(other.m_behaviours),
	//	m_maxForce(other.m_maxForce),
	//	m_force(other.m_force),
	//	m_accel(other.m_accel),
	//	m_vel(other.m_vel),
	//	m_pos(other.m_pos),
	//	m_size(other.m_size),
	//	m_colour(other.m_colour),
	//	m_texture(other.m_texture),
	//	m_currentWaypointIndex(other.m_currentWaypointIndex),
	//	m_currentPath(other.m_currentPath),
	//	m_waypointSearchRadius(other.m_waypointSearchRadius)
	//{}

	Agent::Agent(float circleSize, const pkr::Vector3 & colour, const pkr::Vector2 & startingPos) :
		m_size(circleSize),
		m_colour(colour),
		m_cPos(startingPos) {}

	Agent::~Agent()
	{
		//Behaviours
		for (auto &behaviour : m_behaviours) {
			delete behaviour;			//Do the behaviours have to be deleted?
			behaviour = nullptr;
		}

		//Path
		for (auto &point : m_currentPath) {
			delete point;
			point = nullptr;
		}

	}

	void Agent::addBehaviour(iBehaviour * behaviour)
	{
		m_behaviours.push_back(behaviour);
	}

	void Agent::move(const pkr::Vector2 & lMove)
	{
		m_cPos += lMove;
	}

	void Agent::moveIso(const pkr::Vector2 & lMove)
	{
		m_cPos += KunoApp::Instance()->CoordConverter()->IsometricToCartesian(lMove);
	}


	pkr::Vector2 Agent::pathFollowing()
	{
		////Clear target way point
		//auto targetPoint = pkr::Vector2();

		////If there is an available path
		//if (!m_currentPath.empty()) {
		//	//Get the way points
		//	auto workingPath = m_currentPath;

		//	targetPoint = workingPath[m_currentWaypointIndex];

		//	//If agent has arrived at a waypoint
		//	if (pkr::Vector2::distance(m_pos, targetPoint) <= m_waypointSearchRadius) {
		//		++m_currentWaypointIndex;
		//		if (m_currentWaypointIndex >= workingPath.size()) {
		//			m_currentWaypointIndex = workingPath.size() - 1;
		//		}
		//	}
		//}

		//NOT FINISHED!!!
		return pkr::Vector2();		//Return NULL
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
		m_iPos = app->CoordConverter()->CartesianToIsometric(m_cPos);			//Convert agents coords to isometric
		auto depth = app->DepthSorter()->getSortDepth(m_iPos.y);					//Sort drawing depth of agent

		renderer->setRenderColour(m_colour.r, m_colour.g, m_colour.b);
		renderer->drawCircle(m_iPos.x, m_iPos.y + m_size, m_size, depth);	//By default draw agent as a coloured circle
	}

}