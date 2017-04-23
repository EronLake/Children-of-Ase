#include "stdafx.h"
#include "HUD.h"

bool HUD::show_active_quests=false;
int HUD::FPS=0;
int HUD::AVG = 0;

HUD::HUD()
{
	//init coord of all the icons
  this->hud_empty = new Rectangle(Vector2f(10, 10), HUD::HUD_WIDTH, HUD::HUD_HEIGHT);
  this->hud_health = new Rectangle(Vector2f(10, 10), HUD::HEALTHBAR_WIDTH, HUD::HEALTHBAR_WIDTH);
  this->hud_ase = new Rectangle(Vector2f(10, 10), HUD::ASEBAR_WIDTH, HUD::ASEBAR_HEIGHT);
  this->hud_portrait = new Rectangle(Vector2f(10, 10), HUD::HUD_WIDTH, HUD::HUD_HEIGHT);

  this->hud_empty_tex = new Texture();
  this->hud_ase_tex = new Texture();
  this->hud_health_tex = new Texture();
	this->hud_portrait_tex = new Texture();

  this->black = glm::vec3(0, 0, 0);
}


HUD::~HUD()
{
  delete this->hud_empty;
  delete this->hud_health;
  delete this->hud_ase;
  delete this->hud_portrait;

  delete this->hud_empty_tex;
  delete this->hud_health_tex;
  delete this->hud_ase_tex;
  delete this->hud_portrait_tex;
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

void HUD::drawHUD(WorldObj* obj)
{
  Player* player = nullptr;
  if(obj->getType() != WorldObj::TYPE_PLAYER)
    return;
  else {
    player = dynamic_cast<Player *>(obj);
  }

  double healthPercentage = static_cast<double>(player->getHealth()) / static_cast<double>(player->get_max_health());
  int healthbarWidth = static_cast<int>(ceil(hud_health->sprite.getTexture().getWidth() * healthPercentage));
  double asePercentage = static_cast<double>(player->getAse()) / static_cast<double>(player->getMaxAse());
  int asebarWidth = static_cast<int>(ceil(hud_ase->sprite.getTexture().getWidth() * asePercentage));

  hud_health->sprite.reset_texture();
  hud_health->sprite.setStop(healthbarWidth);
  hud_health->setWidth(HUD::HEALTHBAR_WIDTH * healthPercentage);

	GameWindow::drawSprite(hud_empty->getX(), hud_empty->getY(), hud_empty->getWidth(), hud_empty->getHeight(), hud_empty->sprite);                // Health/ase bar background
  GameWindow::drawSprite(hud_health->getX(), hud_health->getY(), hud_health->getWidth(), hud_health->getHeight(), hud_health->sprite);           // Health bar fill
	GameWindow::drawSprite(hud_ase->getX(), hud_ase->getY(), hud_ase->getWidth(), hud_ase->getHeight(), hud_ase->sprite);                          // Ase bar fill
	GameWindow::drawSprite(hud_portrait->getX(), hud_portrait->getY(), hud_portrait->getWidth(), hud_portrait->getHeight(), hud_portrait->sprite); // Shango portrait
	GameWindow::createText("FPS: " + to_string(FPS), 450, 20, 150, 80, black);                                                                     // FPS counter
	GameWindow::createText("AVG: " + to_string(AVG), 525, 20, 150, 80, black);                                                                     // Average framerate

	if (HUD::show_active_quests) {
		GameWindow::createText("Active Quests", 50, 104.5, 150, 80, black);
		GameWindow::createText("___________", 50, 105, 150, 80, black);
		vector<pair<Action*, int>> quests = player->get_quests();
		for (int i = 0; i < quests.size(); i++) {
			GameWindow::createText(quests[i].first->getName()+": "+ to_string(quests[i].second), 50, 122+(i*15), 150, 80, black);
		}
	}
}
