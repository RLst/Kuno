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
#include "CoordConverter.h"
	
//Tony Le
//Date: 25 Jul 2018
//Kuno; Ninja isometric stealth based
//Yuna Okuma name found here: http://www.fantasynamegenerators.com/japanese_names.php

//This is a singleton so that you can access:
//Camera: to get camera position for viewport to canvas conversions
//DepthSorter:
//CoordConverter: to convert between different coord systems

namespace aie {
	class Renderer2D;
}

namespace util {
	class Camera;
	class TextureManager;
	class DepthSorter;
	class CoordConverter;
}

namespace ai {
	class Agent;
}

namespace pf {
	class Graph;
	class Map;
	class Tile;
}


class KunoApp : public aie::Application 
{
private:
	KunoApp() = default;					//MODERN SINGLETON PATTERN
	virtual ~KunoApp() = default;			//Destructor not required; use shutdown() instead
protected:
	aie::Renderer2D*			m_2dRenderer;
	aie::Font*					m_font;

	//Utilities
	util::Camera*				m_camera;
	util::TextureManager*		m_textureManager;
	util::DepthSorter*			m_depthSorter;
	util::CoordConverter*		m_coordConverter;
	
	//Agents
	ai::Agent*					m_player;
	std::vector<ai::Agent*>		m_enemyList;

	//Map and pathfinding
	pf::Graph*					m_graph;		//DELETE ME!
	pf::Map*					m_map;
	pf::Tile***					m_tiles;

	//GUI
	//GUI::Gui*					m_gui;

	//Audio systems
	//Log systems

public:
	static KunoApp*				getInstance();		//MODERN SINGLETON PATTERN
	static void					resetInstance();	//MODERN SINGLETON PATTERN; call this to delete singleton

	//Setups
	bool startup() override;
	bool setupUtilities();
	bool loadTextures();
	bool setupPF();
	bool setupAI();
	bool setupPlayer();
	bool setupEnemies();

	//Shutdown
	void shutdown() override;

	//Core
	void update(float deltaTime) override;
	void draw() override;

	//Access utilities
	util::Camera*				getCamera() const { return m_camera; }
	util::DepthSorter*			getDepthSorter() const { return m_depthSorter; }
	util::CoordConverter*		getCoordConverter() const { return m_coordConverter; }

};