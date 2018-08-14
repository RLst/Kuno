//////////////////
//// Tony Le ////
// 2 Aug 2018 //
///////////////


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
#include "Conditions.h"
#include "Composites.h"

//PF
#include "PF.h"
#include "Tile.h"
#include "Map.h"

#include <pkr\Vector2.h>
#include <pkr\Vector3.h>

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
	delete m_KeyboardGent;
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

	//// Texture Manager ////
	m_textureManager = new util::TextureManager();

	//// Depth Sorter ////
	m_depthSorter = new util::DepthSorter(0.0f, 100.0f);
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
	//// Build the map ////
	m_map = new pf::Map();
	m_map->buildRandomMap(WORLD_WIDTH, WORLD_DEPTH);
	//m_map = new pf::Map(WORLD_WIDTH, WORLD_DEPTH, pkr::Vector2(0,0));

	//// Connect tile/nodes in map ////
	float NodeConnectRadius = 220;		//4 ways: 180, 8 ways: 200
	m_map->connectNodesByDistance(NodeConnectRadius);

	return true;
}

bool KunoApp::setupPlayer()
{
	m_PathFollowGent = new ai::Agent(40.f, pkr::Vector3(0.9f, 0.9f, 0));
	//m_KeyboardGent = new ai::Agent(40.f, pkr::Vector3(0.25f, 0.75f, 0));
	//m_MouseGent = new ai::Agent(40.f, pkr::Vector3(0.25f, 0.05f, 0.75f));
	//m_FleeGent = new ai::Agent(40.f, pkr::Vector3(0.9f, 0.4f, 0.4f));

	return true;
}

bool KunoApp::setupEnemies()
{
	static int numOfEnemies = 2;

	//Load in a bunch of blue seekers
	pkr::Vector3 enemyColour = pkr::Vector3(0.75f, 0.25f, 0);	//Dark redish

	for (int i = 0; i < numOfEnemies; ++i) {
		m_enemyList.push_back(new ai::Agent(40.0f, enemyColour, pkr::Vector2(i * 100.0f, i * 100.0f)));
	}

	return true;
}

bool KunoApp::setupAI()
{
	//// TEST VALUES ////
	auto lowHealthThreshold = 15;

	//////////////////////////
	//// Setup player(s) ////
	////////////////////////
	aie::Input* input = aie::Input::getInstance();
	//m_KeyboardGent->addBehaviour(new ai::action::tKeyboardControl(input, 500.0f));
	////m_MouseGent->addBehaviour(new ai::action::tMouseControl(input));

	////Flee//
	//auto fleeSeq = new ai::Sequence();
	////fleeSeq->addChild(new ai::condition::CheckHealth(m_FleeGent, lowHealth));
	//fleeSeq->addChild(new ai::action::Flee(m_KeyboardGent, m_map));
	//m_FleeGent->addBehaviour(fleeSeq);

	//Path follower
	auto slTest1 = new ai::Selector();
		auto sqPathToMouse = new ai::Sequence();					//Make a FollowPathSequence
		sqPathToMouse->addChild(new ai::action::tMouseSetDesiredPos());
		sqPathToMouse->addChild(new ai::action::CalculatePath(m_map));
	slTest1->addChild(sqPathToMouse);
	slTest1->addChild(new ai::action::FollowPath());

	//sqPathToMouse->addChild(new ai::action::FollowPath());		//Add a FollowPath action leaf to it
	m_PathFollowGent->addBehaviour(slTest1);				//Add FollowPath sequence to path follower
	

	/////////////////////////
	//// Setup enemies /////
	///////////////////////
	auto samurai = new ai::Selector();			//Root node for a melee samurai
	auto samuraiBow = new ai::Selector();		//Root node for a ranged samurai
	auto lord = new ai::Selector();

	//// Set some test values ////
	//Samurai swordsman
	struct {	//Temp?
		float attackRange = 30.0f;			//The distance from which the enemy can attack
		float alertRange = 300.0f;			//The distance from which the enemy can clearly see
		float suspiciousRange = 500.0f;		//The distance from which the enemy can somewhat see
		float attackSpeed = 2.0f;			//seconds; delay between attacks
		float FOV = 90.0f;					//View cone of the enemy
	} swordsman;
	

	//// TEST ////
	auto EnemyRoot = new ai::Selector();
		//auto decSuccess = new ai::ReturnSuccess();
			auto sqEnemyAction = new ai::Sequence();
			sqEnemyAction->addChild(new ai::condition::WithinRange(m_PathFollowGent, 300));
			sqEnemyAction->addChild(new ai::condition::CheckNotMoving());
			sqEnemyAction->addChild(new ai::action::Seek(m_PathFollowGent));
			sqEnemyAction->addChild(new ai::action::CalculatePath(m_map));
		//decSuccess->setChild(sqEnemyAction);
	EnemyRoot->addChild(sqEnemyAction);
		auto sqPathFinding = new ai::Sequence();
		//sqPathFinding->addChild(new ai::action::CalculatePath(m_map));
		sqPathFinding->addChild(new ai::action::FollowPath());
	EnemyRoot->addChild(sqPathFinding);

	for (auto e : m_enemyList)
	{
		e->addBehaviour(EnemyRoot);
	}


	////// THIS IS IT! Set up enemy AI////
	////Constant behaviours
	//auto UpdateLastSeen = new ai::action::UpdateLastSeen(m_KeyboardGent);
	//auto UpdatePath = new ai::action::CalculatePath(m_map);

	//////Samurai Swordsman
	////Attack Sequence
	//auto AttackSequence = new ai::Sequence();
	//	AttackSequence->addChild(new ai::condition::WithinRange(m_KeyboardGent, swordsman.attackRange));
	//	AttackSequence->addChild(new ai::action::UpdateState(ai::Agent::eState::ALERT));
	//	AttackSequence->addChild(new ai::action::UpdateLastSeen(m_KeyboardGent));
	//		auto AttackDecorator = new ai::DelayDecorator(swordsman.attackSpeed);
	//			AttackDecorator->setChild(new ai::action::Attack(m_KeyboardGent));
	//	AttackSequence->addChild(AttackDecorator);

	////Flee or Pursue Sequence
	//auto FleeOrPursueSequence = new ai::Sequence();
	//FleeOrPursueSequence->addChild(new ai::condition::WithinRange(m_KeyboardGent, swordsman.alertRange));
	//FleeOrPursueSequence->addChild(new ai::action::UpdateState(ai::Agent::eState::ALERT));
	//FleeOrPursueSequence->addChild(UpdateLastSeen);
	//	auto FleeOrPursueSelector = new ai::Selector();
	//		auto FleeSequence = new ai::Sequence();
	//		FleeSequence->addChild(new ai::condition::CheckHealth());
	//		FleeSequence->addChild(new ai::action::Flee());
	//		FleeSequence->addChild(UpdatePath);
	//	FleeOrPursueSelector->addChild(FleeSequence);
	//	FleeOrPursueSelector->addChild(new ai::action::Seek(m_KeyboardGent));
	//	FleeOrPursueSelector->addChild(UpdatePath);
	//FleeOrPursueSequence->addChild(FleeOrPursueSelector);

	////Action
	//auto ActionSel = new ai::Selector();
	//ActionSel->addChild(AttackSequence);
	//ActionSel->addChild(FleeOrPursueSequence);

	////Path
	//auto PathAvailable = new ai::Selector();
	//PathAvailable->addChild(new ai::action::FollowPath());

	////FINAL SETUP
	////Root
	//auto SwordsmanRoot = new ai::Sequence();
	//SwordsmanRoot->addChild(ActionSel);
	//SwordsmanRoot->addChild(PathAvailable);
	//		
	//for (auto e : m_enemyList)
	//{
	//	e->addBehaviour(SwordsmanRoot); 
	//}

	//Delete ai stuff


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
	m_map->update(deltaTime);		//Handle the tile tinting
	
	//Update the agents
	m_PathFollowGent->update(deltaTime);
	//m_KeyboardGent->update(deltaTime);
	//m_MouseGent->update(deltaTime);
	//m_FleeGent->update(deltaTime);

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
	m_PathFollowGent->draw(m_2dRenderer);
	//m_KeyboardGent->draw(m_2dRenderer);				//Keyboard
	//m_MouseGent->draw(m_2dRenderer);			//Mouse
	//m_FleeGent->draw(m_2dRenderer);

	for (auto enemy : m_enemyList) {			//Enemies
		enemy->draw(m_2dRenderer);
	}

//// DEBUGS ////
#ifdef _DEBUG
DEBUG(m_2dRenderer);
#endif
///////////////

	m_2dRenderer->end();
	//// END DRAW ////
}

void KunoApp::DEBUG(aie::Renderer2D* renderer)
{
	//Get input
	aie::Input* input = aie::Input::getInstance();

	//// FPS ////
	char fps[10];
	sprintf_s(fps, 10, "%i FPS", getFPS());
	pkr::Vector2 fpsPos = m_coordConverter->ViewportToCanvas(0, 0);		//Stick to the bottom left hand corner of screen
	m_2dRenderer->setRenderColour(0.1f, 0.1f, 0.1f);
	m_2dRenderer->drawText(m_font, fps, fpsPos.x, fpsPos.y);
	
	//// IMGUI STUFF ////
	pkr::Vector2 view = { (float)input->getMouseX(), (float)input->getMouseY() };			//Get Viewport coords
	pkr::Vector2 canvas = m_coordConverter->ViewportToCanvas(view);							//Convert from Viewport to Canvas
	pkr::Vector2 world = m_coordConverter->CanvasToWorld(canvas);							//Convert from Canvas to World
	pkr::Vector2 world2canvas = m_coordConverter->WorldToCanvas(world);						//Convert from World BACK to Canvas

	ImGui::Begin("DEBUG");

	//// Camera ////
	if (ImGui::CollapsingHeader("Camera"))
	{
		ImGui::Text("x: %.0f, y: %.0f", m_camera->x, m_camera->y);
		ImGui::Text("Zoom: %.3f", m_camera->zoom);
		//ImGui::Text("lastScrollPos: %.3f", m_camera->m_lastScrollPos);
	}

	//// Coord converter ////
	if (ImGui::CollapsingHeader("Coord Converter"))
	{
		ImGui::Text("Viewport > x: %.0f, y: %.0f", view.x, view.y);
		renderer->setRenderColour(1, 0, 0);
		renderer->drawText(m_font, "VIEW", view.x, view.y);

		ImGui::Text("Canvas > x: %.2f, y: %.2f", canvas.x, canvas.y);
		renderer->setRenderColour(0, 1, 0);
		renderer->drawText(m_font, "CANVAS", canvas.x, canvas.y);

		ImGui::Text("World > x: %.2f, y: %.2f", world.x, world.y);
		renderer->setRenderColour(0, 0, 1);
		renderer->drawText(m_font, "WORLD", world.x, world.y, m_depthSorter->getSortDepth(world.y));

		ImGui::Text("World2Canvas > x: %.2f, y: %.2f", world2canvas.x, world2canvas.y);
		renderer->setRenderColour(0, 0, 0);
		renderer->drawText(m_font, "W2C", world2canvas.x, world2canvas.y, m_depthSorter->getSortDepth(world2canvas.y));
	}

	//// Depth Sorter ////
	// An orange circle will locate where the cursor is should be depth sorted by the sorter
	//pkr::Vector2 view = pkr::Vector2((float)input->getMouseX(), (float)input->getMouseY());
	//pkr::Vector2 circCanvas = m_coordConverter->ViewportToCanvas(view);
	if (ImGui::CollapsingHeader("Depth Sorter"))
	{
		float depth = m_depthSorter->getSortDepth(canvas.y);
		m_2dRenderer->setRenderColour(1, 0.85f, 0.40f);
		m_2dRenderer->drawCircle(canvas.x, canvas.y, 5.0f, depth);
		ImGui::Text("Nearest: %.2f, Furthest: %.2f", m_depthSorter->m_minYpos, m_depthSorter->m_maxYpos);
		ImGui::Text("Viewport > x: %.2f, y: %.2f", view.x, view.y);
		ImGui::Text("Canvas > x: %.2f, y: %.2f", canvas.x, canvas.y);
		ImGui::Text("Depth (Cursor): %.2f", depth);
		ImGui::Text("Depth Iterator: %f", m_depthSorter->m_depthIterator);
	}

	//// Tile Address ////
	if (ImGui::CollapsingHeader("Tile Address"))
	{
		auto tileUnderMouse = m_map->findTileFromCanvasPos(canvas);
		ImGui::Text("& of Tile at cursor: %p", tileUnderMouse);
		if (tileUnderMouse != nullptr)
		{
			ImGui::Text("Position > x: %.2f, y: %.2f", tileUnderMouse->pos.x, tileUnderMouse->pos.y);
		}
	}

	ImGui::End();
}
