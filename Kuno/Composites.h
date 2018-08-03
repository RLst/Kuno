#pragma once
#include "AI.h"
#include "PF.h"

namespace ai { namespace composite {

	class FollowPathSequence : public Sequence
	{
	private:
		pf::Path	m_path;		//The path the agent will be following

	public:
		FollowPathSequence() = default;
		~FollowPathSequence() = default;
	};

	class AlertSelector : public Selector
	{
		//add children: attack, pursue

	};

	class AttackSequence : public Sequence
	{
	private:
		Agent *		m_target;
		float		m_attackRange = 100;

	public:
		AttackSequence() = default;
		//AttackSequence(Agent* target, float attackRange) :
		//	m_target(target), m_attackRange(attackRange) {}

		//eResult		execute(Agent *agent, float deltaTime) override;
	};

}
}