#include <ctime>

#include "KunoApp.h"
#include "GameDefines.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "imgui.h"

//Utils
#include "TextureManager.h"
#include "Camera.h"
#include "DepthSorter.h"
#include "CoordConverter.h"

//AI
#include "AI.h"
#include "Agent.h"
#include "Actions.h"
#include "Condition.h"

//PF
#include "PF.h"
#include "Tile.h"
#include "Map.h"

#include "pkr\Vector2.h"
#include "pkr\Vector3.h"

//// MODERN SINGLETON PATTERN ////
KunoApp* KunoApp::Instance()
{
	//Modern, thread-safe
	//C++ 11 mandates that the initializer for a local static variable is only run once, 
	//even in the presence of concurrency
	static KunoApp *m_instance = new KunoApp();
	return m_instance;
}

void KunoApp::resetInstance()
{
	KunoApp* m_toReset = Instance();
	delete m_toReset;
	m_toReset = nullptr;		//CHECK WITH TEACHER!!!
}
/////////////////////////////////

bool KunoApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();

	setVSync(true);

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	//Randomize seed
	srand((unsigned int)time(NULL));

	//// SETUPS ////
	if (setupUtilities() == false) return false;
	if (loadTextures() == false) return false;

	//Setup map and pathfinding
	//setBackgroundColour(0.12f / 4.0f, 0.63f / 4.0f, 1.0f / 4.0f);
	setBackgroundColour(1, 0.65f, 0);
	if (setupMap() == false) return false;

	//Setup Agents
	if (setupPlayer() == false) return false;
	if (setupEnemies() == false) return false;

	//Setup AI systems
	if (setupAI() == false) return false;

	return true;
}

void KunoApp::shutdown() {

	//Core
	delete m_2dRenderer;
	delete m_font;

	//Agents
	delete m_player;
	for (auto enemy : m_enemyList)
		delete enemy;

	//Map
	delete m_map;

	//Utilities
	delete m_camera;
	delete m_textureManager;
	delete m_depthSorter;
	delete m_coordConverter;
}

//// SETUPS ////
bool KunoApp::setupUtilities()
{
	//// Camera ////
	m_camera = new util::Camera(-200, -200, 2.0f);
	//Camera = util::Camera(0, -200, 1.5f);

	//// Texture Manager ////
	m_textureManager = new util::TextureManager();
	//TextureManager = util::TextureManager();

	//// Depth Sorter ////
	m_depthSorter = new util::DepthSorter(0.0f, 15000.0f);
	//DepthSorter = util::DepthSorter(-2000.0f, 2000.0f);
				//note: Z buffer depth of between 0-1 is reserved for the GUI

	//// Coord Converter ////
	m_coordConverter = new util::CoordConverter(m_camera);
	//CoordConverter = util::CoordConverter(&Camera);

	return true;
}

bool KunoApp::loadTextures()
{
	//Test: Load in some core textures
	//MAKE THE FINAL PATH AS: "../assets/tiles/*.png"
	//Ground
	m_textureManager->addTexture("Floor", new aie::Texture("../bin/textures/prototype_iso/floor_N.png"));
	m_textureManager->addTexture("Slab", new aie::Texture("../bin/textures/prototype_iso/slab_N.png"));
	//Walls
	m_textureManager->addTexture("HugeBlock", new aie::Texture("../bin/textures/prototype_iso/blockHuge_N.png"));
	//Static objects
	m_textureManager->addTexture("Column", new aie::Texture("../bin/textures/prototype_iso/column_N.png"));
	m_textureManager->addTexture("ColumnBlocks", new aie::Texture("../bin/textures/prototype_iso/columnBlocks_N.png"));
	m_textureManager->addTexture("SmallBlock", new aie::Texture("../bin/textures/prototype_iso/blockSmall_N.png"));
	m_textureManager->addTexture("LargeBlock", new aie::Texture("../bin/textures/prototype_iso/blockLarge_N.png"));

	return true;
}

bool KunoApp::setupMap()
{
	//Just setup a raw graph
	//m_graph = new pf::Graph();

	//pkr::Vector2 offset = { 100, 100 };
	//int maxCols = 10;
	//int maxRows = 10;
	//float nodeWidth = 100;
	//float nodeHeight = 100;

	///////////// NODE //////////////
	////Make a grid of say 50 x 50, with all nodes connecting to each other in 8 directions
	//for (int row = 0; row < maxRows; ++row) {
	//	for (int col = 0; col < maxCols; ++col) {
	//		//Add a node and position appropriately
	//		m_graph->addNode(pkr::Vector2(offset.x + col * nodeWidth, offset.y + row * nodeHeight));
	//	}
	//}
	//
	////Connect up adjacent neighbouring nodes
	//for (auto nodeA : m_graph->getNodes()) 
	//{
	//	for (auto nodeB : m_graph->getNodes())
	//	{
	//		//Skip if they're both the same node
	//		if (nodeA == nodeB)
	//			continue;
	//		//Find the distance between the node
	//		float distance = pkr::Vector2::distance(nodeA->pos_tmp, nodeB->pos_tmp);
	//		//If they're below a certain range then connect the nodes
	//		if (distance < 60) {
	//			m_graph->addConnection(nodeA, nodeB);
	//			//This should also connect it both ways
	//		}
	//	}
	//}

	//////////// MAP /////////////
	m_map = new pf::Map();
	m_map->buildTestMap(WORLD_WIDTH, WORLD_DEPTH);
	//m_map = new pf::Map(WORLD_WIDTH, WORLD_DEPTH, pkr::Vector2(0,0));

	////Build tile array !!!
	//m_tiles = new pf::Tile**[WORLD_WIDTH];
	//for (int row = 0; row < WORLD_WIDTH; ++row)
	//{
	//	m_tiles[row] = new pf::Tile*[WORLD_DEPTH];
	//	for (int col = 0; col < WORLD_DEPTH; ++col)
	//	{
	//		aie::Texture* inputTex = nullptr;
	//		switch (pkr::Random(1, 3)) {
	//		case 1:	//Floor
	//			inputTex = m_textureManager->getTexture("Floor");
	//			break;
	//		case 2:	//Slab
	//			inputTex = m_textureManager->getTexture("Slab");
	//			break;
	//		case 3: //Huge block
	//			inputTex = m_textureManager->getTexture("HugeBlock");
	//			break;
	//		case 4: //Column
	//			inputTex = m_textureManager->getTexture("Column");
	//			break;
	//		}
	//		m_tiles[row][col] = new pf::Tile({ 0,0 }, inputTex);
	//	}
	//}


	return true;
}

bool KunoApp::setupAI()
{
	////Behaviour tree
	//
	//if (GuardBehaviour)
	//{
	//	//Idle
	//	if (Idle)
	//	{
	//		wait 30 - 60 seconds;
	//		move to patrol
	//	}
	//	//Patrol
	//	if (Patrol)
	//
	//
	//	//
	//
	//}

	//Setup player
	aie::Input* input = aie::Input::getInstance();
	m_player->addBehaviour(new ai::BasicController(aie::Input::getInstance(), 500.0f));

	//Setup enemies
	for (auto e : m_enemyList)
	{
		e->addBehaviour(new ai::SeekAction(m_player, 400.0f));
	}

	return true;
}

bool KunoApp::setupPlayer()
{
	m_player = new ai::Agent(50.0f, pkr::Vector3(0.25f, 0.75f, 0));

	return true;
}

bool KunoApp::setupEnemies()
{
	static int numOfEnemies = 20;

	//Load in a bunch of blue seekers
	pkr::Vector3 seekerColour = pkr::Vector3(0.75f, 0.25f, 0);
	for (int i = 0; i < numOfEnemies; ++i) {
		//Seekers
		ai::Agent* newEnemy = new ai::Agent(40.0f, seekerColour, pkr::Vector2(i * 100.0f, i * 100.0f));
		m_enemyList.push_back(newEnemy);
	}

	return true;
}

//// CORE ////
void KunoApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	////////////////////////////////////////////////
	//Edge scrolling, Zooming
	m_camera->update(deltaTime);

	//Update the map
	
	//Update the agents
	m_player->update(deltaTime);
	for (auto enemy : m_enemyList)
		enemy->update(deltaTime);

	//Update GUI

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void KunoApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	aie::Input* input = aie::Input::getInstance();

	//// Translate camera ////
	m_camera->translate(m_2dRenderer);

	//// START DRAW ////
	m_2dRenderer->begin();

	//// Draw the map ////
	//float mapDrawStartTime = KunoApp::Instance()->getTime();
	m_map->draw(m_2dRenderer);
	//float mapDrawEndTime = KunoApp::Instance()->getTime();

	//Draw agents
	m_player->draw(m_2dRenderer);
	for (auto enemy : m_enemyList) {
		enemy->draw(m_2dRenderer);
	}

	//// DEBUGS ////
	DEBUG(m_2dRenderer);
	///////////////

	//// END DRAW ////
	m_2dRenderer->end();
}

void KunoApp::DEBUG(aie::Renderer2D* renderer)
{
	//Get input
	aie::Input* input = aie::Input::getInstance();

	//// FPS ////
	char fps[10];
	sprintf_s(fps, 10, "%i FPS", getFPS());
	pkr::Vector2 fpsPos = m_coordConverter->ViewportToCartesian(0, 0);		//Stick to the bottom left hand corner of screen
	m_2dRenderer->setRenderColour(0.1f, 0.1f, 0.1f);
	m_2dRenderer->drawText(m_font, fps, fpsPos.x, fpsPos.y);

	//// Camera ////
	ImGui::Begin("Camera");
	ImGui::Text("x: %.0f, y: %.0f", m_camera->x, m_camera->y);
	ImGui::Text("Zoom: %.3f", m_camera->zoom);
	ImGui::Text("lastScrollPos: %.3f", m_camera->m_lastScrollPos);
	ImGui::End();

	//// Coord converter ////
	float x = 0, y = 0;
	x = input->getMouseX(); y = input->getMouseY();										//Get Viewport coords
	pkr::Vector2 cart = m_coordConverter->ViewportToCartesian(pkr::Vector2(x, y));		//Convert from Viewport to Cartesian
	pkr::Vector2 iso = m_coordConverter->CartesianToIsometric(cart);					//Convert from Cartesian to Isometric
	ImGui::Begin("Coord Converter");

	ImGui::Text("Viewport > x: %.0f, y: %.0f", x, y);
	renderer->setRenderColour(1, 0, 0);
	renderer->drawText(m_font, "VIEW", x, y);
	//renderer->drawCircle(x, y, 2.5f);

	ImGui::Text("Cartesian > x: %.2f, y: %.2f", cart.x, cart.y);
	renderer->setRenderColour(0, 1, 0);
	renderer->drawText(m_font, "CART", cart.x, cart.y);
	//renderer->drawCircle(cart.y, cart.y, 2.5f);

	ImGui::Text("Isometric > x: %.2f, y: %.2f", iso.x, iso.y);
	renderer->setRenderColour(0, 0, 1);
	renderer->drawText(m_font, "ISO", iso.x, iso.y, m_depthSorter->getSortDepth(iso.y));
	ImGui::End();

	//// Depth Sorter ////
	// An orange circle will locate where the cursor is should be depth sorted by the sorter
	pkr::Vector2 cartMPos = pkr::Vector2(input->getMouseX(), input->getMouseY());
	pkr::Vector2 isoMpos = m_coordConverter->ViewportToCartesian(cartMPos.x, cartMPos.y);
	float depth = m_depthSorter->getSortDepth(isoMpos.y);
	m_2dRenderer->setRenderColour(1, 0.85f, 0.40f);
	m_2dRenderer->drawCircle(isoMpos.x, isoMpos.y + 15.0f, 15.0f, depth);

	//////////////
	////m_graph->draw(m_2dRenderer);
	////// DEBUG: Check the time it takes to draw the map ////
	//ImGui::Begin("Graph Draw Duration");
	//ImGui::Text("%f", mapDrawEndTime - mapDrawStartTime);
	//ImGui::End();
	////////////

}
