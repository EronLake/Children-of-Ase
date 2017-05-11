//------------------------------
//Eron Lake
//MyGameEngine
//main.cpp
//------------------------------
#include "stdafx.h"
#include <stdio.h>   
#include <stdlib.h>     
#include <time.h>
#include "Player.h"
#include "Village.h"
#include <crtdbg.h>
#include "Rectangle.h"
#include "QuadTree.h"
#include "GameWindow.h"
#include "common.h"
#include "Input.h"
#include "Task.h"
#include "TaskBuffer.h"
#include "MessageLog.h"
#include "DummyController.h"
#include "PhysicsManager.h"
#include "AudioManager.h"
#include "Manager.h"
#include "Movement.h"
#include "RenderHelper.h"
#include "RenderManager.h"
#include <conio.h>
#include "CheckClass.h"
#include "TaskBufferTestSuite.h"
#include <Windows.h>
#include "RegionState.h"
//#include "DialogueGui.h"

//#include "Pool.h"

#include "fmod.hpp"
#include "SoundSystem.h"
#include "memManager.h"

#include "MemoryTestSuite.h"
#include "AudioTestSuite.h"

#include "TestManager.h"
#include "PhysicsTestSuite.h"
#include <ctime> 

#include "DialogueController.h"
#include "DialogueHelper.h"
#include "DialougeTestSuite.h"
#include "DialogueConfig.h"
#include "TagConfig.h"

#include "AIManager.h"
#include "AIController.h"

#include "ObjConfig.h"
#include "HeroConfig.h"

#include "ActionPool.h"
#include "ActionHelper.h"
#include "ActionConfig.h"
//class ActionHelper;
#include "Line.h"
#include "ActionExecFunctions.h"
#include "Alliance.h"
#include "PartyManager.h"
//#include <boost/thread/thread.hpp>  //This is used for Ian's multithread section, but the user needs the boost compiled library installed on their computer
#include "thread"

#include "QuestManager.h"

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#ifdef _DEBUG
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

/*
this variable is used to keep track of time (in frames)
it is imcremented in the game loop
*/
extern int frame_count = 0;
extern bool game_ended = false;

using namespace std;

Texture* Point::tex = new Texture();
Texture* Rectangle::tex = new Texture();
Texture* Rectangle::texUP = new Texture();
Texture* Rectangle::texDOWN = new Texture();
Texture* Rectangle::texLEFT = new Texture();
Texture* Rectangle::texRIGHT = new Texture();
Texture* Rectangle::texAtkUP = new Texture();
Texture* Rectangle::texAtkDOWN = new Texture();
Texture* Rectangle::texAtkLEFT = new Texture();
Texture* Rectangle::texAtkRIGHT = new Texture();
std::mutex mu;
//void testQuadTree();
//bool checkCollision(WorldObj *recA, WorldObj *recB);	//given two bounding boxes, check if they collide
//bool coordOverlap(int value, int min, int max) { return (value >= min) && (value <= max); }		//helper func for checkCollision

void FPS(bool b);
void GAMEPLAY_LOOP(QuadTree* _Quadtree);

bool lineCollision(Line l1, Line l2);
/// Helper function passed to thread to set file. Param is a tuple, first being the Texture* to work on, and second being the param needed to call setFile().
void set_file_with_thread(Texture* t, const pair<string, int>* p_tuple) {
	//std::lock_guard<std::mutex> guard(mu); 
	t->setFile(p_tuple->first, p_tuple->second);
}


int main() {
	WorldObj* screen = new WorldObj(Vector2f(0.0, 0.0), 25000U, 25000U);	//init screen

	QuadTree* collideTree = new QuadTree(0, *screen);
	GameWindow::init();
	GAMEPLAY_LOOP(collideTree);
	return 0;
}


void GAMEPLAY_LOOP(QuadTree* _QuadTree)
{
	game_state current_game_state = game_state::load_game;
	Rectangle::tex->setFile("Assets/Sprites/blankr.png", 1);
	Point::tex->setFile("Assets/Sprites/point.png", 1);

	RiverObj* rivObj = new RiverObj();
	rivObj->initialize_lines();

	UniformGrid* grid = new UniformGrid();
	grid->insert_objs_to_grid(rivObj->getLines());
	
	vector<WorldObj*> recVec;
	vector<WorldObj*> movVec;
	vector<WorldObj*>* largeStruct = new vector<WorldObj*>();
	vector<WorldObj*>* recVec_ptr = &recVec;
	vector<WorldObj*>* movVec_ptr = &movVec;
	vector<Hero*> heroes;

	/* MULTITHREADING SETUP */

	//unordered_map<Texture*, pair<string, int>> textureMap ;
	int num_of_threads = std::thread::hardware_concurrency();
	vector<thread> thread_Vec;

	//psuedo Gameloop
	MessageLog* mLog = new MessageLog();
	TaskBuffer* tBuffer = new TaskBuffer(mLog);

	//need this here for map editor
	ChildrenOfOsi* gameplay_functions = new ChildrenOfOsi(mLog, tBuffer);

	RenderManager* RenM = new RenderManager(mLog, tBuffer, _QuadTree, gameplay_functions, rivObj, largeStruct);
	DummyController* DumM = new DummyController(mLog, tBuffer);
	PhysicsManager* PhysM = new PhysicsManager(mLog, tBuffer, _QuadTree, grid, rivObj);
	//PartyManager* partyM = new PartyManager(gameplay_functions, Alex);
	memManager* memM = new memManager(mLog, tBuffer);
	TestManager* TestM = new TestManager(mLog, tBuffer);
	AudioManager* AudM = new AudioManager(mLog, tBuffer);
	AIHelper* ai = new AIHelper();
	AIManager* AIM = new AIManager(mLog, tBuffer, ai);
	//AIController* AiController = new AIController();
	//ActionHelper::ai = AiController;
	ActionHelper::gameplay_func = gameplay_functions;
	CombatController* combatControl = new CombatController(gameplay_functions);
	QuestManager* questM = new QuestManager;

	//the order defines what order the managers the tasks will be sent to
	DumM->register_manager();
	PhysM->register_manager();
	memM->register_manager();

	AudM->register_manager();
	//TestM->register_manager();
	AIM->register_manager();

	RenM->register_manager();
	bool switch_music = false;
	bool in_village = false;

	HeroConfig::import_config(movVec_ptr, &ObjConfig::textureMap, gameplay_functions, tBuffer);
	Village::init_villages();

	Player* Alex = dynamic_cast<Player*>(Containers::hero_table["Shango"]);


	//draws the logo on startup
	gameplay_functions->draw_logo(Alex);
	tBuffer->run();

	Region* Marsh = new Region("Marsh", "Music/RegionThemes/DesertRegion.flac", "Music/HeroThemes/oya.flac", { 8000,2900 });
	Region* Desert = new Region("Desert", "Music/RegionThemes/MarshRegion.flac", "Music/HeroThemes/ogun.flac", { 5045,13465 });
	Region* Mountain = new Region("Mountain", "Music/RegionThemes/MountainRegion.flac", "nothing", { 21000,4000 });
	Region* Jungle = new Region("Jungle", "Music/RegionThemes/JungleRegion.flac", "Music/HeroThemes/oya.flac", { 17157,20960 });

	
	Region current_region = *Desert;
	Region next_region = *Desert;

	RegionState::regions.push_back(Marsh);
	RegionState::regions.push_back(Desert);
	RegionState::regions.push_back(Mountain);
	RegionState::regions.push_back(Jungle);

	RegionState::current_region = current_region;
	RegionState::next_region = next_region;


	Input* iController = new Input(gameplay_functions, Alex, RenM->renderHelper, tBuffer, recVec_ptr, movVec_ptr);

	Hero* staticRec = Containers::hero_table["Yemoja"];
	heroes.push_back(staticRec);
	Hero* oya = Containers::hero_table["Oya"];
	heroes.push_back(oya);

	vector<vector<Texture*>> starting_location;
	
	ObjConfig::import_config(recVec_ptr, gameplay_functions, tBuffer);

	DialogueConfig::import_config(gameplay_functions, tBuffer);
	DialogueController::getDialogueHelper()->fill_conversations();
	TagConfig::import_config(gameplay_functions, tBuffer);

	WorldObj* barrel = new WorldObj(Vector2f(5200, 3900), 75, 75);
	
	//added so loading the map is optional
	if (LOAD_MAP) {

		gameplay_functions->add_texture("map1_1", 0, 0, 0);
		gameplay_functions->add_texture("map1_2", 0, 0, 0);
		gameplay_functions->add_texture("map1_3", 0, 0, 0);
		gameplay_functions->add_texture("map1_4", 0, 0, 0);
		gameplay_functions->add_texture("map1_5", 0, 0, 0);

		gameplay_functions->add_texture("map2_1", 0, 0, 0);
		gameplay_functions->add_texture("map2_2", 0, 0, 0);
		gameplay_functions->add_texture("map2_3", 0, 0, 0);
		gameplay_functions->add_texture("map2_4", 0, 0, 0);
		gameplay_functions->add_texture("map2_5", 0, 0, 0);

		gameplay_functions->add_texture("map3_1", 0, 0, 0);
		gameplay_functions->add_texture("map3_2", 0, 0, 0);
		gameplay_functions->add_texture("map3_3", 0, 0, 0);
		gameplay_functions->add_texture("map3_4", 0, 0, 0);
		gameplay_functions->add_texture("map3_5", 0, 0, 0);

		gameplay_functions->add_texture("map4_1", 0, 0, 0);
		gameplay_functions->add_texture("map4_2", 0, 0, 0);
		gameplay_functions->add_texture("map4_3", 0, 0, 0);
		gameplay_functions->add_texture("map4_4", 0, 0, 0);
		gameplay_functions->add_texture("map4_5", 0, 0, 0);

		gameplay_functions->add_texture("map5_1", 0, 0, 0);
		gameplay_functions->add_texture("map5_2", 0, 0, 0);
		gameplay_functions->add_texture("map5_3", 0, 0, 0);
		gameplay_functions->add_texture("map5_4", 0, 0, 0);
		gameplay_functions->add_texture("map5_5", 0, 0, 0);

		tBuffer->run();
		RenderHelper::gmap->setTextures();
		RenderHelper::gmap->setSprite();
	}

	HDC hdc = wglGetCurrentDC();
	HGLRC mainContext = wglGetCurrentContext();
	HGLRC loaderContextM = wglCreateContext(hdc);
	wglShareLists(mainContext, loaderContextM);
	std::thread tm([=]() {
		wglMakeCurrent(hdc, loaderContextM);
		RenderHelper::gmap->loadTexture(Alex->getLoc());
		wglMakeCurrent(nullptr, nullptr);
		wglDeleteContext(loaderContextM);
		glFinish();
	});

	gameplay_functions->add_texture("silverSoldierTexture", 0, 0, 0);
	gameplay_functions->add_texture("silverSoldierIdleTex", 0, 0, 0);
	gameplay_functions->add_texture("blueSoldierTexture", 0, 0, 0);
	gameplay_functions->add_texture("blueSoldierIdleTex", 0, 0, 0);
	tBuffer->run();

	ObjConfig::textureMap[Containers::texture_table["silverSoldierTexture"]] = pair<string, int>("Assets/Sprites/SilverSoldierForwardIdle.png", 22);
	ObjConfig::textureMap[Containers::texture_table["silverSoldierIdleTex"]] = pair<string, int>("Assets/Sprites/SilverSoldierForwardIdle.png", 22);
	ObjConfig::textureMap[Containers::texture_table["blueSoldierTexture"]] = pair<string, int>("Assets/Sprites/BlueSoldierForwardIdle.png", 22);
	ObjConfig::textureMap[Containers::texture_table["blueSoldierIdleTex"]] = pair<string, int>("Assets/Sprites/BlueSoldierForwardIdle.png", 22);
	ObjConfig::standard_con.push_back(Containers::texture_table["silverSoldierTexture"]);
	ObjConfig::standard_con.push_back(Containers::texture_table["silverSoldierIdleTex"]);
	ObjConfig::marsh_con.push_back(Containers::texture_table["blueSoldierTexture"]);
	ObjConfig::marsh_con.push_back(Containers::texture_table["blueSoldierIdleTex"]);

	gameplay_functions->add_texture("ss_upRunTex", 0, 0, 0);
	gameplay_functions->add_texture("ss_downRunTex", 0, 0, 0);
	gameplay_functions->add_texture("ss_leftRunTex", 0, 0, 0);
	gameplay_functions->add_texture("ss_rightRunTex", 0, 0, 0);
	gameplay_functions->add_texture("ss_upIdleTex", 0, 0, 0);
	gameplay_functions->add_texture("ss_downIdleTex", 0, 0, 0);
	gameplay_functions->add_texture("ss_leftIdleTex", 0, 0, 0);
	gameplay_functions->add_texture("ss_rightIdleTex", 0, 0, 0);
	gameplay_functions->add_texture("ss_upAtkTex", 0, 0, 0);
	gameplay_functions->add_texture("ss_downAtkTex", 0, 0, 0);
	gameplay_functions->add_texture("ss_leftAtkTex", 0, 0, 0);
	gameplay_functions->add_texture("ss_rightAtkTex", 0, 0, 0);
	gameplay_functions->add_texture("ss_upHurtTex", 0, 0, 0);
	gameplay_functions->add_texture("ss_downHurtTex", 0, 0, 0);
	gameplay_functions->add_texture("ss_leftHurtTex", 0, 0, 0);
	gameplay_functions->add_texture("ss_rightHurtTex", 0, 0, 0);
	gameplay_functions->add_texture("ss_upWalkTex", 0, 0, 0);
	gameplay_functions->add_texture("ss_downWalkTex", 0, 0, 0);
	gameplay_functions->add_texture("ss_leftWalkTex", 0, 0, 0);
	gameplay_functions->add_texture("ss_rightWalkTex", 0, 0, 0);
	gameplay_functions->add_texture("ss_upLungeTex", 0, 0, 0);
	gameplay_functions->add_texture("ss_downLungeTex", 0, 0, 0);
	gameplay_functions->add_texture("ss_leftLungeTex", 0, 0, 0);
	gameplay_functions->add_texture("ss_rightLungeTex", 0, 0, 0);
	gameplay_functions->add_texture("ss_upDeathTex", 0, 0, 0);
	gameplay_functions->add_texture("ss_downDeathTex", 0, 0, 0);
	gameplay_functions->add_texture("ss_leftDeathTex", 0, 0, 0);
	gameplay_functions->add_texture("ss_rightDeathTex", 0, 0, 0);

	tBuffer->run();

	ObjConfig::textureMap[Containers::texture_table["ss_upRunTex"]] = pair<string, int>("Assets/Sprites/SilverSoldierBackSprint.png", 16);
	ObjConfig::textureMap[Containers::texture_table["ss_downRunTex"]] = pair<string, int>("Assets/Sprites/SilverSoldierForwardSprint.png", 16);
	ObjConfig::textureMap[Containers::texture_table["ss_leftRunTex"]] = pair<string, int>("Assets/Sprites/SilverSoldierLeftSprint.png", 16);
	ObjConfig::textureMap[Containers::texture_table["ss_rightRunTex"]] = pair<string, int>("Assets/Sprites/SilverSoldierRightSprint.png", 16);
	ObjConfig::textureMap[Containers::texture_table["ss_upIdleTex"]] = pair<string, int>("Assets/Sprites/SilverSoldierBackIdle.png", 22);
	ObjConfig::textureMap[Containers::texture_table["ss_downIdleTex"]] = pair<string, int>("Assets/Sprites/SilverSoldierForwardIdle.png", 22);
	ObjConfig::textureMap[Containers::texture_table["ss_leftIdleTex"]] = pair<string, int>("Assets/Sprites/SilverSoldierLeftIdle.png", 22);
	ObjConfig::textureMap[Containers::texture_table["ss_rightIdleTex"]] = pair<string, int>("Assets/Sprites/SilverSoldierRightIdle.png", 22);
	ObjConfig::textureMap[Containers::texture_table["ss_upAtkTex"]] = pair<string, int>("Assets/Sprites/SilverSoldierBackSwing.png", 24);
	ObjConfig::textureMap[Containers::texture_table["ss_downAtkTex"]] = pair<string, int>("Assets/Sprites/SilverSoldierForwardSwing.png", 24);
	ObjConfig::textureMap[Containers::texture_table["ss_leftAtkTex"]] = pair<string, int>("Assets/Sprites/SilverSoldierLeftSwing.png", 24);
	ObjConfig::textureMap[Containers::texture_table["ss_rightAtkTex"]] = pair<string, int>("Assets/Sprites/SilverSoldierRightSwing.png", 24);
	ObjConfig::textureMap[Containers::texture_table["ss_upHurtTex"]] = pair<string, int>("Assets/Sprites/SilverSoldierBackRecoil.png", 18);
	ObjConfig::textureMap[Containers::texture_table["ss_downHurtTex"]] = pair<string, int>("Assets/Sprites/SilverSoldierForwardRecoil.png", 18);
	ObjConfig::textureMap[Containers::texture_table["ss_leftHurtTex"]] = pair<string, int>("Assets/Sprites/SilverSoldierLeftRecoil.png", 18);
	ObjConfig::textureMap[Containers::texture_table["ss_rightHurtTex"]] = pair<string, int>("Assets/Sprites/SilverSoldierRightRecoil.png", 18);
	ObjConfig::textureMap[Containers::texture_table["ss_upWalkTex"]] = pair<string, int>("Assets/Sprites/SilverSoldierBackWalk.png", 32);
	ObjConfig::textureMap[Containers::texture_table["ss_downWalkTex"]] = pair<string, int>("Assets/Sprites/SilverSoldierForwardWalk.png", 32);
	ObjConfig::textureMap[Containers::texture_table["ss_leftWalkTex"]] = pair<string, int>("Assets/Sprites/SilverSoldierLeftWalk.png", 32);
	ObjConfig::textureMap[Containers::texture_table["ss_rightWalkTex"]] = pair<string, int>("Assets/Sprites/SilverSoldierRightWalk.png", 32);
	ObjConfig::textureMap[Containers::texture_table["ss_upLungeTex"]] = pair<string, int>("Assets/Sprites/SilverSoldierBackLunge.png", 7);
	ObjConfig::textureMap[Containers::texture_table["ss_downLungeTex"]] = pair<string, int>("Assets/Sprites/SilverSoldierForwardLunge.png", 7);
	ObjConfig::textureMap[Containers::texture_table["ss_leftLungeTex"]] = pair<string, int>("Assets/Sprites/SilverSoldierLeftLunge.png", 7);
	ObjConfig::textureMap[Containers::texture_table["ss_rightLungeTex"]] = pair<string, int>("Assets/Sprites/SilverSoldierRightLunge.png", 7);
	ObjConfig::textureMap[Containers::texture_table["ss_upDeathTex"]] = pair<string, int>("Assets/Sprites/SilverSoldierRightRecoil.png", 18);
	ObjConfig::textureMap[Containers::texture_table["ss_downDeathTex"]] = pair<string, int>("Assets/Sprites/SilverSoldierRightRecoil.png", 18);
	ObjConfig::textureMap[Containers::texture_table["ss_leftDeathTex"]] = pair<string, int>("Assets/Sprites/SilverSoldierRightRecoil.png", 18);
	ObjConfig::textureMap[Containers::texture_table["ss_rightDeathTex"]] = pair<string, int>("Assets/Sprites/SilverSoldierRightRecoil.png", 18);


	ObjConfig::mountain_con.push_back(Containers::texture_table["ss_upRunTex"]);
	ObjConfig::mountain_con.push_back(Containers::texture_table["ss_downRunTex"]);
	ObjConfig::mountain_con.push_back(Containers::texture_table["ss_leftRunTex"]);
	ObjConfig::mountain_con.push_back(Containers::texture_table["ss_rightRunTex"]);
	ObjConfig::mountain_con.push_back(Containers::texture_table["ss_upIdleTex"]);
	ObjConfig::mountain_con.push_back(Containers::texture_table["ss_downIdleTex"]);
	ObjConfig::mountain_con.push_back(Containers::texture_table["ss_leftIdleTex"]);
	ObjConfig::mountain_con.push_back(Containers::texture_table["ss_rightIdleTex"]);
	ObjConfig::mountain_con.push_back(Containers::texture_table["ss_upAtkTex"]);
	ObjConfig::mountain_con.push_back(Containers::texture_table["ss_downAtkTex"]);
	ObjConfig::mountain_con.push_back(Containers::texture_table["ss_leftAtkTex"]);
	ObjConfig::mountain_con.push_back(Containers::texture_table["ss_rightAtkTex"]);
	ObjConfig::mountain_con.push_back(Containers::texture_table["ss_upHurtTex"]);
	ObjConfig::mountain_con.push_back(Containers::texture_table["ss_downHurtTex"]);
	ObjConfig::mountain_con.push_back(Containers::texture_table["ss_leftHurtTex"]);
	ObjConfig::mountain_con.push_back(Containers::texture_table["ss_rightHurtTex"]);
	ObjConfig::mountain_con.push_back(Containers::texture_table["ss_upWalkTex"]);
	ObjConfig::mountain_con.push_back(Containers::texture_table["ss_downWalkTex"]);
	ObjConfig::mountain_con.push_back(Containers::texture_table["ss_leftWalkTex"]);
	ObjConfig::mountain_con.push_back(Containers::texture_table["ss_rightWalkTex"]);
	ObjConfig::mountain_con.push_back(Containers::texture_table["ss_upLungeTex"]);
	ObjConfig::mountain_con.push_back(Containers::texture_table["ss_downLungeTex"]);
	ObjConfig::mountain_con.push_back(Containers::texture_table["ss_leftLungeTex"]);
	ObjConfig::mountain_con.push_back(Containers::texture_table["ss_rightLungeTex"]);
	ObjConfig::mountain_con.push_back(Containers::texture_table["ss_upDeathTex"]);
	ObjConfig::mountain_con.push_back(Containers::texture_table["ss_downDeathTex"]);
	ObjConfig::mountain_con.push_back(Containers::texture_table["ss_leftDeathTex"]);
	ObjConfig::mountain_con.push_back(Containers::texture_table["ss_rightDeathTex"]);

	gameplay_functions->add_texture("bs_upRunTex", 0, 0, 0);
	gameplay_functions->add_texture("bs_downRunTex", 0, 0, 0);
	gameplay_functions->add_texture("bs_leftRunTex", 0, 0, 0);
	gameplay_functions->add_texture("bs_rightRunTex", 0, 0, 0);
	gameplay_functions->add_texture("bs_upIdleTex", 0, 0, 0);
	gameplay_functions->add_texture("bs_downIdleTex", 0, 0, 0);
	gameplay_functions->add_texture("bs_leftIdleTex", 0, 0, 0);
	gameplay_functions->add_texture("bs_rightIdleTex", 0, 0, 0);
	gameplay_functions->add_texture("bs_upAtkTex", 0, 0, 0);
	gameplay_functions->add_texture("bs_downAtkTex", 0, 0, 0);
	gameplay_functions->add_texture("bs_leftAtkTex", 0, 0, 0);
	gameplay_functions->add_texture("bs_rightAtkTex", 0, 0, 0);
	gameplay_functions->add_texture("bs_upHurtTex", 0, 0, 0);
	gameplay_functions->add_texture("bs_downHurtTex", 0, 0, 0);
	gameplay_functions->add_texture("bs_leftHurtTex", 0, 0, 0);
	gameplay_functions->add_texture("bs_rightHurtTex", 0, 0, 0);
	gameplay_functions->add_texture("bs_upWalkTex", 0, 0, 0);
	gameplay_functions->add_texture("bs_downWalkTex", 0, 0, 0);
	gameplay_functions->add_texture("bs_leftWalkTex", 0, 0, 0);
	gameplay_functions->add_texture("bs_rightWalkTex", 0, 0, 0);
	gameplay_functions->add_texture("bs_upLungeTex", 0, 0, 0);
	gameplay_functions->add_texture("bs_downLungeTex", 0, 0, 0);
	gameplay_functions->add_texture("bs_leftLungeTex", 0, 0, 0);
	gameplay_functions->add_texture("bs_rightLungeTex", 0, 0, 0);
	gameplay_functions->add_texture("bs_upDeathTex", 0, 0, 0);
	gameplay_functions->add_texture("bs_downDeathTex", 0, 0, 0);
	gameplay_functions->add_texture("bs_leftDeathTex", 0, 0, 0);
	gameplay_functions->add_texture("bs_rightDeathTex", 0, 0, 0);
	tBuffer->run();

	ObjConfig::textureMap[Containers::texture_table["bs_upRunTex"]] = pair<string, int>("Assets/Sprites/BlueSoldierBackSprint.png", 16);
	ObjConfig::textureMap[Containers::texture_table["bs_downRunTex"]] = pair<string, int>("Assets/Sprites/BlueSoldierForwardSprint.png", 16);
	ObjConfig::textureMap[Containers::texture_table["bs_leftRunTex"]] = pair<string, int>("Assets/Sprites/BlueSoldierLeftSprint.png", 16);
	ObjConfig::textureMap[Containers::texture_table["bs_rightRunTex"]] = pair<string, int>("Assets/Sprites/BlueSoldierRightSprint.png", 16);
	ObjConfig::textureMap[Containers::texture_table["bs_upIdleTex"]] = pair<string, int>("Assets/Sprites/BlueSoldierBackIdle.png", 22);
	ObjConfig::textureMap[Containers::texture_table["bs_downIdleTex"]] = pair<string, int>("Assets/Sprites/BlueSoldierForwardIdle.png", 22);
	ObjConfig::textureMap[Containers::texture_table["bs_leftIdleTex"]] = pair<string, int>("Assets/Sprites/BlueSoldierLeftIdle.png", 22);
	ObjConfig::textureMap[Containers::texture_table["bs_rightIdleTex"]] = pair<string, int>("Assets/Sprites/BlueSoldierRightIdle.png", 22);
	ObjConfig::textureMap[Containers::texture_table["bs_upAtkTex"]] = pair<string, int>("Assets/Sprites/BlueSoldierBackSwing.png", 13);
	ObjConfig::textureMap[Containers::texture_table["bs_downAtkTex"]] = pair<string, int>("Assets/Sprites/BlueSoldierForwardSwing.png", 13);
	ObjConfig::textureMap[Containers::texture_table["bs_leftAtkTex"]] = pair<string, int>("Assets/Sprites/BlueSoldierLeftSwing.png", 13);
	ObjConfig::textureMap[Containers::texture_table["bs_rightAtkTex"]] = pair<string, int>("Assets/Sprites/BlueSoldierRightSwing.png", 13);
	ObjConfig::textureMap[Containers::texture_table["bs_upHurtTex"]] = pair<string, int>("Assets/Sprites/BlueSoldierBackRecoil.png", 18);
	ObjConfig::textureMap[Containers::texture_table["bs_downHurtTex"]] = pair<string, int>("Assets/Sprites/BlueSoldierForwardRecoil.png", 18);
	ObjConfig::textureMap[Containers::texture_table["bs_leftHurtTex"]] = pair<string, int>("Assets/Sprites/BlueSoldierLeftRecoil.png", 18);
	ObjConfig::textureMap[Containers::texture_table["bs_rightHurtTex"]] = pair<string, int>("Assets/Sprites/BlueSoldierRightRecoil.png", 18);
	ObjConfig::textureMap[Containers::texture_table["bs_upWalkTex"]] = pair<string, int>("Assets/Sprites/BlueSoldierBackWalk.png", 32);
	ObjConfig::textureMap[Containers::texture_table["bs_downWalkTex"]] = pair<string, int>("Assets/Sprites/BlueSoldierForwardWalk.png", 32);
	ObjConfig::textureMap[Containers::texture_table["bs_leftWalkTex"]] = pair<string, int>("Assets/Sprites/BlueSoldierLeftWalk.png", 32);
	ObjConfig::textureMap[Containers::texture_table["bs_rightWalkTex"]] = pair<string, int>("Assets/Sprites/BlueSoldierRightWalk.png", 32);
	ObjConfig::textureMap[Containers::texture_table["bs_upLungeTex"]] = pair<string, int>("Assets/Sprites/BlueSoldierBackLunge.png", 7);
	ObjConfig::textureMap[Containers::texture_table["bs_downLungeTex"]] = pair<string, int>("Assets/Sprites/BlueSoldierForwardLunge.png", 7);
	ObjConfig::textureMap[Containers::texture_table["bs_leftLungeTex"]] = pair<string, int>("Assets/Sprites/BlueSoldierLeftLunge.png", 7);
	ObjConfig::textureMap[Containers::texture_table["bs_rightLungeTex"]] = pair<string, int>("Assets/Sprites/BlueSoldierRightLunge.png", 7);
	ObjConfig::textureMap[Containers::texture_table["bs_upDeathTex"]] = pair<string, int>("Assets/Sprites/BlueSoldierUpRecoil.png", 18);
	ObjConfig::textureMap[Containers::texture_table["bs_downDeathTex"]] = pair<string, int>("Assets/Sprites/BlueSoldierDownRecoil.png", 18);
	ObjConfig::textureMap[Containers::texture_table["bs_leftDeathTex"]] = pair<string, int>("Assets/Sprites/BlueSoldierLeftRecoil.png", 18);
	ObjConfig::textureMap[Containers::texture_table["bs_rightDeathTex"]] = pair<string, int>("Assets/Sprites/BlueSoldierRightRecoil.png", 18);

	gameplay_functions->add_texture("treeTex", 0, 0, 0);
	ObjConfig::marsh_con.push_back(Containers::texture_table["bs_upRunTex"]);
	ObjConfig::marsh_con.push_back(Containers::texture_table["bs_downRunTex"]);
	ObjConfig::marsh_con.push_back(Containers::texture_table["bs_leftRunTex"]);
	ObjConfig::marsh_con.push_back(Containers::texture_table["bs_rightRunTex"]);
	ObjConfig::marsh_con.push_back(Containers::texture_table["bs_upIdleTex"]);
	ObjConfig::marsh_con.push_back(Containers::texture_table["bs_downIdleTex"]);
	ObjConfig::marsh_con.push_back(Containers::texture_table["bs_leftIdleTex"]);
	ObjConfig::marsh_con.push_back(Containers::texture_table["bs_rightIdleTex"]);
	ObjConfig::marsh_con.push_back(Containers::texture_table["bs_upAtkTex"]);
	ObjConfig::marsh_con.push_back(Containers::texture_table["bs_downAtkTex"]);
	ObjConfig::marsh_con.push_back(Containers::texture_table["bs_leftAtkTex"]);
	ObjConfig::marsh_con.push_back(Containers::texture_table["bs_rightAtkTex"]);
	ObjConfig::marsh_con.push_back(Containers::texture_table["bs_upHurtTex"]);
	ObjConfig::marsh_con.push_back(Containers::texture_table["bs_downHurtTex"]);
	ObjConfig::marsh_con.push_back(Containers::texture_table["bs_leftHurtTex"]);
	ObjConfig::marsh_con.push_back(Containers::texture_table["bs_rightHurtTex"]);
	ObjConfig::marsh_con.push_back(Containers::texture_table["bs_upWalkTex"]);
	ObjConfig::marsh_con.push_back(Containers::texture_table["bs_downWalkTex"]);
	ObjConfig::marsh_con.push_back(Containers::texture_table["bs_leftWalkTex"]);
	ObjConfig::marsh_con.push_back(Containers::texture_table["bs_rightWalkTex"]);
	ObjConfig::marsh_con.push_back(Containers::texture_table["bs_upLungeTex"]);
	ObjConfig::marsh_con.push_back(Containers::texture_table["bs_downLungeTex"]);
	ObjConfig::marsh_con.push_back(Containers::texture_table["bs_leftLungeTex"]);
	ObjConfig::marsh_con.push_back(Containers::texture_table["bs_rightLungeTex"]);

	gameplay_functions->add_texture("rockTex1", 0, 0, 0);
	gameplay_functions->add_texture("rockTex2", 0, 0, 0);
	tBuffer->run();

	ObjConfig::textureMap[Containers::texture_table["rockTex1"]] = pair<string, int>("Assets/Sprites/rock_1.png", 1);
	ObjConfig::textureMap[Containers::texture_table["rockTex2"]] = pair<string, int>("Assets/Sprites/rock_2.png", 1);
	ObjConfig::standard_con.push_back(Containers::texture_table["rockTex1"]);
	ObjConfig::standard_con.push_back(Containers::texture_table["rockTex2"]);

	gameplay_functions->add_texture("blank", 0, 0, 0);
	gameplay_functions->add_texture("border", 0, 0, 0);
	tBuffer->run();

	ObjConfig::textureMap[Containers::texture_table["blank"]] = pair<string, int>("Assets/Sprites/blank.png", 1);
	ObjConfig::textureMap[Containers::texture_table["border"]] = pair<string, int>("Assets/Sprites/border.png", 1);
	ObjConfig::standard_con.push_back(Containers::texture_table["blank"]);
	ObjConfig::standard_con.push_back(Containers::texture_table["border"]);

	gameplay_functions->add_texture("fire", 0, 0, 0);
	gameplay_functions->add_texture("fireUp", 0, 0, 0);
	gameplay_functions->add_texture("fireDown", 0, 0, 0);
	gameplay_functions->add_texture("fireLeft", 0, 0, 0);
	tBuffer->run();

	ObjConfig::textureMap[Containers::texture_table["fire"]] = pair<string, int>("Assets/Sprites/FireBallTMP.png", 3);
	ObjConfig::textureMap[Containers::texture_table["fireUp"]] = pair<string, int>("Assets/Sprites/FireBallTMPUp.png", 3);
	ObjConfig::textureMap[Containers::texture_table["fireDown"]] = pair<string, int>("Assets/Sprites/FireBallTMPDown.png", 3);
	ObjConfig::textureMap[Containers::texture_table["fireLeft"]] = pair<string, int>("Assets/Sprites/FireBallTMPLeft.png", 3);
	ObjConfig::standard_con.push_back(Containers::texture_table["fire"]);
	ObjConfig::standard_con.push_back(Containers::texture_table["fireUp"]);
	ObjConfig::standard_con.push_back(Containers::texture_table["fireDown"]);
	ObjConfig::standard_con.push_back(Containers::texture_table["fireLeft"]);

	tBuffer->run();

	Rectangle::texRIGHT->setFile("Assets/Sprites/LeftRecoilSpark.png", 18);
	Rectangle::texLEFT->setFile("Assets/Sprites/RightRecoilSpark.png", 18);
	Rectangle::texUP->setFile("Assets/Sprites/ForwardRecoilSpark.png", 18);
	Rectangle::texDOWN->setFile("Assets/Sprites/BackRecoilSpark.png", 18);

	Rectangle::texAtkRIGHT->setFile("Assets/Sprites/LeftRecoilSpark.png", 18);
	Rectangle::texAtkLEFT->setFile("Assets/Sprites/RightRecoilSpark.png", 18);
	Rectangle::texAtkUP->setFile("Assets/Sprites/ForwardRecoilSpark.png", 18);
	Rectangle::texAtkDOWN->setFile("Assets/Sprites/BackRecoilSpark.png", 18);

	for (int i = 0; i < 100; i++) {
		//std:://cout << "AT THE THREAD INITIALIZTION CALL!!!****** " << endl;
	}

	/*
		TRYING TO MULTITHREAD THE SETFILE METHODS ABOVE.
		First, iterate through textureMap and for each texture, assign a new thread to set_file_with_thread().
		When all available threads are working, call join() on all threads before continuing.
		We know all concurrent threads are being utilized when the counter we use while iterating through textureMap has a remainder of 0 when we take the modulo of num_of_threads.

	*/
	//int textureMapCounter = 0;
	//for (const auto& it : ObjConfig::textureMap) {
	//	pair<Texture*, pair<string, int>>* temp_tuple = new pair<Texture*, pair<string, int>>(it.first, it.second);
	//	//cout << "WORKING ON " << temp_tuple->second.first << endl;
	//	// If there are still less than "num_of_threads" in thread_Vec:
	//	if (textureMapCounter % num_of_threads != 0) {

	//		//std::thread temp_thread(set_file_with_thread, std::ref(temp_tuple));
	//		thread_Vec.push_back(std::thread(set_file_with_thread, std::move(temp_tuple)));
	//	}
	//	else {
	//		//cout << "THE THREAD VEC HAS " << thread_Vec.size() << "THREADS" << endl;
	//		for (auto& itr : thread_Vec) {
	//			itr.join();
	//		}
	//		thread_Vec.clear();
	//		thread_Vec.push_back(std::thread(set_file_with_thread, std::ref(temp_tuple)));
	//	}
	//	textureMapCounter++;

	//}
	//for (auto& it : thread_Vec) {
	//	it.join();
	//}
	//thread_Vec.clear();
	 //windows handle

	vector<WorldObj*> vec;
	//vec.push_back(&Alex->melee);

	vector<Soldier*> silverSoldier;
	int silverNum = 2;
	for (int i = 0; i < silverNum; i++) {
		silverSoldier.push_back(new Soldier(17157, 20960 + (i * 20), false));
		gameplay_functions->add_Attack(silverSoldier[i]->getKey(), silverSoldier[i]->body[0].getX(), silverSoldier[i]->body[0].getY(), true, 10);
	}
	tBuffer->run();
	vector<Soldier*> blueSoldiers;
	int blueNum = 2;
	for (int i = 0; i < blueNum; i++) {
		blueSoldiers.push_back(new Soldier(5045, 13465 + (i * 20), false));
		gameplay_functions->add_Attack(blueSoldiers[i]->getKey(), blueSoldiers[i]->body[0].getX(), blueSoldiers[i]->body[0].getY(), true, 10);
	}
	tBuffer->run();
	movVec.push_back(staticRec);
	movVec.push_back(oya);
	for (int i = 0; i < silverSoldier.size(); i++) {
		movVec.push_back(silverSoldier[i]);
	}
	for (int i = 0; i < blueSoldiers.size(); i++) {
		movVec.push_back(blueSoldiers[i]);
	}

	int closest;
	int least_dist;
	int tmp;
	while (RegionState::regions.size() > 0) {
		closest = 0;
		least_dist = 0;
		for (int i = 0; i < RegionState::regions.size(); i++) {
			tmp = Party::dist_location_to_location(Alex->getLoc(), RegionState::regions[i]->loc);
			if (tmp < least_dist || least_dist == 0) {
				closest = i;
				least_dist = tmp;
			}
		}
		if (RegionState::regions[closest] == Desert) {
			starting_location.push_back(ObjConfig::oasis_con);
		}
		else if (RegionState::regions[closest] == Mountain) {
			starting_location.push_back(ObjConfig::mountain_con);
		}
		else if (RegionState::regions[closest] == Jungle) {
			starting_location.push_back(ObjConfig::jungle_con);
		}
		else if (RegionState::regions[closest] == Marsh) {
			starting_location.push_back(ObjConfig::marsh_con);
		}
		RegionState::regions.erase(RegionState::regions.begin()+closest);
	}

	HGLRC loaderContext0 = wglCreateContext(hdc);
	wglShareLists(mainContext, loaderContext0);
	std::thread t0([=]() {
		wglMakeCurrent(hdc, loaderContext0);
		for (int i = 0; i < ObjConfig::standard_con.size(); i++) {
			set_file_with_thread(ObjConfig::standard_con[i], &ObjConfig::textureMap.find(ObjConfig::standard_con[i])->second);
		}
		wglMakeCurrent(nullptr, nullptr);
		wglDeleteContext(loaderContext0);
		/*for (auto it = recVec.begin(); it != recVec.end(); ++it) {
			(*it)->sprite.reset_texture();
		}
		for (auto it = movVec.begin(); it != movVec.end(); ++it) {
			(*it)->sprite.reset_texture();
		}*/
		Alex->sprite.reset_texture();
		glFinish();
	});

	HGLRC loaderContext1 = wglCreateContext(hdc);
	wglShareLists(mainContext, loaderContext1);
	std::thread t1([=]() {
		wglMakeCurrent(hdc, loaderContext1);
		for (int i = 0; i < (starting_location[0]).size(); i++) {
			set_file_with_thread(starting_location[0].at(i), &ObjConfig::textureMap.find(starting_location[0].at(i))->second);
		}
		for (auto it = recVec.begin(); it != recVec.end(); ++it) {
			(*it)->sprite.reset_texture();
		}
		for (auto it = movVec.begin(); it != movVec.end(); ++it) {
			(*it)->sprite.reset_texture();
		}
		for (int i = 0; i < (starting_location[3]).size(); i++) {
			set_file_with_thread(starting_location[3].at(i), &ObjConfig::textureMap.find(starting_location[3].at(i))->second);
		}
		wglMakeCurrent(nullptr, nullptr);
		wglDeleteContext(loaderContext1);
		for (auto it = recVec.begin(); it != recVec.end(); ++it) {
			(*it)->sprite.reset_texture();
		}
		for (auto it = movVec.begin(); it != movVec.end(); ++it) {
			(*it)->sprite.reset_texture();
		}
		glFinish();
	});

	HGLRC loaderContext2 = wglCreateContext(hdc);//Creates the new GL context that we will use for loading
	wglShareLists(mainContext, loaderContext2);//Shares the information between the loading context and the main context
	std::thread t2([=]() {//makes the thread. [=] is a cpp Lambda representation
		wglMakeCurrent(hdc, loaderContext2);//Sets the current context to the loader context
		for (int i = 0; i < (starting_location[1]).size(); i++) {
			set_file_with_thread(starting_location[1].at(i), &ObjConfig::textureMap.find(starting_location[1].at(i))->second);
		}
		for (auto it = recVec.begin(); it != recVec.end(); ++it) {
			(*it)->sprite.reset_texture();
		}
		for (auto it = movVec.begin(); it != movVec.end(); ++it) {
			(*it)->sprite.reset_texture();
		}
		for (int i = 0; i < (starting_location[2]).size(); i++) {
			set_file_with_thread(starting_location[2].at(i), &ObjConfig::textureMap.find(starting_location[2].at(i))->second);
		}
		wglMakeCurrent(nullptr, nullptr);//unassigns the current gl context
		wglDeleteContext(loaderContext2);//deletes the loading context now that it is not needed
		for (auto it = recVec.begin(); it != recVec.end(); ++it) {
			(*it)->sprite.reset_texture();
		}
		for (auto it = movVec.begin(); it != movVec.end(); ++it) {
			(*it)->sprite.reset_texture();
		}
		glFinish(); //Forces all gl calls to be completed before execution
	});
	

	//Alex->setDirection(WorldObj::DIRECTION_DOWN);
	gameplay_functions->add_Attack(Alex->getKey(), Alex->body[0].getX(), Alex->body[0].getY(), true, 10);

	tBuffer->run();

	Alex->melee = Containers::Attack_table[Alex->getKey()];
	Alex->melee->setDmg(85);
	Alex->melee->setSpeed(5);
	Alex->melee->setBaseDir(4);
	Alex->melee->setCoolDown(35);
	Alex->melee->setStaminaCost(45);
	Alex->melee->setPause(-1);
	Alex->melee->setDestroy(false);
	Alex->melee->setKeep(true);
	Alex->melee->setWidth(Alex->body[0].getWidth());
	Alex->melee->setHeight(Alex->body[0].getHeight());
	Alex->set_creator_of_melee();

	Attack* rockThrow = new Attack();
	rockThrow->setDmg(5);
	rockThrow->setSpeed(20);
	rockThrow->setDestroy(true);
	rockThrow->setDuration(100);
	rockThrow->setCoolDown(120);
	rockThrow->setPause(13);
	rockThrow->sprite.setTexture(Containers::texture_table["rockTex1"]);
	rockThrow->sprite.up = Containers::texture_table["rockTex1"];
	rockThrow->sprite.left = Containers::texture_table["rockTex1"];
	rockThrow->sprite.right = Containers::texture_table["rockTex1"];
	rockThrow->sprite.down = Containers::texture_table["rockTex1"];
	rockThrow->setCanCancel(false);
	Alex->addAttackType(rockThrow);

	Attack* fireball = new Attack();
	fireball->setDmg(20);
	fireball->setSpeed(20);
	fireball->setDestroy(true);
	fireball->setDuration(100);
	fireball->setCoolDown(120);
	fireball->setPause(16);
	fireball->setAseCost(25);
	fireball->sprite.up = Containers::texture_table["fireUp"];
	fireball->sprite.left = Containers::texture_table["fireLeft"];
	fireball->sprite.right = Containers::texture_table["fire"];
	fireball->sprite.down = Containers::texture_table["fireDown"];
	fireball->setCanCancel(false);
	Alex->addAttackType(fireball);

	//Alex->melee->sprite.setTexture(blank);
	Alex->melee->sprite.setTexture(Containers::texture_table["border"]);

	DialogueController::setPlayer(Alex);
	//vector<WorldObj*> recVec;
	Attack* spin = new Attack();
	spin->setDmg(15);
	spin->setSpeed(18);
	spin->setDestroy(false);
	spin->setDuration(7);
	spin->setBaseDir(4);
	spin->setCoolDown(100);
	spin->setPause(18);
	spin->setStaminaCost(30);
	spin->setTurn(true);
	spin->sprite.setTexture(Containers::texture_table["border"]);
	Alex->addAttackType(spin);
	Attack* spin2 = new Attack();
	spin2->setDmg(7);
	spin2->setSpeed(15);
	spin2->setDestroy(false);
	spin2->setDuration(7);
	spin2->setBaseDir(4);
	spin2->setCoolDown(0);
	spin2->setPause(23);
	spin2->setTurn(true);
	spin2->sprite.setTexture(Containers::texture_table["border"]);
	Alex->addAttackType(spin2);
	Attack* spin3 = new Attack();
	spin3->setDmg(7);
	spin3->setSpeed(15);
	spin3->setDestroy(false);
	spin3->setDuration(7);
	spin3->setBaseDir(4);
	spin3->setCoolDown(0);
	spin3->setPause(28);
	spin3->setTurn(true);
	spin3->sprite.setTexture(Containers::texture_table["border"]);
	Alex->addAttackType(spin3);
	Attack* spin4 = new Attack();
	spin4->setDmg(7);
	spin4->setSpeed(15);
	spin4->setDestroy(false);
	spin4->setDuration(7);
	spin4->setBaseDir(4);
	spin4->setCoolDown(0);
	spin4->setPause(33);
	spin4->setTurn(true);
	spin4->sprite.setTexture(Containers::texture_table["border"]);
	Alex->addAttackType(spin4);
	spin->setNextAttack(spin2);
	spin2->setNextAttack(spin3);
	spin3->setNextAttack(spin4);

	vector<Vector2f> vertices;
	vector<pair<Vector2f, Vector2f>> edges;

	for (int i = 0; i < vec.size(); i++) {
		WorldObj *obj = vec[i];
		float w = obj->body[0].getWidth();
		float h = obj->body[0].getHeight();
		Vector2f p1 = { obj->body[0].getX() - 105,obj->body[0].getY() - 105 };
		Vector2f p2 = obj->body[0].getTR();
		Vector2f p3 = obj->body[0].getBL();
		Vector2f p4 = obj->body[0].getBR();
		vertices.push_back(p1);
		vertices.push_back(p2);
		vertices.push_back(p3);
		vertices.push_back(p4);
		edges.push_back({ p1, p2 });
		edges.push_back({ p1, p3 });
		edges.push_back({ p2, p4 });
		edges.push_back({ p3, p4 });
		//Put edges in the hit box to prevent
		//visibility lines through the diagonal
		edges.push_back({ p2, p3 });
		edges.push_back({ p1, p4 });
	}

	gameplay_functions->add_Attack(staticRec->getKey(), staticRec->body[0].getX(), staticRec->body[0].getY(), true, 10);
	gameplay_functions->add_Attack(oya->getKey(), oya->body[0].getX(), oya->body[0].getY(), true, 10);
	tBuffer->run();

	staticRec->melee = Containers::Attack_table[staticRec->getKey()];
	staticRec->melee->setDmg(15);
	staticRec->melee->setSpeed(8);
	staticRec->melee->setBaseDir(4);
	staticRec->melee->setCoolDown(60);
	staticRec->melee->setPause(-1);
	staticRec->melee->setDestroy(false);
	staticRec->melee->setKeep(true);
	staticRec->melee->setWidth(50);
	staticRec->melee->setHeight(50);
	staticRec->set_creator_of_melee();
	staticRec->melee->setStaminaCost(90);
	staticRec->setHealth(140);
	staticRec->setMaxStamina(300);
	staticRec->melee->sprite.setTexture(Containers::texture_table["border"]);

	oya->melee = Containers::Attack_table[oya->getKey()];
	oya->melee->setDmg(18);
	oya->melee->setSpeed(7);
	oya->melee->setBaseDir(4);
	oya->melee->setCoolDown(70);
	oya->melee->setPause(-1);
	oya->melee->setDestroy(false);
	oya->melee->setKeep(true);
	oya->melee->setWidth(50);
	oya->melee->setHeight(50);
	oya->set_creator_of_melee();
	oya->melee->setStaminaCost(120);
	oya->setHealth(160);
	oya->setMaxStamina(300);
	oya->melee->sprite.setTexture(Containers::texture_table["border"]);

	for (int i = 0; i < silverNum; i++) {
		silverSoldier[i]->setWidth(150);
		silverSoldier[i]->setHeight(150);
		silverSoldier[i]->sprite.setTexture(Containers::texture_table["silverSoldierTexture"]);
		silverSoldier[i]->sprite.setIdleTexture(Containers::texture_table["silverSoldierIdleTex"]);
		silverSoldier[i]->sprite.up = Containers::texture_table["ss_upRunTex"];
		silverSoldier[i]->sprite.down = Containers::texture_table["ss_downRunTex"];
		silverSoldier[i]->sprite.left = Containers::texture_table["ss_leftRunTex"];
		silverSoldier[i]->sprite.right = Containers::texture_table["ss_rightRunTex"];

		silverSoldier[i]->sprite.id_up = Containers::texture_table["ss_upIdleTex"];
		silverSoldier[i]->sprite.id_left = Containers::texture_table["ss_leftIdleTex"];
		silverSoldier[i]->sprite.id_right = Containers::texture_table["ss_rightIdleTex"];
		silverSoldier[i]->sprite.id_down = Containers::texture_table["ss_downIdleTex"];

		silverSoldier[i]->sprite.atk_up = Containers::texture_table["ss_upAtkTex"];
		silverSoldier[i]->sprite.atk_down = Containers::texture_table["ss_downAtkTex"];
		silverSoldier[i]->sprite.atk_left = Containers::texture_table["ss_leftAtkTex"];
		silverSoldier[i]->sprite.atk_right = Containers::texture_table["ss_rightAtkTex"];

		silverSoldier[i]->sprite.hurt_up = Containers::texture_table["ss_upHurtTex"];
		silverSoldier[i]->sprite.hurt_down = Containers::texture_table["ss_downHurtTex"];
		silverSoldier[i]->sprite.hurt_left = Containers::texture_table["ss_leftHurtTex"];
		silverSoldier[i]->sprite.hurt_right = Containers::texture_table["ss_rightHurtTex"];

		silverSoldier[i]->sprite.death_up = Containers::texture_table["ss_upDeathTex"];
		silverSoldier[i]->sprite.death_down = Containers::texture_table["ss_downDeathTex"];
		silverSoldier[i]->sprite.death_left = Containers::texture_table["ss_leftDeathTex"];
		silverSoldier[i]->sprite.death_right = Containers::texture_table["ss_rightDeathTex"];

		silverSoldier[i]->offsetBody(0, 60, 60, 75, 50);
		silverSoldier[i]->setInteractable(true);
		silverSoldier[i]->setName("silverSoldier");
		silverSoldier[i]->melee = Containers::Attack_table[silverSoldier[i]->getKey()];
		silverSoldier[i]->melee->setDmg(11);
		silverSoldier[i]->melee->setSpeed(5);
		silverSoldier[i]->melee->setBaseDir(4);
		silverSoldier[i]->melee->setCoolDown(60);
		silverSoldier[i]->melee->setPause(-1);
		silverSoldier[i]->melee->setDestroy(false);
		silverSoldier[i]->melee->setKeep(true);
		silverSoldier[i]->melee->setWidth(50);
		silverSoldier[i]->melee->setHeight(50);
		silverSoldier[i]->set_creator_of_melee();
		silverSoldier[i]->melee->setStaminaCost(90);
		silverSoldier[i]->setHealth(110);
		silverSoldier[i]->melee->setStaminaCost(120);
		silverSoldier[i]->setMaxStamina(300);
		silverSoldier[i]->addAttackType(rockThrow);
		silverSoldier[i]->melee->sprite.setTexture(Containers::texture_table["border"]);
		silverSoldier[i]->setSpeed(7);
	}

	for (int i = 0; i < blueNum; i++) {
		blueSoldiers[i]->setWidth(150);
		blueSoldiers[i]->setHeight(150);
		blueSoldiers[i]->sprite.setTexture(Containers::texture_table["blueSoldierTexture"]);
		blueSoldiers[i]->sprite.setIdleTexture(Containers::texture_table["blueSoldierIdleTex"]);
		blueSoldiers[i]->sprite.up = Containers::texture_table["bs_upRunTex"];
		blueSoldiers[i]->sprite.down = Containers::texture_table["bs_downRunTex"];
		blueSoldiers[i]->sprite.left = Containers::texture_table["bs_leftRunTex"];
		blueSoldiers[i]->sprite.right = Containers::texture_table["bs_rightRunTex"];

		blueSoldiers[i]->sprite.id_up = Containers::texture_table["bs_upIdleTex"];
		blueSoldiers[i]->sprite.id_left = Containers::texture_table["bs_leftIdleTex"];
		blueSoldiers[i]->sprite.id_right = Containers::texture_table["bs_rightIdleTex"];
		blueSoldiers[i]->sprite.id_down = Containers::texture_table["bs_downIdleTex"];

		blueSoldiers[i]->sprite.atk_up = Containers::texture_table["bs_upAtkTex"];
		blueSoldiers[i]->sprite.atk_down = Containers::texture_table["bs_downAtkTex"];
		blueSoldiers[i]->sprite.atk_left = Containers::texture_table["bs_leftAtkTex"];
		blueSoldiers[i]->sprite.atk_right = Containers::texture_table["bs_rightAtkTex"];

		blueSoldiers[i]->sprite.hurt_up = Containers::texture_table["bs_upHurtTex"];
		blueSoldiers[i]->sprite.hurt_down = Containers::texture_table["bs_downHurtTex"];
		blueSoldiers[i]->sprite.hurt_left = Containers::texture_table["bs_leftHurtTex"];
		blueSoldiers[i]->sprite.hurt_right = Containers::texture_table["bs_rightHurtTex"];

		blueSoldiers[i]->sprite.death_up = Containers::texture_table["bs_upHurtTex"];
		blueSoldiers[i]->sprite.death_down = Containers::texture_table["bs_downHurtTex"];
		blueSoldiers[i]->sprite.death_left = Containers::texture_table["bs_leftHurtTex"];
		blueSoldiers[i]->sprite.death_right = Containers::texture_table["bs_rightHurtTex"];

		blueSoldiers[i]->offsetBody(0, 60, 60, 75, 50);
		blueSoldiers[i]->setInteractable(true);
		blueSoldiers[i]->setName("blueSoldier");
		blueSoldiers[i]->melee = Containers::Attack_table[blueSoldiers[i]->getKey()];
		blueSoldiers[i]->melee->setDmg(10);
		blueSoldiers[i]->melee->setSpeed(5);
		blueSoldiers[i]->melee->setBaseDir(4);
		blueSoldiers[i]->melee->setCoolDown(60);
		blueSoldiers[i]->melee->setPause(-1);
		blueSoldiers[i]->melee->setDestroy(false);
		blueSoldiers[i]->melee->setKeep(true);
		blueSoldiers[i]->melee->setWidth(50);
		blueSoldiers[i]->melee->setHeight(50);
		blueSoldiers[i]->set_creator_of_melee();
		blueSoldiers[i]->melee->setStaminaCost(90);
		blueSoldiers[i]->setHealth(90);
		blueSoldiers[i]->melee->setStaminaCost(120);
		blueSoldiers[i]->setMaxStamina(300);
		blueSoldiers[i]->addAttackType(rockThrow);
		blueSoldiers[i]->melee->sprite.setTexture(Containers::texture_table["border"]);
		blueSoldiers[i]->setSpeed(8);
	}

	//VisibilityGraph graph;
	ai->graph.vertices = vertices;
	ai->graph.obstacles = edges;
	for (Vector2f vert : ai->graph.vertices) {
		
		std::cout << "X: " << vert.getXloc() << " Y: " << vert.getYloc() << std::endl;
	}
	for (auto edge : ai->graph.obstacles) {
		//////std::////cout << "EDGE from " << edge.first.getXloc() << "," << edge.first.getYloc() << " to " << edge.second.getXloc() << "," << edge.second.getYloc() << std::endl;
	}

	bool visible = true;
	for (Vector2f first : ai->graph.vertices) {
		//ai->graph.insert(first);
		for (Vector2f second : ai->graph.vertices) {
			if (first == second) continue;
			visible = true;
			for (auto check : ai->graph.obstacles) {
				if (ai->graph.intersect(first, second, check.first, check.second)) {
					visible = false;
					break;
				}
			}
			if (visible) { //put vertices in each other's neighbor list
				ai->graph.edges[first].push_back(second);
				ai->graph.edges[second].push_back(first);
			}
		}
	}
	
	///////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////
	//////////////////                                                 ////////////////////////
	//////////////////             INIT CALLS FOR QUESTS               ////////////////////////
	//////////////////                                                 ////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////
	
	// THIS IS BEING RESET IN THE GAME LOOP. planner->get_current_action returns nullptr*/
	
	/*
	AIController::generate_end_state(YEMOJA, OYA);
	AIController::init_plans();
	*/


	/*	VisibilityGraph graph{ {
			{{1400.00,800.00}, {{1400.00, 900.00},{1200.00,800.00}}},
			{{1400.00,900.00}, {{1400.00,800.00},{1200.00,800.00},{1300.00,1000.00}}},
			{{1200.00,800.00}, {{1400.00,800.00},{1400.00,900.00},{1100.00,900.00}}},
			{{1300.00,1000.00}, {{1400.00,900.00},{1100.00,900.00},{1200.00,600.00}}},
			{{1100.00,900.00}, {{1200.00,800.00},{1300.00,1000.00},{1200.00,600.00}}},
			{{1200.00,600.00}, {{1100.00,900.00},{1300.00,1000.00}}}
		} };
		*/
		//ai->graph = graph;
	/*

	ai->start = staticRec->getLoc();
	ai->goal = { 1100.00,1100.00 };

	ai->graph.insert(ai->start);
	//ai->graph.insert(ai->goal);

	staticRec->destination = { 4600.00,3600.00 };
	ai->graph.insert(staticRec->destination);
	ai->graph.insert(Vector2f(5000.00, 4100.00));
	ai->graph.insert(Vector2f(4600.00, 3600.00));
	ai->graph.insert(Vector2f(4500.00, 4000.00));
	ai->graph.insert(Vector2f(5650.00, 3700.00));
	for (Vector2f vert : ai->graph.vertices) {
		//////std::////cout << "X: " << vert.getXloc() << " Y: " << vert.getYloc() << std::endl;
	}
	for (auto edge : ai->graph.obstacles) {
		//////std::////cout << "EDGE from " << edge.first.getXloc() << "," << edge.first.getYloc() << " to " << edge.second.getXloc() << "," << edge.second.getYloc() << std::endl;
	}

	ai->graph._print();

	ai->astar_search(staticRec);
	// gameplay_functions->get_path(staticRec); //Generate the waypoints to the destination
	staticRec->setMode(WANDER);
	*/

	short M = GetKeyState('M') >> 15;

	//osi::GameWindow::init();
	LOG("PAST WINDOW INIT ***********************");
	clock_t start_tick, current_ticks, delta_ticks;
	clock_t fps = 0;
	int fs = 120;
	int wait_time = fs * 3; //always wait 3 seconds	
	int count = 0;
	int state = 0;
	bool start = true;
	float shouldExit = -3000;
	int last_avg = 0;
	int total_fps = 0;

	vector<Soldier*> soldiers_list;
	soldiers_list.push_back(staticRec);
	soldiers_list.push_back(oya);
	for (int i = 0; i < blueSoldiers.size(); i++) {
		soldiers_list.push_back(blueSoldiers[i]);
	}
	for (int i = 0; i < silverSoldier.size(); i++) {
		soldiers_list.push_back(silverSoldier[i]);
	}

	/*std::thread AI([=]() {
		while (GameWindow::isRunning()) {
			combatControl->updateSoliderStatus();
			combatControl->checkParties();
			for (int i = 0; i < soldiers_list.size(); i++) {
				combatControl->update_soldier(soldiers_list[i], state);
			}
		}
	});*/

	t0.join();

	current_game_state = game_state::main_menu;

	//insert all of the immovable objects into the quad tree
	_QuadTree->clear();
	cout << "tree size is  " << _QuadTree->treeSize() << endl;
	for (int i = 0; i < recVec.size(); i++) {
		if (recVec[i]->getName() == "Oasis_Platform" || recVec[i]->getName() == "JungleVillage") largeStruct->push_back(recVec[i]);
		_QuadTree->Insert(recVec[i]);	//insert all obj into tree
	}

	cout << "tree size is  " << _QuadTree->treeSize() << endl;
	cout << "size of recvec is " << recVec.size() << endl;
	cout << "size of largestruct is " << largeStruct->size() << endl;
	for (auto it : *largeStruct) cout << (it)->getName() << endl;

	//HeroConfig::set_hero_sprites();

	while (GameWindow::isRunning()) {
		while (current_game_state == game_state::main_menu) {
			//cout << "currently in the main menu" << endl;
			for (int i = 0; i < 10; i++) {
				cout << "Press Enter to start game" << endl;
				cout << Containers::hero_table["Yemoja"]->rel[1]->getAffinity() << endl;
			}

			if (iController->current_game_state != game_state::main_menu) {
				iController->current_game_state = current_game_state;
			}

			if (shouldExit > 0) {
				_CrtDumpMemoryLeaks();
				return;
			}
			
			start_tick = clock();



			gameplay_functions->drawTut(Alex);

			//run task buffer
			iController->InputCheck();

			tBuffer->run();

			if ((1000 / fs) > (clock() - start_tick)) { //delta_ticks)
				Sleep((1000 / fs) - (clock() - start_tick));
			}
			delta_ticks = clock() - start_tick; //the time, in ms, that took to render the scene
			if (delta_ticks > 0) {
				fps = CLOCKS_PER_SEC / delta_ticks;
			}
			HUD::FPS = fps;
			//cout << "FPS: " << fps << endl;

			current_game_state = iController->current_game_state;
			//if(t0.joinable)t0.join();
		}
		while (current_game_state == game_state::in_game) {

			for (int i = 0; i < 10; i++) {
				//cout << "Press Escape to pause game" << endl;
			}
			if (iController->current_game_state != game_state::in_game) {
				iController->current_game_state = current_game_state;
			}
			//iController->current_game_state = current_game_state;
			//shouldExit++;
			//for (int i = 0; i < 10; i++) {
			//	cout << "SHOULD EXIT IS " << shouldExit << endl;

			//}
			if (shouldExit > 0) {
				_CrtDumpMemoryLeaks();
				return;
			}
			if (start) {
				gameplay_functions->play_sound("Play");
				start = !start;
			}
			start_tick = clock();
			if (!MAP_EDITOR) {
				_QuadTree->clearMovable();
			}
			else {
				_QuadTree->clear();
			}
			//grid->clear();
			//grid->insert_objs_to_grid(rivObj->getLines());
			Alex->updateCD();
			Alex->effect.sprite.animate();
			Alex->WorldObj::animateObj();

			if (MAP_EDITOR) {
				for (int i = 0; i < recVec.size(); i++) {
					if (recVec[i]->getType() != WorldObj::TYPE_WORLDOBJ) {
						recVec[i]->effect.sprite.animate();
						recVec[i]->WorldObj::animateObj();
					}
					 _QuadTree->Insert(recVec[i]);	//insert all obj into tree
				}

				for (int i = 0; i < movVec.size(); i++) {
					//cout << "movevec item type is " << movVec[i]->getType() << endl;
					if (movVec[i]->getType() != WorldObj::TYPE_WORLDOBJ) {
						movVec[i]->effect.sprite.animate();
						movVec[i]->WorldObj::animateObj();
					}
					_QuadTree->Insert(movVec[i]);	//insert all obj into tree
				}

			}
			else {
				//for (int i = 0; i < recVec.size(); i++) {
				//	if (recVec[i]->getType() != WorldObj::TYPE_WORLDOBJ) {
				//		recVec[i]->effect.sprite.animate();
				//		recVec[i]->WorldObj::animateObj();
				//	}
				//	//_QuadTree->Insert(recVec[i]);	//insert all obj into tree
				//}
				for (int i = 0; i < movVec.size(); i++) {
					//cout << "movevec item type is " << movVec[i]->getType() << endl;
					if (movVec[i]->getType() != WorldObj::TYPE_WORLDOBJ) {
						movVec[i]->effect.sprite.animate();
						movVec[i]->WorldObj::animateObj();
					}
					_QuadTree->Insert(movVec[i]);	//insert all obj into tree
				}
				//cout << "inserted into tree " << movVec.size() << " movable objs" << endl;
			}

			state = DialogueController::getState();

			//commented out for demo
			/*if (Alex->getX() > 660 && Alex->getX() < 10847.5) { //Ogun Desert
				if (Alex->getY() < 3523.33) {
					if (RegionState::current_region == *Desert)
						RegionState::next_region = *Marsh;

				}
				else {
					if (RegionState::current_region == *Marsh) {
						RegionState::next_region = *Desert;
					}
				}
			}
			if (Alex->getX() > 10847.5 && Alex->getX() < 12395.5) {
				if (Alex->getY() < 14441) {
					if (RegionState::current_region == *Jungle)
						RegionState::next_region = *Mountain;
				}
				else {
					if (RegionState::current_region == *Mountain) {
						RegionState::next_region = *Jungle;
					}
				}
			}
			if (Alex->getX() > 660 && Alex->getX() < 25000) {
				if (Alex->getY() < 5132.23) {

					if (RegionState::current_region == *Mountain) {
						RegionState::next_region = *Marsh;
					}
				}
				else {
					if (RegionState::current_region == *Marsh)
						RegionState::next_region = *Mountain;
				}
			}
			if (Alex->getX() > 3479.67 && Alex->getX() < 10847.5) {
				if (Alex->getY() < 17000.7) {
					if (RegionState::current_region == *Jungle)
						RegionState::next_region = *Desert;
				}
				else {
					if (RegionState::current_region == *Desert) {
						RegionState::next_region = *Jungle;
					}
				}
			}*/

			//only 3 regions for demo
			if (Alex->getX() > 660 && Alex->getX() < 25000 ){ //Ogun Desert
				if (Alex->getY() < 3523.33) {
					if (RegionState::current_region == *Desert)
						RegionState::next_region = *Marsh;

				}
				else {
					if (RegionState::current_region == *Marsh) {
						RegionState::next_region = *Desert;
					}
				}
			}
			if (Alex->getX() > 600 && Alex->getX() < 25000) {
				if (Alex->getY() < 20000.7) {
					if (RegionState::current_region == *Jungle)
						RegionState::next_region = *Desert;
				}
				else {
					if (RegionState::current_region == *Desert) {
						RegionState::next_region = *Jungle;
					}
				}
			}
			if (!(RegionState::current_region == RegionState::next_region)) {
				RegionState::switch_music = true;
			}

			if (RegionState::switch_music) {
				if (RegionState::in_village) {

					gameplay_functions->change_song("Change", RegionState::current_region.getRTheme(), RegionState::current_region.getVTheme());
					RegionState::switch_music = false;
				}
				else {
					gameplay_functions->change_song("Change", RegionState::current_region.getRTheme(), RegionState::next_region.getRTheme());
					//iController->current_region = current_region;
					RegionState::current_region = RegionState::next_region;

					//current_region->getRTheme(), next_region->getRTheme()
					RegionState::switch_music = false;
				}

			}
			/*combatControl->updateSoliderStatus();
			combatControl->checkParties();
			for (int i = 0; i < soldiers_list.size(); i++) {
				combatControl->update_soldier(soldiers_list[i], state);
			}*/

		//	std::thread AI([=]() {
				
		//	});
			//YemojaPlanner->set_current_action(test_train);
			combatControl->checkParties();
				for (int i = 0; i < soldiers_list.size(); i++) {
					combatControl->update_soldier(soldiers_list[i], state);
				}
			questM->update();

			//draw
			if (state == 0) {
				gameplay_functions->draw_frame(Alex);
			}
			//draw
			else if (state > 0) {
				for (auto itr : Containers::hero_table)
				{
					gameplay_functions->stop(itr.second);
				}
				gameplay_functions->drawDiaGui(Alex);
				
			}

			//run task buffer
			iController->InputCheck();

			tBuffer->run();

			/////////////////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////
			for (auto iter : staticRec->rel) {
				Relationship* my_rel = iter.second;
				int with_hero = iter.first;

				if (my_rel->isChanged()) {
					//reevaluate goals for with_hero
					AIController::reevaluate_state(YEMOJA, with_hero);
					my_rel->setChanged(false);
				}
			}
			//getting here-------------------------------------------------------------------------***********
			//setting give as quest to false so that the excute runs
			//YemojaPlanner->give_as_quest = false;
//			cout << " first dest is " << staticRec->get_action_destination()->getXloc() << ", " << staticRec->get_action_destination()->getYloc() << endl;
			AIController::execute();
//			cout << "after execute dest is " << staticRec->get_action_destination()->getXloc() << ", " << staticRec->get_action_destination()->getYloc() << endl;
			//AI.join();
//			cout << "after thread join dest is " << staticRec->get_action_destination()->getXloc() << ", " << staticRec->get_action_destination()->getYloc() << endl;
			if ((1000 / fs) > (clock() - start_tick)) { //delta_ticks)
				Sleep((1000 / fs) - (clock() - start_tick));
			}
			delta_ticks = clock() - start_tick; //the time, in ms, that took to render the scene
			if (delta_ticks > 0) {
				fps = CLOCKS_PER_SEC / delta_ticks;
			}
			HUD::FPS = fps;
			//cout << "FPS: " << fps << endl;
			total_fps += fps;
			frame_count++;
			HUD::AVG = total_fps / frame_count;

			current_game_state = iController->current_game_state;
			//system("PAUSE");
			//Checks if game has reached final states
			//GameState::check_if_end_game(&current_game_state);
			

		}
		while (current_game_state == game_state::pause_menu) {
			for (int i = 0; i < 10; i++) {
				cout << "Press Q to return to game" << endl;

			}
			if (iController->current_game_state != game_state::pause_menu) {
				iController->current_game_state = current_game_state;
			}

			if (shouldExit > 0) {
				_CrtDumpMemoryLeaks();
				return;
			}
			start_tick = clock();

			//draw
			gameplay_functions->drawTut(Alex);

			//run task buffer
			iController->InputCheck();

			tBuffer->run();

			if ((1000 / fs) > (clock() - start_tick)) { //delta_ticks) {www
				Sleep((1000 / fs) - (clock() - start_tick));
			}
			delta_ticks = clock() - start_tick; //the time, in ms, that took to render the scene
			if (delta_ticks > 0) {
				fps = CLOCKS_PER_SEC / delta_ticks;
			}
			HUD::FPS = fps;
			//total_fps += fps;
			//cout << "FPS: " << fps << endl;

			//frame_count++;
			HUD::AVG = total_fps / frame_count;

			current_game_state = iController->current_game_state;
		}
		while (current_game_state == game_state::victory_menu) {

			if (iController->current_game_state != game_state::victory_menu) {
				iController->current_game_state = current_game_state;
			}

			if (shouldExit > 0) {
				_CrtDumpMemoryLeaks();
				return;
			}
			start_tick = clock();

			//draw
			gameplay_functions->drawTut(Alex);

			//run task buffer
			iController->InputCheck();

			tBuffer->run();

			if (game_ended) {
				break;
			}

			if ((1000 / fs) > (clock() - start_tick)) { //delta_ticks) {www
				Sleep((1000 / fs) - (clock() - start_tick));
			}
			delta_ticks = clock() - start_tick; //the time, in ms, that took to render the scene
			if (delta_ticks > 0) {
				fps = CLOCKS_PER_SEC / delta_ticks;
			}
			HUD::FPS = fps;
			//total_fps += fps;
			//cout << "FPS: " << fps << endl;

			//frame_count++;
			HUD::AVG = total_fps / frame_count;

			current_game_state = iController->current_game_state;

		}
		if (game_ended) {
			break;
		}
	}
	GameWindow::terminate();
}


bool lineCollision(Line l1, Line l2)
{
	float denom = ((l1.getP2().getX() - l1.getP1().getX()) * (l2.getP2().getY() - l2.getP1().getY())) - ((l1.getP2().getY() - l1.getP1().getY()) * (l2.getP2().getX() - l2.getP1().getX()));
	float num1 = ((l1.getP1().getY() - l2.getP1().getY()) * (l2.getP2().getX() - l2.getP1().getX())) - ((l1.getP1().getX() - l2.getP1().getX()) * (l2.getP2().getY() - l2.getP1().getY()));
	float num2 = ((l1.getP1().getY() - l2.getP1().getY()) * (l1.getP2().getX() - l1.getP1().getX())) - ((l1.getP1().getX() - l2.getP1().getX()) * (l1.getP2().getY() - l1.getP1().getY()));

	if (denom == 0) return num1 == 0 && num2 == 0;

	float r = num1 / denom;
	float s = num2 / denom;

	return (r >= 0 && r <= 1) && (s >= 0 && s <= 1);
}

void FPS(bool b) {
	if (b) {
		time_t sec;
		time(&sec);
	}
	time_t now;
	time(&now);

}
