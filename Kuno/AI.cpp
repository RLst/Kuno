//////////////////
//// Tony Le ////
// 2 Aug 2018 //
///////////////


#include "AI.h"
#include "Agent.h"
#include <pkr\Vector2.h>
#include <Renderer2D.h>
#include "GameDefines.h"

namespace ai {

	//Composites
	aComposite::~aComposite()
	{
		//Delete all children
		for (auto &child : m_childBehaviours) {
			delete child;
			child = nullptr;
		}
	}
	void aComposite::addChild(iBehaviour * behaviour)
	{
		m_childBehaviours.push_back(behaviour);
	}
	eResult Selector::execute(Agent * agent, float deltaTime)
	{
		auto child = m_pendingChild;
		m_pendingChild = nullptr;

		//If there weren't any pending child from the last frame
		if (child == nullptr)
			child = m_childBehaviours.front();

		while (child <= m_childBehaviours.back()) {
			auto result = child->execute(agent, deltaTime);

			if (result == SUCCESS)
				return SUCCESS;
			if (result == FAILURE)
				++child;	//Next child
			if (result == RUNNING) {
				m_pendingChild = child;
				return RUNNING;
			}
		}
		return FAILURE;

		//OR node; Returns SUCCESS if any child returns SUCCESS
		//for (auto child : m_childBehaviours) {
		//	if (child->execute(agent, deltaTime) == eResult::SUCCESS)
		//		return eResult::SUCCESS;
		////}
		//return eResult::FAILURE;
	}

	eResult SelectorRandom::execute(Agent * agent, float deltaTime)
	{
		//OR node with random; Returns SUCCESS if any of the randomly select children return SUCESS
		int children = m_childBehaviours.size();
		std::vector<ai::iBehaviour*> openList;
		std::vector<ai::iBehaviour*> closedList;
		
		for (auto child : m_childBehaviours) {
			//Has child been check already?

			//FINISH THIS OFF LATER

		}

		return eResult::FAILURE;
	}

	eResult Sequence::execute(Agent * agent, float deltaTime)
	{
		auto child = m_pendingChild;
		m_pendingChild = nullptr;

		//If there weren't any pending child from the last frame
		if (child == nullptr)
			child = m_childBehaviours.front();

		for (auto it = m_childBehaviours.begin(); it != m_childBehaviours.end(), ++it) {

		}

		while (child <= m_childBehaviours.back()) {		//BUG!!!
			auto result = child->execute(agent, deltaTime);

			if (result == FAILURE)
				return FAILURE;
			if (result == SUCCESS)
				child++;	//Run next child		//POTENTIAL BUG!!!
			if (result == RUNNING) {
				m_pendingChild = child;
				return RUNNING;
			}
		} 
		return eResult::SUCCESS;		//Right now it's just skipping straight to SUCCESS

		////AND node; Returns SUCCESS only if ALL children return SUCCESS
		//for (auto child : m_childBehaviours) {
		//	if (child->execute(agent, deltaTime) == eResult::FAILURE)
		//		return eResult::FAILURE;
		//	//What if it returns RUNNING?
		//}
		//return eResult::SUCCESS;
	}

	//Decorators
	eResult NotDecorator::execute(Agent * agent, float deltaTime)
	{
		//Get result of child...
		eResult result = m_child->execute(agent, deltaTime);

		//Invert
		switch (result) {
		case eResult::SUCCESS:
			return FAILURE; break;
		case eResult::FAILURE:
			return SUCCESS; break;
		default:	//Else return whatever result is
			return result;
		}
	}

	eResult TimeoutDecorator::execute(Agent * agent, float deltaTime)
	{
		m_timeout -= deltaTime;
		if (m_timeout > 0)
			return eResult::FAILURE;
		m_timeout = m_duration;
		//Returns result of child unless it times out
		return m_child->execute(agent, deltaTime);
	}



}