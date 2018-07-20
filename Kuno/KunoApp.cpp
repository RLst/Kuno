#include "KunoApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"

#include "AI.h"
#include "PF.h"
#include "pkr\Vector2.h"
#include "pkr\Vector3.h"

KunoApp::KunoApp() {

}

KunoApp::~KunoApp() {

}

bool KunoApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	////////////////////////////////////////////////////////////////////////
	//Setup map
	//Set sky to night
	setBackgroundColour(0.12f / 4.0f, 0.63f / 4.0f, 1.0f / 4.0f);
	if (setupPF() == false) return false;

	//Setup player
	if (setupPlayer() == false) return false;

	//Setup AI agents
	if (setupAI() == false) return false;

	//////////////////////////////////////////////////////////////////////
	return true;
}

void KunoApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
}

bool KunoApp::setupPF()
{
	//Just setup a raw graph
	m_map = new PF::Graph();

	int maxCols = 15;
	int maxRows = 15;
	float nodeWidth = 40;
	float nodeHeight = 40;

	//Make a grid of say 50 x 50, with all nodes connecting to each other in 8 directions
	for (int col = 0; col < maxCols; ++col) {
		for (int row = 0; row < maxRows; ++row) {
			//Add a node and position appropriately
			m_map->addNode(pkr::Vector2(col * nodeWidth, row * nodeHeight));
		}
	}


	////Connect up adjacent neighbouring nodes
	//for (auto m_map.)
	////Left edge
	//if (col > 0)
	//	m_map->addConnection()

	//	//Top edge

	//	//Right edge

	//	//Bottom edge

	return true;
}

bool KunoApp::setupPlayer()
{
	m_player = new AI::Agent(50, pkr::Vector3(1, 0, 0));
	return true;
}

bool KunoApp::setupAI()
{
	static int numOfEnemies = 10;

	//Load in a bunch of blue seekers
	pkr::Vector3 seekerColour = pkr::Vector3(100, 50, 255);
	for (int i = 0; i < numOfEnemies; ++i) {
		//Seekers
		AI::Agent* newEnemy = new AI::Agent(40.0f, seekerColour, pkr::Vector2(getWindowWidth() / 3.0f, getWindowHeight() / 3.0f));
		m_enemyList.push_back(newEnemy);
	}

	return true;
}

void KunoApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	////////////////////////////////////////////////
	//Update the map


	//Update the agents


	////////////////////////////////////////////////

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void KunoApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	/////////////////////////////////////////////////////
	// begin drawing sprites
	m_2dRenderer->begin();

	//Draw the map
	m_map->draw(m_2dRenderer);


	//Draw agents


	// output some text, uses the last used colour
	m_2dRenderer->setRenderColour(0.4f, 0.4f, 0.4f);
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
	/////////////////////////////////////////////////////////
}