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

//For debugs
//#ifdef _DEBUG
#include "imgui.h"
#include <iostream>
//#endif // _DEBUG


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
	//m_font = new aie::Font("./font/consolas.ttf", 32);

	//Randomize seed
	srand((unsigned int)time(NULL));

	//// SETUPS ////
	if (setupUtilities() == false) return false;
	if (loadTextures() == false) return false;

	//Setup map and pathfinding
	setBackgroundColour(0.12f / 4.0f, 0.63f / 4.0f, 1.0f / 4.0f);
	//setBackgroundColour(1, 0.65f, 0);
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
	delete m_Yuna;

	delete m_SeekGent;
	delete m_FleeGent;
	//delete m_AttackGent;
	//delete m_PatrolGent;
	for (auto E : m_EnemyList)
		delete E;

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
	m_camera = new util::Camera(-200, -200, 0.75f);

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
	m_textureManager->addTexture("Dirt", new aie::Texture("../bin/textures/assets/dirt.png"));
	m_textureManager->addTexture("Sand", new aie::Texture("../bin/textures/assets/sand.png"));
	m_textureManager->addTexture("Grass", new aie::Texture("../bin/textures/assets/grass.png"));
	m_textureManager->addTexture("Path", new aie::Texture("../bin/textures/assets/path.png"));
	m_textureManager->addTexture("Water", new aie::Texture("../bin/textures/assets/water.png"));
	m_textureManager->addTexture("DeepWater", new aie::Texture("../bin/textures/assets/deepwater.png"));

	//m_textureManager->addTexture("Floor", new aie::Texture("./textures/prototype_iso/floor_N.png"));
	//m_textureManager->addTexture("Slab", new aie::Texture("./textures/prototype_iso/slab_N.png"));
	//m_textureManager->addTexture("Dirt", new aie::Texture("./textures/assets/dirt.png"));
	//m_textureManager->addTexture("Sand", new aie::Texture("./textures/assets/sand.png"));
	//m_textureManager->addTexture("Grass", new aie::Texture("./textures/assets/grass.png"));
	//m_textureManager->addTexture("Path", new aie::Texture("./textures/assets/path.png"));
	//m_textureManager->addTexture("Water", new aie::Texture("./textures/assets/water.png"));
	//m_textureManager->addTexture("DeepWater", new aie::Texture("./textures/assets/deepwater.png"));

	//Walls
	m_textureManager->addTexture("Wall", new aie::Texture("../bin/textures/assets/wallGrey.png"));
	m_textureManager->addTexture("WallCrap", new aie::Texture("../bin/textures/assets/wallBrown.png"));

	//m_textureManager->addTexture("Wall", new aie::Texture("./textures/assets/wallGrey.png"));a
	//m_textureManager->addTexture("WallCrap", new aie::Texture("./textures/assets/wallBrown.png"));

	//m_textureManager->addTexture("HugeBlock", new aie::Texture("../bin/textures/prototype_iso/blockHuge_N.png"));
	//
	////Static objects
	//m_textureManager->addTexture("Column", new aie::Texture("../bin/textures/prototype_iso/column_N.png"));
	//m_textureManager->addTexture("ColumnBlocks", new aie::Texture("../bin/textures/prototype_iso/columnBlocks_N.png"));
	//m_textureManager->addTexture("SmallBlock", new aie::Texture("../bin/textures/prototype_iso/blockSmall_N.png"));
	//m_textureManager->addTexture("LargeBlock", new aie::Texture("../bin/textures/prototype_iso/blockLarge_N.png"));

	return true;
}

bool KunoApp::setupMap()
{
	//// Build the map ////
	m_map = new pf::Map();
	m_map->buildKunoMap();
	//m_map->buildRandomMap(WORLD_WIDTH, WORLD_DEPTH);

	//// Connect tile/nodes in map ////
	float NodeConnectRadius = 100;		//4 ways: 180, 8 ways: 200
	m_map->connectNodesByDistance(NodeConnectRadius);

	return true;
}

bool KunoApp::setupPlayer()
{
	m_Yuna = new ai::Agent(20.0f, pkr::Vector3(0.2f, 0.4f, 0.75f), { 550, 50 });
	m_Yuna->setAttack(playerStat.attack);
	m_Yuna->setSneakSpeed(playerStat.sneakSpeed);
	m_Yuna->setWalkSpeed(playerStat.walkSpeed);
	m_Yuna->setRunSpeed(playerStat.runSpeed);

	return true;
}

bool KunoApp::setupEnemies()
{
	typedef pkr::Vector3 Color;

	////Attack
	//Color attackcol = { 0.85f, 0.2f, 0 };	//Red
	//m_AttackGent = new ai::Agent(35.0f, attackcol, { 800, 200 });
	////Patrol
	//Color patrolcol = { 0, 0.2f, 0.9f };	//Blue
	//m_PatrolGent = new ai::Agent(35.0f, patrolcol, { 800, 800 });

	//Seek
	Color seekcol = {0.2f, 0.9f, 0.3f};		//Green
	m_SeekGent = new ai::Agent(enemyStat.size, seekcol, { 135, 135 });
	m_SeekGent->setWalkSpeed(enemyStat.walkSpeed);
	m_SeekGent->setRunSpeed(enemyStat.runSpeed);

	//Flee
	Color fleecol = { 0.85f, 0.85f, 0 };	//Yellow
	m_FleeGent = new ai::Agent(enemyStat.size, fleecol, { 180, 180 });
	m_SeekGent->setWalkSpeed(enemyStat.walkSpeed);
	m_SeekGent->setRunSpeed(enemyStat.runSpeed);

	//Guards
	int enemyAmt = 1;
	Color guardcol = { 0.9f, 0.2f, 0 };

	//Create
	for (int i = 0; i < enemyAmt; ++i)
		m_EnemyList.push_back(new ai::Agent(enemyStat.size, enemyStat.colour));

	//Set guard positions
	m_EnemyList[0]->pos = (pkr::Vector2(90, 90)); m_EnemyList[0]->patrolPath().push_back(pkr::Vector2(90, 90));
	//m_EnemyList[1]->pos = (pkr::Vector2(300, 100)); m_EnemyList[1]->patrolPath().push_back(pkr::Vector2(300, 100));
	//m_EnemyList[2]->pos = (pkr::Vector2(100, 300)); m_EnemyList[2]->patrolPath().push_back(pkr::Vector2(100, 300));
	//m_EnemyList[3]->pos = (pkr::Vector2(300, 300)); m_EnemyList[3]->patrolPath().push_back(pkr::Vector2(300, 300));

	//Set attributes
	for (auto e : m_EnemyList) {
		e->setAttack(enemyStat.attack);
		e->setWalkSpeed(enemyStat.walkSpeed);
		e->setRunSpeed(enemyStat.runSpeed);
	}

	return true;
}

bool KunoApp::setupAI()
{
	//////////////////////////
	//// Setup player(s) ////
	////////////////////////
	aie::Input* input = aie::Input::getInstance();

	//Player
	auto PlayerROOT = new ai::Selector();
		auto sqPathToMouse = new ai::Sequence();	//Make a FollowPathSequence
		sqPathToMouse->addChild(new ai::action::tMouseSetDesiredPos(input));
		sqPathToMouse->addChild(new ai::action::CalculatePath(m_map));
	PlayerROOT->addChild(sqPathToMouse);
	PlayerROOT->addChild(new ai::action::FollowPath());
	m_Yuna->addBehaviour(PlayerROOT);				//Add FollowPath sequence to path follower

	//DEBUG: KeyboardBehaviour
	//m_Yuna->addBehaviour(new ai::action::tKeyboardControl());
	
	////////////////////////
	//// SETUP ENEMIES ////
	//////////////////////

	//// SEEK ////
	auto SeekROOT = new ai::Selector();
		auto sqSeekAction = new ai::Sequence();
		sqSeekAction->addChild(new ai::condition::WithinRange(m_Yuna, enemyStat.sightRange));
		sqSeekAction->addChild(new ai::action::Seek(m_Yuna));
		sqSeekAction->addChild(new ai::action::CalculatePath(m_map));
	SeekROOT->addChild(sqSeekAction);
	SeekROOT->addChild(new ai::action::FollowPath());
	m_SeekGent->addBehaviour(SeekROOT);

	//// FLEE ////
	auto FleeROOT = new ai::Selector();
		auto sqFleeAction = new ai::Sequence();
		sqFleeAction->addChild(new ai::condition::WithinRange(m_Yuna, enemyStat.sightRange));
		sqFleeAction->addChild(new ai::action::Flee(m_Yuna));
		sqFleeAction->addChild(new ai::action::CalculatePath(m_map));
	FleeROOT->addChild(sqFleeAction);
	FleeROOT->addChild(new ai::action::FollowPath());
	m_FleeGent->addBehaviour(FleeROOT);

	//// GUARD ////
	//'Constant' behaviours
	auto bhUpdateLastSeen = new ai::action::UpdateLastSeen(m_Yuna);
	auto bhCalculatePath = new ai::action::CalculatePath(m_map);
	auto bhClearLastSeen = new ai::action::ClearLastSeen();
	auto bhReturnToPost = new ai::action::ReturnToPost();
	auto bhFollowPath = new ai::action::FollowPath();
	auto bhInspect = new ai::action::Inspect();
	auto bhAttack = new ai::action::Attack(m_Yuna);
	auto bhSeek = new ai::action::Seek(m_Yuna);
	auto bhFlee = new ai::action::Flee(m_Yuna);

		//// ActionSelector
		auto ActionSel = new ai::Selector();
	
			//Attack Sequence
			auto AttackSeq = new ai::Sequence();
			AttackSeq->addChild(new ai::condition::WithinRange(m_Yuna, enemyStat.attackRange));
			AttackSeq->addChild(new ai::action::UpdateState(ai::Agent::eState::ALERT));
			AttackSeq->addChild(bhUpdateLastSeen);									//Constant
				auto AttackDec = new ai::DelayDecorator(new ai::action::Attack(m_Yuna), enemyStat.attackSpeed);
			AttackSeq->addChild(AttackDec);
		ActionSel->addChild(AttackSeq);

			//Flee or Pursue Sequence
			auto FleeOrPursueSeq = new ai::Sequence();
			FleeOrPursueSeq->addChild(new ai::condition::WithinRange(m_Yuna, enemyStat.sightRange));
			FleeOrPursueSeq->addChild(new ai::action::UpdateState(ai::Agent::eState::ALERT));
			FleeOrPursueSeq->addChild(bhUpdateLastSeen);							//Constant
				auto FleeOrPursueSel = new ai::Selector();
					auto FleeSeq = new ai::Sequence();
					FleeSeq->addChild(new ai::condition::CheckHealth(enemyStat.lowHealthThres));	
					FleeSeq->addChild(bhFlee);										//Constant
				FleeOrPursueSel->addChild(FleeSeq);
				FleeOrPursueSel->addChild(bhSeek);									//Constant
			FleeOrPursueSeq->addChild(FleeOrPursueSel);
		ActionSel->addChild(FleeOrPursueSeq);

			//Inspect
			auto InspectSeq = new ai::Sequence();
			//InspectSeq->addChild(new ai::condition::WithinRange(m_Yuna, swordsman.suspiciousRange));
			//InspectSeq->addChild(new ai::action::UpdateState(ai::Agent::eState::SUSPICIOUS));
			//InspectSeq->addChild(new ai::action::UpdateLastSeen(m_Yuna));						//Constant
			InspectSeq->addChild(new ai::condition::LastSeenAvailable());
				auto UpdateStateSeq(new ai::Sequence());
					auto NotAlertState = new ai::NotDecorator(new ai::condition::CheckState(ai::Agent::eState::ALERT));
				UpdateStateSeq->addChild(NotAlertState);
				UpdateStateSeq->addChild(new ai::action::UpdateState(ai::Agent::eState::SUSPICIOUS));
			InspectSeq->addChild(new ai::SuccessDecorator(UpdateStateSeq));
			InspectSeq->addChild(bhInspect);													//Constant? Inspects what's at agent.lastSeen
			InspectSeq->addChild(new ai::action::Idle(2.0f, 3.0f));				//Idle between 3-4s
			InspectSeq->addChild(bhClearLastSeen);												//Constant
			InspectSeq->addChild(new ai::action::UpdateState(ai::Agent::eState::GUARD));
		ActionSel->addChild(InspectSeq);
			//InspectSeq->addChild(new ai::TimeoutDecorator(new ai::action::Idle(), 7.5f));

			//Guard
			auto GuardSeq = new ai::Sequence();
			GuardSeq->addChild(new ai::condition::CheckState(ai::Agent::eState::GUARD));
			GuardSeq->addChild(bhReturnToPost);						//Constant
		ActionSel->addChild(GuardSeq);

		//	//Patrol
		//	auto PatrolSeq = new ai::Sequence();
		//	PatrolSeq->addChild(new ai::condition::CheckState(ai::Agent::eState::GUARD));
		//	PatrolSeq->addChild(new ai::action::ReturnToPost());		//Constant
		//ActionSel->addChild(PatrolSeq);

		//Move
		auto MoveSeq = new ai::Sequence();
		MoveSeq->addChild(new ai::action::CalculatePath(m_map));	//Constant
		MoveSeq->addChild(new ai::action::FollowPath());			//Constant

	//ROOT
	auto SwordsmanRoot = new ai::Sequence();
		auto AlwaysSuccess = new ai::SuccessDecorator(ActionSel);
	SwordsmanRoot->addChild(AlwaysSuccess);
	//SwordsmanRoot->addChild(ActionSel);
	SwordsmanRoot->addChild(MoveSeq);
		
	/////////////////////////////
	//// NOTE: Can't seem to load the same AI behaviour root into multiple different agents
	//// They both use the same behaviours
	///////////////////////////

	////Load AI behaviours into enemies
	m_EnemyList[0]->addBehaviour(SwordsmanRoot);
	//auto SwordsmanRootCopy1 = SwordsmanRoot;
	//m_EnemyList[1]->addBehaviour(SwordsmanRootCopy1);
	//auto SwordsmanRootCopy2 = SwordsmanRoot;
	//m_EnemyList[2]->addBehaviour(SwordsmanRootCopy2);
	//auto SwordsmanRootCopy3 = SwordsmanRoot;
	//m_EnemyList[3]->addBehaviour(SwordsmanRootCopy3);

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
	m_Yuna->update(deltaTime);

	m_SeekGent->update(deltaTime);
	m_FleeGent->update(deltaTime);
	std::cout << "ENEMY: BEGIN" << std::endl;
	for (auto Enemy : m_EnemyList)
		Enemy->update(deltaTime);
	std::cout << "ENEMY: END" << std::endl;

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
	m_Yuna->draw(m_2dRenderer);

	//Draw DEBUG agents
	m_SeekGent->draw(m_2dRenderer);
	m_FleeGent->draw(m_2dRenderer);
	for (auto Enemy : m_EnemyList)
		Enemy->draw(m_2dRenderer);

	showInstructions();

#ifdef _DEBUG
	DEBUG(m_2dRenderer);
#endif // _DEBUG

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

void KunoApp::showInstructions()
{
	//// INSTRUCTIONS ////
	ImGui::Begin("INSTRUCTIONS");
	ImGui::Text("Press 'c' to toggle display of tile connections");
	ImGui::Text("Mouse wheel to zoom in and out");
	ImGui::Text("WSAD or move mouse to edge of screen to pan camera");
	ImGui::Text("Click on map to move player agent there");
	ImGui::Text("Left click to set start node, Right click to set end node");
	ImGui::TextWrapped("Press 'spacebar' to toggle between A* and Djikstra algorithm on the map");
	ImGui::End();
}
