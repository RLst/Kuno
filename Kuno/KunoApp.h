#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include <vector>
#include <pkr/Vector2.h>
//#include "AI.h"
//#include "PF.h"
	
namespace AI {
	class Agent;
}

namespace PF {
	class Graph;
}

namespace Util {
	class Camera;
}

class KunoApp : public aie::Application {
public:

	KunoApp();
	virtual ~KunoApp();

	bool startup() override;
	void shutdown() override;

	bool setupAI();
	bool setupPF();
	bool setupPlayer();

	void update(float deltaTime) override;
	void draw() override;

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;

	//Agents
	AI::Agent*				m_player;
	std::vector<AI::Agent*>	m_enemyList;

	//Map and pathfinding
	PF::Graph*			m_map;

	//Camera
	Util::Camera*		m_camera;
};

namespace Util {
	class Camera 
	{
	private:
		int scrollZone = 10;	//10 pixels 
	public:
		Camera()

		int x, y;		//Positions
		void update(float deltaTime, aie::Input* input, aie::Application* app) 
		{
			if (input)
				app->getWindowHeight();


			FINISH ME OFF!!
		}
	};
}