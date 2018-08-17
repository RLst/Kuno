//////////////////
//// Tony Le ////
// 2 Aug 2018 //
///////////////

#pragma once
#include "AI.h"
#include "Agent.h"

namespace pf {
	class Map;
}

namespace ai {
	class Agent;
	class Avatar;

	namespace condition {
		//////////////////////////////////////////////////////////////////////////////////////////////////
		class WithinRange : public iBehaviour
		{
			//Checks if an agent is within range
		private:
			Agent * m_target;
			float	m_range;

		public:
			~WithinRange() override {}
			WithinRange(Agent* target, float range);
			eResult execute(Agent* agent, float deltaTime) override;
		};
		//////////////////////////////////////////////////////////////////////////////////////////////////
		class CheckState : public iBehaviour
		{
			//Checks if an agent is in a certain state (ai::STATE)
		private:
			ai::Agent::eState	m_state;

		public:
			CheckState(ai::Agent::eState state) : m_state(state) {}
			~CheckState() = default;
			eResult execute(Agent* agent, float deltaTime) override;
		};
		//////////////////////////////////////////////////////////////////////////////////////////////////
		class CheckHealth : public iBehaviour
		{
			//Checks if an agent is below a certain amount of hit points/health
		private:
			float		m_lowHealthThreshold;

		public:
			CheckHealth(float lowHealthThreshold = 15.0f) : m_lowHealthThreshold(lowHealthThreshold) {}
			~CheckHealth() = default;
			eResult execute(Agent* agent, float deltaTime) override;
		};
		//////////////////////////////////////////////////////////////////////////////////////////////////
		class CheckNotMoving : public iBehaviour
		{
		public:
			CheckNotMoving() = default;
			~CheckNotMoving() = default;
			eResult execute(Agent* agent, float deltaTime) override;
		};
		//////////////////////////////////////////////////////////////////////////////////////////////////
		class CheckPathAvailable : public iBehaviour
		{
		public:
			CheckPathAvailable() = default;
			~CheckPathAvailable() = default;
			eResult execute(Agent* agent, float deltaTime) override;
		};
		//////////////////////////////////////////////////////////////////////////////////////////////////
		class LastSeenAvailable : public iBehaviour
		{
		public:
			~LastSeenAvailable() = default;
			LastSeenAvailable() = default;
			eResult execute(Agent* agent, float deltaTime) override;
		};
	}
}





