#include "KunoApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "imgui.h"
#include "GameDefines.h"
#include <ctime>

#include "Camera.h"
#include "TextureManager.h"

#include "AI.h"
#include "PF.h"
#include "Tile.h"
#include "Map.h"

#include "pkr\Vector2.h"
#include "pkr\Vector3.h"

//// MODERN SINGLETON PATTERN ////
KunoApp* KunoApp::getInstance()
{
	//Modern, thread-safe
	//C++ 11 mandates that the initializer for a local static variable is only run once, 
	//even in the presence of concurrency
	static KunoApp *m_instance = new KunoApp();
	return m_instance;
}

void KunoApp::resetInstance()
{
	KunoApp* m_toDelete = getInstance();
	delete m_toDelete;
	m_toDelete = nullptr;		//CHECK WITH TEACHER!!!
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
	setBackgroundColour(0.12f / 4.0f, 0.63f / 4.0f, 1.0f / 4.0f);
	if (setupPF() == false) return false;

	//Setup AI systems
	if (setupAI() == false) return false;

	//Setup Agents
	if (setupPlayer() == false) return false;
	if (setupEnemies() == false) return false;

	return true;
}

void KunoApp::shutdown() {

	delete m_2dRenderer;
	delete m_font;

	delete m_player;
	for (auto enemy : m_enemyList)
		delete enemy;

	delete m_graph;
	delete m_map;
	for (int col = 0; col < WORLD_DEPTH; ++col) {
		for (int row = 0; row < WORLD_WIDTH; ++row) {
			if (m_tiles[col][row] != nullptr)
				delete m_tiles[col][row];	//Delete the cells
		}
		delete[] m_tiles[col];	//Delete the array of rows
	}
	delete[] m_tiles;	//Delete the array of columns

	delete m_camera;
}

//// SETUPS ////
bool KunoApp::setupUtilities()
{
	//// Camera ////
	m_camera = new util::Camera();
	m_camera->x = -200;
	m_camera->y = -200;
	m_camera->scale = 2.0f;

	//// Depth Sorter ////
	m_depthSorter = new util::DepthSorter(-2000.0f, 2000.0f);
				//note: Z buffer depth of between 0-1 is reserved for the GUI

	return true;
}

bool KunoApp::loadTextures()
{
	//Startup texture manager
	m_textureManager = new util::TextureManager();

	//Test: Load in some core textures
	//MAKE THE FINAL PATH AS:
	m_textureManager->addTexture("Floor", new aie::Texture("../bin/textures/prototype_iso/floor_N.png"));
	m_textureManager->addTexture("Slab", new aie::Texture("../bin/textures/prototype_iso/slab_N.png"));
	m_textureManager->addTexture("Column", new aie::Texture("../bin/textures/prototype_iso/column_N.png"));
	m_textureManager->addTexture("ColumnBlocks", new aie::Texture("../bin/textures/prototype_iso/columnBlocks_N.png"));
	m_textureManager->addTexture("SmallBlock", new aie::Texture("../bin/textures/prototype_iso/blockSmall_N.png"));
	m_textureManager->addTexture("LargeBlock", new aie::Texture("../bin/textures/prototype_iso/blockLarge_N.png"));
	m_textureManager->addTexture("HugeBlock", new aie::Texture("../bin/textures/prototype_iso/blockHuge_N.png"));

	return true;
}

bool KunoApp::setupPF()
{
	//Just setup a raw graph
	m_graph = new pf::Graph();

	pkr::Vector2 offset = { 60, 60 };
	int maxCols = 30;
	int maxRows = 16;
	float nodeWidth = 40;
	float nodeHeight = 40;

	
	/////////// NODE //////////////
	//Make a grid of say 50 x 50, with all nodes connecting to each other in 8 directions
	for (int row = 0; row < maxRows; ++row) {
		for (int col = 0; col < maxCols; ++col) {
			//Add a node and position appropriately
			m_graph->addNode(pkr::Vector2(offset.x + col * nodeWidth, offset.y + row * nodeHeight));
		}
	}
	
	//Connect up adjacent neighbouring nodes
	for (auto nodeA : m_graph->getNodes()) 
	{
		for (auto nodeB : m_graph->getNodes())
		{
			//Skip if they're both the same node
			if (nodeA == nodeB)
				continue;

			//Find the distance between the node
			float distance = pkr::Vector2::distance(nodeA->pos_tmp, nodeB->pos_tmp);

			//If they're below a certain range then connect the nodes
			if (distance < 60) {
				m_graph->addConnection(nodeA, nodeB);
				//This should also connect it both ways
			}

		}
	}

	//////////// MAP /////////////
	//Should make this load a map from some data or file
	
	//Build tile array !!!
	m_tiles = new pf::Tile**[WORLD_WIDTH];
	for (int row = 0; row < WORLD_WIDTH; ++row)
	{
		m_tiles[row] = new pf::Tile*[WORLD_DEPTH];
		for (int col = 0; col < WORLD_DEPTH; ++col)
		{
			aie::Texture* inputTex = nullptr;
			switch (pkr::Random(1, 3)) {
			case 1:	//Floor
				inputTex = m_textureManager->getTexture("Floor");
				break;
			case 2:	//Slab
				inputTex = m_textureManager->getTexture("Slab");
				break;
			case 3: //Huge block
				inputTex = m_textureManager->getTexture("HugeBlock");
				break;
			case 4: //Column
				inputTex = m_textureManager->getTexture("Column");
				break;
			}
			m_tiles[row][col] = new pf::Tile(inputTex);
		}
	}

	//Build the actual map!
	m_map = new pf::Map(WORLD_WIDTH, WORLD_DEPTH, m_tiles);

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
	return false;
}

bool KunoApp::setupPlayer()
{
	m_player = new ai::Agent(50, pkr::Vector3(1, 0, 0));
	return true;
}

bool KunoApp::setupEnemies()
{
	static int numOfEnemies = 10;

	//Load in a bunch of blue seekers
	pkr::Vector3 seekerColour = pkr::Vector3(100, 50, 255);
	for (int i = 0; i < numOfEnemies; ++i) {
		//Seekers
		ai::Agent* newEnemy = new ai::Agent(40.0f, seekerColour, pkr::Vector2(getWindowWidth() / 3.0f, getWindowHeight() / 3.0f));
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
	//Update GUI

	//Get control input

	//ImGui::Begin("EdgeScrolling");
	//ImGui::Text("Camera pos x: %d, y: %d", m_camera->x, m_camera->y);
	//ImGui::End();
	
	//// DEBUG ////
	//Mouse position
	ImGui::Begin("Mouse Position");
	ImGui::Text("X: %d, Y: %d", input->getMouseX(), input->getMouseY());
	ImGui::End();

	////////////////////////////////////////////////

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void KunoApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	//// SET THE CAMERA ////
	m_2dRenderer->setCameraPos(m_camera->x, m_camera->y);
	m_2dRenderer->setCameraScale(m_camera->scale);
	
	//// DEBUB: Test screenToWorld() ////
	//aie::Input* input = aie::Input::getInstance();
	//ImGui::Begin("Camera Position");
	//ImGui::Text("X: %f, Y: %f", m_camera->x, m_camera->y);
	//ImGui::End();
	//m_camera->testViewportToCanvas(m_2dRenderer);
	//// SUCCESS! 27 July 2018, 10:45

	//// START DRAW ////
	m_2dRenderer->begin();

	//Draw the map
	m_graph->draw(m_2dRenderer);
	m_map->draw(m_2dRenderer);

	//Draw agents

	// output some text, uses the last used colour
	//m_2dRenderer->setRenderColour(0.4f, 0.4f, 0.4f);
	//m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	//// END DRAW ////
	m_2dRenderer->end();
}
///////////////////////////////////////////////////////////////////