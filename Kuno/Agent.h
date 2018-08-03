//////////////////
//// Tony Le ////
// 2 Aug 2018 //
///////////////

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
		//pkr::Vector2			m_force;
		//pkr::Vector2			m_accel;
		pkr::Vector2			m_vel;
		pkr::Vector2			m_cPos;			//px; Cartesian
		pkr::Vector2			m_iPos;			//px; Isometric

		//Circle agent
		float					m_size;
		pkr::Vector3			m_colour;

		//Path Following
		int						m_currentWaypointIndex;	//???Is this right?
		std::vector<pkr::Vector2*> m_currentPath;
		float					m_waypointSearchRadius;
		pkr::Vector2			pathFollowing();

	public:
		//Agent(const Agent &other);	//Copy
		virtual ~Agent();				//Destructor 
		Agent(float circleSize = 25.0f, 
			const pkr::Vector3 &colour = { 0.75f, 0.75f, 0.75f },
			const pkr::Vector2 &startingPos = { 300, 300 });

		//Behaviours
		void				addBehaviour(iBehaviour* behaviour);

		//Translation
		void				move(const pkr::Vector2 &lSpeed, float deltaTime);			//Linear move (instant vel/accel)
		void				moveIso(const pkr::Vector2 &lSpeed, float deltaTime);		//Linear move in isometric

		//State accessors
		pkr::Vector2		getPos() const { return m_iPos; }
		pkr::Vector2		getVel() const { return m_vel; }

		//Core
		void				update(float deltaTime);
		virtual void		draw(aie::Renderer2D* renderer);		//Agent drawn as a circle; this only runs if a sprite object does not override
	
		//Allow access to parent methods (

	};


	class Character : public Agent
	{
	private:
		pkr::Vector2		m_facing;		//normalised vec; where the character is facing

	public:
		pkr::Vector2		getFacing() const { return m_facing; }
	};

}