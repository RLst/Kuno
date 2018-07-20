#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include <vector>
//#include "AI.h"
//#include "PF.h"
	
namespace AI {
	class Agent;
}

namespace PF {
	class Graph;
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

	PF::Graph*					m_map;
	AI::Agent*					m_player;
	std::vector<AI::Agent*>		m_enemyList;
	
};