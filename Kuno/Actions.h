#pragma once

namespace ai {

	////Actions
	//Standard
	class BasicController : public iBehaviour
	{
	private:
		aie::Input* m_input;
		float m_maxForce;
	public:
		BasicController(aie::Input * input = aie::Input::getInstance(), float maxSpeed = 200.0f) : 
			m_input(input), m_maxForce(maxSpeed) {}
		eResult execute(Agent* agent, float deltaTime) override;
	};

	class SeekAction : public iBehaviour 
	{
	//This needs to take in a target agent
	private:
		Agent *			m_target;
		float			m_maxForce;
	public:
		SeekAction(Agent* target, float maxSpeed = 200.0f);		//Point based if target agent not specified
		~SeekAction() { delete m_target; }									//Destructor
		eResult execute(Agent* agent, float deltaTime) override;
	};

	//Pathfinding
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