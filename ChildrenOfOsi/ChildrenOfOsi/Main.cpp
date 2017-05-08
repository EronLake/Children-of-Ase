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
#include "threadManager.h"

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

int getFreeVideoMemory()
{
	int availableKB[4];
	if(GLEW_NVX_gpu_memory_info)
		glGetIntegerv(GL_GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX,&availableKB[0]);
	int temp=GLEW_ATI_meminfo;
	if(GLEW_ATI_meminfo)
		glGetIntegerv(GL_TEXTURE_FREE_MEMORY_ATI,availableKB);
	return availableKB[0];
}


//Eron: needs to be moved to separate file
void check_if_end_game() {
	Village* player_vil = dynamic_cast<Player*>(Containers::hero_table["Shango"])->getVillage();
	Village* yemoja_vil = dynamic_cast<Player*>(Containers::hero_table["Shango"])->getVillage();
	Village* oya_vil = dynamic_cast<Player*>(Containers::hero_table["Shango"])->getVillage();

	//checks if there is only one alliance left end the game (everyone is alligned)
	if (player_vil->get_alliance()->get_num_alliances() == 1) 
	{
		game_ended = true;
	}
	
	//checks if both heroes are conquered (the player conqured the world)
	if (yemoja_vil->get_conquerer() == player_vil && oya_vil->get_conquerer() == player_vil)
	{
		game_ended = true;
	}

	//checks if the hero is alligned with the conqurer (the player teamed up and conqurred the yemoja)
	if (player_vil->get_alliance()->get_alligned_villages()[0] == oya_vil &&
		(yemoja_vil->get_conquerer() == player_vil || yemoja_vil->get_conquerer() == oya_vil))
	{
		game_ended = true;
	}

	//checks if the hero is alligned with the conqurer (the player teamed up and conqurred the oya)
	if (player_vil->get_alliance()->get_alligned_villages()[0] == yemoja_vil &&
		(oya_vil->get_conquerer() == player_vil || oya_vil->get_conquerer() == yemoja_vil))
	{
		game_ended = true;
	}
}


void test(int i) { for(int i=0;i<100;i++) cout << "hello this is the thread running" << endl; }

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
	threadmanager::thread_pool pool(5);
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

	unordered_map<Texture*, pair<string, int>> textureMap;
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

	//HeroConfig::import_config(movVec_ptr, gameplay_functions, tBuffer);

	gameplay_functions->add_hero("Shango", 6445, 10055, true);
	tBuffer->run();

	Player* Alex = dynamic_cast<Player*>(Containers::hero_table["Shango"]);

	Alex->name = SHANGO;
	Alex->setWidth(150);
	Alex->setHeight(150);
	Alex->setPersonality(30, 70, 80, 60, 30, 30, 50);// uncommented this

	//draws the logo on startup
	gameplay_functions->draw_logo(Alex);
	tBuffer->run();

	// Player* Alex = new Player(SHANGO, Vector2f(6445.0, 10155.0), 150.0, 150.0);	//init player
	
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

	gameplay_functions->add_hero("Yemoja", 5045, 13465, true);//5045 old x 13465 old y
	gameplay_functions->add_hero("Oya", 1400, 20960, true);//17157 old x
	tBuffer->run();
	

	Hero* staticRec = Containers::hero_table["Yemoja"];
	heroes.push_back(staticRec);
	Hero* oya = Containers::hero_table["Oya"];
	heroes.push_back(oya);

	staticRec->name = YEMOJA;
	staticRec->setWidth(150);
	staticRec->setHeight(150);
	oya->name = OYA;
	oya->setWidth(150);
	oya->setHeight(150);

	//DialogueController::setAI(AiController);

	vector<Texture*> standard;
	vector<Texture*> oasis;
	vector<Texture*> jungle;
	vector<Texture*> mountain;
	vector<Texture*> marsh;
	vector<vector<Texture*>> starting_location;
	
	ObjConfig::textureMapConfig = &textureMap;
	ObjConfig::standard_con = &standard;
	ObjConfig::oasis_con = &oasis;
	ObjConfig::jungle_con = &jungle;
	ObjConfig::mountain_con = &mountain;
	ObjConfig::marsh_con = &marsh;
	ObjConfig::import_config(recVec_ptr, gameplay_functions, tBuffer);

	DialogueConfig::import_config(gameplay_functions, tBuffer);
	DialogueController::getDialogueHelper()->fill_conversations();
	TagConfig::import_config(gameplay_functions, tBuffer);

	WorldObj* barrel = new WorldObj(Vector2f(5200, 3900), 75, 75);
	//Alex->name = SHANGO;
	
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

	gameplay_functions->add_texture("playerTexture", 0, 0, 0);
	gameplay_functions->add_texture("playerIdleTex", 0, 0, 0);
	tBuffer->run();
	textureMap[Containers::texture_table["playerTexture"]] = pair<string, int>("Assets/Sprites/ShangoForwardIdle.png", 22);
	textureMap[Containers::texture_table["playerIdleTex"]] = pair<string, int>("Assets/Sprites/ShangoForwardIdle.png", 22);
	standard.push_back(Containers::texture_table["playerTexture"]);
	standard.push_back(Containers::texture_table["playerIdleTex"]);

	gameplay_functions->add_texture("upRunTex", 0, 0, 0);
	gameplay_functions->add_texture("downRunTex", 0, 0, 0);
	gameplay_functions->add_texture("leftRunTex", 0, 0, 0);
	gameplay_functions->add_texture("rightRunTex", 0, 0, 0);
	gameplay_functions->add_texture("upIdleTex", 0, 0, 0);
	gameplay_functions->add_texture("downIdleTex", 0, 0, 0);
	gameplay_functions->add_texture("leftIdleTex", 0, 0, 0);
	gameplay_functions->add_texture("rightIdleTex", 0, 0, 0);
	gameplay_functions->add_texture("upAtkTex", 0, 0, 0);
	gameplay_functions->add_texture("downAtkTex", 0, 0, 0);
	gameplay_functions->add_texture("leftAtkTex", 0, 0, 0);
	gameplay_functions->add_texture("rightAtkTex", 0, 0, 0);
	gameplay_functions->add_texture("upAtk2Tex", 0, 0, 0);
	gameplay_functions->add_texture("downAtk2Tex", 0, 0, 0);
	gameplay_functions->add_texture("leftAtk2Tex", 0, 0, 0);
	gameplay_functions->add_texture("rightAtk2Tex", 0, 0, 0);
	gameplay_functions->add_texture("upHurtTex", 0, 0, 0);
	gameplay_functions->add_texture("downHurtTex", 0, 0, 0);
	gameplay_functions->add_texture("leftHurtTex", 0, 0, 0);
	gameplay_functions->add_texture("rightHurtTex", 0, 0, 0);
	tBuffer->run();

	textureMap[Containers::texture_table["upRunTex"]] = pair<string, int>("Assets/Sprites/ShangoBackSprint.png", 16);
	textureMap[Containers::texture_table["downRunTex"]] = pair<string, int>("Assets/Sprites/ShangoForwardSprint.png", 16);
	textureMap[Containers::texture_table["leftRunTex"]] = pair<string, int>("Assets/Sprites/ShangoLeftSprint.png", 16);
	textureMap[Containers::texture_table["rightRunTex"]] = pair<string, int>("Assets/Sprites/ShangoRightSprint.png", 16);
	textureMap[Containers::texture_table["upIdleTex"]] = pair<string, int>("Assets/Sprites/ShangoBackIdle.png", 22);
	textureMap[Containers::texture_table["downIdleTex"]] = pair<string, int>("Assets/Sprites/ShangoForwardIdle.png", 22);
	textureMap[Containers::texture_table["leftIdleTex"]] = pair<string, int>("Assets/Sprites/ShangoLeftIdle.png", 22);
	textureMap[Containers::texture_table["rightIdleTex"]] = pair<string, int>("Assets/Sprites/ShangoRightIdle.png", 22);
	textureMap[Containers::texture_table["upAtkTex"]] = pair<string, int>("Assets/Sprites/ShangoBackSwing.png", 13);
	textureMap[Containers::texture_table["downAtkTex"]] = pair<string, int>("Assets/Sprites/ShangoForwardSwing.png", 13);
	textureMap[Containers::texture_table["leftAtkTex"]] = pair<string, int>("Assets/Sprites/ShangoLeftSwing.png", 13);
	textureMap[Containers::texture_table["rightAtkTex"]] = pair<string, int>("Assets/Sprites/ShangoRightSwing.png", 13);
	textureMap[Containers::texture_table["upAtk2Tex"]] = pair<string, int>("Assets/Sprites/ShangoBackLunge.png", 7);
	textureMap[Containers::texture_table["downAtk2Tex"]] = pair<string, int>("Assets/Sprites/ShangoForwardLunge.png", 7);
	textureMap[Containers::texture_table["leftAtk2Tex"]] = pair<string, int>("Assets/Sprites/ShangoLeftLunge.png", 7);
	textureMap[Containers::texture_table["rightAtk2Tex"]] = pair<string, int>("Assets/Sprites/ShangoRightLunge.png", 7);
	textureMap[Containers::texture_table["upHurtTex"]] = pair<string, int>("Assets/Sprites/ShangoBackRecoil.png", 18);
	textureMap[Containers::texture_table["downHurtTex"]] = pair<string, int>("Assets/Sprites/ShangoForwardRecoil.png", 18);
	textureMap[Containers::texture_table["leftHurtTex"]] = pair<string, int>("Assets/Sprites/ShangoLeftRecoil.png", 18);
	textureMap[Containers::texture_table["rightHurtTex"]] = pair<string, int>("Assets/Sprites/ShangoRightRecoil.png", 18);
	standard.push_back(Containers::texture_table["upRunTex"]);
	standard.push_back(Containers::texture_table["downRunTex"]);
	standard.push_back(Containers::texture_table["leftRunTex"]);
	standard.push_back(Containers::texture_table["rightRunTex"]);
	standard.push_back(Containers::texture_table["upIdleTex"]);
	standard.push_back(Containers::texture_table["downIdleTex"]);
	standard.push_back(Containers::texture_table["leftIdleTex"]);
	standard.push_back(Containers::texture_table["rightIdleTex"]);
	standard.push_back(Containers::texture_table["upAtkTex"]);
	standard.push_back(Containers::texture_table["downAtkTex"]);
	standard.push_back(Containers::texture_table["leftAtkTex"]);
	standard.push_back(Containers::texture_table["rightAtkTex"]);
	standard.push_back(Containers::texture_table["upAtk2Tex"]);
	standard.push_back(Containers::texture_table["downAtk2Tex"]);
	standard.push_back(Containers::texture_table["leftAtk2Tex"]);
	standard.push_back(Containers::texture_table["rightAtk2Tex"]);
	standard.push_back(Containers::texture_table["upHurtTex"]);
	standard.push_back(Containers::texture_table["downHurtTex"]);
	standard.push_back(Containers::texture_table["leftHurtTex"]);
	standard.push_back(Containers::texture_table["rightHurtTex"]);

	gameplay_functions->add_texture("yemojaTexture", 0, 0, 0);
	gameplay_functions->add_texture("yemojaIdleTex", 0, 0, 0);
	tBuffer->run();

  textureMap[Containers::texture_table["yemojaTexture"]] = pair<string, int>("Assets/Sprites/YemojaForwardIdle.png", 22);
	textureMap[Containers::texture_table["yemojaIdleTex"]] = pair<string, int>("Assets/Sprites/YemojaForwardIdle.png", 22);
	oasis.push_back(Containers::texture_table["yemojaTexture"]);
	oasis.push_back(Containers::texture_table["yemojaIdleTex"]);

  gameplay_functions->add_texture("h_upIdleTex", 0, 0, 0);
  gameplay_functions->add_texture("h_downIdleTex", 0, 0, 0);
  gameplay_functions->add_texture("h_leftIdleTex", 0, 0, 0);
  gameplay_functions->add_texture("h_rightIdleTex", 0, 0, 0);
  gameplay_functions->add_texture("h_upWalkTex", 0, 0, 0);
  gameplay_functions->add_texture("h_downWalkTex", 0, 0, 0);
  gameplay_functions->add_texture("h_leftWalkTex", 0, 0, 0);
  gameplay_functions->add_texture("h_rightWalkTex", 0, 0, 0);
	gameplay_functions->add_texture("h_upRunTex", 0, 0, 0);
	gameplay_functions->add_texture("h_downRunTex", 0, 0, 0);
	gameplay_functions->add_texture("h_leftRunTex", 0, 0, 0);
	gameplay_functions->add_texture("h_rightRunTex", 0, 0, 0);
  gameplay_functions->add_texture("YswingRight", 0, 0, 0);
  gameplay_functions->add_texture("YswingUp", 0, 0, 0);
  gameplay_functions->add_texture("YswingDown", 0, 0, 0);
  gameplay_functions->add_texture("YswingLeft", 0, 0, 0);
  gameplay_functions->add_texture("YhurtRight", 0, 0, 0);
  gameplay_functions->add_texture("YhurtUp", 0, 0, 0);
  gameplay_functions->add_texture("YhurtDown", 0, 0, 0);
  gameplay_functions->add_texture("YhurtLeft", 0, 0, 0);
  gameplay_functions->add_texture("YdeathUp", 0, 0, 0);
  gameplay_functions->add_texture("YdeathDown", 0, 0, 0);
  gameplay_functions->add_texture("YdeathLeft", 0, 0, 0);
  gameplay_functions->add_texture("YdeathRight", 0, 0, 0);
	tBuffer->run();

  textureMap[Containers::texture_table["h_upIdleTex"]] = {YEMOJA_PATH + "Yemoja_Idle_N.png", 22};
  textureMap[Containers::texture_table["h_downIdleTex"]] = {YEMOJA_PATH + "Yemoja_Idle_S.png", 22};
  textureMap[Containers::texture_table["h_leftIdleTex"]] = {YEMOJA_PATH + "Yemoja_Idle_W.png", 22};
  textureMap[Containers::texture_table["h_rightIdleTex"]] = {YEMOJA_PATH + "Yemoja_Idle_E.png", 22};
  textureMap[Containers::texture_table["h_upWalkTex"]] = {YEMOJA_PATH + "Yemoja_Walk_N.png", 32};
  textureMap[Containers::texture_table["h_downWalkTex"]] = {YEMOJA_PATH + "Yemoja_Walk_S.png", 32};
  textureMap[Containers::texture_table["h_leftWalkTex"]] = {YEMOJA_PATH + "Yemoja_Walk_W.png", 32};
  textureMap[Containers::texture_table["h_rightWalkTex"]] = {YEMOJA_PATH + "Yemoja_Walk_E.png", 32};
	textureMap[Containers::texture_table["h_upRunTex"]] = {YEMOJA_PATH + "Yemoja_Sprint_N.png", 16};
	textureMap[Containers::texture_table["h_downRunTex"]] = {YEMOJA_PATH + "Yemoja_Sprint_S.png", 16};
	textureMap[Containers::texture_table["h_leftRunTex"]] = {YEMOJA_PATH + "Yemoja_Sprint_W.png", 16};
	textureMap[Containers::texture_table["h_rightRunTex"]] = {YEMOJA_PATH + "Yemoja_Sprint_E.png", 16};
  textureMap[Containers::texture_table["YswingUp"]] = {YEMOJA_PATH + "Yemoja_Breath_N.png", 8};
  textureMap[Containers::texture_table["YswingDown"]] = {YEMOJA_PATH + "Yemoja_Breath_S.png", 8};
  textureMap[Containers::texture_table["YswingLeft"]] = {YEMOJA_PATH + "Yemoja_Breath_W.png", 8};
  textureMap[Containers::texture_table["YswingRight"]] = {YEMOJA_PATH + "Yemoja_Breath_E.png", 8};
  textureMap[Containers::texture_table["YhurtUp"]] = {YEMOJA_PATH + "Yemoja_Recoil_N.png", 9};
  textureMap[Containers::texture_table["YhurtDown"]] = {YEMOJA_PATH + "Yemoja_Recoil_S.png", 9};
  textureMap[Containers::texture_table["YhurtLeft"]] = {YEMOJA_PATH + "Yemoja_Recoil_W.png", 9};
  textureMap[Containers::texture_table["YhurtRight"]] = {YEMOJA_PATH + "Yemoja_Recoil_E.png", 9};
  textureMap[Containers::texture_table["YdeathUp"]] = {YEMOJA_PATH + "Yemoja_Death_N.png", 24};
  textureMap[Containers::texture_table["YdeathDown"]] = {YEMOJA_PATH + "Yemoja_Death_S.png", 24};
  textureMap[Containers::texture_table["YdeathLeft"]] = {YEMOJA_PATH + "Yemoja_Death_W.png", 24};
  textureMap[Containers::texture_table["YdeathRight"]] = {YEMOJA_PATH + "Yemoja_Death_E.png", 24};

  oasis.push_back(Containers::texture_table["h_upIdleTex"]);
  oasis.push_back(Containers::texture_table["h_downIdleTex"]);
  oasis.push_back(Containers::texture_table["h_leftIdleTex"]);
  oasis.push_back(Containers::texture_table["h_rightIdleTex"]);
  oasis.push_back(Containers::texture_table["h_upWalkTex"]);
  oasis.push_back(Containers::texture_table["h_downWalkTex"]);
  oasis.push_back(Containers::texture_table["h_leftWalkTex"]);
  oasis.push_back(Containers::texture_table["h_rightWalkTex"]);
	oasis.push_back(Containers::texture_table["h_upRunTex"]);
	oasis.push_back(Containers::texture_table["h_downRunTex"]);
	oasis.push_back(Containers::texture_table["h_leftRunTex"]);
	oasis.push_back(Containers::texture_table["h_rightRunTex"]);
  oasis.push_back(Containers::texture_table["YswingRight"]);
  oasis.push_back(Containers::texture_table["YswingUp"]);
  oasis.push_back(Containers::texture_table["YswingDown"]);
  oasis.push_back(Containers::texture_table["YswingLeft"]);
  oasis.push_back(Containers::texture_table["YhurtRight"]);
  oasis.push_back(Containers::texture_table["YhurtUp"]);
  oasis.push_back(Containers::texture_table["YhurtDown"]);
  oasis.push_back(Containers::texture_table["YhurtLeft"]);
  oasis.push_back(Containers::texture_table["YdeathUp"]);
  oasis.push_back(Containers::texture_table["YdeathDown"]);
  oasis.push_back(Containers::texture_table["YdeathLeft"]);
  oasis.push_back(Containers::texture_table["YdeathRight"]);

  gameplay_functions->add_texture("Oya_IdleUpTex", 0, 0, 0);
  gameplay_functions->add_texture("Oya_IdleDownTex", 0, 0, 0);
  gameplay_functions->add_texture("Oya_IdleLeftTex", 0, 0, 0);
  gameplay_functions->add_texture("Oya_IdleRightTex", 0, 0, 0);
  gameplay_functions->add_texture("Oya_WalkUpTex", 0, 0, 0);
  gameplay_functions->add_texture("Oya_WalkDownTex", 0, 0, 0);
  gameplay_functions->add_texture("Oya_WalkLeftTex", 0, 0, 0);
  gameplay_functions->add_texture("Oya_WalkRightTex", 0, 0, 0);
  gameplay_functions->add_texture("Oya_SprintUpTex", 0, 0, 0);
  gameplay_functions->add_texture("Oya_SprintDownTex", 0, 0, 0);
  gameplay_functions->add_texture("Oya_SprintLeftTex", 0, 0, 0);
  gameplay_functions->add_texture("Oya_SprintRightTex", 0, 0, 0);
  gameplay_functions->add_texture("Oya_AttackUpTex", 0, 0, 0);
  gameplay_functions->add_texture("Oya_AttackDownTex", 0, 0, 0);
  gameplay_functions->add_texture("Oya_AttackLeftTex", 0, 0, 0);
  gameplay_functions->add_texture("Oya_AttackRightTex", 0, 0, 0);
  gameplay_functions->add_texture("Oya_RecoilUpTex", 0, 0, 0);
  gameplay_functions->add_texture("Oya_RecoilDownTex", 0, 0, 0);
  gameplay_functions->add_texture("Oya_RecoilLeftTex", 0, 0, 0);
  gameplay_functions->add_texture("Oya_RecoilRightTex", 0, 0, 0);
  gameplay_functions->add_texture("Oya_DeathUpTex", 0, 0, 0);
  gameplay_functions->add_texture("Oya_DeathDownTex", 0, 0, 0);
  gameplay_functions->add_texture("Oya_DeathLeftTex", 0, 0, 0);
  gameplay_functions->add_texture("Oya_DeathRightTex", 0, 0, 0);
  tBuffer->run();

  textureMap[Containers::texture_table["Oya_IdleUpTex"]] = {OYA_PATH + "Oya_Idle_N.png", 22};
  textureMap[Containers::texture_table["Oya_IdleDownTex"]] = {OYA_PATH + "Oya_Idle_S.png", 22};
  textureMap[Containers::texture_table["Oya_IdleLeftTex"]] = {OYA_PATH + "Oya_Idle_W.png", 22};
  textureMap[Containers::texture_table["Oya_IdleRightTex"]] = {OYA_PATH + "Oya_Idle_E.png", 22};
  textureMap[Containers::texture_table["Oya_WalkUpTex"]] = {OYA_PATH + "Oya_Walk_N.png", 32};
  textureMap[Containers::texture_table["Oya_WalkDownTex"]] = {OYA_PATH + "Oya_Walk_S.png", 32};
  textureMap[Containers::texture_table["Oya_WalkLeftTex"]] = {OYA_PATH + "Oya_Walk_W.png", 32};
  textureMap[Containers::texture_table["Oya_WalkRightTex"]] = {OYA_PATH + "Oya_Walk_E.png", 32};
  textureMap[Containers::texture_table["Oya_SprintUpTex"]] = {OYA_PATH + "Oya_Sprint_N.png", 16};
  textureMap[Containers::texture_table["Oya_SprintDownTex"]] = {OYA_PATH + "Oya_Sprint_S.png", 16};
  textureMap[Containers::texture_table["Oya_SprintLeftTex"]] = {OYA_PATH + "Oya_Sprint_W.png", 16};
  textureMap[Containers::texture_table["Oya_SprintRightTex"]] = {OYA_PATH + "Oya_Sprint_E.png", 16};
  textureMap[Containers::texture_table["Oya_AttackUpTex"]] = {OYA_PATH + "Oya_Attack_N.png", 3};
  textureMap[Containers::texture_table["Oya_AttackDownTex"]] = {OYA_PATH + "Oya_Attack_S.png", 3};
  textureMap[Containers::texture_table["Oya_AttackLeftTex"]] = {OYA_PATH + "Oya_Attack_W.png", 3};
  textureMap[Containers::texture_table["Oya_AttackRightTex"]] = {OYA_PATH + "Oya_Attack_E.png", 3};
  textureMap[Containers::texture_table["Oya_RecoilUpTex"]] = {OYA_PATH + "Oya_Recoil_N.png", 9};
  textureMap[Containers::texture_table["Oya_RecoilDownTex"]] = {OYA_PATH + "Oya_Recoil_S.png", 9};
  textureMap[Containers::texture_table["Oya_RecoilLeftTex"]] = {OYA_PATH + "Oya_Recoil_W.png", 9};
  textureMap[Containers::texture_table["Oya_RecoilRightTex"]] = {OYA_PATH + "Oya_Recoil_E.png", 9};
  textureMap[Containers::texture_table["Oya_DeathUpTex"]] = {OYA_PATH + "Oya_Death_N.png", 24};
  textureMap[Containers::texture_table["Oya_DeathDownTex"]] = {OYA_PATH + "Oya_Death_S.png", 24};
  textureMap[Containers::texture_table["Oya_DeathLeftTex"]] = {OYA_PATH + "Oya_Death_W.png", 24};
  textureMap[Containers::texture_table["Oya_DeathRightTex"]] = {OYA_PATH + "Oya_Death_E.png", 24};

  jungle.push_back(Containers::texture_table["Oya_IdleUpTex"]);
  jungle.push_back(Containers::texture_table["Oya_IdleDownTex"]);
  jungle.push_back(Containers::texture_table["Oya_IdleLeftTex"]);
  jungle.push_back(Containers::texture_table["Oya_IdleRightTex"]);
  jungle.push_back(Containers::texture_table["Oya_WalkUpTex"]);
  jungle.push_back(Containers::texture_table["Oya_WalkDownTex"]);
  jungle.push_back(Containers::texture_table["Oya_WalkLeftTex"]);
  jungle.push_back(Containers::texture_table["Oya_WalkRightTex"]);
  jungle.push_back(Containers::texture_table["Oya_SprintUpTex"]);
  jungle.push_back(Containers::texture_table["Oya_SprintDownTex"]);
  jungle.push_back(Containers::texture_table["Oya_SprintLeftTex"]);
  jungle.push_back(Containers::texture_table["Oya_SprintRightTex"]);
  jungle.push_back(Containers::texture_table["Oya_AttackUpTex"]);
  jungle.push_back(Containers::texture_table["Oya_AttackDownTex"]);
  jungle.push_back(Containers::texture_table["Oya_AttackLeftTex"]);
  jungle.push_back(Containers::texture_table["Oya_AttackRightTex"]);
  jungle.push_back(Containers::texture_table["Oya_RecoilUpTex"]);
  jungle.push_back(Containers::texture_table["Oya_RecoilDownTex"]);
  jungle.push_back(Containers::texture_table["Oya_RecoilLeftTex"]);
  jungle.push_back(Containers::texture_table["Oya_RecoilRightTex"]);
  jungle.push_back(Containers::texture_table["Oya_DeathUpTex"]);
  jungle.push_back(Containers::texture_table["Oya_DeathDownTex"]);
  jungle.push_back(Containers::texture_table["Oya_DeathLeftTex"]);
  jungle.push_back(Containers::texture_table["Oya_DeathRightTex"]);

	gameplay_functions->add_texture("silverSoldierTexture", 0, 0, 0);
	gameplay_functions->add_texture("silverSoldierIdleTex", 0, 0, 0);
	gameplay_functions->add_texture("blueSoldierTexture", 0, 0, 0);
	gameplay_functions->add_texture("blueSoldierIdleTex", 0, 0, 0);
	tBuffer->run();

	textureMap[Containers::texture_table["silverSoldierTexture"]] = pair<string, int>("Assets/Sprites/SilverSoldierForwardIdle.png", 22);
	textureMap[Containers::texture_table["silverSoldierIdleTex"]] = pair<string, int>("Assets/Sprites/SilverSoldierForwardIdle.png", 22);
	textureMap[Containers::texture_table["blueSoldierTexture"]] = pair<string, int>("Assets/Sprites/BlueSoldierForwardIdle.png", 22);
	textureMap[Containers::texture_table["blueSoldierIdleTex"]] = pair<string, int>("Assets/Sprites/BlueSoldierForwardIdle.png", 22);
	standard.push_back(Containers::texture_table["silverSoldierTexture"]);
	standard.push_back(Containers::texture_table["silverSoldierIdleTex"]);
	marsh.push_back(Containers::texture_table["blueSoldierTexture"]);
	marsh.push_back(Containers::texture_table["blueSoldierIdleTex"]);

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

  textureMap[Containers::texture_table["ss_upIdleTex"]] = {SOLDIER_JUNGLE_PATH + "SoldierJungle_Idle_N.png", 22};
  textureMap[Containers::texture_table["ss_downIdleTex"]] = {SOLDIER_JUNGLE_PATH + "SoldierJungle_Idle_S.png", 22};
  textureMap[Containers::texture_table["ss_leftIdleTex"]] = {SOLDIER_JUNGLE_PATH + "SoldierJungle_Idle_W.png", 22};
  textureMap[Containers::texture_table["ss_rightIdleTex"]] = {SOLDIER_JUNGLE_PATH + "SoldierJungle_Idle_E.png", 22};
  textureMap[Containers::texture_table["ss_upWalkTex"]] = {SOLDIER_JUNGLE_PATH + "SoldierJungle_Walk_N.png", 32};
  textureMap[Containers::texture_table["ss_downWalkTex"]] = {SOLDIER_JUNGLE_PATH + "SoldierJungle_Walk_S.png", 32};
  textureMap[Containers::texture_table["ss_leftWalkTex"]] = {SOLDIER_JUNGLE_PATH + "SoldierJungle_Walk_W.png", 32};
  textureMap[Containers::texture_table["ss_rightWalkTex"]] = {SOLDIER_JUNGLE_PATH + "SoldierJungle_Walk_E.png", 32};
	textureMap[Containers::texture_table["ss_upRunTex"]] = {SOLDIER_JUNGLE_PATH + "SoldierJungle_Sprint_N.png", 16};
	textureMap[Containers::texture_table["ss_downRunTex"]] = {SOLDIER_JUNGLE_PATH + "SoldierJungle_Sprint_S.png", 16};
	textureMap[Containers::texture_table["ss_leftRunTex"]] = {SOLDIER_JUNGLE_PATH + "SoldierJungle_Sprint_W.png", 16};
	textureMap[Containers::texture_table["ss_rightRunTex"]] = {SOLDIER_JUNGLE_PATH + "SoldierJungle_Sprint_E.png", 16};
	textureMap[Containers::texture_table["ss_upAtkTex"]] = {SOLDIER_JUNGLE_PATH + "SoldierJungle_Attack_N.png", 3};
	textureMap[Containers::texture_table["ss_downAtkTex"]] = {SOLDIER_JUNGLE_PATH + "SoldierJungle_Attack_S.png", 3};
	textureMap[Containers::texture_table["ss_leftAtkTex"]] = {SOLDIER_JUNGLE_PATH + "SoldierJungle_Attack_W.png", 3};
	textureMap[Containers::texture_table["ss_rightAtkTex"]] = {SOLDIER_JUNGLE_PATH + "SoldierJungle_Attack_E.png", 3};
  textureMap[Containers::texture_table["ss_upLungeTex"]] = {SOLDIER_JUNGLE_PATH + "SoldierJungle_Attack_N.png", 3};
  textureMap[Containers::texture_table["ss_downLungeTex"]] = {SOLDIER_JUNGLE_PATH + "SoldierJungle_Attack_S.png", 3};
  textureMap[Containers::texture_table["ss_leftLungeTex"]] = {SOLDIER_JUNGLE_PATH + "SoldierJungle_Attack_W.png", 3};
  textureMap[Containers::texture_table["ss_rightLungeTex"]] = {SOLDIER_JUNGLE_PATH + "SoldierJungle_Attack_E.png", 3};
	textureMap[Containers::texture_table["ss_upHurtTex"]] = {SOLDIER_JUNGLE_PATH + "SoldierJungle_Recoil_N.png", 9};
	textureMap[Containers::texture_table["ss_downHurtTex"]] = {SOLDIER_JUNGLE_PATH + "SoldierJungle_Recoil_S.png", 9};
	textureMap[Containers::texture_table["ss_leftHurtTex"]] = {SOLDIER_JUNGLE_PATH + "SoldierJungle_Recoil_W.png", 9};
	textureMap[Containers::texture_table["ss_rightHurtTex"]] = {SOLDIER_JUNGLE_PATH + "SoldierJungle_Recoil_E.png", 9};
	textureMap[Containers::texture_table["ss_upDeathTex"]] = {SOLDIER_JUNGLE_PATH + "SoldierJungle_Death_N.png", 24};
	textureMap[Containers::texture_table["ss_downDeathTex"]] = {SOLDIER_JUNGLE_PATH + "SoldierJungle_Death_S.png", 24};
	textureMap[Containers::texture_table["ss_leftDeathTex"]] = {SOLDIER_JUNGLE_PATH + "SoldierJungle_Death_W.png", 24};
	textureMap[Containers::texture_table["ss_rightDeathTex"]] = {SOLDIER_JUNGLE_PATH + "SoldierJungle_Death_E.png", 24};

	mountain.push_back(Containers::texture_table["ss_upRunTex"]);
	mountain.push_back(Containers::texture_table["ss_downRunTex"]);
	mountain.push_back(Containers::texture_table["ss_leftRunTex"]);
	mountain.push_back(Containers::texture_table["ss_rightRunTex"]);
	mountain.push_back(Containers::texture_table["ss_upIdleTex"]);
	mountain.push_back(Containers::texture_table["ss_downIdleTex"]);
	mountain.push_back(Containers::texture_table["ss_leftIdleTex"]);
	mountain.push_back(Containers::texture_table["ss_rightIdleTex"]);
	mountain.push_back(Containers::texture_table["ss_upAtkTex"]);
	mountain.push_back(Containers::texture_table["ss_downAtkTex"]);
	mountain.push_back(Containers::texture_table["ss_leftAtkTex"]);
	mountain.push_back(Containers::texture_table["ss_rightAtkTex"]);
	mountain.push_back(Containers::texture_table["ss_upHurtTex"]);
	mountain.push_back(Containers::texture_table["ss_downHurtTex"]);
	mountain.push_back(Containers::texture_table["ss_leftHurtTex"]);
	mountain.push_back(Containers::texture_table["ss_rightHurtTex"]);
	mountain.push_back(Containers::texture_table["ss_upWalkTex"]);
	mountain.push_back(Containers::texture_table["ss_downWalkTex"]);
	mountain.push_back(Containers::texture_table["ss_leftWalkTex"]);
	mountain.push_back(Containers::texture_table["ss_rightWalkTex"]);
	mountain.push_back(Containers::texture_table["ss_upLungeTex"]);
	mountain.push_back(Containers::texture_table["ss_downLungeTex"]);
	mountain.push_back(Containers::texture_table["ss_leftLungeTex"]);
	mountain.push_back(Containers::texture_table["ss_rightLungeTex"]);
	mountain.push_back(Containers::texture_table["ss_upDeathTex"]);
	mountain.push_back(Containers::texture_table["ss_downDeathTex"]);
	mountain.push_back(Containers::texture_table["ss_leftDeathTex"]);
	mountain.push_back(Containers::texture_table["ss_rightDeathTex"]);

  gameplay_functions->add_texture("bs_upIdleTex", 0, 0, 0);
  gameplay_functions->add_texture("bs_downIdleTex", 0, 0, 0);
  gameplay_functions->add_texture("bs_leftIdleTex", 0, 0, 0);
  gameplay_functions->add_texture("bs_rightIdleTex", 0, 0, 0);
  gameplay_functions->add_texture("bs_upWalkTex", 0, 0, 0);
  gameplay_functions->add_texture("bs_downWalkTex", 0, 0, 0);
  gameplay_functions->add_texture("bs_leftWalkTex", 0, 0, 0);
  gameplay_functions->add_texture("bs_rightWalkTex", 0, 0, 0);
	gameplay_functions->add_texture("bs_upRunTex", 0, 0, 0);
	gameplay_functions->add_texture("bs_downRunTex", 0, 0, 0);
	gameplay_functions->add_texture("bs_leftRunTex", 0, 0, 0);
	gameplay_functions->add_texture("bs_rightRunTex", 0, 0, 0);
	gameplay_functions->add_texture("bs_upAtkTex", 0, 0, 0);
	gameplay_functions->add_texture("bs_downAtkTex", 0, 0, 0);
	gameplay_functions->add_texture("bs_leftAtkTex", 0, 0, 0);
	gameplay_functions->add_texture("bs_rightAtkTex", 0, 0, 0);
  gameplay_functions->add_texture("bs_upLungeTex", 0, 0, 0);
  gameplay_functions->add_texture("bs_downLungeTex", 0, 0, 0);
  gameplay_functions->add_texture("bs_leftLungeTex", 0, 0, 0);
  gameplay_functions->add_texture("bs_rightLungeTex", 0, 0, 0);
	gameplay_functions->add_texture("bs_upHurtTex", 0, 0, 0);
	gameplay_functions->add_texture("bs_downHurtTex", 0, 0, 0);
	gameplay_functions->add_texture("bs_leftHurtTex", 0, 0, 0);
	gameplay_functions->add_texture("bs_rightHurtTex", 0, 0, 0);
	gameplay_functions->add_texture("bs_upDeathTex", 0, 0, 0);
	gameplay_functions->add_texture("bs_downDeathTex", 0, 0, 0);
	gameplay_functions->add_texture("bs_leftDeathTex", 0, 0, 0);
	gameplay_functions->add_texture("bs_rightDeathTex", 0, 0, 0);
	tBuffer->run();

  textureMap[Containers::texture_table["bs_upIdleTex"]] = {SOLDIER_OASIS_PATH + "SoldierOasis_Idle_N.png", 22};
  textureMap[Containers::texture_table["bs_downIdleTex"]] = {SOLDIER_OASIS_PATH + "SoldierOasis_Idle_S.png", 22};
  textureMap[Containers::texture_table["bs_leftIdleTex"]] = {SOLDIER_OASIS_PATH + "SoldierOasis_Idle_W.png", 22};
  textureMap[Containers::texture_table["bs_rightIdleTex"]] = {SOLDIER_OASIS_PATH + "SoldierOasis_Idle_E.png", 22};
  textureMap[Containers::texture_table["bs_upWalkTex"]] = {SOLDIER_OASIS_PATH + "SoldierOasis_Walk_N.png", 32};
  textureMap[Containers::texture_table["bs_downWalkTex"]] = {SOLDIER_OASIS_PATH + "SoldierOasis_Walk_S.png", 32};
  textureMap[Containers::texture_table["bs_leftWalkTex"]] = {SOLDIER_OASIS_PATH + "SoldierOasis_Walk_W.png", 32};
  textureMap[Containers::texture_table["bs_rightWalkTex"]] = {SOLDIER_OASIS_PATH + "SoldierOasis_Walk_E.png", 32};
	textureMap[Containers::texture_table["bs_upRunTex"]] = {SOLDIER_OASIS_PATH + "SoldierOasis_Sprint_N.png", 16};
	textureMap[Containers::texture_table["bs_downRunTex"]] = {SOLDIER_OASIS_PATH + "SoldierOasis_Sprint_S.png", 16};
	textureMap[Containers::texture_table["bs_leftRunTex"]] = {SOLDIER_OASIS_PATH + "SoldierOasis_Sprint_W.png", 16};
	textureMap[Containers::texture_table["bs_rightRunTex"]] = {SOLDIER_OASIS_PATH + "SoldierOasis_Sprint_E.png", 16};
	textureMap[Containers::texture_table["bs_upAtkTex"]] = {SOLDIER_OASIS_PATH + "SoldierOasis_Attack_N.png", 3};
	textureMap[Containers::texture_table["bs_downAtkTex"]] = {SOLDIER_OASIS_PATH + "SoldierOasis_Attack_S.png", 3};
	textureMap[Containers::texture_table["bs_leftAtkTex"]] = {SOLDIER_OASIS_PATH + "SoldierOasis_Attack_W.png", 3};
	textureMap[Containers::texture_table["bs_rightAtkTex"]] = {SOLDIER_OASIS_PATH + "SoldierOasis_Attack_E.png", 3};
  textureMap[Containers::texture_table["bs_upLungeTex"]] = {SOLDIER_OASIS_PATH + "SoldierOasis_Attack_N.png", 3};
  textureMap[Containers::texture_table["bs_downLungeTex"]] = {SOLDIER_OASIS_PATH + "SoldierOasis_Attack_S.png", 3};
  textureMap[Containers::texture_table["bs_leftLungeTex"]] = {SOLDIER_OASIS_PATH + "SoldierOasis_Attack_W.png", 3};
  textureMap[Containers::texture_table["bs_rightLungeTex"]] = {SOLDIER_OASIS_PATH + "SoldierOasis_Attack_E.png", 3};
	textureMap[Containers::texture_table["bs_upHurtTex"]] = {SOLDIER_OASIS_PATH + "SoldierOasis_Recoil_N.png", 9};
	textureMap[Containers::texture_table["bs_downHurtTex"]] = {SOLDIER_OASIS_PATH + "SoldierOasis_Recoil_S.png", 9};
	textureMap[Containers::texture_table["bs_leftHurtTex"]] = {SOLDIER_OASIS_PATH + "SoldierOasis_Recoil_W.png", 9};
	textureMap[Containers::texture_table["bs_rightHurtTex"]] = {SOLDIER_OASIS_PATH + "SoldierOasis_Recoil_E.png", 9};
	textureMap[Containers::texture_table["bs_upDeathTex"]] = {SOLDIER_OASIS_PATH + "SoldierOasis_Death_N.png", 24};
	textureMap[Containers::texture_table["bs_downDeathTex"]] = {SOLDIER_OASIS_PATH + "SoldierOasis_Death_S.png", 24};
	textureMap[Containers::texture_table["bs_leftDeathTex"]] = {SOLDIER_OASIS_PATH + "SoldierOasis_Death_W.png", 24};
	textureMap[Containers::texture_table["bs_rightDeathTex"]] = {SOLDIER_OASIS_PATH + "SoldierOasis_Death_E.png", 24};

	gameplay_functions->add_texture("treeTex", 0, 0, 0);
	marsh.push_back(Containers::texture_table["bs_upRunTex"]);
	marsh.push_back(Containers::texture_table["bs_downRunTex"]);
	marsh.push_back(Containers::texture_table["bs_leftRunTex"]);
	marsh.push_back(Containers::texture_table["bs_rightRunTex"]);
	marsh.push_back(Containers::texture_table["bs_upIdleTex"]);
	marsh.push_back(Containers::texture_table["bs_downIdleTex"]);
	marsh.push_back(Containers::texture_table["bs_leftIdleTex"]);
	marsh.push_back(Containers::texture_table["bs_rightIdleTex"]);
	marsh.push_back(Containers::texture_table["bs_upAtkTex"]);
	marsh.push_back(Containers::texture_table["bs_downAtkTex"]);
	marsh.push_back(Containers::texture_table["bs_leftAtkTex"]);
	marsh.push_back(Containers::texture_table["bs_rightAtkTex"]);
	marsh.push_back(Containers::texture_table["bs_upHurtTex"]);
	marsh.push_back(Containers::texture_table["bs_downHurtTex"]);
	marsh.push_back(Containers::texture_table["bs_leftHurtTex"]);
	marsh.push_back(Containers::texture_table["bs_rightHurtTex"]);
	marsh.push_back(Containers::texture_table["bs_upWalkTex"]);
	marsh.push_back(Containers::texture_table["bs_downWalkTex"]);
	marsh.push_back(Containers::texture_table["bs_leftWalkTex"]);
	marsh.push_back(Containers::texture_table["bs_rightWalkTex"]);
	marsh.push_back(Containers::texture_table["bs_upLungeTex"]);
	marsh.push_back(Containers::texture_table["bs_downLungeTex"]);
	marsh.push_back(Containers::texture_table["bs_leftLungeTex"]);
	marsh.push_back(Containers::texture_table["bs_rightLungeTex"]);

	gameplay_functions->add_texture("rockTex1", 0, 0, 0);
	gameplay_functions->add_texture("rockTex2", 0, 0, 0);
	tBuffer->run();

	textureMap[Containers::texture_table["rockTex1"]] = pair<string, int>("Assets/Sprites/rock_1.png", 1);
	textureMap[Containers::texture_table["rockTex2"]] = pair<string, int>("Assets/Sprites/rock_2.png", 1);
	standard.push_back(Containers::texture_table["rockTex1"]);
	standard.push_back(Containers::texture_table["rockTex2"]);

	gameplay_functions->add_texture("blank", 0, 0, 0);
	gameplay_functions->add_texture("border", 0, 0, 0);
	tBuffer->run();

  textureMap[Containers::texture_table["blank"]] = pair<string, int>("Assets/Sprites/blank.png", 1);
	textureMap[Containers::texture_table["border"]] = pair<string, int>("Assets/Sprites/border.png", 1);
	standard.push_back(Containers::texture_table["blank"]);
	standard.push_back(Containers::texture_table["border"]);

	gameplay_functions->add_texture("fire", 0, 0, 0);
	gameplay_functions->add_texture("fireUp", 0, 0, 0);
	gameplay_functions->add_texture("fireDown", 0, 0, 0);
	gameplay_functions->add_texture("fireLeft", 0, 0, 0);
	tBuffer->run();

	textureMap[Containers::texture_table["fire"]] = pair<string, int>("Assets/Sprites/FireBallTMP.png", 3);
	textureMap[Containers::texture_table["fireUp"]] = pair<string, int>("Assets/Sprites/FireBallTMPUp.png", 3);
	textureMap[Containers::texture_table["fireDown"]] = pair<string, int>("Assets/Sprites/FireBallTMPDown.png", 3);
	textureMap[Containers::texture_table["fireLeft"]] = pair<string, int>("Assets/Sprites/FireBallTMPLeft.png", 3);
	standard.push_back(Containers::texture_table["fire"]);
	standard.push_back(Containers::texture_table["fireUp"]);
	standard.push_back(Containers::texture_table["fireDown"]);
	standard.push_back(Containers::texture_table["fireLeft"]);

	gameplay_functions->add_texture("firebreatheRight", 0, 0, 0);
	gameplay_functions->add_texture("firebreatheUp", 0, 0, 0);
	gameplay_functions->add_texture("firebreatheDown", 0, 0, 0);
	gameplay_functions->add_texture("firebreatheLeft", 0, 0, 0);
	tBuffer->run();

	textureMap[Containers::texture_table["firebreatheRight"]] = pair<string, int>("Assets/Sprites/ShangoRightBreath.png", 14);
	textureMap[Containers::texture_table["firebreatheUp"]] = pair<string, int>("Assets/Sprites/ShangoBackBreath.png", 14);
	textureMap[Containers::texture_table["firebreatheDown"]] = pair<string, int>("Assets/Sprites/ShangoForwardBreath.png", 14);
	textureMap[Containers::texture_table["firebreatheLeft"]] = pair<string, int>("Assets/Sprites/ShangoLeftBreath.png", 14);
	standard.push_back(Containers::texture_table["firebreatheRight"]);
	standard.push_back(Containers::texture_table["firebreatheUp"]);
	standard.push_back(Containers::texture_table["firebreatheDown"]);
	standard.push_back(Containers::texture_table["firebreatheLeft"]);

	gameplay_functions->add_texture("spinRight", 0, 0, 0);
	gameplay_functions->add_texture("spinUp", 0, 0, 0);
	gameplay_functions->add_texture("spinDown", 0, 0, 0);
	gameplay_functions->add_texture("spinLeft", 0, 0, 0);
	tBuffer->run();

	textureMap[Containers::texture_table["spinRight"]] = pair<string, int>("Assets/Sprites/ShangoRightSpin.png", 22);
	textureMap[Containers::texture_table["spinUp"]] = pair<string, int>("Assets/Sprites/ShangoBackSpin.png", 22);
	textureMap[Containers::texture_table["spinDown"]] = pair<string, int>("Assets/Sprites/ShangoForwardSpin.png", 22);
	textureMap[Containers::texture_table["spinLeft"]] = pair<string, int>("Assets/Sprites/ShangoLeftSpin.png", 22);
	standard.push_back(Containers::texture_table["spinRight"]);
	standard.push_back(Containers::texture_table["spinUp"]);
	standard.push_back(Containers::texture_table["spinDown"]);
	standard.push_back(Containers::texture_table["spinLeft"]);

	//load sprite from a configuration file?
	Alex->setHealth(200);

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
	//for (const auto& it : textureMap) {
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
			starting_location.push_back(oasis);
		}
		else if (RegionState::regions[closest] == Mountain) {
			starting_location.push_back(mountain);
		}
		else if (RegionState::regions[closest] == Jungle) {
			starting_location.push_back(jungle);
		}
		else if (RegionState::regions[closest] == Marsh) {
			starting_location.push_back(marsh);
		}
		RegionState::regions.erase(RegionState::regions.begin()+closest);
	}

	HGLRC loaderContext0 = wglCreateContext(hdc);
	wglShareLists(mainContext, loaderContext0);
	std::thread t0([=]() {
		wglMakeCurrent(hdc, loaderContext0);
		for (int i = 0; i < standard.size(); i++) {
			set_file_with_thread(standard[i], &textureMap.find(standard[i])->second);
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
			set_file_with_thread(starting_location[0].at(i), &textureMap.find(starting_location[0].at(i))->second);
		}
		for (auto it = recVec.begin(); it != recVec.end(); ++it) {
			(*it)->sprite.reset_texture();
		}
		for (auto it = movVec.begin(); it != movVec.end(); ++it) {
			(*it)->sprite.reset_texture();
		}
		for (int i = 0; i < (starting_location[3]).size(); i++) {
			set_file_with_thread(starting_location[3].at(i), &textureMap.find(starting_location[3].at(i))->second);
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
			set_file_with_thread(starting_location[1].at(i), &textureMap.find(starting_location[1].at(i))->second);
		}
		for (auto it = recVec.begin(); it != recVec.end(); ++it) {
			(*it)->sprite.reset_texture();
		}
		for (auto it = movVec.begin(); it != movVec.end(); ++it) {
			(*it)->sprite.reset_texture();
		}
		for (int i = 0; i < (starting_location[2]).size(); i++) {
			set_file_with_thread(starting_location[2].at(i), &textureMap.find(starting_location[2].at(i))->second);
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
	
	Alex->sprite.setTexture(Containers::texture_table["playerTexture"]);
	Alex->sprite.setIdleTexture(Containers::texture_table["playerIdleTex"]);
	Alex->sprite.up = Containers::texture_table["upRunTex"];
	Alex->sprite.down = Containers::texture_table["downRunTex"];
	Alex->sprite.left = Containers::texture_table["leftRunTex"];
	Alex->sprite.right = Containers::texture_table["rightRunTex"];

	Alex->sprite.id_up = Containers::texture_table["upIdleTex"];
	Alex->sprite.id_left = Containers::texture_table["leftIdleTex"];
	Alex->sprite.id_right = Containers::texture_table["rightIdleTex"];
	Alex->sprite.id_down = Containers::texture_table["downIdleTex"];

	Alex->sprite.atk_up = Containers::texture_table["upAtkTex"];
	Alex->sprite.atk_down = Containers::texture_table["downAtkTex"];
	Alex->sprite.atk_left = Containers::texture_table["leftAtkTex"];
	Alex->sprite.atk_right = Containers::texture_table["rightAtkTex"];
	Alex->sprite.atk2_up = Containers::texture_table["upAtk2Tex"];
	Alex->sprite.atk2_down = Containers::texture_table["downAtk2Tex"];
	Alex->sprite.atk2_left = Containers::texture_table["leftAtk2Tex"];
	Alex->sprite.atk2_right = Containers::texture_table["rightAtk2Tex"];

	Alex->sprite.spin_up = Containers::texture_table["spinUp"];
	Alex->sprite.spin_down = Containers::texture_table["spinDown"];
	Alex->sprite.spin_left = Containers::texture_table["spinLeft"];
	Alex->sprite.spin_right = Containers::texture_table["spinRight"];
	Alex->sprite.breathe_up = Containers::texture_table["firebreatheUp"];
	Alex->sprite.breathe_down = Containers::texture_table["firebreatheDown"];
	Alex->sprite.breathe_left = Containers::texture_table["firebreatheLeft"];
	Alex->sprite.breathe_right = Containers::texture_table["firebreatheRight"];

	Alex->sprite.hurt_up = Containers::texture_table["upHurtTex"];
	Alex->sprite.hurt_down = Containers::texture_table["downHurtTex"];
	Alex->sprite.hurt_left = Containers::texture_table["leftHurtTex"];
	Alex->sprite.hurt_right = Containers::texture_table["rightHurtTex"];

	Alex->offsetBody(0, 50, 50, 50, 50);
	Alex->setInteractable(true);
	Alex->setName("Shango");
	Alex->setTalkDist(20);

	Alex->setDirection(WorldObj::DIRECTION_DOWN);
	gameplay_functions->add_Attack(Alex->getKey(), Alex->body[0].getX(), Alex->body[0].getY(), true, 10);

	tBuffer->run();

	Alex->melee = Containers::Attack_table[Alex->getKey()];
	Alex->melee->setDmg(10);
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

	staticRec->setWidth(150);
	staticRec->setHeight(150);
	staticRec->name = YEMOJA;

	staticRec->sprite.setTexture(Containers::texture_table["yemojaTexture"]);
	staticRec->sprite.setIdleTexture(Containers::texture_table["yemojaIdleTex"]);
  staticRec->sprite.id_up = Containers::texture_table["h_upIdleTex"];
  staticRec->sprite.id_left = Containers::texture_table["h_leftIdleTex"];
  staticRec->sprite.id_right = Containers::texture_table["h_rightIdleTex"];
  staticRec->sprite.id_down = Containers::texture_table["h_downIdleTex"];
	staticRec->sprite.up = Containers::texture_table["h_upWalkTex"];
	staticRec->sprite.down = Containers::texture_table["h_downWalkTex"];
	staticRec->sprite.left = Containers::texture_table["h_leftWalkTex"];
	staticRec->sprite.right = Containers::texture_table["h_rightWalkTex"];
	staticRec->sprite.hurt_up = Containers::texture_table["YhurtUp"];
	staticRec->sprite.hurt_down = Containers::texture_table["YhurtDown"];
	staticRec->sprite.hurt_left = Containers::texture_table["YhurtLeft"];
	staticRec->sprite.hurt_right = Containers::texture_table["YhurtRight"];
	staticRec->sprite.atk_up = Containers::texture_table["YswingUp"];
	staticRec->sprite.atk_down = Containers::texture_table["YswingDown"];
	staticRec->sprite.atk_left = Containers::texture_table["YswingLeft"];
	staticRec->sprite.atk_right = Containers::texture_table["YswingRight"];
	staticRec->sprite.death_up = Containers::texture_table["bs_upHurtTex"];
	staticRec->sprite.death_down = Containers::texture_table["bs_upHurtTex"];
	staticRec->sprite.death_left = Containers::texture_table["bs_upHurtTex"];
	staticRec->sprite.death_right = Containers::texture_table["bs_upHurtTex"];

  oya->sprite.setTexture(Containers::texture_table["Oya_IdleDownTex"]);
  oya->sprite.setIdleTexture(Containers::texture_table["Oya_IdleDownTex"]);
  oya->sprite.id_up = Containers::texture_table["Oya_IdleUpTex"];
  oya->sprite.id_down = Containers::texture_table["Oya_IdleDownTex"];
  oya->sprite.id_left = Containers::texture_table["Oya_IdleLeftTex"];
  oya->sprite.id_right = Containers::texture_table["Oya_IdleRightTex"];
  oya->sprite.up = Containers::texture_table["Oya_WalkUpTex"];
  oya->sprite.down = Containers::texture_table["Oya_WalkDownTex"];
  oya->sprite.left = Containers::texture_table["Oya_WalkLeftTex"];
  oya->sprite.right = Containers::texture_table["Oya_WalkRightTex"];
  oya->sprite.atk_up = Containers::texture_table["Oya_AttackUpTex"];
  oya->sprite.atk_down = Containers::texture_table["Oya_AttackDownTex"];
  oya->sprite.atk_left = Containers::texture_table["Oya_AttackLeftTex"];
  oya->sprite.atk_right = Containers::texture_table["Oya_AttackRightTex"];
  oya->sprite.hurt_up = Containers::texture_table["Oya_RecoilUpTex"];
  oya->sprite.hurt_down = Containers::texture_table["Oya_RecoilDownTex"];
  oya->sprite.hurt_left = Containers::texture_table["Oya_RecoilLeftTex"];
  oya->sprite.hurt_right = Containers::texture_table["Oya_RecoilRightTex"];
  oya->sprite.death_up = Containers::texture_table["Oya_DeathUpTex"];
  oya->sprite.death_down = Containers::texture_table["Oya_DeathDownTex"];
  oya->sprite.death_left = Containers::texture_table["Oya_DeathLeftTex"];
  oya->sprite.death_right = Containers::texture_table["Oya_DeathRightTex"];

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
	/*for (Vector2f first : ai->graph.vertices) {
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
	}*/

	staticRec->setName("Yemoja");
	staticRec->setInteractable(true);
	staticRec->setPersonality(30, 80, 80, 50, 50, 50, 80);// uncommented this
	oya->setPersonality(80, 50, 80, 50, 80, 80, 50);// uncommented this

	//staticRec->rel[OYA]->setAffinity(60);// uncommented this
	//staticRec->rel[OYA]->setNotoriety(40);// uncommented this
	//staticRec->rel[OYA]->setStrength(80);// uncommented this

	//staticRec->rel[SHANGO]->setAffinity(60);//added this
	//staticRec->rel[SHANGO]->setNotoriety(40);//added this
	//staticRec->rel[SHANGO]->setStrength(80);//added this

	//staticRec->rel[OYA]->setAffEstimate(60);// uncommented this
	//staticRec->rel[OYA]->setNotorEstimate(70);// uncommented this
	//staticRec->rel[OYA]->setStrEstimate(40);// uncommented this

	//staticRec->rel[SHANGO]->setAffEstimate(60);//added this
	//staticRec->rel[SHANGO]->setNotorEstimate(70);//added this
	//staticRec->rel[SHANGO]->setStrEstimate(40);//added this


	//*oya = *staticRec;
	//oya->setSpeed(5);
	oya->setName("Oya");
	oya->name = OYA;
	oya->offsetBody(0, 35, 35, 65, 15);
	staticRec->offsetBody(0, 60, 60, 75, 50);
	oya->shiftY(300);
	oya->setHealth(50);

	// SET UP RELATIONSHIP REFERENCE FOR YEMOJA 
	std::unordered_map<int, Relationship*> yemojaRelRef;
	yemojaRelRef[1] = new Relationship();
	yemojaRelRef[2] = new Relationship();
	yemojaRelRef[3] = new Relationship();

	std::unordered_map<int, Relationship*> OyaRelRef;
	OyaRelRef[1] = new Relationship();
	OyaRelRef[2] = new Relationship();
	OyaRelRef[3] = new Relationship();

	std::unordered_map<int, Relationship*> shangoRel;
	shangoRel[1] = new Relationship();
	shangoRel[2] = new Relationship();
	shangoRel[3] = new Relationship();

	Alex->rel = shangoRel;

	staticRec->rel = yemojaRelRef;
	oya->rel = OyaRelRef;

	ActionConfig::import_config(gameplay_functions, tBuffer, staticRec);
	ActionConfig::import_config(gameplay_functions, tBuffer, oya);

	Planner* YemojaPlanner = new Planner(staticRec);
	Planner* OyaPlanner = new Planner(oya);
	AIController::set_plan(YEMOJA, YemojaPlanner);
	AIController::set_plan(OYA, OyaPlanner);
	
	Action* test_ally = new Action(nullptr, nullptr, nullptr, 10, 1, "Create Alliance", "execute_train");
	Action* test_train = new Action(staticRec, oya, nullptr, 10, 1, "Conquer", "execute_conquer");

	RelPrecon* prec = new RelPrecon(Preconditions::AFF, 60);
	RelPost* post = new RelPost(Postcondition::STR, 10);
	RelPrecon* prec1 = new RelPrecon(Preconditions::AFF, 30);
	RelPost* post1 = new RelPost(Postcondition::STR, 15);
	RelPost* post2 = new RelPost(Postcondition::AFF, 15);
	

	
	test_ally->req_preconds.push_back(std::make_shared<RelPrecon>(*prec));
	test_ally->doer_succ_postconds.push_back(std::make_shared<RelPost>(*post));
	
	test_train->req_preconds.push_back(std::make_shared<RelPrecon>(*prec1));
	test_train->doer_succ_postconds.push_back(std::make_shared<RelPost>(*post1));
	test_train->doer_succ_postconds.push_back(std::make_shared<RelPost>(*post2));
	
	///////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////
	//////////////////                                                 ////////////////////////
	//////////////////             INIT CALLS FOR QUESTS               ////////////////////////
	//////////////////                                                 ////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////
	
	// THIS IS BEING RESET IN THE GAME LOOP. planner->get_current_action returns nullptr*/
	
	
	AIController::generate_end_state(YEMOJA, OYA);
	AIController::init_plans();
   // test_train->setDoer(staticRec);
	//YemojaPlanner->set_current_action(test_train);

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
	short M = GetKeyState('M') >> 15;
	Party::grave->set_perm(true);
	Party* party = new Party();
	Party* party2 = new Party();
	Party* party3 = new Party();
	Party* party4 = new Party();
	party->addToParty(Alex, true);
	for (int i = 0; i < silverSoldier.size(); i++) {
		party4->addToParty(silverSoldier[i], false);
	}
	for (int i = 0; i < blueSoldiers.size(); i++) {
		party3->addToParty(blueSoldiers[i], false);
	}
	party3->addToParty(staticRec, true);
	party4->addToParty(oya, true);
	Village* v1 = new Village();
	//Village* v2 = new Village();
	Village* v3 = new Village();
	Village* v4 = new Village();
	v1->set_village_location(Alex->getLoc());
	//v2->set_village_location({ 6030, 4000 });
	v3->set_village_location(staticRec->getLoc());
	v4->set_village_location(oya->getLoc());
	v1->add_member(Alex);
	for (int i = 0; i < silverSoldier.size(); i++) {
		v4->add_member(silverSoldier[i]);
	}
	for (int i = 0; i < blueSoldiers.size(); i++) {
		v3->add_member(blueSoldiers[i]);
	}
	v3->add_member(staticRec);
	v4->add_member(oya);
	v1->leader = Alex;
	v3->leader = staticRec;
	v4->leader = oya;
	//v4->defenders->addToParty(oya, true);
	Alliance* a1 = new Alliance(v1);
	//Alliance* a2 = new Alliance(v2);
	Alliance* a3 = new Alliance(v3);
	Alliance* a4 = new Alliance(v4);
	v1->addToParties(party);
	//v2->addToParties(party2);
	v3->addToParties(party3);
	v4->addToParties(party4);
	//War* war = new War();
	//war->setWarParties(v1, v2);
	//a1->add_alliance_to_alliance(v3->get_alliance());
	//if (blueSoldiers.size() > 0)party2->set_defend(blueSoldiers[0]->getLoc());
	//party2->setMode(Party::MODE_DEFEND);
	party3->set_defend(staticRec->getLoc());
	party3->setMode(Party::MODE_ATTACK);

	Alliance::update_enemies();

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

	if (PRELOAD_TEX) t0.join();

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
			cout << "Memory Left: " << getFreeVideoMemory() << endl;

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

			cout <<"Memory Left: "<< getFreeVideoMemory() << endl;

			//draw
			if (state == 0) {
				gameplay_functions->draw_frame(Alex);
			}
			//draw
			else if (state > 0) {
				gameplay_functions->drawDiaGui(Alex);
				gameplay_functions->stop(staticRec);
			}

			//run task buffer
			iController->InputCheck();

			//pool.push(test);
			
			cout << "size of buffer is " << tBuffer->queue_buffer.size() << " and physics buffer size is " << tBuffer->physics_buffer.size() << endl;

			//cout << "shango's position BEFORE is at " << Alex->getX() << ", " << Alex->getY() << endl;
			//iterate through physics_buffer
			while(tBuffer->physics_buffer_isEmpty() == false) {
				Task* curr_task = tBuffer->pop_physics();
				cout << "num of idle threads is " << pool.n_idle() << endl;
				pool.push([&,tBuffer,curr_task](int id){ tBuffer->assignTask(0,curr_task); });
			}
			tBuffer->physics_buffer_empty();
			//pool.stop(true);
			//cout << "DONE WITH PHYSICS TASKS" << endl;
			//cout << "shango's position AFTER is at " << Alex->getX() << ", " << Alex->getY() << endl;
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
			YemojaPlanner->give_as_quest = false;
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

			//Checks if game has reached final states
			check_if_end_game();

			current_game_state = iController->current_game_state;
			//system("PAUSE");
			

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
