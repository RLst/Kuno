//////////////////
//// Tony Le ////
// 2 Aug 2018 //
///////////////

#pragma once

#include <vector>
#include <list>
//#include <pkr\Vector3.h>
//#include <pkr\Vector2.h>

//For header definitions
#include <Renderer2D.h>
#include <Input.h>

namespace aie {
	//class Renderer2D;
	//class Font;
	//class Texture;
	//class Input;
}

//AI holds all the core implementation of the behaviour tree 
//ie. ibehaviour node, composites, selectors, sequence, decorators, etc
//Leaf nodes such as actions and conditions are in their own files

namespace ai {

	class Agent;

	//// Core Behaviour Tree Implementation ////

	//Enums for AI
	enum eResult {
		FAILURE,
		SUCCESS,
		RUNNING,
	};


	//Behaviour (interface)
	class iBehaviour
	{
	public:
		iBehaviour() {}
		virtual ~iBehaviour() {}
		virtual eResult execute(Agent* agent, float deltaTime) = 0;
	};


	//COMPOSITE (abstract)
	class aComposite : public iBehaviour
	{
	protected:
		std::list<iBehaviour*>		m_childBehaviours;
		iBehaviour*					m_runningChild = nullptr;
	public:
		~aComposite() override;
		virtual eResult execute(Agent* agent, float deltaTime) = 0;
		void addChild(iBehaviour* behaviour);
	};

	//SELECTOR
	class Selector : public aComposite
	{
	public:
		eResult execute(Agent* agent, float deltaTime) override;
	};

	//RANDOM SELECTOR
	class SelectorRandom : public aComposite
	{
	public:
		eResult execute(Agent* agent, float deltaTime) override;
	};

	//SEQUENCE
	class Sequence : public aComposite
	{
	public:
		eResult execute(Agent* agent, float deltaTime) override;
	};


	//// DECORATORS ////
	class aDecorator : public iBehaviour
	{
	protected:
		iBehaviour * m_child;
	public:
		~aDecorator() override { delete m_child; }
		virtual eResult execute(Agent* agent, float deltaTime) = 0;
		void	setChild(iBehaviour * behaviour) { m_child = behaviour; }
	};

	//NOT
	class NotDecorator : public aDecorator
		//Inverts SUCCESS or FAILURE
	{
	public:
		eResult execute(Agent* agent, float deltaTime) override;
	};

	//TIMEOUT
	class TimeoutDecorator : public aDecorator
		//Executes child behaviour until timeout
	{
	private:
		float m_timeout;		//Countdown time
		float m_duration;		//Original duration
	public:
		TimeoutDecorator(float timeout, float duration) : m_timeout(timeout), m_duration(duration) {}
		~TimeoutDecorator() override { delete m_child; }
		eResult execute(Agent* agent, float deltaTime) override;
	};

}