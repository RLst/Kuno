//////////////////
//// Tony Le ////
// 2 Aug 2018 //
///////////////

#pragma once

#include <vector>
#include <pkr/Vector2.h>
#include <pkr/Vector3.h>
#include "PF.h"
#include "AI.h"

namespace aie {
	class Texture;
}

namespace ai {

	class iBehaviour;

	////Agents
	class Agent
	{
	private:
		friend class		iBehaviour;

		//Base Agent ie. if nothing inherits this, default sprite of agent is a circle
		float				m_size;
		pkr::Vector3		m_colour;

	protected:
		std::vector<iBehaviour*> m_behaviours;

		pkr::Vector2		m_cPos;				//px; CANVAS (Isometric)

		//Damage
		float				m_health = 100;		
		float				m_attack;			//The amount of damage this agent

		//pkr::Vector2		m_force;
		//pkr::Vector2		m_accel;
		//pkr::Vector2		m_vel;
		float				m_facing = 0;		//Where the agent is looking at

		//Speeds
		float				m_sneakSpeed =	100;
		float				m_walkSpeed =	200;
		float				m_runSpeed =	300;
		float				m_maxSpeed =	400;

		//Last seen enemy's position
		pkr::Vector2		m_lastSeenPos;
		bool				m_lastSeenAvail = false;

		//Pathfinding
		pf::Path			m_path;
		pkr::Vector2		m_desiredPos = pkr::Vector2();	//UpdatePath will use this to create a path

	public:
		enum class eState
		{
			NORMAL,
			STEALTH,
			PATROL,
			SUSPICIOUS,
			ALERT,
		};

		eState				state = eState::ALERT;
		pkr::Vector2		pos;				//WORLD

	public:
		//Agent(const Agent &other);	//Copy
		virtual ~Agent();				//Destructor 			
		Agent(float circleSize = 25.0f, const pkr::Vector3 &colour = { 0.75f, 0.75f, 0.75f }, const pkr::Vector2 &startingPos = { 300, 300 });

		//Behaviours
		void				addBehaviour(iBehaviour* behaviour);

		//Translation
		void				move(const pkr::Vector2 &speed, float deltaTime);				//For debug; Move in world coordinates
		void				moveOnCanvas(const pkr::Vector2 &speed, float deltaTime);		//For debug; Move on the canvas itself
		void				seek(const pkr::Vector2 &target, float deltaTime);

		//// Accessors ////
		//Speed
		void				setSneakSpeed(float sneakSpeed) { m_sneakSpeed = sneakSpeed; }
		void				setWalkSpeed(float walkSpeed) { m_walkSpeed = walkSpeed; }
		void				setRunSpeed(float runSpeed) { m_runSpeed = runSpeed; }
		float				getSpeed() const;

		//Health & Attack
		float				getHealth() const { return m_health; }
		void				takeDamage(float attack) { m_health -= attack; }
		float				getAttack() const { return m_attack; }
		bool				isAlive() { return m_health > 0; }

		//Last seen
		bool				isLastSeenAvailable() const { return m_lastSeenAvail; }
		void				setLastSeen(pkr::Vector2 lastSeenPos);
		void				clearLastSeen() { m_lastSeenAvail = false; }

		//Pathfinding
		eResult				followPath(float deltaTime);						
		void				setPath(const pf::Path path) { m_path = path; }
		pf::Path			getPath() const { return m_path; }
		pkr::Vector2		getDesiredPos() const { return m_desiredPos; }
		void				setDesiredPos(pkr::Vector2 desiredPos) { m_desiredPos = desiredPos; }

		//Core
		virtual void		update(float deltaTime);
		virtual void		draw(aie::Renderer2D* renderer);		//Agent drawn as a circle; this only runs if a sprite object does not override
	};


	class Avatar : public Agent
		//Gives the agent a sprite or animation (from spritesheets)
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