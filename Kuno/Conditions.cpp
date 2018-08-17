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
			return (agent->isMoving()) ? FAILURE : SUCCESS;
		}

		eResult CheckPathAvailable::execute(Agent * agent, float deltaTime)
		{
			return (agent->getPath().isAvailable()) ? SUCCESS : FAILURE;

		}

		eResult LastSeenAvailable::execute(Agent * agent, float deltaTime)
		{
			return (agent->isLastSeenAvailable()) ? SUCCESS : FAILURE;
		}

	}

}



