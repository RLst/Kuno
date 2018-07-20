#pragma once

#include <vector>
#include <list>
#include <pkr\Vector3.h>
#include <pkr\Vector2.h>

//For header definitions
#include <Renderer2D.h>
#include <Input.h>

namespace aie {
	class Renderer2D;
	class Font;
	class Texture;
	//class Input;
}


//AI methods and implementations ie. Behaviour tree
namespace AI {

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
		virtual ~iBehaviour() {}	//CHECK how these are supposed to be setup
		virtual eResult execute(Agent* agent, float deltaTime) = 0;
	};


	//Composites
	class iComposite : public iBehaviour
	{
	protected:
		std::list<iBehaviour*>		m_childBehaviours;
	public:
		iComposite() {}
		virtual ~iComposite() {}
		virtual eResult execute(Agent* agent, float deltaTime) = 0;
	};

	class Selector : public iComposite
	{
	public:
		Selector() {}
		~Selector() override {}
		eResult execute(Agent* agent, float deltaTime) override;
	};

	class Sequence : public iComposite
	{
	public:
		Sequence() {}
		~Sequence() override {}
		eResult execute(Agent* agent, float deltaTime) override;
	};


	//Decorators
	class iDecorator : public iBehaviour
	{
	protected:
		iBehaviour * m_child;
	public:
		iDecorator() {}
		~iDecorator() {}
		virtual eResult execute(Agent* agent, float deltaTime) = 0;
		void	setChild(iBehaviour * behaviour) { m_child = behaviour; }
	};
	class NotDecorator : public iDecorator
		//Inverts SUCCESS or FAILURE
	{
	public:
		NotDecorator() {}
		~NotDecorator() override { delete m_child; }
		eResult execute(Agent* agent, float deltaTime) override;
	};

	class TimeoutDecorator : public iDecorator
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


	////Agents
	class Agent
	{
	protected:
		std::vector<iBehaviour*>	m_behaviours;

		//Some basic transformation data
		float						m_maxForce;
		pkr::Vector2				m_force;
		pkr::Vector2				m_accel;
		pkr::Vector2				m_vel;
		pkr::Vector2				m_pos;

		//Circle agent
		float						m_size = 0;
		pkr::Vector3				m_colour;

		//Texture agent
		aie::Texture*				m_texture = nullptr;

	public:
		Agent(const Agent &other);		//Copy
		Agent(const pkr::Vector2 &startingPos = pkr::Vector2(300,300), float maxForce = 200.0f);	//Standard
		Agent(float size, const pkr::Vector2 &startingPos = pkr::Vector2(300, 300), const pkr::Vector3 &colour = pkr::Vector3(1,1,1));	//Circle agent constructor
		Agent(aie::Texture* texture, const pkr::Vector2 &startingPos = pkr::Vector2(300, 300));		//Texture agent
		virtual ~Agent();	//Destructor 

		//Add
		void						addBehaviour(iBehaviour* behaviour);
		void						addForce(const pkr::Vector2 &force);

		//State accessors
		pkr::Vector2				getPos() const { return m_pos; }

		//Core
		void						update(float deltaTime);
		void						draw(aie::Renderer2D* renderer);
	};


	///////////////////////////////////////////////////
	//// Leafs - Where all the action takes place! ////
	///////////////////////////////////////////////////
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


	//////Conditions
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


	//////Actions
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
		//This needs to take in the target agent
	{
	private:
		Agent *		m_target;
		float		m_maxForce;
	public:
		SeekAction(Agent* target, float maxSpeed = 200.0f);		//Comprehensive
		~SeekAction() { delete m_target; }						//Destructor
		eResult execute(Agent* agent, float deltaTime) override;
	};

}

