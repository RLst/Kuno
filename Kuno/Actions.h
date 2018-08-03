//////////////////
//// Tony Le ////
// 2 Aug 2018 //
///////////////

#pragma once
#include "AI.h"
#include <pkr/Vector2.h>

namespace aie {
	class Input;
}

namespace ai {

	class Agent;
	class iBehaviour;

	namespace action {

	//// CONTROL AGENT BY INPUT ////
	class KeyboardControl : public iBehaviour		//Keyboard controller
	{
	private:
		aie::Input*		m_input;
		float			m_maxForce;
	public:
		KeyboardControl(aie::Input * input = aie::Input::getInstance(), float maxForce = 200.0f);
		eResult execute(Agent* agent, float deltaTime) override;
	};

	class MouseControl : public iBehaviour
	{
	private:
		aie::Input*		m_input;
		float			m_maxForce;
		pkr::Vector2	m_destination;
		float			m_arriveThreshold = 5.0f;			//Raw inits; adjust accordingly
		//float			m_arriveSmoothZone = 20.0f;
	public:
		MouseControl(aie::Input * input = aie::Input::getInstance(), float maxForce = 500.0f);
		eResult execute(Agent* agent, float deltaTime) override;
	};


	//// ENEMY AI Behaviours ////
	class Seek : public iBehaviour 
	{
	//This needs to take in a target agent
	private:
		Agent *			m_target;
		pkr::Vector2	m_destination;
		float			m_maxForce;
	public:
		Seek(Agent* target, float maxForce = 200.0f);		//Point based if target agent not specified
		//SeekAction(pkr::Vector2 destination, float maxLspeed = 200.0f);
		//~SeekAction() { delete m_target; }									//Destructor
		eResult execute(Agent* agent, float deltaTime) override;
	};


	////// Pathfinding ////
	//class PatrolSequence : public aComposite
	//{
	//	//If agent doesn't not have a patrol path
	//		//Get path
	//			//Look through paths
	//	//else
	//		//Seek towards next path step/node
	//};


	class Idle : public iBehaviour
	{
	private:
		Agent * m_agent;
	public:
		Idle() = default;
		~Idle() = default;
		eResult execute(Agent* agent, float deltaTime) override;
	};

	class Patrol : public iBehaviour		//MAYBE THIS NEEDS TO BE A COMPOSITE???
	{
	private:
		Agent *			m_pathAgent;
		float			m_maxForce;
	public:
		Patrol(Agent* pathObject, float maxForce = 200);
		~Patrol() { delete m_pathAgent; }
		eResult execute(Agent* agent, float deltaTime) override;
	};

	class Attack : public iBehaviour
	{
	private:
		Agent *			m_target;
		
	public:
		eResult			execute(Agent *agent, float deltaTime) override;

	};

	}
}