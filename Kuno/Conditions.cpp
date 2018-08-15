//////////////////
//// Tony Le ////
// 2 Aug 2018 //
///////////////


#include "Conditions.h"
#include "Agent.h"

namespace ai {
	namespace condition {

		WithinRange::WithinRange(Agent * target, float range) :
			m_target(target), m_range(range) {}
		eResult WithinRange::execute(Agent * agent, float deltaTime)
		{
			if (pkr::Vector2::distance(agent->pos, m_target->pos) < m_range)
				return eResult::SUCCESS;		//Target agent is within range
			else
				return eResult::FAILURE;
		}

		eResult CheckState::execute(Agent * agent, float deltaTime)
		{
			//Return success if state matches
			if (agent->state == m_state)
				return eResult::SUCCESS;
			else
				return eResult::FAILURE;
		}

		eResult CheckHealth::execute(Agent * agent, float deltaTime)
		{
			if (agent->getHealth() < m_lowHealthThreshold)
				return SUCCESS;
			else
				return FAILURE;
		}

		eResult CheckNotMoving::execute(Agent * agent, float deltaTime)
		{
			return (agent->m_isMoving) ? FAILURE : SUCCESS;
		}

		eResult CheckPathAvailable::execute(Agent * agent, float deltaTime)
		{
			return (agent->getPath().isAvailable()) ? SUCCESS : FAILURE;

		}

	}

}




/*
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
	eResult ReachedEndOfPath::execute(Agent * agent, float deltaTime)
	{
		//If the agent has reached the end of the path then return success


		return eResult();
	}
*/