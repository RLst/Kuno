#pragma once

#include "Application.h"
#include "Renderer2D.h"

namespace AI {
	class Agent;
}

namespace PF {
	class Node;
	class Edge;
	class Graph;
}

class KunoApp : public aie::Application {
public:

	KunoApp();
	virtual ~KunoApp();

	bool startup() override;
	void shutdown() override;

	bool setupAI();

	void update(float deltaTime) override;
	void draw() override;

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;

	
};