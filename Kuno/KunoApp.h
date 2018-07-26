#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include <vector>
#include <pkr/Vector2.h>
#include "AI.h"
#include "PF.h"
#include "Map.h"
#include "Util.h"
	
//Tony Le
//Date: 25 Jul 2018
//Kuno; Ninja isometric stealth based
//Yuna Okuma name found here: http://www.fantasynamegenerators.com/japanese_names.php

//namespace AI {
//	class Agent;
//}
//
//namespace PF {
//	class Graph;
//}
//namespace Util {
//	class Camera;
//}

class KunoApp : public aie::Application {
public:

	KunoApp() = default;
	virtual ~KunoApp() = default;

	//Setups
	bool startup() override;
	bool setupCamera();
	bool loadTextures();
	bool setupPF();
	bool setupAI();
	bool setupPlayer();
	bool setupEnemies();

	void shutdown() override;

	void update(float deltaTime) override;
	void draw() override;

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;

	//Texture manager
	Util::TextureManager*	m_texManager;
	
	//Agents
	AI::Agent*				m_player;
	std::vector<AI::Agent*>	m_enemyList;

	//Map and pathfinding
	PF::Graph*			m_graph;
	PF::Map*			m_map;
	PF::Tile***			m_tiles;

	//Camera
	Util::Camera*		m_camera;

	//GUI
	//GUI::Gui*			m_gui;
};