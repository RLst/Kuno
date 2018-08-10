//////////////////
//// Tony Le ////
// 2 Aug 2018 //
///////////////

#pragma once

#include <vector>
#include <pkr/Vector2.h>
#include <pkr/Vector3.h>
#include "PF.h"

namespace aie {
	class Texture;
}

namespace ai {

	class iBehaviour;

	//enum class eEnemyState
	//{
	//	PATROL,
	//	SUSPICIOUS,
	//	ALERT
	//};

	//enum class ePlayerState 
	//{
	//	NORMAL,
	//	STEALTH
	//};

	////Agents
	class Agent
	{
	private:
		friend class		iBehaviour;

	protected:
		std::vector<iBehaviour*> m_behaviours;

		pkr::Vector2		m_cPos;				//px; CANVAS (Isometric)
		//pkr::Vector2		m_force;
		//pkr::Vector2		m_accel;
		//pkr::Vector2		m_vel;
		float				m_health = 10;

		//// PATHFINDING ////
		int					m_currentWaypointID;	//???Is this right?
		pf::Path			m_path;
		float				m_pathRadius = 5.0f;

		//Circle agent only (if nothing inherits this, will default to a circle being drawn)
		float				m_size;
		pkr::Vector3		m_colour;

		//Flags
		bool				m_lastSeenAvailable = false;		//NOT IDEAL

	public:
		enum class eState
		{
			NORMAL,
			STEALTH,
			PATROL,
			SUSPICIOUS,
			ALERT,
		};

		eState				state;
		pkr::Vector2		pos;				//WORLD
		float				m_facing = 0;		//Where the agent is looking at
		float				m_maxSpeed = 400;

	public:
		//Agent(const Agent &other);	//Copy
		virtual ~Agent();				//Destructor 
		Agent(float circleSize = 25.0f, const pkr::Vector3 &colour = { 0.75f, 0.75f, 0.75f }, const pkr::Vector2 &startingPos = { 300, 300 });

		//Behaviours
		void				addBehaviour(iBehaviour* behaviour);

		//Translation
		void				move(const pkr::Vector2 &speed, float deltaTime);				//Make this private later; Move in world coordinates
		void				moveOnCanvas(const pkr::Vector2 &speed, float deltaTime);		//Move in pixels on the canvas itself
		void				seek(const pkr::Vector2 &target, float deltaTime);

		//Accessors
		//pkr::Vector2		getPos() const { return m_pos; }			//Get world position
		//pkr::Vector2		getCpos() const { return m_cPos; }			//Get canvas position
		//float				getMaxSpeed() const { return m_maxSpeed; }
		//STATE				getState() const { return m_state; }
		float				getHealth() const { return m_health; }
		void				takeDamage(float damage) { m_health -= damage; }
		bool				isLastSeenAvailable() const { return m_lastSeenAvailable; }
		void				setLastSeenAvailable(bool set) { m_lastSeenAvailable = set; }

		////Pathfinding
		bool				moveByPath(const pf::Path &path, float deltaTime);		//Returns true if reached the end of the path?
		bool				followPath(float deltaTime);
		void				setPath(pf::Path path) { m_path = path;	}
		pf::Path			getPath() const { return m_path; }

		//Core
		virtual void		update(float deltaTime);
		virtual void		draw(aie::Renderer2D* renderer);		//Agent drawn as a circle; this only runs if a sprite object does not override
	
	};


	class Character : public Agent
	{
	private:
		//Textures
		aie::Texture*		m_tex;

	public:
		//Core
		void				update(float deltaTime) override;
		void				draw(aie::Renderer2D* renderer) override;
	};

}