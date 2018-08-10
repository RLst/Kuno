//////////////////
//// Tony Le ////
// 2 Aug 2018 //
///////////////

#pragma once
#include "AI.h"
#include "PF.h"
#include "Map.h"
#include <pkr/Vector2.h>

namespace aie {
	class Input;
}

namespace ai {

	class Agent;
	class iBehaviour;

	namespace action {

	//// CONTROL AGENT BY INPUT ////
	class KeyboardControl : public iBehaviour	//DEBUG
	{
	private:
		aie::Input*		m_input;
		float			m_maxForce;
	public:
		KeyboardControl(aie::Input * input = aie::Input::getInstance(), float maxForce = 200.0f);
		eResult execute(Agent* agent, float deltaTime) override;
	};

	//////////////////////////////////////////////////////////////////////////////////////////////////
	class MouseControl : public iBehaviour		//DEBUG
	{
	private:
		aie::Input*		m_input;
		float			m_maxSpeed;
		pkr::Vector2	m_dest;								//WORLD
		float			m_arriveThreshold = 5.0f;			//Raw inits; adjust accordingly
	public:
		MouseControl(aie::Input * input = aie::Input::getInstance(), float maxForce = 500.0f);
		eResult execute(Agent* agent, float deltaTime) override;
	};
	/////////////////////////////////////////////////////////////////////////////////////////////////
	class MouseLeftClicked : public iBehaviour	//DEBUG
	{
		aie::Input*		m_input;
	public:
		MouseLeftClicked(aie::Input * input = aie::Input::getInstance()) :
			m_input(input) {}
		eResult execute(Agent* agent, float deltaTime) override 
		{
			if (m_input->wasMouseButtonPressed(aie::INPUT_MOUSE_BUTTON_LEFT)) {
				return SUCCESS;
			}
			else
				return FAILURE;
		}
	};

	//////////////////////////////////////////////////////////////////////////////////////////////////
	class Seek : public iBehaviour 
	{
	//This needs to take in a target agent
	private:
		Agent *			m_target = nullptr;
		pkr::Vector2	m_dest;										//WORLD
		float			m_maxSpeed;
		float			m_arriveRadius = 20.0f;					//Raw inits; adjust accordingly
	public:
		~Seek() = default;											//Destructor
		Seek(Agent* target, float maxSpeed = 200.0f);				//Point based if target agent not specified
		Seek(pkr::Vector2 destination, float maxSpeed = 200.0f);

		//Modify
		void			setTarget(Agent* agent) { m_target = agent; }
		void			setDestination(pkr::Vector2 destination) { m_dest = destination; }
		void			setMaxSpeed(float maxSpeed) { m_maxSpeed = maxSpeed; }
		void			setArriveRadius(float arriveRadius) { m_arriveRadius = arriveRadius; }

		//Core
		eResult execute(Agent* agent, float deltaTime) override;
	};

	//////////////////////////////////////////////////////////////////////////////////////////////////
	class SeekToPoint : public iBehaviour
	{
	private:

	public:
		~SeekToPoint() = default;
		SeekToPoint() = default;
	};

	//////////////////////////////////////////////////////////////////////////////////////////////////
	class SeekAndArrive : public iBehaviour
	{
		Agent *			m_target = nullptr;
		pkr::Vector2	m_dest;										//WORLD
		float			m_maxSpeed;
		float			m_slowZone = 50.0f;			//radius; raw; adjust accordingly
		float			m_arriveZone = 2.0f;		//radius, raw; adjust accordingly
	public:
		~SeekAndArrive() = default;											//Destructor
		SeekAndArrive(Agent* target, float maxSpeed = 200.0f);				//Point based if target agent not specified
		SeekAndArrive(pkr::Vector2 destination, float maxSpeed = 200.0f);

		//Modify
		void			setTarget(Agent* agent) { m_target = agent; }
		void			setDestination(pkr::Vector2 destination) { m_dest = destination; }
		void			setMaxSpeed(float maxSpeed) { m_maxSpeed = maxSpeed; }
		void			setArriveRadius(float arriveRadius) { m_slowZone = arriveRadius; }

		//Core
		eResult execute(Agent* agent, float deltaTime) override;
	};

	//////////////////////////////////////////////////////////////////////////////////////////////////
	class Idle : public iBehaviour
	{
	private:
		Agent * m_agent;
	public:
		Idle() = default;
		~Idle() = default;
		eResult execute(Agent* agent, float deltaTime) override;
	};

	//////////////////////////////////////////////////////////////////////////////////////////////////
	class PatrolPath : public iBehaviour		//MAYBE THIS NEEDS TO BE A COMPOSITE???
	{
	private:
		Agent *			m_pathAgent;
		float			m_maxForce;
	public:
		PatrolPath(Agent* pathObject, float maxForce = 200);
		~PatrolPath() { delete m_pathAgent; }
		eResult execute(Agent* agent, float deltaTime) override;
	};

	//////////////////////////////////////////////////////////////////////////////////////////////////
	class Attack : public iBehaviour
	{
	private:
		Agent * m_target;
	public:
		eResult	execute(Agent *agent, float deltaTime) override;
	};
	/////////////////////////////////////////////////////////////////////////////////////////////////
	class GetNextPathWaypoint : public iBehaviour 
	{
	private:
		pf::Path*		m_path;		//?

	public:

		
	};
	/////////////////////////////////////////////////////////////////////////////////////////////////
	class FollowPath : public iBehaviour
	{
	private:
		pf::Path*		m_path;
		int				m_currentWaypoint = 0;			//std::vector index; -1 means pathfollowing has not started yet
		float			m_pathRadius;					//Should make a class Path and put this together; To smoooth the pathfinding a bit
	public:
		FollowPath(float pathRadius = 10.0f);
		~FollowPath() = default;

		eResult			execute(Agent *agent, float deltaTime) override;

		//Test
		void			setPath(pf::Path* path) { m_path = path; }
	};
	/////////////////////////////////////////////////////////////////////////////////////////////////
	class Flee : public iBehaviour
	{
	protected:
		pf::Map*	m_map;
		pf::Path	m_path;
		Agent *		m_target;
		float		m_fleeRange;
	public:
		Flee() = default;
		Flee(Agent* target, pf::Map* map, float fleeRange = 400);
		//Flee(Agent* target, float fleeRange);
		eResult		execute(Agent *agent, float deltaTime) override;
		void		getPath(Agent* agent, pkr::Vector2 destination);
	};
		//////////////////////////////////////////////////////////////////////////////////////////////////
		class UpdateState : public iBehaviour
		{
			//Changes the state of the agent to a set state
		private:
			ai::Agent::eState		m_desiredState;

		public:
			UpdateState(ai::Agent::eState desiredState) : m_desiredState(desiredState) { /*m_desiredState = desiredState;*/ }
			~UpdateState() = default;
			eResult execute(Agent* agent, float deltaTime) override;
		};
		//////////////////////////////////////////////////////////////////////////////////////////////////
		class UpdateLastSeen : public iBehaviour
		{
			//Stores the last seen position of target agent
		private:
			pkr::Vector2	m_lastSeen;
			bool			m_isAvailable;		//Last seen exist; NOT SURE IF THIS IS NEEDED

		public:
			UpdateLastSeen() = default;
			~UpdateLastSeen() = default;
			eResult execute(Agent* agent, float deltaTime) override;
		};
		//////////////////////////////////////////////////////////////////////////////////////////////////


	}
}