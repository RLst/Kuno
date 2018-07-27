#include "Agent.h"
#include <Vector2.h>
#include "AI.h"


namespace ai {

	//// Agent ////

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

	Agent::Agent(float maxForce, const pkr::Vector2 & startingPos) :
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
		//if (m_texture != nullptr) 
		//	delete m_texture;
	}

	void Agent::addBehaviour(iBehaviour * behaviour)
	{
		m_behaviours.push_back(behaviour);
	}

	void Agent::addForce(const pkr::Vector2 & force)
	{
		m_force += force;
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
		//Draw agent as a coloured circle
		renderer->setRenderColour(m_colour.r, m_colour.g, m_colour.b);
		renderer->drawCircle(m_pos.x, m_pos.y, m_size);
	}

}