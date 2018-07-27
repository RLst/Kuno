#pragma once

#include <vector>
#include <Vector2.h>
#include <Vector3.h>
#include "PF.h"

namespace aie {
	class Texture;
}

namespace ai {

	class iBehaviour;

	////Agents
	class Agent
	{
	protected:
		std::vector<iBehaviour*> m_behaviours;

		//Some basic transformation data
		float					m_maxForce;
		pkr::Vector2			m_force;
		pkr::Vector2			m_accel;
		pkr::Vector2			m_vel;
		pkr::Vector2			m_pos;

		//Circle agent
		float					m_size = 0;
		pkr::Vector3			m_colour;

		//Texture agent
		aie::Texture*			m_texture = nullptr;

		//Path Following
		int						m_currentWaypointIndex;	//???Is this right?
		std::vector<pkr::Vector2>* m_currentPath;
		float					m_waypointSearchRadius;
		pkr::Vector2			pathFollowing();

	public:
		//Agent(const Agent &other);		//Copy

		Agent(float maxForce = 200.0f, const pkr::Vector2 &startingPos = pkr::Vector2(300, 300));	//Standard

		Agent(float circleSize, const pkr::Vector3 &colour = pkr::Vector3(1, 1, 1), const pkr::Vector2 &startingPos = pkr::Vector2(300, 300));	//Circle agent constructor

		Agent(aie::Texture* agentTexture, const pkr::Vector2 &startingPos = pkr::Vector2(300, 300));		//Texture agent
		virtual ~Agent();	//Destructor 

		//Add
		void				addBehaviour(iBehaviour* behaviour);
		void				addForce(const pkr::Vector2 &force);

		//State accessors
		pkr::Vector2		getPos() const { return m_pos; }

		//Core
		void				update(float deltaTime);
		void				draw(aie::Renderer2D* renderer);
	};


}