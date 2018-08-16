//////////////////
//// Tony Le ////
// 2 Aug 2018 //
///////////////


#include "AI.h"
#include "Agent.h"
#include <pkr\Vector2.h>
#include <Renderer2D.h>
#include "GameDefines.h"

#include <iostream>

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
		for (int i = m_runningChild; i < m_childBehaviours.size(); ++i)
		{
			auto result = m_childBehaviours[i]->execute(agent, deltaTime);

			m_runningChild = i;

			if (result == eResult::RUNNING) {
				return eResult::RUNNING;
			}
			else if (result == eResult::SUCCESS) {
				m_runningChild = 0;
				return eResult::SUCCESS;
			}
		}
		m_runningChild = 0;
		return eResult::FAILURE;

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

		for (int i = m_runningChild; i < m_childBehaviours.size(); ++i)
		{
			auto result = m_childBehaviours[i]->execute(agent, deltaTime);

			m_runningChild = i;

			if (result == eResult::RUNNING) {
				return eResult::RUNNING;
			}
			else if (result == FAILURE) {
				m_runningChild = 0;
				return FAILURE;
			}
		}
		m_runningChild = 0;
		return SUCCESS;

		/*
		//AND node; Returns SUCCESS only if ALL children return SUCCESS
		for (auto child : m_childBehaviours) {
			if (child->execute(agent, deltaTime) == eResult::FAILURE)
				return eResult::FAILURE;
			//What if it returns RUNNING?
		}
		return eResult::SUCCESS;
		*/
	}

	NotDecorator::NotDecorator(iBehaviour * childBehaviour)
	{
		//Constructor directly takes in a child behaviour
		setChild(childBehaviour);
	}

	//Decorators
	eResult NotDecorator::execute(Agent * agent, float deltaTime)
	{
		//Get result of child...
		eResult result = m_child->execute(agent, deltaTime);

		std::cout << "NotDecorator";

		//Invert
		switch (result) {
		case eResult::SUCCESS:
			std::cout << "SUCCESS > FAILURE" << std::endl;
			return FAILURE; break;
		case eResult::FAILURE:
			std::cout << "FAILURE > SUCCESS" << std::endl;
			return SUCCESS; break;
		default:	//Else return whatever result is
			std::cout << "OTHER" << std::endl;
			return result;
		}
	}

	TimeoutDecorator::TimeoutDecorator(iBehaviour * child, float timeout) :
		m_timeout(timeout)
	{
		setChild(child);
	}

	eResult TimeoutDecorator::execute(Agent * agent, float deltaTime)
	{
		std::cout << "TimeoutDecorator: " << m_timeout << std::endl;

		m_timeout -= deltaTime;
		if (m_timeout > 0) {
			m_timeout = m_reset;		//Resets the timeout
			return eResult::FAILURE;
		}
		//Returns result of child unless it times out ie: runs the child for duration set
		return m_child->execute(agent, deltaTime);
	}

	DelayDecorator::DelayDecorator(iBehaviour * child, float delay) :
		m_delay(delay)
	{
		setChild(child);
	}

	eResult DelayDecorator::execute(Agent * agent, float deltaTime)
	{
		std::cout << "DelayDecorator: " << m_delay << std::endl;

		//If first run
		if (m_delay == m_reset) {
			//Run once and then start countdown
			m_delay -= deltaTime;
			return m_child->execute(agent, deltaTime);
		}
		m_delay -= deltaTime;
		//If delay < 0 then reset
		if (m_delay < 0) {
			m_delay = m_reset;
		}
		return eResult::FAILURE;
	}

	eResult ReturnSuccess::execute(Agent * agent, float deltaTime)
	{
		std::cout << "SuccessDecorator" << std::endl;

		m_child->execute(agent, deltaTime);
		return eResult::SUCCESS;	//ALWAYS RETURN SUCCESS!
	}

}