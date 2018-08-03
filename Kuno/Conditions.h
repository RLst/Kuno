//////////////////
//// Tony Le ////
// 2 Aug 2018 //
///////////////

#pragma once
#include "AI.h"

namespace pf {
	class Map;
}

namespace ai {
	class Agent;
	class Character;

	namespace condition {


	class WithinRangeCondition : public iBehaviour 
	{
		//Checks if an agent is within range
	private:
		Agent *		m_target;
		float		m_range;

	public:
		~WithinRangeCondition() override { /*delete m_target;*/ }
		WithinRangeCondition(Agent* target, float range);
		eResult execute(Agent* agent, float deltaTime) override;
	};

	class OutOfAttackingRange : public iBehaviour
	{
		//NOTE! maybe just use WithinRangeCondition() with different range and NotDecorator() instead
		//Returns success if agent out of attack range
	private:
		Agent *		m_target;
		float		m_attackRange;

	public:
		~OutOfAttackingRange() override { /*delete m_target;*/ }
		OutOfAttackingRange(Agent* target, float attackRange);
		eResult execute(Agent* agent, float deltaTime) override;
	};


	class InViewCondition : public iBehaviour
	{
		//Checks to see if an agent is within view of target agent
		//Will have to 
	private:
		Agent *		m_target;
		pf::Map*	m_map;

		float		m_FOV = 80;					//degrees
		float		m_sightDistance = 100;		//px?

	public:
		~InViewCondition() override { delete m_target; }
		InViewCondition(Agent* target, pf::Map* map);
		eResult execute(Agent* agent, float deltaTime) override;
	};


	}
}