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
	class Decorator : public iBehaviour
	{
	public:
		Decorator() {}
		~Decorator() override {}
		eResult execute(Agent* agent, float deltaTime) override;
	};

	////Agents
	class Agent 
	{
	protected:
		std::vector<iBehaviour*>	m_behaviours;

		//Some basic transformation data
		pkr::Vector2				m_force;
		pkr::Vector2				m_accel;
		pkr::Vector2				m_vel;
		pkr::Vector2				m_pos;
		float						m_size;
		pkr::Vector3				m_colour;

	public:
		Agent() {}
		Agent(const Agent &other);		//Copy

		Agent(	const pkr::Vector2 &pos,	//Agent drawn as circle
				float size,
				const pkr::Vector3 &colour = pkr::Vector3());

		virtual ~Agent();	//Destructor 

		//Add
		void		addBehaviour(iBehaviour* behaviour);

		void		addForce(const pkr::Vector2 &force);

		//State accessors
		pkr::Vector2		getPos() const { return m_pos; }

		//Core
		void		update(float deltaTime);
		void		draw(aie::Renderer2D* renderer);
	};

	///////////////////////////////////////////////////
	//// Leaf nodes - Where all the action takes place!
	///////////////////////////////////////////////////
	//Conditions
	class tEnemiesCloseCondition : public iBehaviour
	{
	private:
		std::vector<Agent*> m_enemies;
		float		m_range;

		Agent*		m_enemyFoundInRange;		//How do you relay this information to AttackAction?
	public:
		//This class will need to take in a list of enemy agents
		tEnemiesCloseCondition(std::vector<Agent*> listOfEnemies, float range) :
			m_enemies(listOfEnemies), m_range(range) {}

		//void setEnemyList(std::vector<Agent*> listOfEnemies);
		//std::vector<Agent*> getEnemyList() const;
		eResult execute(Agent* agent, float deltaTime) override;
	};

	//Actions
	class tAttackAction : public iBehaviour
	{
	private:
		std::vector<Agent*> m_enemiesInRange;
		Agent*		m_enemyInRange;
		int			m_damageToApply;
		float		m_range;

	public:
		eResult execute(Agent* agent, float deltaTime) override;
	};

	class BasicKeyboardController : public iBehaviour
	{
	private:
		aie::Input* m_input;
	public:
		BasicKeyboardController(aie::Input * input = aie::Input::getInstance()) : m_input(input) {}
		eResult execute(Agent* agent, float deltaTime) override;
	};

	class SeekAction : public iBehaviour 
		//This needs to take in the target agent
	{
	private:
		Agent *		m_target;
		float		m_maxSpeed;
	public:
		SeekAction(Agent* target, float maxSpeed = 200.0f) :	//Comprehensive
			m_target(target), m_maxSpeed(maxSpeed) {}
		~SeekAction() { delete m_target; }						//Destructor
		eResult execute(Agent* agent, float deltaTime) override;
	};

}

