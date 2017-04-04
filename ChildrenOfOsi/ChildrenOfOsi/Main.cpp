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
#include "Region.h"
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

#include "AIManager.h"
#include "AIController.h"

#include "ObjConfig.h"
#include "ActionPool.h"
#include "ActionHelper.h"
#include "ActionConfig.h"
//class ActionHelper;
#include "Line.h"
#include "ActionExecFunctions.h"
#include "Alliance.h"
#include "PartyManager.h"

using namespace std;



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

void ERONS_LOOP(QuadTree* _Quadtree);
void ALESSIO_TEST();
void ALEX_LOOP(QuadTree* _Quadtree);
void ANDREWS_LOOP(QuadTree* _QuadTree);
void FPS(bool b);
void GAMEPLAY_LOOP(QuadTree* _Quadtree);

//bool collide(WorldObj* recA, WorldObj* recB);
//void Darion_Ian_Test();

void ANDREWS_TEST();
void PHYSICS_TEST();
bool lineCollision(Line l1, Line l2);
/// Helper function passed to thread to set file. Param is a tuple, first being the Texture* to work on, and second being the param needed to call setFile().
void set_file_with_thread(pair<Texture*, pair<string, int>> p_tuple) { std::lock_guard<std::mutex> guard(mu); p_tuple.first->setFile(p_tuple.second.first, p_tuple.second.second); }



//AIController* AiController = new AIController();
//AIController* ActionHelper::ai = AiController;

int main() {

	 //   DialogueHelper* dhelper = new DialogueHelper();

		//ERONS_LOOP();
	    //DialogueHelper* dhelper = new DialogueHelper();

		//dhelper->get_dialog("Yemoja");
		//LOG("Hello world!");
		//ERONS_LOOP();
		/************************************************************************************************SET-UP*******************************************************/
		WorldObj* screen = new WorldObj(Vector2f(0.0, 0.0), 20000U, 20000U);	//init screen

		QuadTree* collideTree = new QuadTree(0, screen);

		/************************************************************************************************TESTING*******************************************************/
		//Player* Daniel = new Player(SHANGO, Vector2f(512.0, 512.0), 150.0, 150.0);
		//Soldier* Alex = new Soldier(Vector2f(512.0 - 150.0, 512.0 - 150.0), 150.0, 150.0);
		//while (1) {
		//	
		//	Alex->getEvadeRange(Daniel);
		//	////cout << "COMBAT RANGE WITH GETTER IS " << Alex->getCombatMoveDestination().getXloc() << ", " << Alex->getCombatMoveDestination().getYloc() << endl;
		//	//////cout << "Alex's target location is: " << Alex->getEvadeRange(Daniel).getXloc() << ", " << Alex->getEvadeRange(Daniel).getYloc() << endl;
		//	//////cout << "Alex's target location is COMBAT: " << Alex->getCombatMoveDestination().getXloc() << ", " << Alex->getCombatMoveDestination().getYloc() << endl;
		//}
		osi::GameWindow::init();
		////pauses the program for viewing

		//system("PAUSE");


		////demonstration of a meory leak
		///*while (true) {
		//	void* a = malloc(64);
		//	delete a;
		//}

		/*Darion Ian Test*/
		//Darion_Ian_Test();

/* ERON */
		//ERONS_LOOP(collideTree);
		/* ERON */
		
		/*ALESSIO*/
		//ALESSIO_TEST();

		/* ALEX */
		//ALEX_LOOP(collideTree);
		//ANDREWS_LOOP(collideTree);

	                                   
		//testQuadTree();
		//ALEX_LOOP(collideTree);   
		
		GAMEPLAY_LOOP(collideTree);


	return 0;
}


void GAMEPLAY_LOOP(QuadTree* _QuadTree)
{
	Rectangle::tex->setFile("Assets/Sprites/blank1.png", 1);
	

	vector<WorldObj*> recVec;
	vector<WorldObj*>* recVec_ptr = &recVec;
	vector<Hero*> heroes;

	/* MULTITHREADING SETUP */

	unordered_map<Texture*, pair<string, int>> textureMap;
	int num_of_threads = std::thread::hardware_concurrency();
	vector<thread> thread_Vec;
	
	/************************************************************/

	//psuedo Gameloop
	MessageLog* mLog = new MessageLog();
	TaskBuffer* tBuffer = new TaskBuffer(mLog);

	//need this here for map editor
	ChildrenOfOsi* gameplay_functions = new ChildrenOfOsi(mLog, tBuffer);

	//Player* Alex = new Player(SHANGO, Vector2f(4900.0, 3700.0), 40.0, 40.0);	//init player
	Player* Alex = new Player(SHANGO, Vector2f(6445.0, 10155.0), 150.0, 150.0);	//init player

	////cout << "Alex's width and height is " << Alex->getWidth() << ", " << Alex->getHeight() << endl;


	RenderManager* RenM = new RenderManager(mLog, tBuffer, _QuadTree, gameplay_functions);
	
	//create Managers and add to Manager table

	DummyController* DumM = new DummyController(mLog, tBuffer);
	PhysicsManager* PhysM = new PhysicsManager(mLog, tBuffer, _QuadTree);

	PartyManager* partyM = new PartyManager(gameplay_functions, Alex);
	memManager* memM = new memManager(mLog, tBuffer);
	TestManager* TestM = new TestManager(mLog, tBuffer);
	AudioManager* AudM = new AudioManager(mLog, tBuffer);
	AIHelper* ai = new AIHelper();
	AIManager* AIM = new AIManager(mLog, tBuffer, ai);

	AIController* AiController = new AIController();
	ActionHelper::ai = AiController;
	ActionHelper::gameplay_func = gameplay_functions;

	CombatController* combatControl = new CombatController(gameplay_functions);

	//the order defines what order the managers the tasks will be sent to
	DumM->register_manager();
	PhysM->register_manager();
	memM->register_manager();
	
	AudM->register_manager();
	//TestM->register_manager();
	AIM->register_manager();
    
 	RenM->register_manager();
//	gameplay_functions->add_hero("Shango", 4900, 3700, true);
//	tBuffer->run();
//	Hero* alex = Containers::hero_table["Shango"];
//	Player* Alex = dynamic_cast<Player*>(alex);
	bool switch_music = false;
	bool in_village = false;


	Region* Ogun = new Region("Ogun", "RegionThemes/OgunRegion.flac", "nothing");
	Region* Desert = new Region("Desert", "RegionThemes/DesertRegion.flac", "nothing");
	Region* Mountain = new Region("Desert", "RegionThemes/MountainRegion.flac", "nothing");
	Region* Jungle = new Region("Desert", "RegionThemes/JungleRegion.flac", "nothing");

	Region current_region = *Desert;
	Region next_region = *Desert;

    Input* iController = new Input(gameplay_functions, Alex, RenM->renderHelper, tBuffer, recVec_ptr, AiController);
	
	
	gameplay_functions->add_hero("Yemoja", 6445.0, 10355.0, true);
	gameplay_functions->add_hero("Oya", 4400, 3600, true);
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

	DialogueController::setAI(AiController);
	//DialogueGui* convoGui = new DialogueGui();

	//Player* Alex = new Player(1000,600, true);	//init player
	//WorldObj* Alex = new WorldObj(1000, 600, true);

	ObjConfig::import_config(recVec_ptr, gameplay_functions, tBuffer);
	
	DialogueConfig::import_config(gameplay_functions, tBuffer);
	DialogueController::getDialogueHelper()->fill_conversations();
	
	WorldObj* barrel = new WorldObj(Vector2f(5200, 3900), 75, 75);
	//Alex->name = SHANGO;
	gameplay_functions->add_texture("map1_1", 0, 0, 0);
	gameplay_functions->add_texture("map1_2", 0, 0, 0);
	gameplay_functions->add_texture("map1_3", 0, 0, 0);
	gameplay_functions->add_texture("map1_4", 0, 0, 0);

	gameplay_functions->add_texture("map2_1", 0, 0, 0);
	gameplay_functions->add_texture("map2_2", 0, 0, 0);
	gameplay_functions->add_texture("map2_3", 0, 0, 0);
	gameplay_functions->add_texture("map2_4", 0, 0, 0);

	gameplay_functions->add_texture("map3_1", 0, 0, 0);
	gameplay_functions->add_texture("map3_2", 0, 0, 0);
	gameplay_functions->add_texture("map3_3", 0, 0, 0);
	gameplay_functions->add_texture("map3_4", 0, 0, 0);

	gameplay_functions->add_texture("map4_1", 0, 0, 0);
	gameplay_functions->add_texture("map4_2", 0, 0, 0);
	gameplay_functions->add_texture("map4_3", 0, 0, 0);
	gameplay_functions->add_texture("map4_4", 0, 0, 0);

	tBuffer->run();

	gameplay_functions->init_map(Alex);

	tBuffer->run();

    Texture* objTexture = new Texture();
	textureMap[objTexture] = pair<string, int>("Assets/Sprites/YemojasHouse.png", 1);

	Texture* playerTexture = new Texture();
	Texture* playerIdleTex = new Texture();
	textureMap[playerTexture] = pair<string, int>("Assets/Sprites/ShangoForwardIdle.png", 22);
	textureMap[playerIdleTex] = pair<string, int>("Assets/Sprites/ShangoForwardIdle.png", 22);

	Texture* upRunTex = new Texture();
	Texture* downRunTex = new Texture();
	Texture* leftRunTex = new Texture();
	Texture* rightRunTex = new Texture();
	Texture* upIdleTex = new Texture();
	Texture* downIdleTex = new Texture();
	Texture* leftIdleTex = new Texture();
	Texture* rightIdleTex = new Texture();
	Texture* upAtkTex = new Texture();
	Texture* downAtkTex = new Texture();
	Texture* leftAtkTex = new Texture();
	Texture* rightAtkTex = new Texture();
	Texture* upAtk2Tex = new Texture();
	Texture* downAtk2Tex = new Texture();
	Texture* leftAtk2Tex = new Texture();
	Texture* rightAtk2Tex = new Texture();
	Texture* upHurtTex = new Texture();
	Texture* downHurtTex = new Texture();
	Texture* leftHurtTex = new Texture();
	Texture* rightHurtTex = new Texture();
	textureMap[upRunTex] = pair<string, int>("Assets/Sprites/ShangoBackSprint.png", 16);
	textureMap[downRunTex] = pair<string, int>("Assets/Sprites/ShangoForwardSprint.png", 16);
	textureMap[leftRunTex] = pair<string, int>("Assets/Sprites/ShangoLeftSprint.png", 16);
	textureMap[rightRunTex] = pair<string, int>("Assets/Sprites/ShangoRightSprint.png", 16);
	textureMap[upIdleTex] = pair<string, int>("Assets/Sprites/ShangoBackIdle.png", 22);
	textureMap[downIdleTex] = pair<string, int>("Assets/Sprites/ShangoForwardIdle.png", 22);
	textureMap[leftIdleTex] = pair<string, int>("Assets/Sprites/ShangoLeftIdle.png", 22);
	textureMap[rightIdleTex] = pair<string, int>("Assets/Sprites/ShangoRightIdle.png", 22);
	textureMap[upAtkTex] = pair<string, int>("Assets/Sprites/ShangoBackSwing.png", 13);
	textureMap[downAtkTex] = pair<string, int>("Assets/Sprites/ShangoForwardSwing.png", 13);
	textureMap[leftAtkTex] = pair<string, int>("Assets/Sprites/ShangoLeftSwing.png", 13);
	textureMap[rightAtkTex] = pair<string, int>("Assets/Sprites/ShangoRightSwing.png", 13);
	textureMap[upAtk2Tex] = pair<string, int>("Assets/Sprites/ShangoBackLunge.png", 7);
	textureMap[downAtk2Tex] = pair<string, int>("Assets/Sprites/ShangoForwardLunge.png", 7);
	textureMap[leftAtk2Tex] = pair<string, int>("Assets/Sprites/ShangoLeftLunge.png", 7);
	textureMap[rightAtk2Tex] = pair<string, int>("Assets/Sprites/ShangoRightLunge.png", 7);
	textureMap[upHurtTex] = pair<string, int>("Assets/Sprites/ShangoBackRecoil.png", 18);
	textureMap[downHurtTex] = pair<string, int>("Assets/Sprites/ShangoForwardRecoil.png", 18);
	textureMap[leftHurtTex] = pair<string, int>("Assets/Sprites/ShangoLeftRecoil.png", 18);
	textureMap[rightHurtTex] = pair<string, int>("Assets/Sprites/ShangoRightRecoil.png", 18);




	Texture* yemojaTexture = new Texture();
	Texture* yemojaIdleTex = new Texture();
	textureMap[yemojaTexture] = pair<string, int>("Assets/Sprites/YemojaForwardIdle.png", 22);
	textureMap[yemojaIdleTex] = pair<string, int>("Assets/Sprites/YemojaForwardIdle.png", 22);

	Texture* h_upRunTex = new Texture();
	Texture* h_downRunTex = new Texture();
	Texture* h_leftRunTex = new Texture();
	Texture* h_rightRunTex = new Texture();
	Texture* h_upIdleTex = new Texture();
	Texture* h_downIdleTex = new Texture();
	Texture* h_leftIdleTex = new Texture();
	Texture* h_rightIdleTex = new Texture();
	textureMap[h_upRunTex] = pair<string, int>("Assets/Sprites/YemojaBackSprint.png", 26);
	textureMap[h_downRunTex] = pair<string, int>("Assets/Sprites/YemojaFrontSprint.png", 26);
	textureMap[h_leftRunTex] = pair<string, int>("Assets/Sprites/YemojaLeftSprint.png", 26);
	textureMap[h_rightRunTex] = pair<string, int>("Assets/Sprites/YemojaRightSprint.png", 26);
	textureMap[h_upIdleTex] = pair<string, int>("Assets/Sprites/YemojaBackIdle.png", 22);
	textureMap[h_downIdleTex] = pair<string, int>("Assets/Sprites/YemojaForwardIdle.png", 22);
	textureMap[h_leftIdleTex] = pair<string, int>("Assets/Sprites/YemojaLeftIdle.png", 22);
	textureMap[h_rightIdleTex] = pair<string, int>("Assets/Sprites/YemojaRightIdle.png", 22);





	Texture* silverSoldierTexture = new Texture();
	Texture* silverSoldierIdleTex = new Texture();
	Texture* blueSoldierTexture = new Texture();
	Texture* blueSoldierIdleTex = new Texture();
	textureMap[silverSoldierTexture] = pair<string, int>("Assets/Sprites/SilverSoldierForwardIdle.png", 22);
	textureMap[silverSoldierIdleTex] = pair<string, int>("Assets/Sprites/SilverSoldierForwardIdle.png", 22);
	textureMap[blueSoldierTexture] = pair<string, int>("Assets/Sprites/BlueSoldierForwardIdle.png", 22);
	textureMap[blueSoldierIdleTex] = pair<string, int>("Assets/Sprites/BlueSoldierForwardIdle.png", 22);


	Texture* ss_upRunTex = new Texture();
	Texture* ss_downRunTex = new Texture();
	Texture* ss_leftRunTex = new Texture();
	Texture* ss_rightRunTex = new Texture();
	Texture* ss_upIdleTex = new Texture();
	Texture* ss_downIdleTex = new Texture();
	Texture* ss_leftIdleTex = new Texture();
	Texture* ss_rightIdleTex = new Texture();
	Texture* ss_upAtkTex = new Texture();
	Texture* ss_downAtkTex = new Texture();
	Texture* ss_leftAtkTex = new Texture();
	Texture* ss_rightAtkTex = new Texture();
	Texture* ss_upHurtTex = new Texture();
	Texture* ss_downHurtTex = new Texture();
	Texture* ss_leftHurtTex = new Texture();
	Texture* ss_rightHurtTex = new Texture();
	Texture* ss_upWalkTex = new Texture();
	Texture* ss_downWalkTex = new Texture();
	Texture* ss_leftWalkTex = new Texture();
	Texture* ss_rightWalkTex = new Texture();
	Texture* ss_upLungeTex = new Texture();
	Texture* ss_downLungeTex = new Texture();
	Texture* ss_leftLungeTex = new Texture();
	Texture* ss_rightLungeTex = new Texture();
	textureMap[ss_upRunTex] = pair<string, int>("Assets/Sprites/SilverSoldierBackSprint.png", 16);
	textureMap[ss_downRunTex] = pair<string, int>("Assets/Sprites/SilverSoldierForwardSprint.png", 16);
	textureMap[ss_leftRunTex] = pair<string, int>("Assets/Sprites/SilverSoldierLeftSprint.png", 16);
	textureMap[ss_rightRunTex] = pair<string, int>("Assets/Sprites/SilverSoldierRightSprint.png", 16);
	textureMap[ss_upIdleTex] = pair<string, int>("Assets/Sprites/SilverSoldierBackIdle.png", 22);
	textureMap[ss_downIdleTex] = pair<string, int>("Assets/Sprites/SilverSoldierForwardIdle.png", 22);
	textureMap[ss_leftIdleTex] = pair<string, int>("Assets/Sprites/SilverSoldierLeftIdle.png", 22);
	textureMap[ss_rightIdleTex] = pair<string, int>("Assets/Sprites/SilverSoldierRightIdle.png", 22);
	textureMap[ss_upAtkTex] = pair<string, int>("Assets/Sprites/SilverSoldierBackSwing.png", 24);
	textureMap[ss_downAtkTex] = pair<string, int>("Assets/Sprites/SilverSoldierForwardSwing.png", 24);
	textureMap[ss_leftAtkTex] = pair<string, int>("Assets/Sprites/SilverSoldierLeftSwing.png", 24);
	textureMap[ss_rightAtkTex] = pair<string, int>("Assets/Sprites/SilverSoldierRightSwing.png", 24);
	textureMap[ss_upHurtTex] = pair<string, int>("Assets/Sprites/SilverSoldierBackRecoil.png", 18);
	textureMap[ss_downHurtTex] = pair<string, int>("Assets/Sprites/SilverSoldierForwardRecoil.png", 18);
	textureMap[ss_leftHurtTex] = pair<string, int>("Assets/Sprites/SilverSoldierLeftRecoil.png", 18);
	textureMap[ss_rightHurtTex] = pair<string, int>("Assets/Sprites/SilverSoldierRightRecoil.png", 18);
	textureMap[ss_upWalkTex] = pair<string, int>("Assets/Sprites/SilverSoldierBackWalk.png", 32);
	textureMap[ss_downWalkTex] = pair<string, int>("Assets/Sprites/SilverSoldierForwardWalk.png", 32);
	textureMap[ss_leftWalkTex] = pair<string, int>("Assets/Sprites/SilverSoldierLeftWalk.png", 32);
	textureMap[ss_rightWalkTex] = pair<string, int>("Assets/Sprites/SilverSoldierRightWalk.png", 32);
	textureMap[ss_upLungeTex] = pair<string, int>("Assets/Sprites/SilverSoldierBackLunge.png", 7);
	textureMap[ss_downLungeTex] = pair<string, int>("Assets/Sprites/SilverSoldierForwardLunge.png", 7);
	textureMap[ss_leftLungeTex] = pair<string, int>("Assets/Sprites/SilverSoldierLeftLunge.png", 7);
	textureMap[ss_rightLungeTex] = pair<string, int>("Assets/Sprites/SilverSoldierRightLunge.png", 7);







	Texture* bs_upRunTex = new Texture();
	Texture* bs_downRunTex = new Texture();
	Texture* bs_leftRunTex = new Texture();
	Texture* bs_rightRunTex = new Texture();
	Texture* bs_upIdleTex = new Texture();
	Texture* bs_downIdleTex = new Texture();
	Texture* bs_leftIdleTex = new Texture();
	Texture* bs_rightIdleTex = new Texture();
	Texture* bs_upAtkTex = new Texture();
	Texture* bs_downAtkTex = new Texture();
	Texture* bs_leftAtkTex = new Texture();
	Texture* bs_rightAtkTex = new Texture();
	Texture* bs_upHurtTex = new Texture();
	Texture* bs_downHurtTex = new Texture();
	Texture* bs_leftHurtTex = new Texture();
	Texture* bs_rightHurtTex = new Texture();
	Texture* bs_upWalkTex = new Texture();
	Texture* bs_downWalkTex = new Texture();
	Texture* bs_leftWalkTex = new Texture();
	Texture* bs_rightWalkTex = new Texture();
	Texture* bs_upLungeTex = new Texture();
	Texture* bs_downLungeTex = new Texture();
	Texture* bs_leftLungeTex = new Texture();
	Texture* bs_rightLungeTex = new Texture();
	textureMap[bs_upRunTex] = pair<string, int>("Assets/Sprites/ShangoBackSprint.png", 16);
	textureMap[bs_downRunTex] = pair<string, int>("Assets/Sprites/ShangoForwardSprint.png", 16);
	textureMap[bs_leftRunTex] = pair<string, int>("Assets/Sprites/ShangoLeftSprint.png", 16);
	textureMap[bs_rightRunTex] = pair<string, int>("Assets/Sprites/ShangoRightSprint.png", 16);
	textureMap[bs_upIdleTex] = pair<string, int>("Assets/Sprites/ShangoBackIdle.png", 22);
	textureMap[bs_downIdleTex] = pair<string, int>("Assets/Sprites/ShangoForwardIdle.png", 22);
	textureMap[bs_leftIdleTex] = pair<string, int>("Assets/Sprites/ShangoLeftIdle.png", 22);
	textureMap[bs_rightIdleTex] = pair<string, int>("Assets/Sprites/ShangoRightIdle.png", 22);
	textureMap[bs_upAtkTex] = pair<string, int>("Assets/Sprites/ShangoBackSwing.png", 13);
	textureMap[bs_downAtkTex] = pair<string, int>("Assets/Sprites/ShangoForwardSwing.png", 13);
	textureMap[bs_leftAtkTex] = pair<string, int>("Assets/Sprites/ShangoLeftSwing.png", 13);
	textureMap[bs_rightAtkTex] = pair<string, int>("Assets/Sprites/ShangoRightSwing.png", 13);
	textureMap[bs_upHurtTex] = pair<string, int>("Assets/Sprites/ShangoBackRecoil.png", 18);
	textureMap[bs_downHurtTex] = pair<string, int>("Assets/Sprites/ShangoForwardRecoil.png", 18);
	textureMap[bs_leftHurtTex] = pair<string, int>("Assets/Sprites/ShangoLeftRecoil.png", 18);
	textureMap[bs_rightHurtTex] = pair<string, int>("Assets/Sprites/ShangoRightRecoil.png", 18);
	textureMap[bs_upWalkTex] = pair<string, int>("Assets/Sprites/BlueSoldierBackWalk.png", 32);
	textureMap[bs_downWalkTex] = pair<string, int>("Assets/Sprites/BlueSoldierForwardWalk.png", 32);
	textureMap[bs_leftWalkTex] = pair<string, int>("Assets/Sprites/BlueSoldierLeftWalk.png", 32);
	textureMap[bs_rightWalkTex] = pair<string, int>("Assets/Sprites/BlueSoldierRightWalk.png", 32);
	textureMap[bs_upLungeTex] = pair<string, int>("Assets/Sprites/BlueSoldierBackLunge.png", 7);
	textureMap[bs_downLungeTex] = pair<string, int>("Assets/Sprites/BlueSoldierForwardLunge.png", 7);
	textureMap[bs_leftLungeTex] = pair<string, int>("Assets/Sprites/BlueSoldierLeftLunge.png", 7);
	textureMap[bs_rightLungeTex] = pair<string, int>("Assets/Sprites/BlueSoldierRightLunge.png", 7);






	Texture* treeTex = new Texture();
	Texture* treeTex1 = new Texture();
	Texture* treeTex2 = new Texture();
	textureMap[treeTex] = pair<string, int>("Assets/Sprites/tree.png", 1);
	textureMap[treeTex1] = pair<string, int>("Assets/Sprites/tree1.png", 1);
	textureMap[treeTex2] = pair<string, int>("Assets/Sprites/tree2.png", 1);



	Texture* rockTex = new Texture();
	Texture* rockTex1 = new Texture();
	Texture* rockTex2 = new Texture();
	textureMap[rockTex] = pair<string, int>("Assets/Sprites/rock_1.png", 1);
	textureMap[rockTex2] = pair<string, int>("Assets/Sprites/rock_2.png", 1);

	Texture* pierTex = new Texture();
	textureMap[pierTex] = pair<string, int>("Assets/Sprites/pier.png", 1);

	Texture* blank = new Texture();
	Texture* border = new Texture();
	textureMap[blank] = pair<string, int>("Assets/Sprites/blank.png", 1);
	textureMap[border] = pair<string, int>("Assets/Sprites/border.png", 1);

	Texture* fire = new Texture();
	Texture* fireUp = new Texture();
	Texture* fireDown = new Texture();
	Texture* fireLeft = new Texture();
	textureMap[fire] = pair<string, int>("Assets/Sprites/FireBallTMP.png", 3);
	textureMap[fireUp] = pair<string, int>("Assets/Sprites/FireBallTMPUp.png", 3);
	textureMap[fireDown] = pair<string, int>("Assets/Sprites/FireBallTMPDown.png", 3);
	textureMap[fireLeft] = pair<string, int>("Assets/Sprites/FireBallTMPLeft.png", 3);

	Texture* firebreatheRight = new Texture();
	Texture* firebreatheUp = new Texture();
	Texture* firebreatheDown = new Texture();
	Texture* firebreatheLeft = new Texture();
	textureMap[firebreatheRight] = pair<string, int>("Assets/Sprites/ShangoRightBreath.png", 14);
	textureMap[firebreatheUp] = pair<string, int>("Assets/Sprites/ShangoBackBreath.png", 14);
	textureMap[firebreatheDown] = pair<string, int>("Assets/Sprites/ShangoForwardBreath.png", 14);
	textureMap[firebreatheLeft] = pair<string, int>("Assets/Sprites/ShangoLeftBreath.png", 14);

	Texture* spinRight = new Texture();
	Texture* spinUp = new Texture();
	Texture* spinDown = new Texture();
	Texture* spinLeft = new Texture();
	textureMap[spinRight] = pair<string, int>("Assets/Sprites/ShangoRightSpin.png", 22);
	textureMap[spinUp] = pair<string, int>("Assets/Sprites/ShangoBackSpin.png", 22);
	textureMap[spinDown] = pair<string, int>("Assets/Sprites/ShangoForwardSpin.png", 22);
	textureMap[spinLeft] = pair<string, int>("Assets/Sprites/ShangoLeftSpin.png", 22);


	Texture* sparkRight = new Texture();
	Texture* sparkUp = new Texture();
	Texture* sparkDown = new Texture();
	Texture* sparkLeft = new Texture();



	//load sprite from a configuration file?
	blank->setFile("Assets/Sprites/blank.png", 1);
	border->setFile("Assets/Sprites/border.png", 1);
	objTexture->setFile("Assets/Sprites/YemojasHouse.png",1);
	Soldier* silverSoldier = new Soldier(4000, 3300, true);
	Soldier* silverSoldier2 = new Soldier(4300, 3300, true);
	Soldier* blueSoldier = new Soldier(5630, 4000, true);
	Soldier* blueSoldier2 = new Soldier(5830, 4000, true);
	Soldier* blueSoldier3 = new Soldier(6030, 4000, true);
	Alex->setHealth(200);

	playerTexture->setFile("Assets/Sprites/ShangoForwardIdle.png",22);
	playerIdleTex->setFile("Assets/Sprites/ShangoForwardIdle.png",22);

	upRunTex->setFile("Assets/Sprites/ShangoBackSprint.png",16);
	downRunTex->setFile("Assets/Sprites/ShangoForwardSprint.png",16);
	leftRunTex->setFile("Assets/Sprites/ShangoLeftSprint.png",16);
	rightRunTex->setFile("Assets/Sprites/ShangoRightSprint.png",16);
	upIdleTex->setFile("Assets/Sprites/ShangoBackIdle.png",22);
	downIdleTex->setFile("Assets/Sprites/ShangoForwardIdle.png",22);
	leftIdleTex->setFile("Assets/Sprites/ShangoLeftIdle.png",22);
	rightIdleTex->setFile("Assets/Sprites/ShangoRightIdle.png",22);
	upAtkTex->setFile("Assets/Sprites/ShangoBackSwing.png", 13);
	downAtkTex->setFile("Assets/Sprites/ShangoForwardSwing.png", 13);
	leftAtkTex->setFile("Assets/Sprites/ShangoLeftSwing.png", 13);
	rightAtkTex->setFile("Assets/Sprites/ShangoRightSwing.png", 13);
	upAtk2Tex->setFile("Assets/Sprites/ShangoBackLunge.png", 7);
	downAtk2Tex->setFile("Assets/Sprites/ShangoForwardLunge.png", 7);
	leftAtk2Tex->setFile("Assets/Sprites/ShangoLeftLunge.png", 7);
	rightAtk2Tex->setFile("Assets/Sprites/ShangoRightLunge.png", 7);
	upHurtTex->setFile("Assets/Sprites/ShangoBackRecoil.png", 18);
	downHurtTex->setFile("Assets/Sprites/ShangoForwardRecoil.png", 18);
	leftHurtTex->setFile("Assets/Sprites/ShangoLeftRecoil.png", 18);
	rightHurtTex->setFile("Assets/Sprites/ShangoRightRecoil.png", 18);


	yemojaTexture->setFile("Assets/Sprites/YemojaForwardIdle.png", 22);
	yemojaIdleTex->setFile("Assets/Sprites/YemojaForwardIdle.png", 22);

	h_upRunTex->setFile("Assets/Sprites/YemojaBackSprint.png", 26);
	h_downRunTex->setFile("Assets/Sprites/YemojaFrontSprint.png", 26);
	h_leftRunTex->setFile("Assets/Sprites/YemojaLeftSprint.png", 26);
	h_rightRunTex->setFile("Assets/Sprites/YemojaRightSprint.png", 26);
	h_upIdleTex->setFile("Assets/Sprites/YemojaBackIdle.png", 22);
	h_downIdleTex->setFile("Assets/Sprites/YemojaForwardIdle.png", 22);
	h_leftIdleTex->setFile("Assets/Sprites/YemojaLeftIdle.png", 22);
	h_rightIdleTex->setFile("Assets/Sprites/YemojaRightIdle.png", 22);

	silverSoldierTexture->setFile("Assets/Sprites/SilverSoldierForwardIdle.png", 22);
	silverSoldierIdleTex->setFile("Assets/Sprites/SilverSoldierForwardIdle.png", 22);
	blueSoldierTexture->setFile("Assets/Sprites/BlueSoldierForwardIdle.png", 22);
	blueSoldierIdleTex->setFile("Assets/Sprites/BlueSoldierForwardIdle.png", 22);

	bs_upRunTex->setFile("Assets/Sprites/BlueSoldierBackSprint.png", 16);
	bs_downRunTex->setFile("Assets/Sprites/BlueSoldierForwardSprint.png", 16);
	bs_leftRunTex->setFile("Assets/Sprites/BlueSoldierLeftSprint.png", 16);
	bs_rightRunTex->setFile("Assets/Sprites/BlueSoldierRightSprint.png", 16);
	bs_upIdleTex->setFile("Assets/Sprites/BlueSoldierBackIdle.png", 22);
	bs_downIdleTex->setFile("Assets/Sprites/BlueSoldierForwardIdle.png", 22);
	bs_leftIdleTex->setFile("Assets/Sprites/BlueSoldierLeftIdle.png", 22);
	bs_rightIdleTex->setFile("Assets/Sprites/BlueSoldierRightIdle.png", 22);
	bs_upAtkTex->setFile("Assets/Sprites/BlueSoldierBackSwing.png", 13);
	bs_downAtkTex->setFile("Assets/Sprites/BlueSoldierForwardSwing.png", 13);
	bs_leftAtkTex->setFile("Assets/Sprites/BlueSoldierLeftSwing.png", 13);
	bs_rightAtkTex->setFile("Assets/Sprites/BlueSoldierRightSwing.png", 13);
	bs_upHurtTex->setFile("Assets/Sprites/BlueSoldierBackRecoil.png", 18);
	bs_downHurtTex->setFile("Assets/Sprites/BlueSoldierForwardRecoil.png", 18);
	bs_leftHurtTex->setFile("Assets/Sprites/BlueSoldierLeftRecoil.png", 18);
	bs_rightHurtTex->setFile("Assets/Sprites/BlueSoldierRightRecoil.png", 18);
	bs_upWalkTex->setFile("Assets/Sprites/BlueSoldierBackWalk.png", 32);
	bs_downWalkTex->setFile("Assets/Sprites/BlueSoldierForwardWalk.png", 32);
	bs_leftWalkTex->setFile("Assets/Sprites/BlueSoldierLeftWalk.png", 32);
	bs_rightWalkTex->setFile("Assets/Sprites/BlueSoldierRightWalk.png", 32);
	bs_upLungeTex->setFile("Assets/Sprites/BlueSoldierBackLunge.png", 7);
	bs_downLungeTex->setFile("Assets/Sprites/BlueSoldierForwardLunge.png", 7);
	bs_leftLungeTex->setFile("Assets/Sprites/BlueSoldierLeftLunge.png", 7);
	bs_rightLungeTex->setFile("Assets/Sprites/BlueSoldierRightLunge.png", 7);

	ss_upRunTex->setFile("Assets/Sprites/SilverSoldierBackSprint.png", 16);
	ss_downRunTex->setFile("Assets/Sprites/SilverSoldierForwardSprint.png", 16);
	ss_leftRunTex->setFile("Assets/Sprites/SilverSoldierLeftSprint.png", 16);
	ss_rightRunTex->setFile("Assets/Sprites/SilverSoldierRightSprint.png", 16);
	ss_upIdleTex->setFile("Assets/Sprites/SilverSoldierBackIdle.png", 22);
	ss_downIdleTex->setFile("Assets/Sprites/SilverSoldierForwardIdle.png", 22);
	ss_leftIdleTex->setFile("Assets/Sprites/SilverSoldierLeftIdle.png", 22);
	ss_rightIdleTex->setFile("Assets/Sprites/SilverSoldierRightIdle.png", 22);
	ss_upAtkTex->setFile("Assets/Sprites/SilverSoldierBackSwing.png", 24);
	ss_downAtkTex->setFile("Assets/Sprites/SilverSoldierForwardSwing.png", 24);
	ss_leftAtkTex->setFile("Assets/Sprites/SilverSoldierLeftSwing.png", 24);
	ss_rightAtkTex->setFile("Assets/Sprites/SilverSoldierRightSwing.png", 24);
	ss_upHurtTex->setFile("Assets/Sprites/SilverSoldierBackRecoil.png", 18);
	ss_downHurtTex->setFile("Assets/Sprites/SilverSoldierForwardRecoil.png", 18);
	ss_leftHurtTex->setFile("Assets/Sprites/SilverSoldierLeftRecoil.png", 18);
	ss_rightHurtTex->setFile("Assets/Sprites/SilverSoldierRightRecoil.png", 18);
	ss_upWalkTex->setFile("Assets/Sprites/SilverSoldierBackWalk.png", 32);
	ss_downWalkTex->setFile("Assets/Sprites/SilverSoldierForwardWalk.png", 32);
	ss_leftWalkTex->setFile("Assets/Sprites/SilverSoldierLeftWalk.png", 32);
	ss_rightWalkTex->setFile("Assets/Sprites/SilverSoldierRightWalk.png", 32);
	ss_upLungeTex->setFile("Assets/Sprites/SilverSoldierBackLunge.png", 7);
	ss_downLungeTex->setFile("Assets/Sprites/SilverSoldierForwardLunge.png", 7);
	ss_leftLungeTex->setFile("Assets/Sprites/SilverSoldierLeftLunge.png", 7);
	ss_rightLungeTex->setFile("Assets/Sprites/SilverSoldierRightLunge.png", 7);

	treeTex->setFile("Assets/Sprites/tree.png", 1);
	treeTex1->setFile("Assets/Sprites/tree1.png", 1);
	treeTex2->setFile("Assets/Sprites/tree2.png", 1);

	rockTex->setFile("Assets/Sprites/rock_1.png", 1);
	rockTex2->setFile("Assets/Sprites/rock_2.png", 1);

	pierTex->setFile("Assets/Sprites/pier.png", 1);

	fire->setFile("Assets/Sprites/FireBallTMP.png", 3);
	fireUp->setFile("Assets/Sprites/FireBallTMPUp.png", 3);
	fireDown->setFile("Assets/Sprites/FireBallTMPDown.png", 3);
	fireLeft->setFile("Assets/Sprites/FireBallTMPLeft.png", 3);

	firebreatheRight->setFile("Assets/Sprites/ShangoRightBreath.png", 14);
	firebreatheUp->setFile("Assets/Sprites/ShangoBackBreath.png", 14);
	firebreatheDown->setFile("Assets/Sprites/ShangoForwardBreath.png", 14);
	firebreatheLeft->setFile("Assets/Sprites/ShangoLeftBreath.png", 14);

	spinRight->setFile("Assets/Sprites/ShangoRightSpin.png", 22);
	spinUp->setFile("Assets/Sprites/ShangoBackSpin.png", 22);
	spinDown->setFile("Assets/Sprites/ShangoForwardSpin.png", 22);
	spinLeft->setFile("Assets/Sprites/ShangoLeftSpin.png", 22);

	for (int i = 0; i < 100; i++) {
	cout << "AT THE THREAD INITIALIZTION CALL!!!****** " << endl;
	}

	/* 
		TRYING TO MULTITHREAD THE SETFILE METHODS ABOVE.
		First, iterate through textureMap and for each texture, assign a new thread to set_file_with_thread(). 
		When all available threads are working, call join() on all threads before continuing. 
		We know all concurrent threads are being utilized when the counter we use while iterating through textureMap has a remainder of 0 when we take the modulo of num_of_threads.

	*/
	//int textureMapCounter = 0;
	//for (const auto& it : textureMap) {
	//	auto temp_tuple = pair<Texture*, pair<string, int>>(it.first, it.second);
	//	cout << "WORKING ON " << temp_tuple.second.first << endl;
	//	// If there are still less than "num_of_threads" in thread_Vec:
	//	if (textureMapCounter % num_of_threads != 0) {

	//		//std::thread temp_thread(set_file_with_thread, std::ref(temp_tuple));
	//		thread_Vec.push_back(std::thread(set_file_with_thread, std::ref(temp_tuple)));
	//	}
	//	else {
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

	Rectangle::texRIGHT->setFile("Assets/Sprites/LeftRecoilSpark.png", 18);
	Rectangle::texLEFT->setFile("Assets/Sprites/RightRecoilSpark.png", 18);
	Rectangle::texUP->setFile("Assets/Sprites/ForwardRecoilSpark.png", 18);
	Rectangle::texDOWN->setFile("Assets/Sprites/BackRecoilSpark.png", 18);

	Rectangle::texAtkRIGHT->setFile("Assets/Sprites/LeftRecoilSpark.png", 18);
	Rectangle::texAtkLEFT->setFile("Assets/Sprites/RightRecoilSpark.png", 18);
	Rectangle::texAtkUP->setFile("Assets/Sprites/ForwardRecoilSpark.png", 18);
	Rectangle::texAtkDOWN->setFile("Assets/Sprites/BackRecoilSpark.png", 18);




	Alex->sprite.setTexture(playerTexture);
	Alex->sprite.setIdleTexture(playerIdleTex);
	Alex->sprite.up = upRunTex;
	Alex->sprite.down = downRunTex;
	Alex->sprite.left = leftRunTex;
	Alex->sprite.right = rightRunTex;

	Alex->sprite.id_up = upIdleTex;
	Alex->sprite.id_left =leftIdleTex;
	Alex->sprite.id_right = rightIdleTex;
	Alex->sprite.id_down = downIdleTex;

	Alex->sprite.atk_up = upAtkTex;
	Alex->sprite.atk_down = downAtkTex;
	Alex->sprite.atk_left = leftAtkTex;
	Alex->sprite.atk_right = rightAtkTex;
	Alex->sprite.atk2_up = upAtk2Tex;
	Alex->sprite.atk2_down = downAtk2Tex;
	Alex->sprite.atk2_left = leftAtk2Tex;
	Alex->sprite.atk2_right = rightAtk2Tex;

	Alex->sprite.spin_up = spinUp;
	Alex->sprite.spin_down = spinDown;
	Alex->sprite.spin_left = spinLeft;
	Alex->sprite.spin_right = spinRight;
	Alex->sprite.breathe_up = firebreatheUp;
	Alex->sprite.breathe_down = firebreatheDown;
	Alex->sprite.breathe_left = firebreatheLeft;
	Alex->sprite.breathe_right = firebreatheRight;

	Alex->sprite.hurt_up = upHurtTex;
	Alex->sprite.hurt_down = downHurtTex;
	Alex->sprite.hurt_left = leftHurtTex;
	Alex->sprite.hurt_right = rightHurtTex;

	Alex->offsetBody(0, 50, 50, 50, 50);
	Alex->setInteractable(true);
	Alex->setName("Shango");
	Alex->setTalkDist(20);

	Alex->setDirection(2);
	//gameplay_functions->add_Attack(Alex->getKey(), Alex->body[0].getX(), Alex->body[0].getY(),true,10);

	gameplay_functions->add_Attack(Alex->getKey(), Alex->body[0].getX(), Alex->body[0].getY(),true,10);


	tBuffer->run();

	Alex->melee = Containers::Attack_table[Alex->getKey()];
	Alex->melee->setDmg(10);
	Alex->melee->setSpeed(5);
	Alex->melee->setBaseDir(4);
	Alex->melee->setCoolDown(37);
	Alex->melee->setPause(-1);
	Alex->melee->setDestroy(false);
	Alex->melee->setKeep(true);
	Alex->melee->setWidth(Alex->body[0].getWidth());
	Alex->melee->setHeight(Alex->body[0].getHeight());


	Attack* rockThrow = new Attack();
	rockThrow->setDmg(5);
	rockThrow->setSpeed(20);
	rockThrow->setDestroy(true);
	rockThrow->setDuration(100);
	rockThrow->setCoolDown(120);
	rockThrow->setPause(13);
	rockThrow->sprite.setTexture(rockTex);
	rockThrow->sprite.up = rockTex;
	rockThrow->sprite.left = rockTex;
	rockThrow->sprite.right = rockTex;
	rockThrow->sprite.down = rockTex;
	rockThrow->setCanCancel(false);
	Alex->addAttackType(rockThrow);

	Attack* fireball = new Attack();
	fireball->setDmg(15);
	fireball->setSpeed(10);
	fireball->setDestroy(true);
	fireball->setDuration(100);
	fireball->setCoolDown(240);
	fireball->setPause(24);
	fireball->sprite.up=fireUp;
	fireball->sprite.left = fireLeft;
	fireball->sprite.right = fire;
	fireball->sprite.down = fireDown;
	fireball->setCanCancel(false);
	Alex->addAttackType(fireball);

	//Alex->melee->sprite.setTexture(blank);
	Alex->melee->sprite.setTexture(border);

	DialogueController::setPlayer(Alex);
	//vector<WorldObj*> recVec;
	Attack* spin = new Attack();
	spin->setDmg(7);
	spin->setSpeed(18);
	spin->setDestroy(false);
	spin->setDuration(7);
	spin->setBaseDir(4);
	spin->setCoolDown(100);
	spin->setPause(18);
	spin->setTurn(true);
	spin->sprite.setTexture(border);
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
	spin2->sprite.setTexture(border);
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
	spin3->sprite.setTexture(border);
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
	spin4->sprite.setTexture(border);
	Alex->addAttackType(spin4);
	spin->setNextAttack(spin2);
	spin2->setNextAttack(spin3);
	spin3->setNextAttack(spin4);

	vector<WorldObj*> vec;
	//vec.push_back(&Alex->melee);

	for (int i = 1; i < 6; i++) {
		if (i > 4) {
			WorldObj* obj = new WorldObj(Vector2f(4100, 3550),500,333);
		
			obj->sprite.setTexture(objTexture);
			obj->setInteractable(true);
			std::string building = "Building ";
			obj->setName(building += std::to_string(i));
			//objs->offsetBody(0, 50, 50, 50, 50);
			obj->offsetBody(0, 25, 50, 25, 25);
			vec.push_back(obj);
			continue;
		}

		WorldObj* objs = new WorldObj(Vector2f(220+50 * i, 300 * (i*2)), 600.0, 400.0);
		objs->sprite.setTexture(objTexture);
		objs->setInteractable(true);
		std::string building="Building ";
		objs->setName(building+= std::to_string(i));
		//objs->offsetBody(0, 50, 50, 50, 50);
		objs->offsetBody(0, 110, 150, 120, 60);
		recVec.push_back(objs);
		
	}

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
	//Texture* barrelTex = new Texture();
	//gameplay_functions->add_texture("barrelTex", 0, 0, 0);
	//tBuffer->run();

	

	//gameplay_functions->add_worldObj("barrel1", 5200, 3900, true);
	//tBuffer->run();


	
	//gameplay_functions->add_soldier("silverSoldier", 4900, 3300, true);

	//tBuffer->run();
	

	//Containers::soldier_table["silverSoldier"];
	//WorldObj* barrel = Containers::worldObj_table["barrel1"];
//    Containers::texture_table["barrelTex"]->setFile("Assets/Sprites/Barrel.png", 1);
	
//	Texture* barrelTex = 
	//barrel->setWidth(75);
	//barrel->setHeight(75);

	//barrel->sprite.setTexture(Containers::texture_table["barrelTex"]);

	

	staticRec->setWidth(150);
	staticRec->setHeight(150);
	staticRec->name = YEMOJA;
	//Hero* staticRec = new Hero(YEMOJA, Vector2f(4600, 3600), 100.0, 100.0);
	///should actually use gameplay_functions->add_hero("Yemoja", 4600, 3600, true)
	/// Containers::hero_table[name]->setWidht(widht)

	silverSoldier->setWidth(150);
	silverSoldier->setHeight(150);
	silverSoldier2->setWidth(150);
	silverSoldier2->setHeight(150);
	blueSoldier->setWidth(150);
	blueSoldier->setHeight(150);
	blueSoldier2->setWidth(150);
	blueSoldier2->setHeight(150);
	blueSoldier3->setWidth(150);
	blueSoldier3->setHeight(150);


	staticRec->sprite.setTexture(yemojaTexture);
	staticRec->sprite.setIdleTexture(yemojaIdleTex);
	staticRec->sprite.up = h_upRunTex;
	staticRec->sprite.down = h_downRunTex;
	staticRec->sprite.left = h_leftRunTex;
	staticRec->sprite.right = h_rightRunTex;
	staticRec->sprite.id_up = h_upIdleTex;
	staticRec->sprite.id_left = h_leftIdleTex;
	staticRec->sprite.id_right = h_rightIdleTex;
	staticRec->sprite.id_down = h_downIdleTex;
	staticRec->sprite.hurt_up = upHurtTex;
	staticRec->sprite.hurt_down = downHurtTex;
	staticRec->sprite.hurt_left = leftHurtTex;
	staticRec->sprite.hurt_right = rightHurtTex;

	blueSoldier->sprite.setTexture(blueSoldierTexture);
	blueSoldier->sprite.setIdleTexture(blueSoldierIdleTex);
	blueSoldier->sprite.up = bs_upRunTex;
	blueSoldier->sprite.down = bs_downRunTex;
	blueSoldier->sprite.left = bs_leftRunTex;
	blueSoldier->sprite.right = bs_rightRunTex;
	
	blueSoldier->sprite.id_up = bs_upIdleTex;
	blueSoldier->sprite.id_left = bs_leftIdleTex;
	blueSoldier->sprite.id_right = bs_rightIdleTex;
	blueSoldier->sprite.id_down = bs_downIdleTex;
	
	blueSoldier->sprite.atk_up = bs_upAtkTex;
	blueSoldier->sprite.atk_down = bs_downAtkTex;
	blueSoldier->sprite.atk_left = bs_leftAtkTex;
	blueSoldier->sprite.atk_right = bs_rightAtkTex;
	
	blueSoldier->sprite.hurt_up = bs_upHurtTex;
	blueSoldier->sprite.hurt_down = bs_downHurtTex;
	blueSoldier->sprite.hurt_left = bs_leftHurtTex;
	blueSoldier->sprite.hurt_right = bs_rightHurtTex;

	blueSoldier2->sprite.setTexture(blueSoldierTexture);
	blueSoldier2->sprite.setIdleTexture(blueSoldierIdleTex);
	blueSoldier2->sprite.up = bs_upRunTex;
	blueSoldier2->sprite.down = bs_downRunTex;
	blueSoldier2->sprite.left = bs_leftRunTex;
	blueSoldier2->sprite.right = bs_rightRunTex;

	blueSoldier2->sprite.id_up = bs_upIdleTex;
	blueSoldier2->sprite.id_left = bs_leftIdleTex;
	blueSoldier2->sprite.id_right = bs_rightIdleTex;
	blueSoldier2->sprite.id_down = bs_downIdleTex;

	blueSoldier2->sprite.atk_up = bs_upAtkTex;
	blueSoldier2->sprite.atk_down = bs_downAtkTex;
	blueSoldier2->sprite.atk_left = bs_leftAtkTex;
	blueSoldier2->sprite.atk_right = bs_rightAtkTex;

	blueSoldier2->sprite.hurt_up = bs_upHurtTex;
	blueSoldier2->sprite.hurt_down = bs_downHurtTex;
	blueSoldier2->sprite.hurt_left = bs_leftHurtTex;
	blueSoldier2->sprite.hurt_right = bs_rightHurtTex;

	blueSoldier3->sprite.setTexture(blueSoldierTexture);
	blueSoldier3->sprite.setIdleTexture(blueSoldierIdleTex);
	blueSoldier3->sprite.up = bs_upRunTex;
	blueSoldier3->sprite.down = bs_downRunTex;
	blueSoldier3->sprite.left = bs_leftRunTex;
	blueSoldier3->sprite.right = bs_rightRunTex;

	blueSoldier3->sprite.id_up = bs_upIdleTex;
	blueSoldier3->sprite.id_left = bs_leftIdleTex;
	blueSoldier3->sprite.id_right = bs_rightIdleTex;
	blueSoldier3->sprite.id_down = bs_downIdleTex;

	blueSoldier3->sprite.atk_up = bs_upAtkTex;
	blueSoldier3->sprite.atk_down = bs_downAtkTex;
	blueSoldier3->sprite.atk_left = bs_leftAtkTex;
	blueSoldier3->sprite.atk_right = bs_rightAtkTex;

	blueSoldier3->sprite.hurt_up = bs_upHurtTex;
	blueSoldier3->sprite.hurt_down = bs_downHurtTex;
	blueSoldier3->sprite.hurt_left = bs_leftHurtTex;
	blueSoldier3->sprite.hurt_right = bs_rightHurtTex;

	silverSoldier->sprite.setTexture(silverSoldierTexture);
	silverSoldier->sprite.setIdleTexture(silverSoldierIdleTex);
	silverSoldier->sprite.up = ss_upRunTex;
	silverSoldier->sprite.down = ss_downRunTex;
	silverSoldier->sprite.left = ss_leftRunTex;
	silverSoldier->sprite.right = ss_rightRunTex;

	silverSoldier->sprite.id_up = ss_upIdleTex;
	silverSoldier->sprite.id_left = ss_leftIdleTex;
	silverSoldier->sprite.id_right = ss_rightIdleTex;
	silverSoldier->sprite.id_down = ss_downIdleTex;

	silverSoldier->sprite.atk_up = ss_upAtkTex;
	silverSoldier->sprite.atk_down = ss_downAtkTex;
	silverSoldier->sprite.atk_left = ss_leftAtkTex;
	silverSoldier->sprite.atk_right = ss_rightAtkTex;

	silverSoldier->sprite.hurt_up = ss_upHurtTex;
	silverSoldier->sprite.hurt_down = ss_downHurtTex;
	silverSoldier->sprite.hurt_left = ss_leftHurtTex;
	silverSoldier->sprite.hurt_right = ss_rightHurtTex;


	silverSoldier->offsetBody(0, 60, 60, 75, 50);
	silverSoldier->setInteractable(true);
	silverSoldier->setName("silverSoldier");
  // silverSoldier->setHealth(50);

	silverSoldier2->sprite.setTexture(silverSoldierTexture);
	silverSoldier2->sprite.setIdleTexture(silverSoldierIdleTex);
	silverSoldier2->sprite.up = ss_upRunTex;
	silverSoldier2->sprite.down = ss_downRunTex;
	silverSoldier2->sprite.left = ss_leftRunTex;
	silverSoldier2->sprite.right = ss_rightRunTex;

	silverSoldier2->sprite.id_up = ss_upIdleTex;
	silverSoldier2->sprite.id_left = ss_leftIdleTex;
	silverSoldier2->sprite.id_right = ss_rightIdleTex;
	silverSoldier2->sprite.id_down = ss_downIdleTex;

	silverSoldier2->sprite.atk_up = ss_upAtkTex;
	silverSoldier2->sprite.atk_down = ss_downAtkTex;
	silverSoldier2->sprite.atk_left = ss_leftAtkTex;
	silverSoldier2->sprite.atk_right = ss_rightAtkTex;

	silverSoldier2->sprite.hurt_up = ss_upHurtTex;
	silverSoldier2->sprite.hurt_down = ss_downHurtTex;
	silverSoldier2->sprite.hurt_left = ss_leftHurtTex;
	silverSoldier2->sprite.hurt_right = ss_rightHurtTex;


	silverSoldier2->offsetBody(0, 60, 60, 75, 50);
	silverSoldier2->setInteractable(true);
	silverSoldier2->setName("silverSoldier");
  // silverSoldier2->setHealth(50);

	blueSoldier->offsetBody(0, 60, 60, 75, 50);
	blueSoldier->setInteractable(true);
	blueSoldier->setName("blueSoldier");

	blueSoldier2->offsetBody(0, 60, 60, 75, 50);
	blueSoldier2->setInteractable(true);
	blueSoldier2->setName("blueSoldier2");

	blueSoldier3->offsetBody(0, 60, 60, 75, 50);
	blueSoldier3->setInteractable(true);
	blueSoldier3->setName("blueSoldier3");

	gameplay_functions->add_Attack(silverSoldier->getKey(), silverSoldier->body[0].getX(), silverSoldier->body[0].getY(), true, 10);
	gameplay_functions->add_Attack(silverSoldier2->getKey(), silverSoldier2->body[0].getX(), silverSoldier2->body[0].getY(), true, 10);
	gameplay_functions->add_Attack(blueSoldier->getKey(), blueSoldier->body[0].getX(), blueSoldier->body[0].getY(), true, 10);
	gameplay_functions->add_Attack(blueSoldier2->getKey(), blueSoldier2->body[0].getX(), blueSoldier2->body[0].getY(), true, 10);
	gameplay_functions->add_Attack(blueSoldier3->getKey(), blueSoldier3->body[0].getX(), blueSoldier3->body[0].getY(), true, 10);
	tBuffer->run();


	silverSoldier->melee = Containers::Attack_table[silverSoldier->getKey()];
	silverSoldier->melee->setDmg(10);
	silverSoldier->melee->setSpeed(5);
	silverSoldier->melee->setBaseDir(4);
	silverSoldier->melee->setCoolDown(100);
	silverSoldier->melee->setPause(-1);
	silverSoldier->melee->setDestroy(false);
	silverSoldier->melee->setKeep(true);
	silverSoldier->melee->setWidth(50);
	silverSoldier->melee->setHeight(50);

	silverSoldier->melee->setStaminaCost(90);
	silverSoldier->setHealth(70);

	silverSoldier->melee->setStaminaCost(120);
	silverSoldier->setMaxStamina(300);
	silverSoldier->setHealth(1000);


	silverSoldier->addAttackType(rockThrow);
	silverSoldier->melee->sprite.setTexture(border);

	silverSoldier2->melee = Containers::Attack_table[silverSoldier2->getKey()];
	silverSoldier2->melee->setDmg(10);
	silverSoldier2->melee->setSpeed(5);
	silverSoldier2->melee->setBaseDir(4);
	silverSoldier2->melee->setCoolDown(100);
	silverSoldier2->melee->setPause(-1);
	silverSoldier2->melee->setDestroy(false);
	silverSoldier2->melee->setKeep(true);
	silverSoldier2->melee->setWidth(50);
	silverSoldier2->melee->setHeight(50);

	silverSoldier2->melee->setStaminaCost(90);
	silverSoldier2->setHealth(50);

	silverSoldier2->melee->setStaminaCost(120);
	silverSoldier2->setHealth(1000);
	silverSoldier2->setMaxStamina(300);


	silverSoldier2->addAttackType(rockThrow);
	silverSoldier2->melee->sprite.setTexture(border);


	blueSoldier->melee = Containers::Attack_table[blueSoldier->getKey()];
	blueSoldier->melee->setDmg(10);
	blueSoldier->melee->setSpeed(1);
	blueSoldier->melee->setBaseDir(4);
	blueSoldier->melee->setCoolDown(100);
	blueSoldier->melee->setPause(-1);
	blueSoldier->melee->setDestroy(false);
	blueSoldier->melee->setKeep(true);
	blueSoldier->melee->setWidth(50);
	blueSoldier->melee->setHeight(50);
	blueSoldier->melee->setStaminaCost(120);
	blueSoldier->setHealth(100);
	blueSoldier->setMaxStamina(300);
	
	blueSoldier->addAttackType(rockThrow);
	blueSoldier->melee->sprite.setTexture(border);

	blueSoldier2->melee = Containers::Attack_table[blueSoldier2->getKey()];
	blueSoldier2->melee->setDmg(10);
	blueSoldier2->melee->setSpeed(1);
	blueSoldier2->melee->setBaseDir(4);
	blueSoldier2->melee->setCoolDown(100);
	blueSoldier2->melee->setPause(-1);
	blueSoldier2->melee->setDestroy(false);
	blueSoldier2->melee->setKeep(true);
	blueSoldier2->melee->setWidth(50);
	blueSoldier2->melee->setHeight(50);
	blueSoldier2->melee->setStaminaCost(120);
	blueSoldier2->setHealth(100);
	blueSoldier2->setMaxStamina(300);

	blueSoldier2->addAttackType(rockThrow);
	blueSoldier2->melee->sprite.setTexture(border);

	blueSoldier3->melee = Containers::Attack_table[blueSoldier3->getKey()];
	blueSoldier3->melee->setDmg(10);
	blueSoldier3->melee->setSpeed(1);
	blueSoldier3->melee->setBaseDir(4);
	blueSoldier3->melee->setCoolDown(100);
	blueSoldier3->melee->setPause(-1);
	blueSoldier3->melee->setDestroy(false);
	blueSoldier3->melee->setKeep(true);
	blueSoldier3->melee->setWidth(50);
	blueSoldier3->melee->setHeight(50);
	blueSoldier3->melee->setStaminaCost(120);
	blueSoldier3->setHealth(100);
	blueSoldier3->setMaxStamina(300);

	blueSoldier3->addAttackType(rockThrow);
	blueSoldier3->melee->sprite.setTexture(border);
	//silverSoldier->addAttackType(spin);

	//combatControl->addtoTargets(Alex);
	//combatControl->addtoTargets(silverSoldier);
	//combatControl->addtoTargets(silverSoldier2);

	//VisibilityGraph graph;
	ai->graph.vertices = vertices;
	ai->graph.obstacles = edges;
	for (Vector2f vert : ai->graph.vertices) {
		//////std:://cout << "X: " << vert.getXloc() << " Y: " << vert.getYloc() << std::endl;
	}
	for (auto edge : ai->graph.obstacles) {
		//////std:://cout << "EDGE from " << edge.first.getXloc() << "," << edge.first.getYloc() << " to " << edge.second.getXloc() << "," << edge.second.getYloc() << std::endl;
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
	staticRec->setHealth(35);
	*oya = *staticRec;
	//oya->setSpeed(5);
	oya->setName("Oya");
	oya->name = OYA;
	oya->offsetBody(0, 35, 35, 65, 15);
	staticRec->offsetBody(0, 35, 35, 65, 15);
	oya->shiftY(300);
	oya->setHealth(50);

	ActionConfig::import_config(gameplay_functions, tBuffer, staticRec,
		oya);

	Planner* YemojaPlanner = new Planner(staticRec);
	AiController->hero_planners[YEMOJA] = YemojaPlanner;
	Action* test_train = new Action(staticRec, oya, staticRec, 10, 1, "train", "execute_train");
	AiController->hero_planners[YEMOJA]->set_current_action(test_train);


	/*
	WorldObj* tree = new WorldObj(Vector2f(4000, 2600), 800, 500);
	tree->sprite.setTexture(treeTex);
	tree->offsetBody(0, 275, 375, 375, 75);
	WorldObj* tree1 = new WorldObj(Vector2f(3300, 4600), 700, 600);
	tree1->sprite.setTexture(treeTex1);
	tree1->offsetBody(0, 275, 375, 375, 75);
	WorldObj* tree2 = new WorldObj(Vector2f(4700, 4500), 700, 600);
	tree2->sprite.setTexture(treeTex2);
	tree2->offsetBody(0, 275, 375, 375, 75);
	//WorldObj* tree1 = new WorldObj(Vector2f())
	//staticRec->goal.setXloc(500);
	//staticRec->goal.setYloc(1200);
	*/
	recVec.push_back(staticRec);
	//recVec.push_back(silverSoldier);
	recVec.push_back(blueSoldier);
	recVec.push_back(blueSoldier2);
	recVec.push_back(blueSoldier3);
	//recVec.push_back(silverSoldier2);
	//recVec.push_back(oya);
	//recVec.push_back(barrel);
	//recVec.push_back(tree);;
	//recVec.push_back(tree1);
	//recVec.push_back(tree2);
	//recVec.push_back(vec[0]);
	
	//recVec.push_back(vec[1]);
	//recVec.push_back(myRec1); recVec.push_back(myRec2);

	//pauses the program for viewing
	//system("PAUSE");

	//demonstration of a meory leak
	//while (true) {
	//	void* a = malloc(64);
	//	delete a;
	//}
	
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
		//////std:://cout << "X: " << vert.getXloc() << " Y: " << vert.getYloc() << std::endl;
	}
	for (auto edge : ai->graph.obstacles) {
		//////std:://cout << "EDGE from " << edge.first.getXloc() << "," << edge.first.getYloc() << " to " << edge.second.getXloc() << "," << edge.second.getYloc() << std::endl;
	}

	ai->graph._print();


	//ai->astar_search(staticRec);

	//vector<Vector2f> path = ai->get_path();


	//for (Vector2f next : path) {
	//	////std:://cout << "X: " << next.getXloc() << " Y: " << next.getYloc() << std::endl;
	//}

	//std::unordered_map<std::string, Manager*> manager_table;

	//manager_table["DumM"] = DumM;

	//Alex->WorldObj::setWidth(100);
	//Alex->WorldObj::setHeight(100);
	//Alex->setX(10);
	//Alex->setY(10);
	ai->astar_search(staticRec);
   // gameplay_functions->get_path(staticRec); //Generate the waypoints to the destination
	staticRec->setMode(WANDER);

	ActionPool* poolAct = new ActionPool(Alex);
	Alex->actionPool_map[1] = poolAct;
	Action mic = Action();
	//mic.preconds["affAbove"] = 50;
	//mic.postconds["aff"] = 5;
	Action mac = Action();
	//mac.preconds["affAbove"] = 55;
//	mac.postconds["aff"] = 5;
	mac.setDoer(Alex);
	mac.setReceiver(staticRec);
	poolAct->micro.push_back(&mic);
	poolAct->macro.push_back(&mac);
	poolAct->updateMiddle();
	vector<Action> test = poolAct->getActions(staticRec, *poolAct->macro.back());

	for (int i = 0; i < test.size(); i++) {
		int t = test[i].exeAction();
	}
	poolAct->macro.back()->exeAction();

	Vector2f silverSoldierInitialLoc = silverSoldier->getLoc();
	Vector2f silverSoldier2InitialLoc = silverSoldier2->getLoc();
	silverSoldier->setEvade(false);
	silverSoldier2->setEvade(false);
	bool OSAtkMode = true;
	short M = GetKeyState('M') >> 15;
	Party* party = new Party();
	//party->addToParty(Alex, true);
	//party->addToParty(staticRec, true);
	//party->addToParty(oya, true);
	Party* party2 = new Party();
	party2->addToParty(silverSoldier, false);
	Party* party3 = new Party();

	party3->addToParty(silverSoldier2, true);

	//Village* vPlayer = new Village();
	//Village* v1 = new Village();
	//Village* v2 = new Village();
	//vPlayer->addToParties(party);

	party2->addToParty(silverSoldier2, false);

	Party* party4= new Party();
	Village* v1 = new Village();
	Village* v2 = new Village();
	Village* v3 = new Village();
	Village* v4 = new Village();

	v1->addToParties(party2);
	v2->addToParties(party3);
	v3->addToParties(party);
	Alliance* a1 = new Alliance(v1);
	//a1->addToAlliance(vPlayer);
	Alliance* a2 = new Alliance(v2);
	War* war = new War();
	war->setWarParties(v1,v2);
	party4->addToParty(blueSoldier, true);
	party4->addToParty(blueSoldier2, false);
	party4->addToParty(blueSoldier3, false);
	party4->updateFollowers();
	v4->addToParties(party4);
	War* war2 = new War();
	war2->setWarParties(v3, v4);

	//party->addToParty(silverSoldier, false);
	
	party->addToParty(Alex, true);
		
	party->addToParty(oya, false);
	
	party->addToParty(staticRec, false);
	
	party->updateFollowers();
	Alliance::updateEnemies();

	partyM->addToPartyList(party);
	partyM->addToPartyList(party2);
	partyM->addToPartyList(party3);
	partyM->addToPartyList(party4);

	vector<WorldObj*> enemyVec;
	//osi::GameWindow::init();
	LOG("PAST WINDOW INIT ***********************");
	clock_t start_tick, current_ticks, delta_ticks;
	clock_t fps = 0;
	int fs = 120;
int wait_time = fs * 3; //always wait 3 seconds	
	int count = 0;
	int state = 0;
	bool start = true;

	while (osi::GameWindow::isRunning()) {
		if (start) {
			gameplay_functions->play_sound("Play");
			//gameplay_functions->play_sound("Walk");
			//gameplay_functions->pause_unpause("Pause", "walk_loop.wav");
			start = !start;
		}
		start_tick = clock();
		_QuadTree->clear();
		Alex->updateCD();
		silverSoldier->updateCD();
		silverSoldier2->updateCD();
		blueSoldier->updateCD();
		blueSoldier2->updateCD();
		blueSoldier3->updateCD();
		for (int i = 0; i < recVec.size(); i++) {
			_QuadTree->Insert(recVec[i]);	//insert all obj into tree
	
		}
		state = DialogueController::getState();

		std::cout << "X: " << Alex->getX() << " Y: " << Alex->getY() << std::endl;

	if (Alex->getX() > 5285.83 && Alex->getX() < 7079.86) { //Ogun Desert
		if (Alex->getY() < 3523.33) {
			if(current_region == *Desert)
			next_region = *Ogun;
			
		}
		else {
			if (current_region == *Ogun) {
			next_region = *Desert;
			}
		}
	}
	if (Alex->getX() > 10847.5 && Alex->getX() < 12395.5) {
		if (Alex->getY() < 14441) {
			if(current_region == *Jungle)
			next_region = *Mountain;
		}
		else {
			if (current_region == *Mountain) {
			next_region = *Jungle;
			}
		}
	}
	if (Alex->getX() > 13091 && Alex->getX() < 13825.9) {
		if (Alex->getY() < 5132.23) {
			
			if (current_region == *Mountain) {
				next_region = *Ogun;
			}
		}
		else {
			if (current_region == *Ogun)
				next_region = *Mountain;
		}
	}
	if (Alex->getX() > 3479.67 && Alex->getX() < 9446.06) {
		if (Alex->getY() < 15980.7) {
			if (current_region == *Jungle)
				next_region = *Desert;
		}
		else {
			if (current_region == *Desert) {
				next_region = *Jungle;
			}
		}
	}
	if (!(current_region == next_region)) {
		switch_music = true;
	}
	
	if (switch_music) {
		if (in_village) {
			gameplay_functions->change_song("Change", current_region.getRTheme(), next_region.getVTheme());
			switch_music = false;

		}
		else {
			gameplay_functions->change_song("Change", current_region.getRTheme(), next_region.getRTheme());
			//iController->current_region = current_region;
			current_region = next_region;

			//current_region->getRTheme(), next_region->getRTheme()
			switch_music = false;
		}

	}



		//std::cout << "X: " << Alex->getX() << " Y: " << Alex->getY() << std::endl;
		//std::cout << "CR: " << current_region.name << " NR: " << next_region.name<< std::endl;
		//std::cout << "CA: " << current_region.getRTheme() << " NA: " << next_region.getRTheme() << std::endl;

	/*	if (staticRec->destination != Vector2f(0, 0)) { //Hero has a destination
			if (staticRec->waypoint != Vector2f(0,0) && state == 0) { //Hero has a waypoint to the desination, and not in dialog
				gameplay_functions->move_toward(staticRec); //Take a step towards the current waypoint//cout
			//	////std:://cout << "Request a step" << std::endl;
			}
			else if (state == 0)                //Hero needs waypoints to destination, and not in dialog
			{
				gameplay_functions->get_path(staticRec); //Generate waypoints to destination
			}
		}

		else if (staticRec->getMode() != WAIT) //Hero has no destination, and not in wait mode.
		{
			int r = rand() % 4;
			ai->start = staticRec->getLoc();
			//////std:://cout << "at " << ai->start.getXloc() << "," << ai->start.getYloc() << std::endl;
			//////std:://cout << "picked " << r << std::endl;
			switch (r) {
			case 0:
				
				staticRec->destination = Vector2f(5000.00, 4100.00);
				break;
			case 1:
				staticRec->destination = Vector2f(4600.00, 3600.0);
				break;
			case 2:
				staticRec->destination = Vector2f(4500.00, 4000.0);
				break;
			case 3:
				staticRec->destination = Vector2f(5650.00, 3700.00);
				break;
			}
			//Generate the destination
		}
		else   //Hero has no destination and is waiting to generate one
		{
			count++;
			if (count >= wait_time) {
				count = 0;
				staticRec->setMode(WANDER);
			}
		}*/
		combatControl->checkParties();
		combatControl->follow(oya, state);
		//combatControl->follow(silverSoldier, state);
		//combatControl->follow(staticRec, state);
		combatControl->follow(silverSoldier, state);
		combatControl->follow(silverSoldier2, state);
		combatControl->fight(silverSoldier, state);
		combatControl->fight(silverSoldier2, state);


		partyM->updateSoliderStatus();

		combatControl->fight(blueSoldier, state);




		//combatControl->follow(blueSoldier, state);
		//combatControl->follow(blueSoldier2, state);
		//combatControl->follow(blueSoldier3, state);
		//combatControl->fight(blueSoldier, state);
		combatControl->fight(blueSoldier2, state);
		combatControl->fight(blueSoldier3, state);

		partyM->updateSoliderStatus();

		/*
		////cout << "Alex's position is " << Alex->getLoc().getXloc() << ", " << Alex->getLoc().getYloc() << endl;
		////cout << "OS's position is " << silverSoldier->getLoc().getXloc() << ", " << silverSoldier->getLoc().getYloc() << endl;
		////cout << "OS's DESTINATION IS: " << silverSoldier->destination.getXloc() << ", " << silverSoldier->destination.getYloc() << endl;

		/* DEFINE COMBAT MOVEMENT AI HERE 
		   At the start of each frame, we want to check for a given npc, whether there is hostile enemy on the map.
		   Then, set the enemy and set the waypoint and destination to be the enemy's location. Since we do not have access
		   to skills and cooldowns and what not,
		   * WHEN NPC REACHES DESTINATION, destination is being automatically set to (0,0)!!! */
		//attack mode
		/*
		enemyVec.clear();
		enemyVec.push_back(Alex);
		if (enemyVec.empty()) silverSoldier->setEvade(true);
		for (auto it : enemyVec) {
			//if discovered Alex, set silverSoldier combat mode to 0(attack).
			if (silverSoldier->getCurrentEnemy() != nullptr) break;
			if (it == Alex) {
				////cout << "*************************************FOUND ENEMY****************************************" << endl;
				//silverSoldier->setMode(0);
				OSAtkMode = true;
				silverSoldier->setCurrentEnemy(it);
				break;
			}
		}

		if (silverSoldier->getCool()) {
			silverSoldier->setEvade(false);
		} else if (silverSoldier->destination == silverSoldier->getLoc() || silverSoldier->destination==Vector2f(0,0)) {
			silverSoldier->setEvade(true);
			//silverSoldier->waypoint = Vector2f(-1, -1);
			float x = rand() % 300 + 100;
			int x2 = rand() % 2;
			float y = rand() % 300 + 100;
			int y2 = rand() % 2;
			if (x2 == 0)x = -x;
			if (y2 == 0)y = -y;
			silverSoldier->destination = Vector2f(silverSoldier->getCurrentEnemy()->getX()+x, silverSoldier->getCurrentEnemy()->getY()+y);
			silverSoldier->waypoint = Vector2f(silverSoldier->getCurrentEnemy()->getX() + x, silverSoldier->getCurrentEnemy()->getY() + y);
		}

		//if OS has an enemy, move to the enemy
		if (silverSoldier->getCurrentEnemy() != nullptr && !silverSoldier->getEvade() ){//&& silverSoldier->destination != Vector2f(0,0)) {
			////cout << "*************************************************MOVING TO ENEMY******************************************" << endl;
			silverSoldier->waypoint = Vector2f(silverSoldier->getCurrentEnemy()->getX() + (silverSoldier->getCurrentEnemy()->getWidth() / 4), silverSoldier->getCurrentEnemy()->getY() + (silverSoldier->getCurrentEnemy()->getHeight()/4));
			silverSoldier->destination = Vector2f(silverSoldier->getCurrentEnemy()->getX() + (silverSoldier->getCurrentEnemy()->getWidth() / 4), silverSoldier->getCurrentEnemy()->getY() + (silverSoldier->getCurrentEnemy()->getHeight()/4));

				//enemy is facing up
			if (silverSoldier->getCurrentEnemy()->getDirection() == 8) {

				silverSoldier->waypoint.shiftYloc(-80);
				silverSoldier->destination.shiftYloc(-80);
				silverSoldier->waypoint.shiftXloc(-30);
				silverSoldier->destination.shiftXloc(-30);

				//enemy is facing right
			}
			else if (silverSoldier->getCurrentEnemy()->getDirection() == 6) {

				silverSoldier->waypoint.shiftXloc(30);
				silverSoldier->destination.shiftXloc(30);
				silverSoldier->waypoint.shiftYloc(-30);
				silverSoldier->destination.shiftYloc(-30);
			}
				//enemy is facing left
			else if (silverSoldier->getCurrentEnemy()->getDirection() == 4) {
				silverSoldier->waypoint.shiftXloc(-80);
				silverSoldier->destination.shiftXloc(-80);
				silverSoldier->waypoint.shiftYloc(-30);
				silverSoldier->destination.shiftYloc(-30);
			}
				//enemy is facing down
			else if (silverSoldier->getCurrentEnemy()->getDirection() == 2) {
				silverSoldier->waypoint.shiftYloc(30);
				silverSoldier->destination.shiftYloc(30);
				silverSoldier->waypoint.shiftXloc(-30);
				silverSoldier->destination.shiftXloc(-30);
			}

			//gameplay_functions->move_toward(silverSoldier);

			//npc is at enemy destination, attack.
			if (silverSoldier->destination == silverSoldier->getLoc()) {
				silverSoldier->face(silverSoldier->getCurrentEnemy());
				////cout << "COOL DOWN FOR ATTACK IS " << silverSoldier->getCool() << endl;
				if (silverSoldier->getCool()) {
					////std:://cout << "Pressed F" << std::endl;
					//gameplay_functions->special(silverSoldier, 0);
					silverSoldier->meleeAttack();
					gameplay_functions->melee(silverSoldier);
				}
				

			}
		}

		////evade mode
		if (silverSoldier->getCurrentEnemy() != nullptr && silverSoldier->getEvade() ){//&& silverSoldier->destination != Vector2f(0, 0)) {
			//if OS is in evade mode, use the getEvadeRange method to find the waypoint and set it to destination
			if (silverSoldier->destination == Vector2f(-1, -1)) {
				////cout << "****INSIDE THE EVADE MODE SETTER*****" << endl;
				//silverSoldier->waypoint = silverSoldier->getEvadeRange(silverSoldier->getCurrentEnemy());
				silverSoldier->destination = silverSoldier->getEvadeRange(silverSoldier->getCurrentEnemy());
				////cout << "shango waypoint is " << silverSoldier->waypoint.getXloc() << silverSoldier->waypoint.getYloc() << endl;
			}
			//if reached destination, strafe left or right
			if (silverSoldier->getLoc() == silverSoldier->destination) {
				////cout << "******* INSIDE THE EVADE MODE STRAFE *******" << endl;
				//silverSoldier->waypoint = silverSoldier->getStrafeLocation(silverSoldier->getCurrentEnemy());
				silverSoldier->destination = silverSoldier->getEvadeRange(silverSoldier->getCurrentEnemy());
				////cout << "silverSoldier destination inside strafe function is " << silverSoldier->waypoint.getXloc() << ", " << silverSoldier->waypoint.getYloc() << endl;
			}
			/*if (silverSoldier->waypoint != Vector2f(0, 0) && state == 0) { //Hero has a waypoint to the desination, and not in dialog
				gameplay_functions->move_toward(silverSoldier); //Take a step towards the current waypoint
															  //	////std:://cout << "Request a step" << std::endl;
			}
			else if (state == 0)                //Hero needs waypoints to destination, and not in dialog
			{
				gameplay_functions->get_path(silverSoldier); //Generate waypoints to destination
			}
			//gameplay_functions->move_toward(silverSoldier);
		}
	//	ai->graph.insert(silverSoldier->destination);
		//ai->graph.insert(silverSoldier->getLoc());
		if (silverSoldier->destination != Vector2f(0, 0)) { //Hero has a destination
			if (silverSoldier->waypoint != Vector2f(0, 0) && state == 0) { //Hero has a waypoint to the desination, and not in dialog
				gameplay_functions->move_toward(silverSoldier); //Take a step towards the current waypoint
															//	////std:://cout << "Request a step" << std::endl;
			}
			else if (state == 0)                //Hero needs waypoints to destination, and not in dialog
			{
				gameplay_functions->get_path(silverSoldier); //Generate waypoints to destination
			}
		}
		else {

		}
		combatControl->follow(oya, state);
		//toggle between evade and attack mode
		//if (M) {
		//	if (OSAtkMode) {
		//		OSAtkMode = false;
		//		silverSoldier->waypoint = Vector2f(-1, -1);
		//		silverSoldier->destination = Vector2f(-1, -1);
		//	}
		//	else {
		//		OSAtkMode = true;
		//	}
		//}

	
	*/


		
		//ai->plan_step(staticRec);
		//clock 

		/*float diffX = staticRec->getX() - staticRec->goal.getXloc();

		float diffY = staticRec->getY() - staticRec->goal.getYloc();
		float slope = abs(diffY / diffX);

		float diagSpeed = sqrt(staticRec->getSpeed()*staticRec->getSpeed() / (slope + 1));

		staticRec->setDiagXSpeed(diagSpeed);
		staticRec->setDiagYSpeed((slope*diagSpeed));


		X: 1520 Y: 970
		X: 1520 Y: 1230
		X: 1450 Y: 1050
		X: 1520 Y: 970
		X: 1520 Y: 1230
		X: 1450 Y: 1050

		if (abs(diffX) < 6) diffX = 0;
		if (abs(diffY) < 6) diffY = 0;
		bool left = false;
		bool up = false;
		bool down = false;
		bool right = false;

		//gameplay_functions->move_toward(staticRec);

		if (diffX < 0) right = true;
		if (diffX > 0) left = true;
		if (diffY < 0) down = true;
		if (diffY > 0) up = true;
		if (up) {
			gameplay_functions->move_toward(staticRec);
		//	if (right) gameplay_functions->move_up_right(staticRec);
		//	else if (left) gameplay_functions->move_up_left(staticRec);
			//else gameplay_functions->move_up(staticRec);
		}
		else if (down) {
			gameplay_functions->move_toward(staticRec);
			//if (right) gameplay_functions->move_down_right(staticRec);
			//else if (left) gameplay_functions->move_down_left(staticRec);
			//else gameplay_functions->move_down(staticRec);
		}
		else if (right) {
			gameplay_functions->move_toward(staticRec);
		//	gameplay_functions->move_right(staticRec);
		}
		else if (left) {
			gameplay_functions->move_toward(staticRec);
			//gameplay_functions->move_left(staticRec);
		}
		else {
			gameplay_functions->stop(staticRec);
		}*/
		//iController->InputCheck();

		//Alex->WorldObj::drawObj(0,0);
		//for (int i = 0; i < recVec.size(); i++) {
		//	recVec[i]->drawObj(0,0);
		//}
		//Alex->WorldObj::animateObj();
		////Alex->WorldObj::shiftX(.5);
		//osi::GameWindow::refresh();
		//draw
		if (state == 0) {
			//LOG("ERROR AFTER PRESSING Q TO QUIT THE DIALOGUE GUI");
			gameplay_functions->draw_frame(Alex);
			//gameplay_functions->drawHUD(Alex);
			
		}
		else if (state > 0) {
			gameplay_functions->drawDiaGui(Alex);
			gameplay_functions->stop(staticRec);
		}
		//convoGui->drawGui();

		//gameplay_functions->draw_frame(convoGui);
		//run task buffer
		iController->InputCheck();
		//temp_action->execute();

		tBuffer->run();
		//	////cout << tBuffer->queue_buffer.size() << endl;
		//tBuffer->empty();

		/////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////
		for (auto iter : staticRec->rel) {
			Relationship* my_rel = iter.second;
			int with_hero = iter.first;

			if (my_rel->isChanged()) {
				//reevaluate goals for with_hero
				AiController->reevaluate_state(YEMOJA, with_hero);
				my_rel->setChanged(false);
			}
		}
		//getting here-------------------------------------------------------------------------***********
	//	AiController->execute();

		if ((1000 / fs) > (clock() - start_tick)) { //delta_ticks) {www
			Sleep((1000 / fs) - (clock() - start_tick));
		}
		delta_ticks = clock() - start_tick; //the time, in ms, that took to render the scene
		if (delta_ticks > 0)
			fps = CLOCKS_PER_SEC / delta_ticks;
		if (DialogueController::getState() == 0) {
			//cout << "FPS: " << fps << endl;
		}

		frame_count++;
	}
	osi::GameWindow::terminate();
}

void ALESSIO_TEST() {
	
}

void ALEX_LOOP(QuadTree* _QuadTree) {
	//LOG("Hello world!");

	Player* Alex = new Player(SHANGO,Vector2f(1000.0, 600.0), 100.0, 100.0);	//init player
	Texture* playerTexture = new Texture();
	Texture* objTexture = new Texture();
	Texture* uptex = new Texture();
	Texture* downtex = new Texture();
	Texture* lefttex = new Texture();
	Texture* righttex = new Texture();


	objTexture->setFile("YemojasHouse.jpg",1);
	playerTexture->setFile("phi.png",1);

	//uptex->setFile("Shango")

	Alex->sprite.setTexture(playerTexture);
	Alex->sprite.up = uptex;
	Alex->sprite.down = downtex;
	Alex->sprite.left = lefttex;
	Alex->sprite.right = righttex;
	Alex->offsetBody(0, 50, 50, 50, 50);
	vector<WorldObj*> recVec;	

	for (int i = 1; i < 5; i++) {
		WorldObj* objs = new WorldObj(Vector2f(100 * i , 100 * i ), 200.0, 200.0);
		objs->sprite.setTexture(objTexture);
		//objs->offsetBody(0, 50, 50, 50, 50);
		//objs->offsetBody(0, 70, 70, 70, 70);
		recVec.push_back(objs);
	}
	WorldObj* staticRec = new WorldObj(Vector2f(1800, 1350), 100.0, 100.0);
	staticRec->sprite.setTexture(playerTexture);
	recVec.push_back(staticRec);

	//recVec.push_back(myRec1); recVec.push_back(myRec2);

	//pauses the program for viewing
	//system("PAUSE");

	//demonstration of a meory leak
	//while (true) {
	//	void* a = malloc(64);
	//	delete a;
	//}

	//psuedo Gameloop
	MessageLog* mLog = new MessageLog();
	TaskBuffer* tBuffer = new TaskBuffer(mLog);
	ChildrenOfOsi* gameplay_functions = new ChildrenOfOsi(mLog, tBuffer);
	//need this for map editor
	RenderManager* RenM = new RenderManager(mLog, tBuffer, _QuadTree, gameplay_functions);

	AIController* ai = new AIController();
	Input* iController = new Input(gameplay_functions, Alex, RenM->renderHelper, tBuffer, &recVec, ai);
	//create Managers and add to Manager table

	DummyController* DumM = new DummyController(mLog, tBuffer);
	PhysicsManager* PhysM = new PhysicsManager(mLog, tBuffer, _QuadTree);
	
	memManager* memM = new memManager(mLog, tBuffer);
	TestManager* TestM = new TestManager(mLog, tBuffer);

	//the order defines what order the managers the tasks will be sent to
	DumM->register_manager();
	PhysM->register_manager();
	memM->register_manager();
	RenM->register_manager();
	TestM->register_manager();


	//std::unordered_map<std::string, Manager*> manager_table;

	//manager_table["DumM"] = DumM;

	//Alex->WorldObj::setWidth(100);
	//Alex->WorldObj::setHeight(100);
	//Alex->setX(10);
	//Alex->setY(10);

	//osi::GameWindow::init();
	LOG("PAST WINDOW INIT ***********************");
	clock_t start_tick, current_ticks, delta_ticks;
	clock_t fps = 0;
	int fs = 60;
	while (osi::GameWindow::isRunning()) {
		start_tick = clock();
		_QuadTree->clear();
		for (int i = 0; i < recVec.size(); i++) {
			_QuadTree->Insert(recVec[i]);	//insert all obj into tree
		}
		//clock 
		iController->InputCheck();
		//Alex->WorldObj::drawObj(0,0);
		//for (int i = 0; i < recVec.size(); i++) {
		//	recVec[i]->drawObj(0,0);
		//}
		//Alex->WorldObj::animateObj();
		////Alex->WorldObj::shiftX(.5);
		//osi::GameWindow::refresh();
		//draw
		//gameplay_functions->draw_frame(Alex);
		//run task buffer
		//iController->InputCheck();
		tBuffer->run();
	//	////cout << tBuffer->queue_buffer.size() << endl;
		//tBuffer->empty();
	
		
		if ((1000/fs) > (clock() - start_tick)){ //delta_ticks) {www
			Sleep((1000/fs) - (clock() - start_tick));
		}
		delta_ticks = clock() - start_tick; //the time, in ms, that took to render the scene
		if (delta_ticks > 0)
		fps = CLOCKS_PER_SEC / delta_ticks;
		////cout << "FPS: "<<fps << endl;
	}
	osi::GameWindow::terminate();
}


void ERONS_LOOP(QuadTree* _QuadTree) {
	/////////////////////////////////////////////////////////////////
	//ERON'S LOOP NO TOUCHY    **** Justin touched it, oops ****  ****Ian did too. Sue me****
	/////////////////////////////////////////////////////////////////
	LOG("Hello world!");

	//pauses the program for viewing
	system("PAUSE");

	//Player* Alex = new Player(SHANGO, Vector2f(4900.0, 3700.0), 40.0, 40.0);	//init player
	Player* Alex = new Player(SHANGO, Vector2f(4900.0, 3700.0), 150.0, 150.0);	//init player

																				//////cout << "Alex's width and height is " << Alex->getWidth() << ", " << Alex->getHeight() << endl;

	vector<WorldObj*> recVec;
	vector<WorldObj*>* recVec_ptr = &recVec;

	//psuedo Gameloop
	MessageLog* mLog = new MessageLog();
	TaskBuffer* tBuffer = new TaskBuffer(mLog);

	//need this here for map editor
	ChildrenOfOsi* gameplay_functions = new ChildrenOfOsi(mLog, tBuffer);
	RenderManager* RenM = new RenderManager(mLog, tBuffer, _QuadTree, gameplay_functions);

	
	
	//create Managers and add to Manager table

	DummyController* DumM = new DummyController(mLog, tBuffer);
	PhysicsManager* PhysM = new PhysicsManager(mLog, tBuffer, _QuadTree);

	memManager* memM = new memManager(mLog, tBuffer);
	TestManager* TestM = new TestManager(mLog, tBuffer);
	AudioManager* AudM = new AudioManager(mLog, tBuffer);
	AIHelper* ai = new AIHelper();
	AIManager* AIM = new AIManager(mLog, tBuffer, ai);

	AIController* AiController = new AIController();
	ActionHelper::ai = AiController;
	ActionHelper::gameplay_func = gameplay_functions;

	CombatController* combatControl = new CombatController(gameplay_functions);
	Input* iController = new Input(gameplay_functions, Alex, RenM->renderHelper, tBuffer, recVec_ptr, AiController);
	//the order defines what order the managers the tasks will be sent to
	DumM->register_manager();
	PhysM->register_manager();
	memM->register_manager();
	RenM->register_manager();
	AudM->register_manager();
	//TestM->register_manager();
	AIM->register_manager();

	ObjConfig::import_config(recVec_ptr, gameplay_functions, tBuffer);

	Texture* objTexture = new Texture();

	Texture* playerTexture = new Texture();
	Texture* playerIdleTex = new Texture();

	Texture* upRunTex = new Texture();
	Texture* downRunTex = new Texture();
	Texture* leftRunTex = new Texture();
	Texture* rightRunTex = new Texture();
	Texture* upIdleTex = new Texture();
	Texture* downIdleTex = new Texture();
	Texture* leftIdleTex = new Texture();
	Texture* rightIdleTex = new Texture();
	Texture* upAtkTex = new Texture();
	Texture* downAtkTex = new Texture();
	Texture* leftAtkTex = new Texture();
	Texture* rightAtkTex = new Texture();
	Texture* upHurtTex = new Texture();
	Texture* downHurtTex = new Texture();
	Texture* leftHurtTex = new Texture();
	Texture* rightHurtTex = new Texture();

	Texture* yemojaTexture = new Texture();
	Texture* yemojaIdleTex = new Texture();

	Texture* h_upRunTex = new Texture();
	Texture* h_downRunTex = new Texture();
	Texture* h_leftRunTex = new Texture();
	Texture* h_rightRunTex = new Texture();
	Texture* h_upIdleTex = new Texture();
	Texture* h_downIdleTex = new Texture();
	Texture* h_leftIdleTex = new Texture();
	Texture* h_rightIdleTex = new Texture();

	Texture* treeTex = new Texture();
	Texture* treeTex1 = new Texture();
	Texture* treeTex2 = new Texture();

	Texture* rockTex = new Texture();
	Texture* rockTex1 = new Texture();
	Texture* rockTex2 = new Texture();

	Texture* pierTex = new Texture();

	Texture* blank = new Texture();

	//load sprite from a configuration file?
	blank->setFile("Assets/Sprites/blank1.png", 1);
	objTexture->setFile("Assets/Sprites/YemojasHouse.png", 1);

	playerTexture->setFile("Assets/Sprites/ShangoForwardIdle.png", 22);
	playerIdleTex->setFile("Assets/Sprites/ShangoForwardIdle.png", 22);

	upRunTex->setFile("Assets/Sprites/ShangoBackSprint.png", 16);
	downRunTex->setFile("Assets/Sprites/ShangoForwardSprint.png", 16);
	leftRunTex->setFile("Assets/Sprites/ShangoLeftSprint.png", 16);
	rightRunTex->setFile("Assets/Sprites/ShangoRightSprint.png", 16);
	upIdleTex->setFile("Assets/Sprites/ShangoBackIdle.png", 22);
	downIdleTex->setFile("Assets/Sprites/ShangoForwardIdle.png", 22);
	leftIdleTex->setFile("Assets/Sprites/ShangoLeftIdle.png", 22);
	rightIdleTex->setFile("Assets/Sprites/ShangoRightIdle.png", 22);
	upAtkTex->setFile("Assets/Sprites/ShangoBackSwing.png", 24);
	downAtkTex->setFile("Assets/Sprites/ShangoForwardSwing.png", 24);
	leftAtkTex->setFile("Assets/Sprites/ShangoLeftSwingEffect.png", 24);
	rightAtkTex->setFile("Assets/Sprites/ShangoRightSwingEffect.png", 24);
	upHurtTex->setFile("Assets/Sprites/ShangoBackRecoil.png", 18);
	downHurtTex->setFile("Assets/Sprites/ShangoForwardRecoil.png", 18);
	leftHurtTex->setFile("Assets/Sprites/ShangoLeftRecoil.png", 18);
	rightHurtTex->setFile("Assets/Sprites/ShangoRightRecoil.png", 18);


	yemojaTexture->setFile("Assets/Sprites/YemojaFrontIdle.png", 1);
	yemojaIdleTex->setFile("Assets/Sprites/YemojaFrontIdle.png", 1);

	h_upRunTex->setFile("Assets/Sprites/YemojaBackSprite.png", 26);
	h_downRunTex->setFile("Assets/Sprites/YemojaForwardSprite.png", 26);
	h_leftRunTex->setFile("Assets/Sprites/YemojaLeftSprite.png", 26);
	h_rightRunTex->setFile("Assets/Sprites/YemojaRightSprite.png", 26);
	h_upIdleTex->setFile("Assets/Sprites/YemojaBackIdle.png", 1);
	h_downIdleTex->setFile("Assets/Sprites/YemojaFrontIdle.png", 1);
	h_leftIdleTex->setFile("Assets/Sprites/YemojaLeftIdle.png", 1);
	h_rightIdleTex->setFile("Assets/Sprites/YemojaRightIdle.png", 1);

	treeTex->setFile("Assets/Sprites/tree.png", 1);
	treeTex1->setFile("Assets/Sprites/tree1.png", 1);
	treeTex2->setFile("Assets/Sprites/tree2.png", 1);

	rockTex->setFile("Assets/Sprites/rock_1.png", 1);
	rockTex2->setFile("Assets/Sprites/rock_2.png", 1);

	pierTex->setFile("Assets/Sprites/pier.png", 1);
	/* SET UP SPRITE CHANGE, MIGHT NEED A SINGLETON?*/


	Alex->sprite.setTexture(playerTexture);
	Alex->sprite.setIdleTexture(playerIdleTex);
	Alex->sprite.up = upRunTex;
	Alex->sprite.down = downRunTex;
	Alex->sprite.left = leftRunTex;
	Alex->sprite.right = rightRunTex;

	Alex->sprite.id_up = upIdleTex;
	Alex->sprite.id_left = leftIdleTex;
	Alex->sprite.id_right = rightIdleTex;
	Alex->sprite.id_down = downIdleTex;

	Alex->sprite.atk_up = upAtkTex;
	Alex->sprite.atk_down = downAtkTex;
	Alex->sprite.atk_left = leftAtkTex;
	Alex->sprite.atk_right = rightAtkTex;

	Alex->sprite.hurt_up = upHurtTex;
	Alex->sprite.hurt_down = downHurtTex;
	Alex->sprite.hurt_left = leftHurtTex;
	Alex->sprite.hurt_right = rightHurtTex;

	Alex->offsetBody(0, 50, 50, 50, 50);
	Alex->setInteractable(true);
	Alex->setName("Alex");
	Alex->setTalkDist(20);

	Alex->setDirection(2);
	//gameplay_functions->add_Attack(Alex->getKey(), Alex->body[0].getX(), Alex->body[0].getY(),true,10);

	gameplay_functions->add_Attack(Alex->getKey(), Alex->body[0].getX(), Alex->body[0].getY(), true, 10);


	tBuffer->run();

	Alex->melee = Containers::Attack_table[Alex->getKey()];
	Alex->melee->setDmg(10);
	Alex->melee->setSpeed(5);
	Alex->melee->setBaseDir(4);
	Alex->melee->setCoolDown(120);
	Alex->melee->setPause(-1);
	Alex->melee->setDestroy(false);
	Alex->melee->setKeep(true);
	Alex->melee->setWidth(Alex->body[0].getWidth());
	Alex->melee->setHeight(Alex->body[0].getHeight());


	Attack* rockThrow = new Attack();
	rockThrow->setDmg(5);
	rockThrow->setSpeed(20);
	rockThrow->setDestroy(true);
	rockThrow->setDuration(248);
	rockThrow->setCoolDown(120);
	rockThrow->setPause(24);
	rockThrow->sprite.setTexture(rockTex);
	Alex->addAttackType(rockThrow);

	//Alex->melee->sprite.setTexture(blank);
	Alex->melee->sprite.setTexture(blank);

	DialogueController::setPlayer(Alex);
	//vector<WorldObj*> recVec;
	Attack* spin = new Attack();
	spin->setDmg(7);
	spin->setSpeed(7);
	spin->setDestroy(true);
	spin->setDuration(5);
	spin->setBaseDir(6);
	spin->setCoolDown(600);
	spin->setPause(24);
	spin->sprite.setTexture(rockTex);
	Alex->addAttackType(spin);
	Attack* spin2 = new Attack();
	spin2->setDmg(7);
	spin2->setSpeed(7);
	spin2->setDestroy(true);
	spin2->setDuration(5);
	spin2->setBaseDir(6);
	spin2->setCoolDown(600);
	spin2->setPause(29);
	spin2->sprite.setTexture(rockTex);
	Alex->addAttackType(spin2);
	Attack* spin3 = new Attack();
	spin3->setDmg(7);
	spin3->setSpeed(7);
	spin3->setDestroy(true);
	spin3->setDuration(5);
	spin3->setBaseDir(6);
	spin3->setCoolDown(600);
	spin3->setPause(34);
	spin3->sprite.setTexture(rockTex);
	Alex->addAttackType(spin3);
	Attack* spin4 = new Attack();
	spin4->setDmg(7);
	spin4->setSpeed(7);
	spin4->setDestroy(true);
	spin4->setDuration(5);
	spin4->setBaseDir(6);
	spin4->setCoolDown(600);
	spin4->setPause(39);
	spin4->sprite.setTexture(rockTex);
	Alex->addAttackType(spin4);

	vector<WorldObj*> vec;
	//vec.push_back(&Alex->melee);
/**/
	for (int i = 1; i < 6; i++) {
		if (i > 4) {
			WorldObj* obj = new WorldObj(Vector2f(4100, 3550), 500, 333);

			obj->sprite.setTexture(objTexture);
			obj->setInteractable(true);
			std::string building = "Building ";
			obj->setName(building += std::to_string(i));
			//objs->offsetBody(0, 50, 50, 50, 50);
			obj->offsetBody(0, 25, 50, 25, 25);
			vec.push_back(obj);
			continue;
		}

		WorldObj* objs = new WorldObj(Vector2f(220 + 50 * i, 300 * (i * 2)), 600.0, 400.0);
		objs->sprite.setTexture(objTexture);
		objs->setInteractable(true);
		std::string building = "Building ";
		objs->setName(building += std::to_string(i));
		//objs->offsetBody(0, 50, 50, 50, 50);
		objs->offsetBody(0, 110, 150, 120, 60);
		recVec.push_back(objs);

	}

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

	gameplay_functions->add_hero("Yemoja", 4600, 3600, true);

	gameplay_functions->add_hero("silverSoldier", 4900, 3300, true);

	tBuffer->run();

	Hero* staticRec = Containers::hero_table["Yemoja"];
	Hero* silverSoldier = Containers::hero_table["silverSoldier"];

	Action* test_fight = new Action(staticRec, silverSoldier, staticRec, 10, 1, "fight", "execute_fight");

	AiController->hero_planners[YEMOJA]->set_current_action(test_fight);

	staticRec->setWidth(100);
	staticRec->setHeight(100);
	staticRec->name = YEMOJA;

	silverSoldier->setWidth(150);
	silverSoldier->setHeight(150);

	staticRec->sprite.setTexture(yemojaTexture);
	staticRec->sprite.setIdleTexture(yemojaIdleTex);
	staticRec->sprite.up = h_upRunTex;
	staticRec->sprite.down = h_downRunTex;
	staticRec->sprite.left = h_leftRunTex;
	staticRec->sprite.right = h_rightRunTex;
	staticRec->sprite.id_up = h_upIdleTex;
	staticRec->sprite.id_left = h_leftIdleTex;
	staticRec->sprite.id_right = h_rightIdleTex;
	staticRec->sprite.id_down = h_downIdleTex;
	staticRec->sprite.hurt_up = upHurtTex;
	staticRec->sprite.hurt_down = downHurtTex;
	staticRec->sprite.hurt_left = leftHurtTex;
	staticRec->sprite.hurt_right = rightHurtTex;

	silverSoldier->sprite.setTexture(playerTexture);
	silverSoldier->sprite.setIdleTexture(playerIdleTex);
	silverSoldier->sprite.up = upRunTex;
	silverSoldier->sprite.down = downRunTex;
	silverSoldier->sprite.left = leftRunTex;
	silverSoldier->sprite.right = rightRunTex;

	silverSoldier->sprite.id_up = upIdleTex;
	silverSoldier->sprite.id_left = leftIdleTex;
	silverSoldier->sprite.id_right = rightIdleTex;
	silverSoldier->sprite.id_down = downIdleTex;

	silverSoldier->sprite.atk_up = upAtkTex;
	silverSoldier->sprite.atk_down = downAtkTex;
	silverSoldier->sprite.atk_left = leftAtkTex;
	silverSoldier->sprite.atk_right = rightAtkTex;

	silverSoldier->sprite.hurt_up = upHurtTex;
	silverSoldier->sprite.hurt_down = downHurtTex;
	silverSoldier->sprite.hurt_left = leftHurtTex;
	silverSoldier->sprite.hurt_right = rightHurtTex;

	silverSoldier->offsetBody(0, 50, 50, 50, 50);
	silverSoldier->setInteractable(true);
	silverSoldier->setName("silverSoldier");

	gameplay_functions->add_Attack(silverSoldier->getKey(), silverSoldier->body[0].getX(), silverSoldier->body[0].getY(), true, 10);
	tBuffer->run();


	silverSoldier->melee = Containers::Attack_table[silverSoldier->getKey()];
	silverSoldier->melee->setDmg(10);
	silverSoldier->melee->setSpeed(5);
	silverSoldier->melee->setBaseDir(4);
	silverSoldier->melee->setCoolDown(200);
	silverSoldier->melee->setPause(-1);
	silverSoldier->melee->setDestroy(false);
	silverSoldier->melee->setKeep(true);
	silverSoldier->melee->setWidth(silverSoldier->body[0].getWidth());
	silverSoldier->melee->setHeight(silverSoldier->body[0].getHeight());

	silverSoldier->addAttackType(rockThrow);
	silverSoldier->melee->sprite.setTexture(blank);





	//VisibilityGraph graph;
	ai->graph.vertices = vertices;
	ai->graph.obstacles = edges;
	for (Vector2f vert : ai->graph.vertices) {
		//////std:://cout << "X: " << vert.getXloc() << " Y: " << vert.getYloc() << std::endl;
	}
	for (auto edge : ai->graph.obstacles) {
		//////std:://cout << "EDGE from " << edge.first.getXloc() << "," << edge.first.getYloc() << " to " << edge.second.getXloc() << "," << edge.second.getYloc() << std::endl;
	}

	bool visible = true;

	staticRec->setName("Yemoja");
	staticRec->setInteractable(true);
	staticRec->setHealth(100);

	recVec.push_back(staticRec);
	recVec.push_back(silverSoldier);
	
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
		//////std:://cout << "X: " << vert.getXloc() << " Y: " << vert.getYloc() << std::endl;
	}
	for (auto edge : ai->graph.obstacles) {
		//////std:://cout << "EDGE from " << edge.first.getXloc() << "," << edge.first.getYloc() << " to " << edge.second.getXloc() << "," << edge.second.getYloc() << std::endl;
	}

	ai->graph._print();

	ai->astar_search(staticRec);
	// gameplay_functions->get_path(staticRec); //Generate the waypoints to the destination
	staticRec->setMode(WANDER);

	ActionPool* poolAct = new ActionPool(Alex);
	Alex->actionPool_map[1] = poolAct;
	Action mic = Action();
	//mic.preconds["affAbove"] = 50;
	//mic.postconds["aff"] = 5;
	Action mac = Action();
	//mac.preconds["affAbove"] = 55;
	//	mac.postconds["aff"] = 5;
	mac.setDoer(Alex);
	mac.setReceiver(staticRec);
	poolAct->micro.push_back(&mic);
	poolAct->macro.push_back(&mac);
	poolAct->updateMiddle();
	//std:://cout << poolAct->macro.back().getName() << endl;
	vector<Action> test = poolAct->getActions(staticRec, *poolAct->macro.back());
	for (int i = 0; i < test.size(); i++) {
		int t = test[i].exeAction();
	}
	poolAct->macro.back()->exeAction();

	Vector2f silverSoldierInitialLoc = silverSoldier->getLoc();

	silverSoldier->setEvade(false);
	bool OSAtkMode = true;
	short M = GetKeyState('M') >> 15;

	vector<WorldObj*> enemyVec;
	//osi::GameWindow::init();
	LOG("PAST WINDOW INIT ***********************");
	clock_t start_tick, current_ticks, delta_ticks;
	clock_t fps = 0;
	int fs = 60;
	int wait_time = fs * 3; //always wait 3 seconds
	int count = 0;
	int state = 0;
	while (osi::GameWindow::isRunning()) {
		start_tick = clock();
		_QuadTree->clear();
		Alex->updateCD();
		silverSoldier->updateCD();
		for (int i = 0; i < recVec.size(); i++) {
			_QuadTree->Insert(recVec[i]);	//insert all obj into tree

		}
		state = DialogueController::getState();

		if (staticRec->destination != Vector2f(0, 0)) { //Hero has a destination
			if (staticRec->waypoint != Vector2f(0, 0) && state == 0) { //Hero has a waypoint to the desination, and not in dialog
				gameplay_functions->move_toward(staticRec); //Take a step towards the current waypoint
															//	////std:://cout << "Request a step" << std::endl;
			}
			else if (state == 0)                //Hero needs waypoints to destination, and not in dialog
			{
				gameplay_functions->get_path(staticRec); //Generate waypoints to destination
			}
		}

		else if (staticRec->getMode() != WAIT) //Hero has no destination, and not in wait mode.
		{
			int r = rand() % 4;
			ai->start = staticRec->getLoc();
			//////std:://cout << "at " << ai->start.getXloc() << "," << ai->start.getYloc() << std::endl;
			//////std:://cout << "picked " << r << std::endl;
			switch (r) {
			case 0:

				staticRec->destination = Vector2f(5000.00, 4100.00);
				break;
			case 1:
				staticRec->destination = Vector2f(4600.00, 3600.0);
				break;
			case 2:
				staticRec->destination = Vector2f(4500.00, 4000.0);
				break;
			case 3:
				staticRec->destination = Vector2f(5650.00, 3700.00);
				break;
			}
			//Generate the destination
		}
		else   //Hero has no destination and is waiting to generate one
		{
			count++;
			if (count >= wait_time) {
				count = 0;
				staticRec->setMode(WANDER);
			}
		}


		////cout << "Alex's position is " << Alex->getLoc().getXloc() << ", " << Alex->getLoc().getYloc() << endl;
		////cout << "OS's position is " << silverSoldier->getLoc().getXloc() << ", " << silverSoldier->getLoc().getYloc() << endl;
		////cout << "OS's DESTINATION IS: " << silverSoldier->destination.getXloc() << ", " << silverSoldier->destination.getYloc() << endl;

		/* DEFINE COMBAT MOVEMENT AI HERE
		At the start of each frame, we want to check for a given npc, whether there is hostile enemy on the map.
		Then, set the enemy and set the waypoint and destination to be the enemy's location. Since we do not have access
		to skills and cooldowns and what not,
		* WHEN NPC REACHES DESTINATION, destination is being automatically set to (0,0)!!! */
		//attack mode
		//enemyVec.clear();
		//enemyVec.push_back(Alex);
		//if (enemyVec.empty()) silverSoldier->setEvade(true);
		//for (auto it : enemyVec) {
		//	//if discovered Alex, set silverSoldier combat mode to 0(attack).
		//	if (silverSoldier->getCurrentEnemy() != nullptr) break;
		//	if (it == Alex) {
		//		//cout << "*************************************FOUND ENEMY****************************************" << endl;
		//		//silverSoldier->setMode(0);
		//		OSAtkMode = true;
		//		silverSoldier->setCurrentEnemy(it);
		//		break;
		//	}
		//}

		//if (silverSoldier->getCool()) {
		//	silverSoldier->setEvade(false);
		//}
		//else if (silverSoldier->destination == silverSoldier->getLoc() || silverSoldier->destination == Vector2f(0, 0)) {
		//	silverSoldier->setEvade(true);
		//	//silverSoldier->waypoint = Vector2f(-1, -1);
		//	float x = rand() % 300 + 100;
		//	int x2 = rand() % 2;
		//	float y = rand() % 300 + 100;
		//	int y2 = rand() % 2;
		//	if (x2 == 0)x = -x;
		//	if (y2 == 0)y = -y;
		//	silverSoldier->destination = Vector2f(silverSoldier->getCurrentEnemy()->getX() + x, silverSoldier->getCurrentEnemy()->getY() + y);
		//	silverSoldier->waypoint = Vector2f(silverSoldier->getCurrentEnemy()->getX() + x, silverSoldier->getCurrentEnemy()->getY() + y);
		//}


		////if OS has an enemy, move to the enemy
		//if (silverSoldier->getCurrentEnemy() != nullptr && !silverSoldier->getEvade()) {//&& silverSoldier->destination != Vector2f(0,0)) {
		//	//cout << "*************************************************MOVING TO ENEMY******************************************" << endl;
		//	silverSoldier->waypoint = Vector2f(silverSoldier->getCurrentEnemy()->getX() + (silverSoldier->getCurrentEnemy()->getWidth() / 4), silverSoldier->getCurrentEnemy()->getY() + (silverSoldier->getCurrentEnemy()->getHeight() / 4));
		//	silverSoldier->destination = Vector2f(silverSoldier->getCurrentEnemy()->getX() + (silverSoldier->getCurrentEnemy()->getWidth() / 4), silverSoldier->getCurrentEnemy()->getY() + (silverSoldier->getCurrentEnemy()->getHeight() / 4));


		//	//enemy is facing up
		//	if (silverSoldier->getCurrentEnemy()->getDirection() == 8) {

		//		silverSoldier->waypoint.shiftYloc(-80);
		//		silverSoldier->destination.shiftYloc(-80);
		//		silverSoldier->waypoint.shiftXloc(-30);
		//		silverSoldier->destination.shiftXloc(-30);

		//		//enemy is facing right
		//	}
		//	else if (silverSoldier->getCurrentEnemy()->getDirection() == 6) {

		//		silverSoldier->waypoint.shiftXloc(30);
		//		silverSoldier->destination.shiftXloc(30);
		//		silverSoldier->waypoint.shiftYloc(-30);
		//		silverSoldier->destination.shiftYloc(-30);
		//	}
		//	//enemy is facing left
		//	else if (silverSoldier->getCurrentEnemy()->getDirection() == 4) {
		//		silverSoldier->waypoint.shiftXloc(-80);
		//		silverSoldier->destination.shiftXloc(-80);
		//		silverSoldier->waypoint.shiftYloc(-30);
		//		silverSoldier->destination.shiftYloc(-30);
		//	}
		//	//enemy is facing down
		//	else if (silverSoldier->getCurrentEnemy()->getDirection() == 2) {
		//		silverSoldier->waypoint.shiftYloc(30);
		//		silverSoldier->destination.shiftYloc(30);
		//		silverSoldier->waypoint.shiftXloc(-30);
		//		silverSoldier->destination.shiftXloc(-30);
		//	}

		//	//gameplay_functions->move_toward(silverSoldier);


		//	//npc is at enemy destination, attack.
		//	if (silverSoldier->destination == silverSoldier->getLoc()) {
		//		silverSoldier->face(silverSoldier->getCurrentEnemy());
		//		//cout << "COOL DOWN FOR ATTACK IS " << silverSoldier->getCool() << endl;
		//		if (silverSoldier->getCool()) {
		//			//std::cout << "Pressed F" << std::endl;
		//			//gameplay_functions->special(silverSoldier, 0);
		//			silverSoldier->meleeAttack();
		//			gameplay_functions->melee(silverSoldier);
		//		}



		//	}
		//}

		//////evade mode
		//if (silverSoldier->getCurrentEnemy() != nullptr && silverSoldier->getEvade()) {//&& silverSoldier->destination != Vector2f(0, 0)) {
		//																		   //if OS is in evade mode, use the getEvadeRange method to find the waypoint and set it to destination
		//	if (silverSoldier->destination == Vector2f(-1, -1)) {
		//		//cout << "****INSIDE THE EVADE MODE SETTER*****" << endl;
		//		//silverSoldier->waypoint = silverSoldier->getEvadeRange(silverSoldier->getCurrentEnemy());
		//		silverSoldier->destination = silverSoldier->getEvadeRange(silverSoldier->getCurrentEnemy());
		//		//cout << "shango waypoint is " << silverSoldier->waypoint.getXloc() << silverSoldier->waypoint.getYloc() << endl;
		//	}
		//	//if reached destination, strafe left or right
		//	if (silverSoldier->getLoc() == silverSoldier->destination) {
		//		//cout << "******* INSIDE THE EVADE MODE STRAFE *******" << endl;
		//		//silverSoldier->waypoint = silverSoldier->getStrafeLocation(silverSoldier->getCurrentEnemy());
		//		silverSoldier->destination = silverSoldier->getEvadeRange(silverSoldier->getCurrentEnemy());
		//		//cout << "silverSoldier destination inside strafe function is " << silverSoldier->waypoint.getXloc() << ", " << silverSoldier->waypoint.getYloc() << endl;
		//	}
		//	/*if (silverSoldier->waypoint != Vector2f(0, 0) && state == 0) { //Hero has a waypoint to the desination, and not in dialog
		//	gameplay_functions->move_toward(silverSoldier); //Take a step towards the current waypoint
		//	//	//std::cout << "Request a step" << std::endl;
		//	}
		//	else if (state == 0)                //Hero needs waypoints to destination, and not in dialog
		//	{
		//	gameplay_functions->get_path(silverSoldier); //Generate waypoints to destination
		//	}/**/
		//	//gameplay_functions->move_toward(silverSoldier);
		//}
		////	ai->graph.insert(silverSoldier->destination);
		////ai->graph.insert(silverSoldier->getLoc());
		//if (silverSoldier->destination != Vector2f(0, 0)) { //Hero has a destination
		//	if (silverSoldier->waypoint != Vector2f(0, 0) && state == 0) { //Hero has a waypoint to the desination, and not in dialog
		//		gameplay_functions->move_toward(silverSoldier); //Take a step towards the current waypoint
		//													  //	//std::cout << "Request a step" << std::endl;
		//	}
		//	else if (state == 0)                //Hero needs waypoints to destination, and not in dialog
		//	{
		//		gameplay_functions->get_path(silverSoldier); //Generate waypoints to destination
		//	}
		//}
		//else {


		//}

		if (state == 0) {
			//LOG("ERROR AFTER PRESSING Q TO QUIT THE DIALOGUE GUI");
			gameplay_functions->draw_frame(Alex);

		}
		else if (state > 0) {
			gameplay_functions->drawDiaGui(Alex);
			gameplay_functions->stop(staticRec);
		}
		//convoGui->drawGui();

		//gameplay_functions->draw_frame(convoGui);
		//run task buffer
		//iController->InputCheck();
		//ActionExecFunctions::ActionExecMap[AiController->hero_planners[YEMOJA]->get_current_action()]
		AiController->hero_planners[YEMOJA]->get_current_action()->execute();
		tBuffer->run();
		//	////cout << tBuffer->queue_buffer.size() << endl;
		//tBuffer->empty();

		/////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////
		for (auto iter : staticRec->rel) {
			Relationship* my_rel = iter.second;
			int with_hero = iter.first;

			if (my_rel->isChanged()) {
				//reevaluate goals for with_hero
				AiController->reevaluate_state(YEMOJA, with_hero);
				my_rel->setChanged(false);
			}
		}
		AiController->execute();

		if ((1000 / fs) > (clock() - start_tick)) { //delta_ticks) {www
			Sleep((1000 / fs) - (clock() - start_tick));
		}
		delta_ticks = clock() - start_tick; //the time, in ms, that took to render the scene
		if (delta_ticks > 0)
			fps = CLOCKS_PER_SEC / delta_ticks;
		if (DialogueController::getState() == 0) {
			//////cout << "FPS: " << fps << endl;
		}


	}
	for (auto iter : AudM->soundHelper->sounds) {
		AudM->soundHelper->releaseSound(iter.second);
	}
	AudM->soundHelper->m_pSystem->release();
	
	osi::GameWindow::terminate();

	
}
 /*
void Darion_Ian_Test() {
	MemoryPool* hero_pool = create_pool(2048);
	MemNode* head_ptr = init_pool(hero_pool, 32);
	////std:://cout << std::endl;

	MemNode* m = head_ptr;

	while (m != NULL) {
		////std:://cout << "Availability:" << m->getAvailability() << std::endl;
		////std:://cout << "Block Pointer:" << m->getBlockPointer() << std::endl;
		if (m->hasNext() != NULL)
			////std:://cout << "Next Block:" << m->getNext()->getBlockPointer() << std::endl;
		////std:://cout << "--------------------" << std::endl;
		m = m->getNext();
	}

	////std:://cout << hero_pool->num_of_blocks << " Blocks" << std::endl;
	Warrior* myWarrior = new(find_available_block(head_ptr)) Warrior();
	////std:://cout << "Address of myWarrior:" << myWarrior << std::endl;
	////std:://cout << "Health:" << myWarrior->health << std::endl;

	Warrior* war = new(find_available_block(head_ptr)) Warrior(775, false, 3.9f, 2.7f);
	war->health = 69;
	////std:://cout << "Address of war:" << war << std::endl;
	////std:://cout << "Health:" << war->health << std::endl;

	destroy_pool(hero_pool);
	destroy_MemNode_list(head_ptr);


}
 */
/////////////////////////////////////////////////////////////////
//ERON'S LOOP NO TOUCHY
/////////////////////////////////////////////////////////////////

void ANDREWS_TEST() {
	FMOD::Channel *channels[32]; //all of the channels

	foo::soundType type;
	FMOD::Sound* soundSample;
	const char* name;              //the variables required
	FMOD::Channel* channel;
	bool ispaused;
	unsigned int time;

	// Initialize our sound system
	SoundSystem soundsystem;

	type = foo::soundType::music;
	name = "04.wav";
	channel = channels[0];//assign the channel
	ispaused = false;

	soundsystem.createSound(&soundSample, name);// Create the sound
	soundSample->getLength(&time, FMOD_TIMEUNIT_PCM);// Find the length

													 //SoundObject* playable = new SoundObject("04.wav", &soundSample, type);
													 //object stuff


	soundsystem.playSound(soundSample, false, channel, ispaused, 1); 	// Play the sound, with loop mode


	////cout << "Press return to quit." << endl;  // Do something meanwhile...
	cin.get();

	soundsystem.releaseSound(soundSample); // Release the sound
}
void ANDREWS_LOOP(QuadTree* _QuadTree) {
	//LOG("Hello world!");

	Player* Alex = new Player(SHANGO,Vector2f(500.0, 100.0), 100.0, 100.0);	//init player
	Texture* playerTexture = new Texture();
	playerTexture->setFile("phi.png",1);
	Alex->sprite.setTexture(playerTexture);
	Alex->offsetBody(0, 50, 50, 50, 50);
	vector<WorldObj*> recVec;

	for (int i = 1; i < 5; i++) {
		WorldObj* objs = new WorldObj(Vector2f(100 * i, 100 * i), 200.0, 200.0);
		objs->sprite.setTexture(playerTexture);
		objs->offsetBody(0, 50, 50, 50, 50);
		recVec.push_back(objs);
	}
	//recVec.push_back(myRec1); recVec.push_back(myRec2);

	//pauses the program for viewing
	//system("PAUSE");

	//demonstration of a meory leak
	//while (true) {
	//	void* a = malloc(64);
	//	delete a;
	//}

	//psuedo Gameloop
	MessageLog* mLog = new MessageLog();
	TaskBuffer* tBuffer = new TaskBuffer(mLog);

	//need this here for map editor
	ChildrenOfOsi* gameplay_functions = new ChildrenOfOsi(mLog, tBuffer);
	RenderManager* RenM = new RenderManager(mLog, tBuffer, _QuadTree, gameplay_functions);
	AIController* ai = new AIController();
	
	Input* iController = new Input(gameplay_functions, Alex, RenM->renderHelper, tBuffer, &recVec, ai);
	//create Managers and add to Manager table

	DummyController* DumM = new DummyController(mLog, tBuffer);
	PhysicsManager* PhysM = new PhysicsManager(mLog, tBuffer, _QuadTree);
	
	//memManager* memM = new memManager(mLog, tBuffer);
	TestManager* TestM = new TestManager(mLog, tBuffer);
	AudioManager* AudM = new AudioManager(mLog, tBuffer);

	//the order defines what order the managers the tasks will be sent to
	DumM->register_manager();
	PhysM->register_manager();
	//memM->register_manager();
	RenM->register_manager();
	TestM->register_manager();
	AudM->register_manager();

	////cout << endl;
	////cout << "STARTING PHYSICS TESTS" << endl;
	PHYSICS_TEST();

	//std::unordered_map<std::string, Manager*> manager_table;

	//manager_table["DumM"] = DumM;

	/*	Alex->WorldObj::setWidth(100);
	Alex->WorldObj::setHeight(100);
	Alex->setX(100);
	Alex->setY(100);*/

	//osi::GameWindow::init();
	LOG("PAST WINDOW INIT ***********************");
	while (osi::GameWindow::isRunning()) {
		_QuadTree->clear();
		for (int i = 0; i < recVec.size(); i++) {
			_QuadTree->Insert(recVec[i]);	//insert all obj into tree
		}
		//clock 
		iController->InputCheck();
		//Alex->WorldObj::drawObj();
		//for (int i = 0; i < recVec.size(); i++) {
		//	recVec[i]->drawObj();
		//}
		//Alex->WorldObj::animateObj();
		osi::GameWindow::refresh();
		//draw
		//gameplay_functions->draw_frame(Alex);
		//run task buffer
		tBuffer->run();


	}
	osi::GameWindow::terminate();
}

void PHYSICS_TEST() {
	PhysicsTestSuite* test = new PhysicsTestSuite();
	if (test->test_movement()) {
		////cout << "MOVEMENT TEST SUCCEEDED" << endl;
	}
	else {
		////cout << "MOVEMENT TEST FAILED" << endl;
	}

	if (test->test_collision()) {
		////cout << "COLLISION TEST SUCCEEDED" << endl;
	}
	else {
		////cout << "COLLISION TEST FAILED" << endl;
	}
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
