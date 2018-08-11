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
		//auto child = m_runningChild;
		//m_runningChild = nullptr;

		////If there weren't any pending child from the last frame
		//if (child == nullptr)
		//	child = m_childBehaviours.front();

		//while (child <= m_childBehaviours.back()) {
		//	auto result = child->execute(agent, deltaTime);

		//	if (result == eResult::SUCCESS)
		//		return eResult::SUCCESS;
		//	else if (result == eResult::FAILURE)
		//		continue; /*++child;*/	//Next child
		//	else if (result == eResult::RUNNING) {
		//		m_runningChild = child;
		//		return eResult::RUNNING;
		//	}
		//}
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

		// cout << "Sequence Tick - " << children.size() << " children" << endl;

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


		//ReturnCode Sequence::tick()
		//{

		//	// cout << "Sequence Tick - " << children.size() << " children" << endl;

		//	for (int i = currentChild; i < children.size(); ++i)
		//	{
		//		ReturnCode childstatus = children[i]->tick();

		//		currentChild = i;

		//		if (childstatus == ReturnCode::RUNNING)
		//		{
		//			return ReturnCode::RUNNING;
		//		}
		//		else if (childstatus == ReturnCode::FAILURE)
		//		{
		//			currentChild = 0;
		//			return ReturnCode::FAILURE;
		//		}
		//	}

		//	currentChild = 0;
		//	return ReturnCode::SUCCESS;

		//};



		//auto child = m_runningChild;
		//m_runningChild = nullptr;

		////If there weren't any pending child from the last frame
		//if (child == nullptr)
		//	child = m_childBehaviours.front();

		//while (child != m_childBehaviours.back())
		//{
		//	auto result = child->execute(agent, deltaTime);

		//	if (result == FAILURE)
		//		return FAILURE;
		//	else if (result == SUCCESS)
		//		child++; /*++child;*/	//Next child
		//	else if (result == RUNNING) {
		//		m_runningChild = child;
		//		return RUNNING;
		//	}

		////}
		//
		//for (auto it = m_childBehaviours.begin(); it != m_childBehaviours.end(); ++it) {
		//	auto result = (*it)->execute(agent, deltaTime);

		//	if (result == FAILURE)
		//		return FAILURE;
		//	else if (result == SUCCESS)
		//		++it; /*++child;*/	//Next child
		//	else if (result == RUNNING) {
		//		m_runningChild = *it;
		//		return RUNNING;
		//	}
		//}

		//return SUCCESS;




		//class Composite : public Node
		//{
		//protected:
		//	//bool resumable;
		//	int currentChild;
		//	vector<Node*> children;

		//public:
		//	Composite() { currentChild = 0; };
		//	~Composite() {};

		//	void addChild(Node *n) { children.push_back(n); }
		//	virtual ReturnCode tick() {};
		//};

		//class Sequence : public Composite
		//{
		//public:
		//	Sequence() {};
		//	~Sequence() {};
		//	ReturnCode tick();
		//};








		//for (auto child : m_childBehaviours) {
		//	auto result = child->execute(agent, deltaTime);

		//	if (result == FAILURE)
		//		return FAILURE;
		//	else if (result == SUCCESS)
		//		continue; /*++child;*/	//Next child
		//	else if (result == RUNNING) {
		//		m_runningChild = child;
		//		return RUNNING;
		//	}
		//}
		//return SUCCESS;

		/*
		auto child = m_runningChild;
		m_runningChild = nullptr;

		//If there weren't any pending child from the last frame
		if (child == nullptr)
			child = m_childBehaviours.front();

		for (auto it = m_childBehaviours.begin(); it != m_childBehaviours.end(), it++) {

		}
		*/

		/*
		for (auto child : m_childBehaviours) {
			auto result = child->execute(agent, deltaTime);

			if (result == FAILURE) return FAILURE;
			else if (result == SUCCESS)
				continue;	//next child?
			else if (result == RUNNING) {
				m_runningChild = child;
				return RUNNING;
			}
		}
		return SUCCESS;
		*/

		/*
		while (child <= m_childBehaviours.back()) {		//BUG!!!
			auto result = child->execute(agent, deltaTime);

			if (result == FAILURE)
				return FAILURE;
			if (result == SUCCESS)
				child++;	//Run next child		//POTENTIAL BUG!!!
			if (result == RUNNING) {
				m_runningChild = child;
				return RUNNING;
			}
		} 
		return eResult::SUCCESS;		//Right now it's just skipping straight to SUCCESS
		*/

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
		if (m_timeout > 0) {
			m_timeout = m_duration;		//Resets the timeout
			return eResult::RUNNING;
			//return eResult::FAILURE;
		}
		//Returns result of child unless it times out ie: runs the child for duration set
		return m_child->execute(agent, deltaTime);
	}



}