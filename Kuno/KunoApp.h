#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include <vector>
#include <pkr\math\Vector2.h>

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

	//Character setup properties
	struct {
		float attack = 15.0f;
		float stealthAttack = 110.0f;
		float attackSpeed = 1.0f;		//Seconds
		float attackRange = 50.0f;
		float sneakSpeed = 50.0f;
		float walkSpeed = 100.0f;
		float runSpeed = 200;
	} playerStat;

	struct {
		//Core
		float size = 20.0f;
		pkr::Vector3 colour = { 0.9f, 0.2f, 0 };
		//Attacks
		float attack = 20.0f;
		float attackSpeed = 1.0f;			//seconds; delay between attacks
		float lowHealthThres = 20.0f;		//Triggers flee if health goes below this
											//Ranges
		float attackRange = 40.0f;			//The distance from which the enemy can attack
		float sightRange = 150.0f;			//The distance from which the enemy can clearly see
		float suspiciousRange = 300.0f;		//The distance from which the enemy can somewhat see
		//float FOV = 90.0f;					//View cone of the enemy
											//Speeds
		float walkSpeed = 50.0f;
		float runSpeed = 150.0f;
	} enemyStat;

protected:
	aie::Renderer2D*			m_2dRenderer;
	aie::Font*					m_font;

	//// Agents ////
	//Player
	ai::Agent*					m_Yuna;

	//Enemies
	ai::Agent*					m_SeekGent;
	ai::Agent*					m_FleeGent;
	//ai::Agent*					m_AttackGent;
	//ai::Agent*					m_PatrolGent;

	ai::Agent*					m_Enemy;
	std::vector<ai::Agent*>		m_EnemyList;

	//std::vector<ai::Agent*>		m_Swordsman;
	//std::vector<ai::Agent*>		m_Bowmen;
	//ai::Agent*					m_Lord;

	//Map and pathfinding
	pf::Map*					m_map;

	//GUI
	//Audio systems
	//Log systems

private:
	//Utilities
	util::Camera*				m_camera;
	util::TextureManager*		m_textureManager;
	util::DepthSorter*			m_depthSorter;
	util::CoordConverter*		m_coordConverter;

public:
	static KunoApp*				Instance();			//MODERN SINGLETON PATTERN
	static void					resetInstance();	//MODERN SINGLETON PATTERN; call this to delete singleton

	//Setups
	bool startup() override;
	bool setupUtilities();
	bool loadTextures();
	bool setupMap();
	bool setupAI();
	bool setupPlayer();
	bool setupEnemies();

	//Shutdown
	void shutdown() override;

	//Core
	void update(float deltaTime) override;
	void draw() override;

	//Access utilities
	util::Camera*				Camera() const { return m_camera; }
	util::TextureManager*		TextureManager() const { return m_textureManager; }
	util::DepthSorter*			DepthSorter() const { return m_depthSorter; }
	util::CoordConverter*		CoordConverter() const { return m_coordConverter; }

	//DEBUGS
	void DEBUG(aie::Renderer2D* renderer);			//Print important values and test stuff
	void showInstructions();
	//pf::Map*					getMap() const { return m_map; }
};