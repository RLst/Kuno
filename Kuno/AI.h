#pragma once

#include <vector>
#include <list>
#include <pkr\Vector3.h>
#include <pkr\Vector2.h>

//For header definitions
#include <Renderer2D.h>
#include <Input.h>
#include "Path.h"

namespace aie {
	class Renderer2D;
	class Font;
	class Texture;
	//class Input;
}


//AI methods and implementations ie. Behaviour tree
namespace ai {

	class Agent;

	////Core Behaviour Tree Implementation
	enum eResult {
		FAILURE,
		SUCCESS,
		RUNNING,
	};



	class iBehaviour
	{
	public:
		iBehaviour() {}
		virtual ~iBehaviour() {}
		virtual eResult execute(Agent* agent, float deltaTime) = 0;
	};



	//Composites
	class aComposite : public iBehaviour
	{
	protected:
		std::list<iBehaviour*>		m_childBehaviours;
	public:
		~aComposite() override;
		virtual eResult execute(Agent* agent, float deltaTime) = 0;
		void addChild(iBehaviour* behaviour);
	};

	class Selector : public aComposite
	{
	public:
		eResult execute(Agent* agent, float deltaTime) override;
	};

	class Sequence : public aComposite
	{
	public:
		eResult execute(Agent* agent, float deltaTime) override;
	};



	//Decorators
	class aDecorator : public iBehaviour
	{
	protected:
		iBehaviour * m_child;
	public:
		~aDecorator() override { delete m_child; }
		virtual eResult execute(Agent* agent, float deltaTime) = 0;
		void	setChild(iBehaviour * behaviour) { m_child = behaviour; }
	};

	class NotDecorator : public aDecorator
		//Inverts SUCCESS or FAILURE
	{
	public:
		eResult execute(Agent* agent, float deltaTime) override;
	};

	class TimeoutDecorator : public aDecorator
		//Executes child behaviour until timeout
	{
	private:
		float m_timeout;		//Countdown time
		float m_duration;		//Original duration
	public:
		TimeoutDecorator(float timeout, float duration) : m_timeout(timeout), m_duration(duration) {}
		~TimeoutDecorator() override { delete m_child; }
		eResult execute(Agent* agent, float deltaTime) override;
	};





	///////////////////////////////////////////////////
	//// Leafs - Where all the action takes place! ////
	///////////////////////////////////////////////////
	////Conditions


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


	////////////// TESTS /////////////////////
	////Composites
	//class tAttackSequence : public Sequence
	//{
	//private:
	//	std::vector<Agent*>	m_enemiesInRange;
	//public:
	//	tAttackSequence() { m_enemiesInRange.clear(); }
	//	~tAttackSequence() {}
	//	
	//	eResult execute(Agent* agent, float deltaTime) override;
	//};
	//class tEnemiesCloseCondition : public iBehaviour
	//{
	//private:
	//	std::vector<Agent*> m_enemies;
	//	float		m_range;
	//	std::vector<Agent*>	m_enemyFoundInRange;		//How do you relay this information to AttackAction?
	//public:
	//	//This class will need to take in a list of enemy agents
	//	tEnemiesCloseCondition(std::vector<Agent*> listOfEnemies, float range);
	//	//void setEnemyList(std::vector<Agent*> listOfEnemies);
	//	//std::vector<Agent*> getEnemyList() const;
	//	eResult execute(Agent* agent, float deltaTime) override;
	//};
	//class tAttackAction : public iBehaviour
	//{
	//private:
	//	std::vector<Agent*> m_enemiesInRange;
	//	Agent*		m_enemyInRange;
	//	int			m_damageToApply;
	//	float		m_range;
	//public:
	//	eResult execute(Agent* agent, float deltaTime) override;
	//};
}

