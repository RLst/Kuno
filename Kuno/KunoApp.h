#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include <vector>
#include <pkr/Vector2.h>
#include "AI.h"
#include "PF.h"
#include "Map.h"
#include "TextureManager.h"
#include "Camera.h"
#include "DepthSorter.h"
	
//Tony Le
//Date: 25 Jul 2018
//Kuno; Ninja isometric stealth based
//Yuna Okuma name found here: http://www.fantasynamegenerators.com/japanese_names.php

class KunoApp : public aie::Application 
{
private:
	KunoApp() = default;					//MODERN SINGLETON PATTERN

	virtual ~KunoApp() = default;			//Destructor not required; use shutdown() instead
protected:
	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;

	//Texture manager
	util::TextureManager* m_textureManager;

	//Depth sorter
	util::DepthSorter*	m_depthSorter;
	
	//Agents
	ai::Agent*			m_player;
	std::vector<ai::Agent*>	m_enemyList;

	//Map and pathfinding
	pf::Graph*			m_graph;
	pf::Map*			m_map;
	pf::Tile***			m_tiles;

	//Camera
	util::Camera*		m_camera;

	//GUI
	//GUI::Gui*			m_gui;

	//Audio systems

	//Log systems

public:
	static KunoApp*		getInstance();		//MODERN SINGLETON PATTERN
	static void			resetInstance();	//MODERN SINGLETON PATTERN; call this to delete singleton

	//Setups
	bool startup() override;
	bool setupUtilities();
	bool loadTextures();
	bool setupPF();
	bool setupAI();
	bool setupPlayer();
	bool setupEnemies();

	void shutdown() override;

	void update(float deltaTime) override;
	void draw() override;

	//Access utilities
	util::DepthSorter*	getDepthSorter() const { return m_depthSorter; }

};