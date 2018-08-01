#include "Condition.h"
#include "Agent.h"

namespace ai {
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
		//If target agent is within line of sight, within view and within range...
		if (pkr::Vector2::angleBetween(agent->getFacing()
			//// ???????????
			// How do I access Character::getFacing() without having to rewrite the whole execute()???

			return SUCCESS;		//Target agent is IN VIEW
		}
		else
			return FAILURE;
		
	}
	
}