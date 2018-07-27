#include "Actions.h"
#include "AI.h"
#include "Agent.h"

namespace ai {

	SeekAction::SeekAction(Agent * target, float maxSpeed) :
		m_target(target), m_maxForce(maxSpeed) {}

	eResult SeekAction::execute(Agent * agent, float deltaTime)
	{	//Seek vector = Target position - Agent position
		//Find the normalised seek vector towards target
		pkr::Vector2 nrmSeekVector = pkr::Vector2::normalise(m_target->getPos() - agent->getPos());

		//Apply max force towards target
		agent->addForce(nrmSeekVector * m_maxForce);

		return eResult::SUCCESS;
	}

}