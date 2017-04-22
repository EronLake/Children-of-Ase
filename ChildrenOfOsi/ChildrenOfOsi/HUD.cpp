#include "stdafx.h"
#include "HUD.h"

bool HUD::show_active_quests=false;
int HUD::FPS=0;
int HUD::AVG = 0;

HUD::HUD()
{
	//init coord of all the icons
	hud_empty = new Rectangle(Vector2f(10, 10), 400, 400);
	hud_ase = new Rectangle(Vector2f(10, 10), 400, 400);
	hud_health = new Rectangle(Vector2f(10, 10), 400, 400);
	hud_portrait = new Rectangle(Vector2f(10, 10), 400, 400);

	hud_empty_tex = new Texture();
	hud_ase_tex = new Texture();
	hud_health_tex = new Texture();
	hud_portrait_tex = new Texture();

	black = glm::vec3(0, 0, 0);
}


HUD::~HUD()
{
}

void HUD::loadTexture()
{
	//setFile, load, setFrame
	// read access violation here, some sort of nullptr
	hud_empty_tex->setFile("Assets/Sprites/HUD_empty.png", 1);
	hud_ase_tex->setFile("Assets/Sprites/HUD_ase.png", 1);
	hud_health_tex->setFile("Assets/Sprites/HUD_health.png", 1);
	hud_portrait_tex->setFile("Assets/Sprites/HUD_portrait.png", 1);
}

void HUD::setSprite()
{
	hud_empty->sprite.setTexture(hud_empty_tex);
	hud_ase->sprite.setTexture(hud_ase_tex);
	hud_health->sprite.setTexture(hud_health_tex);
	hud_portrait->sprite.setTexture(hud_portrait_tex);
}

/*
void HUD::setTextures()
{
	hud_empty->sprite.setTexture(hud_empty_tex);
	hud_empty->sprite.setTexture(hud_empty_tex);
	hud_empty->sprite.setTexture(hud_empty_tex);
	hud_empty->sprite.setTexture(hud_empty_tex);

}
*/
void HUD::drawHUD(WorldObj* obj)
{
	Player* player = nullptr;
	if (obj->getType() == WorldObj::TYPE_PLAYER) {
		player = dynamic_cast<Player*>(obj);
	}
	//this->start = tex->getFrameWidth() * index;
	//this->stop = tex->getFrameWidth() * (index + 1);
	//

	hud_health->sprite.setStart((player->getHealth()/2));
	hud_health->sprite.setStop(player->getHealth() *19/4);
	
	//hud_ase->sprite.setStop(player->getAse() * 2 - 5);
	
	//---------------------------

	int damage_taken = (200 - player->getHealth())*1.9;

	if (damage_taken/1.9 > 140)
	{
		damage_taken += (200 - player->getHealth())* .4;
		////std:://cout << player->getHealth() << std::endl;
	}
	if (damage_taken > player->getHealth() / 5) 
	{ 
		damage_taken -= (200 - player->getHealth())* .5;
	}

	GameWindow::drawSprite(hud_empty->getX(), hud_empty->getY(), hud_empty->getWidth(), hud_empty->getHeight(), hud_empty->sprite);
	GameWindow::drawSprite(hud_ase->getX(), hud_ase->getY(), hud_ase->getWidth(), hud_ase->getHeight(), hud_ase->sprite);
	GameWindow::drawSprite(hud_health->getX() - damage_taken, hud_health->getY(), hud_health->getWidth(), hud_health->getHeight(), hud_health->sprite);
	GameWindow::drawSprite(hud_portrait->getX(), hud_portrait->getY(), hud_portrait->getWidth(), hud_portrait->getHeight(), hud_portrait->sprite);
	GameWindow::createText("FPS: "+to_string(FPS), 450, 20, 150, 80, black);
	GameWindow::createText("AVG: " + to_string(AVG), 525, 20, 150, 80, black);
	if (HUD::show_active_quests) {
		GameWindow::createText("Active Quests", 50, 104.5, 150, 80, black);
		GameWindow::createText("___________", 50, 105, 150, 80, black);
		vector<pair<Action*, int>> quests = player->get_quests();
		for (int i = 0; i < quests.size(); i++) {
			GameWindow::createText(quests[i].first->getName()+": "+ to_string(quests[i].second), 50, 122+(i*15), 150, 80, black);
		}
	}
}
