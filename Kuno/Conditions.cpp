//////////////////
//// Tony Le ////
// 2 Aug 2018 //
///////////////


#include "Conditions.h"
#include "Agent.h"

namespace ai {
	namespace condition {

	WithinRangeCondition::WithinRangeCondition(Agent * target, float range) :
		m_target(target), m_range(range) {}
	eResult WithinRangeCondition::execute(Agent * agent, float deltaTime)
	{
		if (pkr::Vector2::distance(agent->getPos(), m_target->getPos()) < m_range)
			return SUCCESS;		//Target agent is within range
		else
			return FAILURE;
	}

	InViewCondition::InViewCondition(Agent * target, pf::Map * map) :
		m_target(target), m_map(map) {}
	eResult InViewCondition::execute(Agent * agent, float deltaTime)
	{
		//Character* ch = agent;
		////If target agent is within line of sight, within view and within range...
		//if (pkr::Vector2::angleBetween(agent->getFacing()
		//	//// ???????????
		//	// How do I access Character::getFacing() without having to rewrite the whole execute()???

		//	return SUCCESS;		//Target agent is IN VIEW
		//}
		//else
		//	return FAILURE;
		return eResult();
	}

	HealthLowCond::HealthLowCond(Agent * subject) :
		m_subject(subject), m_lowHealthThreshold(15)
	{}

	eResult HealthLowCond::execute(Agent * agent, float deltaTime)
	{
		if (agent->getHealth() < m_lowHealthThreshold)
			return eResult::SUCCESS;
		else
			return eResult::FAILURE;
	}

	}
}