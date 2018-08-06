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

	////Agents
	class Agent
	{
	protected:
		std::vector<iBehaviour*> m_behaviours;

		//Some basic transformation data
		float				m_maxForce;
		//pkr::Vector2		m_force;
		//pkr::Vector2		m_accel;
		//pkr::Vector2		m_vel;
		pkr::Vector2		m_pos;				//WORLD
		pkr::Vector2		m_cPos;				//px; CANVAS (Isometric)

		//Circle agent
		float				m_size;
		pkr::Vector3		m_colour;

		//Path Following
		int					m_currentWaypointID;	//???Is this right?
		pf::Path*			m_path;
		float				m_pathRadius;
		//bool				m_isPatrolling = false;
		//int				m_pathingDirection;
		//pkr::Vector2		followPath();

	public:
		//Agent(const Agent &other);	//Copy
		virtual ~Agent();				//Destructor 
		Agent(float circleSize = 25.0f, const pkr::Vector3 &colour = { 0.75f, 0.75f, 0.75f }, const pkr::Vector2 &startingPos = { 300, 300 });

		//Behaviours
		void				addBehaviour(iBehaviour* behaviour);
		//iBehaviour		getBehaviour(iBehaviour* behaviour);	//How to get ie. the FollowPath behaviour so I can change it's working path?

		//Translation
		void				move(const pkr::Vector2 &speed, float deltaTime);				//Move in world coordinates
		void				moveOnCanvas(const pkr::Vector2 &speed, float deltaTime);		//Move in pixels on the canvas itself
		void				seek(const pkr::Vector2 &target, float deltaTime);

		//State accessors
		pkr::Vector2		getPos() const { return m_pos; }			//Get world position
		pkr::Vector2		getCpos() const { return m_cPos; }			//Get canvas position
		float				getMaxSpeed() const { return m_maxForce; }

		//Pathfinding
		pf::Path*			getPath() const { return m_path; }
		void				setPath(pf::Path* path) { m_path = path; }
		//void				setPatrolling(bool patrolState) { m_isPatrolling = patrolState; }

		//Core
		virtual void		update(float deltaTime);
		virtual void		draw(aie::Renderer2D* renderer);		//Agent drawn as a circle; this only runs if a sprite object does not override
	
		//Allow access to parent methods (

	};


	class Character : public Agent
	{
	private:
		//Textures
		aie::Texture*		m_tex;

		//Extra translations
		pkr::Vector2		m_facing;		//normalised vec; where the character is facing

	public:
		pkr::Vector2		getFacing() const { return m_facing; }

		//Core
		void				update(float deltaTime) override;
		void				draw(aie::Renderer2D* renderer) override;
	};

}