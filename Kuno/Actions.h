//////////////////
//// Tony Le ////
// 2 Aug 2018 //
///////////////

#pragma once
#include "AI.h"
#include "PF.h"
#include "Map.h"
#include <pkr/Vector2.h>
#include "Agent.h"

namespace aie {
	class Input;
}

namespace ai {

	class Agent;
	class iBehaviour;

	namespace action {
		//// TEST BEHAVIOURS ////
		/////////////////////////////////////////////////////////////////////////////////////////////////
		class tKeyboardControl : public iBehaviour	//DEBUG
		{
		private:
			aie::Input*		m_input;
			float			m_maxForce;
		public:
			tKeyboardControl(aie::Input * input = aie::Input::getInstance(), float maxForce = 200.0f);
			eResult execute(Agent* agent, float deltaTime) override;
		};

		//////////////////////////////////////////////////////////////////////////////////////////////////
		class tMouseControl : public iBehaviour		//DEBUG
		{
		private:
			aie::Input*		m_input;
			float			m_maxSpeed;
			pkr::Vector2	m_dest;								//WORLD
			float			m_arriveThreshold = 5.0f;			//Raw inits; adjust accordingly
		public:
			tMouseControl(aie::Input * input = aie::Input::getInstance(), float maxForce = 500.0f);
			eResult execute(Agent* agent, float deltaTime) override;
		};
		/////////////////////////////////////////////////////////////////////////////////////////////////
		class tMouseSetDesiredPos : public iBehaviour
		{
		private:
			aie::Input*		m_input;
		public:
			~tMouseSetDesiredPos() = default;
			tMouseSetDesiredPos(aie::Input* input = aie::Input::getInstance());
			eResult execute(Agent* agent, float deltaTime) override;
		};

		/////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////////////
		class MouseLeftClicked : public iBehaviour
		{
			aie::Input*		m_input;
		public:
			MouseLeftClicked(aie::Input * input = aie::Input::getInstance()) :
				m_input(input) {}
			eResult execute(Agent* agent, float deltaTime) override
			{
				if (m_input->wasMouseButtonPressed(aie::INPUT_MOUSE_BUTTON_LEFT)) {
					return eResult::SUCCESS;
				}
				else
					return eResult::FAILURE;
			}
		};
		//////////////////////////////////////////////////////////////////////////////////////////////////
		class Attack : public iBehaviour
		{
		private:
			Agent * m_target;
		public:
			Attack(Agent* target) : m_target(target) {}
			~Attack() = default;
			eResult	execute(Agent *agent, float deltaTime) override;
		};
		//////////////////////////////////////////////////////////////////////////////////////////////////
		class Idle : public iBehaviour
			//MAYBE THIS SHOULD BE HEADED BY A TIMEOUT DECORATOR
			//Agent idles; for basic implementation, do nothing
		{
		private:
			float		m_minTime;
			float		m_maxTime;
			float		m_duration = 0;
			float		m_timeout;
		public:
			Idle(float minIdleTime, float maxIdleTime);
			~Idle() = default;
			eResult execute(Agent* agent, float deltaTime) override;
		};
		/////////////////////////////////////////////////////////////////////////////////////////////////
		class Flee : public iBehaviour
		{
		private:
			Agent *		m_target = nullptr;
			//float		m_fleeRange;
		public:
			~Flee() = default;
			Flee(Agent* target);
			eResult		execute(Agent *agent, float deltaTime) override;
		};
		/////////////////////////////////////////////////////////////////////////////////////////////////
		class FollowPath : public iBehaviour
			//HOW TO UTILISE:
			//- Add this behaviour LAST to the main selector
			//It will return SUCCESS unless there's no path, 
			//that way it won't be saved as a pending child and can be interrupted
		{
		public:
			FollowPath() = default;
			~FollowPath() = default;
			eResult			execute(Agent *agent, float deltaTime) override;
		};
		//////////////////////////////////////////////////////////////////////////////////////////////////
		class Seek : public iBehaviour
		{
			/*Requirements:
			1. target agent*, where/what to seek
			1a. target path*?, where to seek
			2. agent speed can be access in agent
			3. arriveRadius.. some default value, can be customized thru constructor... no big deal
			*/
		private:
			Agent *		m_target = nullptr;
			float		m_maxSpeed;
			float		m_arriveRadius;						//Raw inits; adjust accordingly
		public:
			~Seek() = default;											//Destructor
			Seek(Agent* target, float arriveRadius = 20.0f);
			eResult execute(Agent* agent, float deltaTime) override;

			//Modify
			//void			setTarget(Agent* agent) { m_target = agent; }
			//void			setDestination(pkr::Vector2 destination) { m_dest = destination; }
			//void			setMaxSpeed(float maxSpeed) { m_maxSpeed = maxSpeed; }
			//void			setArriveRadius(float arriveRadius) { m_arriveRadius = arriveRadius; }
		};
		//////////////////////////////////////////////////////////////////////////////////////////////////
		class Pursue : public iBehaviour
			//This can't really be implemented unless the agents are moving using linear motion
			//Need the agent's current speed to be able to pursue
			//Use Seek instead
		{
		private:
			Agent * m_target = nullptr;
		public:
			Pursue(Agent* target);
			~Pursue() = default;
			eResult execute(Agent* agent, float deltaTime) override;
		};
		//////////////////////////////////////////////////////////////////////////////////////////////////
		class UpdateState : public iBehaviour
		{
			//Changes the state of the agent to a desired state stored in this behaviour node
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
			//Sets the last position the agent had seen the target agent
		private:
			Agent *			m_target = nullptr;
		public:
			UpdateLastSeen(Agent* target) : m_target(target) {}
			~UpdateLastSeen() = default;
			eResult execute(Agent* agent, float deltaTime) override;
		};
		//////////////////////////////////////////////////////////////////////////////////////////////////
		class ClearLastSeen : public iBehaviour
		{
		public:
			ClearLastSeen() = default;
			~ClearLastSeen() = default;
			eResult execute(Agent* agent, float deltaTime) override;
		};
		//////////////////////////////////////////////////////////////////////////////////////////////////
		class CalculatePath : public iBehaviour
			/*Changes the agent's path and sets it to available so the agent can start pathing
			Requires: 
				&KunoApp::m_map

			Enemy Logic:
			1. agent(enemy) wants to move to a position on the map
			2. Finds the Map's equivalent tile/node using Map::findTileFromPos()
			3. Sends this tile as the destination tile/node into Map::getAstarPath() and retrieves desired path
			4. Desired path is then stored in Agent object, ready for agent to follow/use it

			Player Logic:
			1. User clicks on an canvas position that corresponds the an area on the map
			2. Mouse canvas position is directly converted to a corresponding map tile/node* OR
			Mouse canvas position is converted to world position
			3. Pass this tile* as destination tile into Map::getAStarPath() and retrieve desired path
			4. Desired path is then stored in Agent object, ready for agent to follow

			Steps 2, 3 and 4 are basically the same and will be encapsulated in this class

			Improvements:
			Agent object should have a ptr to Path, passes the pointer into getAStarPath(), 
			which getAstar will directly modify

			//1. Where will the initial path be stored? In Map I think..
			//2. This will take in a desired path ie. from the Map
			*/			
		{
			pf::Map*		m_map;
		public:
			~CalculatePath() = default;
			CalculatePath(pf::Map* map) : m_map(map) {}
			eResult execute(Agent* agent, float deltaTime) override;
		};
		//////////////////////////////////////////////////////////////////////////////////////////////////
		class ReturnToPost : public iBehaviour
			//Simply returns to the first waypoint in patrol path
		{
		public:
			~ReturnToPost() = default;
			ReturnToPost() = default;
			eResult execute(Agent* agent, float deltaTime) override;
		};

	}
}







/*
BRAINSTORM:
Transform/move behaviours constructors
To allow ie. a Seek behaviour to not only seek an agent but also a path object etc
Move(Agent* targetAgent)	//Setup behaviour that uses another agent
Move(Path* anAgentsPath)	//Setup behaviour that uses a path

//////////////////////////////////////////////////////////////////////////////////////////////////
class PatrolPath : public iBehaviour		//MAYBE THIS NEEDS TO BE A COMPOSITE???
{
private:
Agent * m_pathAgent;
float			m_maxForce;
public:
PatrolPath(Agent* pathObject, float maxForce = 200);
~PatrolPath() { delete m_pathAgent; }
eResult execute(Agent* agent, float deltaTime) override;
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


*/