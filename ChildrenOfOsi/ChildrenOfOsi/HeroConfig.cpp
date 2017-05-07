#include "stdafx.h"
#include "HeroConfig.h"


HeroConfig::HeroConfig()
{
}


HeroConfig::~HeroConfig()
{
}

void HeroConfig::import_config(vector<WorldObj*>* movVec, ChildrenOfOsi* gameplay_func, TaskBuffer* tBuffer)
{
	Json::Value root;
	Json::Reader reader;


	std::ifstream file("hero_config.json");

	file >> root;

	for (auto itr = root.begin(); itr != root.end(); itr++)
	{
		set_hero(movVec, gameplay_func, tBuffer, (*itr)["x"].asFloat(), (*itr)["y"].asFloat(),
			(*itr)["width"].asFloat(), (*itr)["hight"].asFloat(),
			(*itr)["name"].asString(), (*itr)["hero_id"].asInt(),
			(*itr)["bodyx1"].asFloat(), (*itr)["bodyx2"].asFloat(),
			(*itr)["bodyy1"].asFloat(), (*itr)["bodyy2"].asFloat(),
			(*itr)["health"].asInt(), (*itr)["max_stamina"].asInt(),
			(*itr)["aggression"].asInt(), (*itr)["kindness"].asInt(), (*itr)["honor"].asInt(),
			(*itr)["pride"].asInt(), (*itr)["recklessness"].asInt(), (*itr)["extroversion"].asInt(),
			(*itr)["greed"].asInt());
	}

	for (auto itr = root.begin(); itr != root.end(); itr++)
	{
		init_hero_planner(gameplay_func, tBuffer, (*itr)["name"].asString(), (*itr)["hero_id"].asInt());
	}

	AIController::init_plans();

}

void HeroConfig::set_hero(vector<WorldObj*>* movVec, ChildrenOfOsi* gameplay_func, TaskBuffer* tBuffer, float x, float y, float width,
	float hight, std::string name, int hero_id, float bodyx1, float bodyx2, float bodyy1, float bodyy2,int health, int max_stamina,
	int a, int k, int h, int p, int r, int e, int g)
{

	gameplay_func->add_hero(name, 100 * x, 100 * y, true);

	tBuffer->run();

	Containers::hero_table[name]->name = hero_id;
	Containers::hero_table[name]->setName(name);
	Containers::hero_table[name]->setWidth(width);
	Containers::hero_table[name]->setHeight(hight);
	Containers::hero_table[name]->offsetBody(0, bodyx1, bodyx2, bodyy1, bodyy2);

	//needs to be handled separately
	//Containers::hero_table[name]->sprite.setTexture(Containers::texture_table[tex_file]);

	Containers::hero_table[name]->setInteractable(true);
	Containers::hero_table[name]->setPersonality(a, k, h, p, r, e, g);

	Containers::hero_table[name]->setHealth(health);
	Containers::hero_table[name]->setMaxStamina(max_stamina);

	//push to moveVec
	movVec->push_back(Containers::hero_table[name]);

	if (hero_id == SHANGO)
	{

	}
	else if (hero_id == YEMOJA)
	{

	}
	else if (hero_id == OYA)
	{

	}
	else if (hero_id == OSHOSI)
	{

	}
	else if (hero_id == OGUN)
	{

	}



	//player 

	//Alex->name = SHANGO;
	//Alex->setWidth(150);
	//Alex->setHeight(150);
	//Alex->setPersonality(30, 70, 80, 60, 30, 30, 50);// uncommented this
	//gameplay_functions->add_hero("Shango", 6445, 10055, true);

	//Alex->setHealth(200);							 //Texture* playerTexture = new Texture();
	//staticRec->setMaxStamina(300);					 //Texture* playerIdleTex = new Texture();
	


	//heroes

	//gameplay_functions->add_hero("Yemoja", 6445.0, 10355.0, true);
	//gameplay_functions->add_hero("Oya", 4400, 3600, true);

	//tBuffer->run();

	//staticRec->setName("Yemoja");
	//staticRec->setInteractable(true);

	//Hero* staticRec = Containers::hero_table["Yemoja"];
	//heroes.push_back(staticRec);
	//Hero* oya = Containers::hero_table["Oya"];
	//heroes.push_back(oya);

//	gameplay_functions->add_Attack(staticRec->getKey(), staticRec->body[0].getX(), staticRec->body[0].getY(), true, 10);
//	gameplay_functions->add_Attack(oya->getKey(), oya->body[0].getX(), oya->body[0].getY(), true, 10);
//	tBuffer->run();

	//oya->offsetBody(0, 35, 35, 65, 15);
	//staticRec->offsetBody(0, 60, 60, 75, 50);
	//oya->shiftY(300);
	//oya->setHealth(50);





	/*
	LOG(Containers::texture_table[tex_file]);
	if (Containers::texture_table[tex_file]) {

	//std:://cout << tex_file << "Already in Table /////////////////////////////" << endl;
	}
	else
	{
	//std:://cout << tex_file << "Not in Table /////////////////////////////" << endl;

	gameplay_func->add_texture(tex_file, 0, 0, 0);

	//set file takes up memory
	tBuffer->run();
	Containers::texture_table[tex_file]->setFile("Assets/Sprites/" + tex_file + ".png", frame_num);

	}
	*/


	//player/////////////////

	//melee_stuff

	/*
	Alex->melee = Containers::Attack_table[Alex->getKey()];
	Alex->melee->setDmg(10);
	Alex->melee->setSpeed(5);
	Alex->melee->setBaseDir(4);
	Alex->melee->setCoolDown(35);
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
	fireball->setDmg(15);
	fireball->setSpeed(10);
	fireball->setDestroy(true);
	fireball->setDuration(100);
	fireball->setCoolDown(180);
	fireball->setPause(24);
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
	spin->setDmg(7);
	spin->setSpeed(18);
	spin->setDestroy(false);
	spin->setDuration(7);
	spin->setBaseDir(4);
	spin->setCoolDown(100);
	spin->setPause(18);
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
	*/




	//sprite_stuff
	/*
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
	*/
	
	//heroes

	//melee stuff 
	/*
	staticRec->melee = Containers::Attack_table[staticRec->getKey()];
	staticRec->melee->setDmg(15);
	staticRec->melee->setSpeed(5);
	staticRec->melee->setBaseDir(4);
	staticRec->melee->setCoolDown(60);
	staticRec->melee->setPause(-1);
	staticRec->melee->setDestroy(false);
	staticRec->melee->setKeep(true);
	staticRec->melee->setWidth(50);
	staticRec->melee->setHeight(50);
	staticRec->set_creator_of_melee();
	staticRec->melee->setStaminaCost(90);
	staticRec->setHealth(100);
	staticRec->setMaxStamina(300);
	staticRec->melee->sprite.setTexture(Containers::texture_table["border"]);

	oya->melee = Containers::Attack_table[oya->getKey()];
	oya->melee->setDmg(10);
	oya->melee->setSpeed(5);
	oya->melee->setBaseDir(4);
	oya->melee->setCoolDown(80);
	oya->melee->setPause(-1);
	oya->melee->setDestroy(false);
	oya->melee->setKeep(true);
	oya->melee->setWidth(50);
	oya->melee->setHeight(50);
	oya->set_creator_of_melee();
	oya->melee->setStaminaCost(120);
	oya->setHealth(100);
	oya->setMaxStamina(300);
	oya->melee->sprite.setTexture(Containers::texture_table["border"]);
	*/

	//spite stuff
	
    /*
	gameplay_functions->add_texture("yemojaTexture", 0, 0, 0);
	gameplay_functions->add_texture("yemojaIdleTex", 0, 0, 0);
	tBuffer->run();
	//Texture* yemojaTexture = new Texture();
	//Texture* yemojaIdleTex = new Texture();
	textureMap[Containers::texture_table["yemojaTexture"]] = pair<string, int>("Assets/Sprites/YemojaForwardIdle.png", 22);
	textureMap[Containers::texture_table["yemojaIdleTex"]] = pair<string, int>("Assets/Sprites/YemojaForwardIdle.png", 22);
	oasis.push_back(Containers::texture_table["yemojaTexture"]);
	oasis.push_back(Containers::texture_table["yemojaIdleTex"]);

	gameplay_functions->add_texture("h_upRunTex", 0, 0, 0);
	gameplay_functions->add_texture("h_downRunTex", 0, 0, 0);
	gameplay_functions->add_texture("h_leftRunTex", 0, 0, 0);
	gameplay_functions->add_texture("h_rightRunTex", 0, 0, 0);
	gameplay_functions->add_texture("h_upIdleTex", 0, 0, 0);
	gameplay_functions->add_texture("h_downIdleTex", 0, 0, 0);
	gameplay_functions->add_texture("h_leftIdleTex", 0, 0, 0);
	gameplay_functions->add_texture("h_rightIdleTex", 0, 0, 0);
	tBuffer->run();

	textureMap[Containers::texture_table["h_upRunTex"]] = pair<string, int>("Assets/Sprites/YemojaBackSprint.png", 16);
	textureMap[Containers::texture_table["h_downRunTex"]] = pair<string, int>("Assets/Sprites/YemojaForwardSprint.png", 16);
	textureMap[Containers::texture_table["h_leftRunTex"]] = pair<string, int>("Assets/Sprites/YemojaLeftSprint.png", 16);
	textureMap[Containers::texture_table["h_rightRunTex"]] = pair<string, int>("Assets/Sprites/YemojaRightSprint.png", 16);
	textureMap[Containers::texture_table["h_upIdleTex"]] = pair<string, int>("Assets/Sprites/YemojaBackIdle.png", 22);
	textureMap[Containers::texture_table["h_downIdleTex"]] = pair<string, int>("Assets/Sprites/YemojaForwardIdle.png", 22);
	textureMap[Containers::texture_table["h_leftIdleTex"]] = pair<string, int>("Assets/Sprites/YemojaLeftIdle.png", 22);
	textureMap[Containers::texture_table["h_rightIdleTex"]] = pair<string, int>("Assets/Sprites/YemojaRightIdle.png", 22);
	oasis.push_back(Containers::texture_table["h_upRunTex"]);
	oasis.push_back(Containers::texture_table["h_downRunTex"]);
	oasis.push_back(Containers::texture_table["h_leftRunTex"]);
	oasis.push_back(Containers::texture_table["h_rightRunTex"]);
	oasis.push_back(Containers::texture_table["h_upIdleTex"]);
	oasis.push_back(Containers::texture_table["h_downIdleTex"]);
	oasis.push_back(Containers::texture_table["h_leftIdleTex"]);
	oasis.push_back(Containers::texture_table["h_rightIdleTex"]);

	gameplay_functions->add_texture("silverSoldierTexture", 0, 0, 0);
	gameplay_functions->add_texture("silverSoldierIdleTex", 0, 0, 0);
	gameplay_functions->add_texture("blueSoldierTexture", 0, 0, 0);
	gameplay_functions->add_texture("blueSoldierIdleTex", 0, 0, 0);
	tBuffer->run();
	*/
}

void HeroConfig::init_hero_planner(ChildrenOfOsi* gameplay_func, TaskBuffer* tBuffer, std::string name, int hero_id)
{
	//initializes action pool for given hero
	ActionConfig::import_config(gameplay_func, tBuffer, Containers::hero_table[name]);

	//initializes planner for given hero
	Planner* heroPlanner = new Planner(Containers::hero_table[name]);
	AIController::set_plan(hero_id, heroPlanner);
}


