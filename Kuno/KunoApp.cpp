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

#include <pkr\math\Vector2.h>
#include <pkr\math\Vector3.h>

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
#ifdef _DEBUG
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);
#elif NDEBUG
	m_font = new aie::Font("./font/consolas.ttf", 32);
#endif

	//Randomize seed
	srand((unsigned int)time(NULL));

	//// SETUPS ////
	if (setupUtilities() == false) return false;
	if (loadTextures() == false) return false;

	//Setup map and pathfinding
	setBackgroundColour(0.12f / 2.0f, 0.63f / 2.0f, 1.0f / 2.0f);
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
	delete m_seeker;
	delete m_fleer;
	for (auto g : m_guardList)
		delete g;

	//Map
	delete m_map;

	//Utilities
	delete m_camera;
	delete m_textureManager;
	delete m_depthSorter;
	delete m_coordConverter;
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

	m_seeker->update(deltaTime);
	m_fleer->update(deltaTime);

#ifdef _DEBUG
	std::cout << "ENEMY: BEGIN" << std::endl;
#endif // _DEBUG
	for (auto g : m_guardList)
		g->update(deltaTime);
#ifdef _DEBUG
	std::cout << "ENEMY: END" << std::endl;
#endif // _DEBUG

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
	m_seeker->draw(m_2dRenderer);
	m_fleer->draw(m_2dRenderer);
	for (auto g : m_guardList)
		g->draw(m_2dRenderer);

#ifdef _DEBUG
	DEBUG(m_2dRenderer);
#endif // _DEBUG

	m_2dRenderer->end();
	//// END DRAW ////
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
				//note: Z buffer depth of between 0-1 is reserved for the GUI

	//// Coord Converter ////
	m_coordConverter = new util::CoordConverter(m_camera);

	return true;
}

bool KunoApp::loadTextures()
{
#ifdef _DEBUG
	//Prototype
	//m_textureManager->addTexture("Floor", new aie::Texture("../bin/textures/prototype_iso/floor_N.png"));
	//m_textureManager->addTexture("FloorGrassRound", new aie::Texture("../bin/textures/prototype_iso/floorGrassRound_N.png"));
	//m_textureManager->addTexture("Slab", new aie::Texture("../bin/textures/prototype_iso/slab_N.png"));
	//m_textureManager->addTexture("SmallBlock", new aie::Texture("../bin/textures/prototype_iso/blockSmall_N.png"));
	//m_textureManager->addTexture("LargeBlock", new aie::Texture("../bin/textures/prototype_iso/blockLarge_N.png"));
	//m_textureManager->addTexture("HugeBlock", new aie::Texture("../bin/textures/prototype_iso/blockHuge_N.png"));
	//m_textureManager->addTexture("Column", new aie::Texture("../bin/textures/prototype_iso/column_N.png"));
	//m_textureManager->addTexture("Steps", new aie::Texture("../bin/textures/prototype_iso/stepsSmallSlabs_N.png"));
	//m_textureManager->addTexture("WallCorner", new aie::Texture("../bin/textures/prototype_iso/wallCorner_N.png"));

	//Kuno (My hand drawn tiles)
	m_textureManager->addTexture("Path", new aie::Texture("../bin/textures/assets/path.png"));
	m_textureManager->addTexture("Grass", new aie::Texture("../bin/textures/assets/grass.png"));
	m_textureManager->addTexture("Dirt", new aie::Texture("../bin/textures/assets/dirt.png"));
	m_textureManager->addTexture("Sand", new aie::Texture("../bin/textures/assets/sand.png"));
	m_textureManager->addTexture("Water", new aie::Texture("../bin/textures/assets/water.png"));
	m_textureManager->addTexture("DeepWater", new aie::Texture("../bin/textures/assets/deepwater.png"));
	m_textureManager->addTexture("Wall", new aie::Texture("../bin/textures/assets/wall.png"));
#elif NDEBUG
	//As above but with different paths (need to check exact reason)
	//Final path has to be "../assets/tiles/*.png"
	m_textureManager->addTexture("Path", new aie::Texture("./textures/assets/path.png"));
	m_textureManager->addTexture("Grass", new aie::Texture("./textures/assets/grass.png"));
	m_textureManager->addTexture("Dirt", new aie::Texture("./textures/assets/dirt.png"));
	m_textureManager->addTexture("Sand", new aie::Texture("./textures/assets/sand.png"));
	m_textureManager->addTexture("Water", new aie::Texture("./textures/assets/water.png"));
	m_textureManager->addTexture("DeepWater", new aie::Texture("./textures/assets/deepwater.png"));
	m_textureManager->addTexture("Wall", new aie::Texture("./textures/assets/wall.png"));
#endif

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
	m_Yuna = new ai::Agent(20.0f, pkr::Vector3(0.2f, 0.4f, 0.75f), { 350, 100 });
	m_Yuna->setAttack(playerStat.attack);
	m_Yuna->setSneakSpeed(playerStat.sneakSpeed);
	m_Yuna->setWalkSpeed(playerStat.walkSpeed);
	m_Yuna->setRunSpeed(playerStat.runSpeed);
	
	return true;
}

bool KunoApp::setupEnemies()
{
	typedef pkr::Vector3 Color;

	//Seek
	Color seekcol = {0.2f, 0.9f, 0.3f};		//Green
	m_seeker = new ai::Agent(enemyStat.size, seekcol, { 900, 850 });
	m_seeker->setWalkSpeed(enemyStat.walkSpeed);
	m_seeker->setRunSpeed(enemyStat.runSpeed);

	//Flee
	Color fleecol = { 0.85f, 0.85f, 0 };	//Yellow
	m_fleer = new ai::Agent(enemyStat.size, fleecol, { 800, 850 });
	m_fleer->setWalkSpeed(enemyStat.walkSpeed);
	m_fleer->setRunSpeed(enemyStat.runSpeed);

	//Guards
	int noOfGuards = 3;
	Color guardcol = { 0.9f, 0.2f, 0 };

	//Create
	for (int i = 0; i < noOfGuards; ++i)
		m_guardList.push_back(new ai::Agent(enemyStat.size, enemyStat.colour));

	//Set guard positions
	m_guardList[0]->pos = (pkr::Vector2(850, 850)); m_guardList[0]->patrolPath().push_back(pkr::Vector2(850, 850));
	m_guardList[1]->pos = (pkr::Vector2(450, 750)); m_guardList[1]->patrolPath().push_back(pkr::Vector2(450, 750));
	m_guardList[2]->pos = (pkr::Vector2(450, 600)); m_guardList[2]->patrolPath().push_back(pkr::Vector2(450, 600));
	//m_EnemyList[3]->pos = (pkr::Vector2(300, 300)); m_EnemyList[3]->patrolPath().push_back(pkr::Vector2(300, 300));

	//Set attributes
	for (auto g : m_guardList) {
		g->setAttack(enemyStat.attack);
		g->setWalkSpeed(enemyStat.walkSpeed);
		g->setRunSpeed(enemyStat.runSpeed);
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
	m_seeker->addBehaviour(SeekROOT);

	//// FLEE ////
	auto FleeROOT = new ai::Selector();
		auto sqFleeAction = new ai::Sequence();
		sqFleeAction->addChild(new ai::condition::WithinRange(m_Yuna, enemyStat.sightRange));
		sqFleeAction->addChild(new ai::action::Flee(m_Yuna));
		sqFleeAction->addChild(new ai::action::CalculatePath(m_map));
	FleeROOT->addChild(sqFleeAction);
	FleeROOT->addChild(new ai::action::FollowPath());
	m_fleer->addBehaviour(FleeROOT);

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
	m_guardList[0]->addBehaviour(SwordsmanRoot);
	//auto SwordsmanRootCopy1 = SwordsmanRoot;
	//m_guardList[1]->addBehaviour(SwordsmanRoot);
	//auto SwordsmanRootCopy2 = SwordsmanRoot;
	//m_EnemyList[2]->addBehaviour(SwordsmanRootCopy2);
	//auto SwordsmanRootCopy3 = SwordsmanRoot;
	//m_EnemyList[3]->addBehaviour(SwordsmanRootCopy3);

	return true;
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

	//// Instructions ////
	if (ImGui::CollapsingHeader("Help"))
	{
		ImGui::Text("C - Toggle tile connections");
		ImGui::Text("Mouse wheel - Zoom in/out");
		ImGui::Text("WASD or mouse to edges - Pan camera");
		ImGui::Text("Click on map to move player");
		ImGui::Text("Left click - Set start test path node");
		ImGui::Text("Right click - Set end test path node");
		ImGui::Text("Space - Toggle pathfinding algorithm");
	}

	//// Camera ////
	if (ImGui::CollapsingHeader("Camera"))
	{
		ImGui::Text("x: %.0f, y: %.0f", m_camera->x, m_camera->y);
		ImGui::Text("Zoom: %.3f", m_camera->zoom);
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
	// An orange circle will locate where the cursor is should be sorted by the depth sorter
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

	//// Tile connections ////
	if (ImGui::CollapsingHeader("Tile Connections"))
	{
		int index = 0;
		//For each 
		for (auto t : m_map->getTiles())
		{
			for (auto c : t->connections)
			{
				//Canvas coords
				pkr::Vector2 start = t->cPos;
				pkr::Vector2 end = c->target->cPos;

				//Set line color based on terrain cost
				float maxCost = 5.0f;
				// (c->cost / maxCost)
				renderer->setRenderColour((c->cost / maxCost), 0, 0);
				renderer->drawLine(start.x, start.y, end.x, end.y, 2.f, 0.2f);

				//World coords
				start = t->pos;
				end = c->target->pos;

				//Print debugs
				ImGui::Text("Edge: %d, x1: %.1f, y1: %.1f, x2: %.1f, y2: %.1f", index, start.x, start.y, end.x, end.y);

			} ++index;
		}
	}

	if (ImGui::CollapsingHeader("Path"))
	{
		const char* algorithm;
		algorithm = (m_map->useAstar) ? "A* Search" : "Dijkstra Search";
		ImGui::TextColored({ 1,0.5f,0,1 }, algorithm);	ImGui::SameLine; ImGui::Text("Press space to toggle");

		//Print path waypoints
		auto path = m_map->getPath();
		renderer->setRenderColour(0.90f, 0, 0);
		if (!path.empty()) {
			//Loop through all sets of waypoints and draw the path (isometrically)
			for (int i = 0; i < path.size() - 1; ++i) {
				auto start = CoordConverter()->WorldToCanvas(path[i]);
				auto end = CoordConverter()->WorldToCanvas(path[i + 1]);
				renderer->drawLine(start.x, start.y, end.x, end.y, 6.f, 0.3f);
				ImGui::Text("%d > x: %.2f, y: %.2f", i, start.x, start.y);
			}
		}
	}

	ImGui::End();
}
