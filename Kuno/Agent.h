//////////////////
//// Tony Le ////
// 2 Aug 2018 //
///////////////

#pragma once

#include <vector>
#include <pkr\math\Vector2.h>
#include <pkr\math\Vector3.h>
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
		float				m_facing = 0;		//Where the agent is looking at

		//Speeds
		//float				m_dragCoeff;
		//pkr::Vector2		m_force;
		//pkr::Vector2		m_accel;
		//pkr::Vector2		m_vel;
		float				m_sneakSpeed =	100;
		float				m_walkSpeed =	200;
		float				m_runSpeed =	300;
		float				m_maxSpeed =	400;

		//Last seen enemy's position
		pkr::Vector2		m_lastSeenPos;
		bool				m_lastSeenAvail = false;

		//Pathfinding
		pf::Path			m_path;
		pf::Path			m_patrolPath;		//Only add one waypoint to set as a guard, +1 for patrolling
		pkr::Vector2		m_desiredPos = pkr::Vector2();		//UpdatePath will use this to create a path
		/////////////////////////////////////////////
		//// CRAP AND CLUNKY: WRITE BETTER CODE ////
		///////////////////////////////////////////
		//Flag that states whether or not the desired position is currently being seeked to or not
		bool				m_isMoving = false;
		/////////////////////////////////////////

	public:

		enum class eState
		{
			NORMAL,
			STEALTH,
			PATROL,
			GUARD,
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
		//void				addForce(const pkr::Vector2 & force, float deltaTime);
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
		void				setAttack(const float attack) { m_attack = attack; }
		bool				isAlive() { return m_health > 0; }

		//Last seen
		bool				isLastSeenAvailable() const { return m_lastSeenAvail; }
		void				setLastSeen(pkr::Vector2 lastSeenPos);
		pkr::Vector2		getLastSeen() const { return m_lastSeenPos; }
		void				clearLastSeen() { m_lastSeenAvail = false; }

		//Pathfinding
		bool				isMoving() const { return m_isMoving; }

		eResult				followPath(float deltaTime);						
		void				setPath(const pf::Path path) { m_path = path; }
		pf::Path			getPath() const { return m_path; }

		pf::Path			patrolPath() const { return m_patrolPath; }
		pf::Path&			patrolPath() { return m_patrolPath; }
		void				setPatrolPath(const pf::Path patrolPath) { m_patrolPath = patrolPath; }

		//bool				isGuardPostAvailable() const { return m_patrolPath.isAvailable(); }
		//pkr::Vector2		getPostPos() const { if (m_patrolPath.isAvailable()) return m_patrolPath[0]; }		//Need refinement ie. const and reference etc
		//void				setPostPos(const pkr::Vector2 guardPostPos) { if (m_patrolPath.isAvailable()) m_patrolPath[0] = guardPostPos; }

		pkr::Vector2		getDesiredPos() const { return m_desiredPos; }
		void				setDesiredPos(pkr::Vector2 desiredPos);		//Also sets the isMoving flag


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