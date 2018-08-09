//////////////////
//// Tony Le ////
// 2 Aug 2018 //
///////////////

#pragma once

#include <vector>
#include <list>
//#include <pkr\Vector3.h>
//#include <pkr\Vector2.h>

//For header definitions
#include <Renderer2D.h>
#include <Input.h>

namespace aie {
	//class Renderer2D;
	//class Font;
	//class Texture;
	//class Input;
}

//AI holds all the core implementation of the behaviour tree 
//ie. ibehaviour node, composites, selectors, sequence, decorators, etc
//Leaf nodes such as actions and conditions are in their own files

namespace ai {

	class Agent;

	//// Core Behaviour Tree Implementation ////

	//Enums for AI
	enum eResult {
		FAILURE,
		SUCCESS,
		RUNNING,
	};


	//Behaviour (interface)
	class iBehaviour
	{
	public:
		iBehaviour() {}
		virtual ~iBehaviour() {}
		virtual eResult execute(Agent* agent, float deltaTime) = 0;
	};


	//COMPOSITE (abstract)
	class aComposite : public iBehaviour
	{
	protected:
		std::list<iBehaviour*>		m_childBehaviours;
		iBehaviour*					m_runningChild = nullptr;
	public:
		~aComposite() override;
		virtual eResult execute(Agent* agent, float deltaTime) = 0;
		void addChild(iBehaviour* behaviour);
	};

	//SELECTOR
	class Selector : public aComposite
	{
	public:
		eResult execute(Agent* agent, float deltaTime) override;
	};

	//RANDOM SELECTOR
	class SelectorRandom : public aComposite
	{
	public:
		eResult execute(Agent* agent, float deltaTime) override;
	};

	//SEQUENCE
	class Sequence : public aComposite
	{
	public:
		eResult execute(Agent* agent, float deltaTime) override;
	};


	//// DECORATORS ////
	class aDecorator : public iBehaviour
	{
	protected:
		iBehaviour * m_child;
	public:
		~aDecorator() override { delete m_child; }
		virtual eResult execute(Agent* agent, float deltaTime) = 0;
		void	setChild(iBehaviour * behaviour) { m_child = behaviour; }
	};

	//NOT
	class NotDecorator : public aDecorator
		//Inverts SUCCESS or FAILURE
	{
	public:
		eResult execute(Agent* agent, float deltaTime) override;
	};

	//TIMEOUT
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

}

/*Behaviour tree logic 'pseudocode'

Agent
	//Pathfinding related
	private Map*	m_map	//for pathfinding(), findTileFromPos()
	private Path	m_path
	private bool	m_pathAvailable
	private bool	m_isPatrolling?



>> ENEMYROOTSEQ()
	private pkr::Vector2	m_lastSeenLocation
	private bool			m_lastSeenLocationExists

	^ ActionSel()
		^ AttackSeq()
			if WithinRange(attackRange) [& WithinView()]
				UpdateState(agent.state = eState::ALERT)
				UpdateLastSeenLocation(opponent.pos)
				Timeout(agent.attackSpeed)		//attackspeed in seconds
					Attack()	//opponent.takeDamage(agent.damage / (clamp(distance(opponent, agent), closestAttack, attackRange) * closestAttack))

		^ FleeOrPursueSeq()
			if WithinRange(alertViewRange) [& WithinView()]
				UpdateState(ALERT)
				UpdateLastSeenLocation(opponent.pos)
				TakeActionSel()
					^ FleeSeq()
						if LowHealth()
							Flee(opponent)		//Could/Might have to combine the two below into one
								GetFleePath()
								SetNewAgentPath(Flee)
					^ Pursue(opponent)
						GetPursuePath()
						SetNewAgentPath(Pursue)


		^ SeekSel()
			if WithinRange(suspiciousViewRange)
				UpdateState(agent.state = SUSPICIOUS)
				UpdateLastSeenLocation(opponent.pos)
				TakeActionSel()
				^ SeekSeq()
						if LastSeenLocationExists()
							Seek(LastSeenLocation)
								GetSeekPath()
								SetNewAgentPath(Seek)
							Timeout(5,10)
								AlertedInspect()	//"Where did she go?" Faster and more alert than SuspiciousInspect()
							ClearLastSeenLocation()
							UpdateState(NORMAL)

		^ NormalSeq()
			PatrolSeq()
				GetPatrolPath()
				SetNewAgentPath()
				SetAgentToPatrol()
		
^ FollowPathSeq()
	isPathAvailable()
	GetNextWaypoint()
	FollowPath()	//state(normal || suspicious) ? walk : run (state is alert)
	PatrolSel()
		^ if state(normal)	//patrol
			ReversePath()	//Set current agent path to reverse 
			TimeoutDecorator(5-10s)
				Idle() //Essentially do nothing; play idle animation;
		^ else	//Not patrolling; clearpath and end
			ClearPath()		//Set m_pathAvailable to false





PLAYERROOT()

MouseClick()
	ClampWithinMap()
	if clicked on map
		SetNewAgentPath()
		Move(walk/sneak)
	if clicked on enemy agent
		Move(walk/sneak)
		Attack(normal/stealth)

MouseDoubleClick()
	ClampWithinMap()
	if clicked on map
		SetNewAgentPath()
		Move(run)
		UpdateState(normal)
	if clicked on enemy agent
		Move(run)
		Attack(normal/stealth)	//Stealth only if you're right next to the enemy?

MouseRightButtonDown()
	GuardUp()

KeyboardPress(space)
	ToggleStealthMode()


*/