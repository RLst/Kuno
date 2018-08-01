#pragma once
#include "AI.h"
#include <pkr/Vector2.h>

namespace aie {
	class Input;
}

namespace ai {

	class Agent;
	class iBehaviour;

	//// CONTROL AGENT BY INPUT ////
	class BasicController : public iBehaviour		//Keyboard controller
	{
	private:
		aie::Input*		m_input;
		float			m_lSpeedMax;
	public:
		BasicController(aie::Input * input = aie::Input::getInstance(), float maxSpeed = 200.0f);
		eResult execute(Agent* agent, float deltaTime) override;
	};

	class MouseController : public iBehaviour
	{
	private:
		aie::Input*		m_input;
		float			m_lSpeedMax;
		pkr::Vector2	m_destination;
		float			m_arriveThreshold = 5.0f;			//Raw inits; adjust accordingly
		//float			m_arriveSmoothZone = 20.0f;
	public:
		MouseController(aie::Input * input = aie::Input::getInstance(), float maxSpeed = 500.0f);
		eResult execute(Agent* agent, float deltaTime) override;
	};

	//// ENEMY AI Behaviours ////
	class SeekAction : public iBehaviour 
	{
	//This needs to take in a target agent
	private:
		Agent *			m_target;
		pkr::Vector2	m_destination;
		float			m_maxLspeed;
	public:
		SeekAction(Agent* target, float maxLspeed = 200.0f);		//Point based if target agent not specified
		//SeekAction(pkr::Vector2 destination, float maxLspeed = 200.0f);
		//~SeekAction() { delete m_target; }									//Destructor
		eResult execute(Agent* agent, float deltaTime) override;
	};

	//// Pathfinding ////
	class PatrolAction : public iBehaviour
	{
	private:
		Agent *			m_pathAgent;
		float			m_maxForce;
	public:
		PatrolAction(Agent* pathObject);
		~PatrolAction() { delete m_pathAgent; }
		eResult execute(Agent* agent, float deltaTime) override;
	};

}