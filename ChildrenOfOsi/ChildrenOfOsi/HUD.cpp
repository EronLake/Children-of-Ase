#include "stdafx.h"
#include "HUD.h"

bool HUD::show_active_quests = false;
bool HUD::if_animating = false;
int HUD::FPS = 0;
int HUD::AVG = 0;

HUD::HUD()
{
  this->healthbar_empty_rect = new Rectangle({HUD::HEALTHBAR_X, HUD::HEALTHBAR_Y}, HUD::HEALTHBAR_WIDTH, HUD::HEALTHBAR_HEIGHT);
  this->healthbar_full_rect = new Rectangle({HUD::HEALTHBAR_X, HUD::HEALTHBAR_Y}, HUD::HEALTHBAR_WIDTH, HUD::HEALTHBAR_HEIGHT);
  this->healthbar_decor_segment_rect = new Rectangle({HUD::HEALTHBAR_DECOR_SEGMENT_X, HUD::HEALTHBAR_DECOR_SEGMENT_Y}, HUD::HEALTHBAR_DECOR_SEGMENT_WIDTH, HUD::HEALTHBAR_DECOR_SEGMENT_HEIGHT);
  this->healthbar_decor_tail_rect = new Rectangle({HUD::HEALTHBAR_DECOR_TAIL_X, HUD::HEALTHBAR_DECOR_TAIL_Y}, HUD::HEALTHBAR_DECOR_TAIL_WIDTH, HUD::HEALTHBAR_DECOR_TAIL_HEIGHT);
  this->aseflame_empty_rect = new Rectangle({HUD::ASEFLAME_X, HUD::ASEFLAME_Y}, HUD::ASEFLAME_WIDTH, HUD::ASEFLAME_HEIGHT);
  this->aseflame_full_rect = new Rectangle({HUD::ASEFLAME_X, HUD::ASEFLAME_Y}, HUD::ASEFLAME_WIDTH, HUD::ASEFLAME_HEIGHT);
  this->portrait_background_rect = new Rectangle({HUD::PORTRAIT_X, HUD::PORTRAIT_Y}, HUD::PORTRAIT_WIDTH, HUD::PORTRAIT_HEIGHT);
  this->portrait_rect = new Rectangle({HUD::PORTRAIT_X, HUD::PORTRAIT_Y}, HUD::PORTRAIT_WIDTH, HUD::PORTRAIT_HEIGHT);

  this->minimap_rect = new Rectangle({HUD::MINIMAP_X, HUD::MINIMAP_Y}, HUD::MINIMAP_WIDTH, HUD::MINIMAP_HEIGHT);
  this->minimap_frame_rect = new Rectangle({HUD::MINIMAP_FRAME_X, HUD::MINIMAP_FRAME_Y}, HUD::MINIMAP_FRAME_WIDTH, HUD::MINIMAP_FRAME_HEIGHT);
  this->minimap_cursor_rect = new Rectangle({HUD::MINIMAP_CURSOR_X, HUD::MINIMAP_CURSOR_Y}, HUD::MINIMAP_CURSOR_WIDTH, HUD::MINIMAP_CURSOR_HEIGHT);
  this->keybind_display_rect = new Rectangle({HUD::KEYBIND_DISPLAY_X, HUD::KEYBIND_DISPLAY_Y}, HUD::KEYBIND_DISPLAY_WIDTH, HUD::KEYBIND_DISPLAY_HEIGHT);

  this->ori_flame_rect = new Rectangle({ HUD::ORI_FLAME_X, HUD::ORI_FLAME_Y }, HUD::ORI_FLAME_WIDTH, HUD::ORI_FLAME_HEIGHT);
  this->ori_crown_rect = new Rectangle({ HUD::ORI_CROWN_X, HUD::ORI_CROWN_Y }, HUD::ORI_CROWN_WIDTH, HUD::ORI_CROWN_HEIGHT);

  this->healthbar_empty_tex = new Texture();
  this->healthbar_full_tex = new Texture();
  this->healthbar_decor_segment_tex = new Texture();
  this->healthbar_decor_tail_tex = new Texture();
  this->aseflame_empty_tex = new Texture();
  this->aseflame_full_tex = new Texture();
  this->portrait_background_tex = new Texture();
  this->portrait_empty_tex = new Texture();
  this->portrait_full_tex = new Texture();

  this->minimap_tex = new Texture();
  this->minimap_frame_tex = new Texture();
  this->minimap_cursor_tex = new Texture();
  this->keybind_display_tex = new Texture();

  this->ori_flame_tex = new Texture();
  this->ori_crown_tex = new Texture();
}

HUD::~HUD()
{
  delete this->healthbar_empty_rect;
  delete this->healthbar_full_rect;
  delete this->healthbar_decor_segment_rect;
  delete this->healthbar_decor_tail_rect;
  delete this->aseflame_empty_rect;
  delete this->aseflame_full_rect;
  delete this->portrait_background_rect;
  delete this->portrait_rect;

  delete this->minimap_rect;
  delete this->minimap_frame_rect;
  delete this->minimap_cursor_rect;
  delete this->keybind_display_rect;

  delete this->ori_flame_rect;
  delete this->ori_crown_rect;

  delete this->healthbar_empty_tex;
  delete this->healthbar_full_tex;
  delete this->healthbar_decor_segment_tex;
  delete this->healthbar_decor_tail_tex;
  delete this->aseflame_empty_tex;
  delete this->aseflame_full_tex;
  delete this->portrait_background_tex;
  delete this->portrait_empty_tex;
  delete this->portrait_full_tex;

  delete this->minimap_tex;
  delete this->minimap_frame_tex;
  delete this->minimap_cursor_tex;
  delete this->keybind_display_tex;

  delete this->ori_flame_tex;
  delete this->ori_crown_tex;
}

void HUD::loadTexture()
{
  this->healthbar_empty_tex->setFile(SPRITES_PATH + "HUD_Healthbar_Empty.png", 1);
  this->healthbar_full_tex->setFile(SPRITES_PATH + "HUD_Healthbar_Full.png", 1);
  this->healthbar_decor_segment_tex->setFile(SPRITES_PATH + "HUD_HealthbarDecor_Segment.png", 1);
  this->healthbar_decor_tail_tex->setFile(SPRITES_PATH + "HUD_HealthbarDecor_Tail.png", 1);
  this->aseflame_empty_tex->setFile(SPRITES_PATH + "HUD_AseFlame_Empty.png", 1);
  this->aseflame_full_tex->setFile(SPRITES_PATH + "HUD_AseFlame_Full.png", 1);
  this->portrait_background_tex->setFile(SPRITES_PATH + "HUD_PortraitBase.png", 1);
  this->portrait_empty_tex->setFile(SPRITES_PATH + "HUD_Portrait_Empty.png", 1);
  this->portrait_full_tex->setFile(SPRITES_PATH + "HUD_Portrait_Full.png", 1);

  this->minimap_tex->setFile(SPRITES_PATH + "HUD_Minimap.png", 1);
  this->minimap_frame_tex->setFile(SPRITES_PATH + "HUD_Minimap_Frame.png", 1);
  this->minimap_cursor_tex->setFile(SPRITES_PATH + "HUD_Minimap_Cursor.png", 1);
  this->keybind_display_tex->setFile(SPRITES_PATH + "HUD_KeybindDisplay.png", 1);

  this->ori_flame_tex->setFile(SPRITES_PATH + "Ori_Flame.png", 4);
  this->ori_crown_tex->setFile(SPRITES_PATH + "Ori_Crown.png", 1);
}

void HUD::setSprite()
{
  this->healthbar_empty_rect->sprite.setTexture(this->healthbar_empty_tex);
  this->healthbar_full_rect->sprite.setTexture(this->healthbar_full_tex);
  this->healthbar_decor_segment_rect->sprite.setTexture(this->healthbar_decor_segment_tex);
  this->healthbar_decor_tail_rect->sprite.setTexture(this->healthbar_decor_tail_tex);
  this->aseflame_empty_rect->sprite.setTexture(this->aseflame_empty_tex);
  this->aseflame_full_rect->sprite.setTexture(this->aseflame_full_tex);
  this->portrait_background_rect->sprite.setTexture(this->portrait_background_tex);
  this->portrait_rect->sprite.setTexture(this->portrait_full_tex);

  this->minimap_rect->sprite.setTexture(this->minimap_tex);
  this->minimap_frame_rect->sprite.setTexture(this->minimap_frame_tex);
  this->minimap_cursor_rect->sprite.setTexture(this->minimap_cursor_tex);
  this->keybind_display_rect->sprite.setTexture(this->keybind_display_tex);

  this->ori_flame_rect->sprite.setTexture(this->ori_flame_tex);
  this->ori_crown_rect->sprite.setTexture(this->ori_crown_tex);
}

void HUD::drawHUD(WorldObj* obj)
{
  if(DialogueController::getState() != 0)
    return;

  Player* player = nullptr;
  if(obj->getType() != WorldObj::TYPE_PLAYER)
    return;
  else {
    player = dynamic_cast<Player *>(obj);
  }

  Hero* yemoja = Containers::hero_table["Yemoja"];
  Hero* oya = Containers::hero_table["Oya"];
  Hero* ogun = Containers::hero_table["Ogun"];

  this->drawMainHUD(player);
  this->drawMinimap(player, yemoja, oya, ogun);
  this->drawKeybindDisplay();
  this->drawOri(player);

  // Framerate information for debugging
  if(DEBUG) {
    GameWindow::createText("FPS: " + to_string(FPS), 450, 20, 150, 80, {0.0F, 0.0F, 0.0F});
    GameWindow::createText("AVG: " + to_string(AVG), 525, 20, 150, 80, {0.0F, 0.0F, 0.0F});
  }

  // Draw the listing of active quests
  if(HUD::show_active_quests) {
    GameWindow::createText("ACTIVE QUESTS", 810, 180.5, 150, 80, {0.0F, 0.0F, 0.0F});
    GameWindow::createText("_____________", 810, 180, 150, 80, {0.0F, 0.0F, 0.0F});
    vector<pair<Action*, int>> quests = player->get_quests();
    for(int i = 0; i < quests.size(); i++) {
		std::string::size_type name_end = quests[i].first->getName().find_last_of('_');
		std::string act_name = quests[i].first->getName().substr(0, name_end);
      GameWindow::createText(act_name+' '+quests[i].first->getReceiver()->getName(), 810, 202 + (i * 15), 150, 80, {0.0F, 0.0F, 0.0F});
    }
  }
}

void HUD::drawMainHUD(Player *player)
{
  float healthPercentage = static_cast<double>(player->getHealth()) / static_cast<double>(player->get_max_health());
  float asePercentage = static_cast<double>(player->getAse()) / static_cast<double>(player->getMaxAse());
  int healthbarWidth = static_cast<int>(ceil(healthbar_full_rect->sprite.getTexture().getWidth() * healthPercentage));
  int filledSmallAseFlames = static_cast<int>(ceil(asePercentage * HUD::ASEFLAME_COUNT));

  // Set the healthbar to display a portion of its width according to remaining health
  healthbar_full_rect->sprite.reset_texture();
  healthbar_full_rect->sprite.setStop(healthbarWidth);
  healthbar_full_rect->setWidth(HUD::HEALTHBAR_WIDTH * healthPercentage);

  // Draw the background for the portrait of Shango
  GameWindow::drawSprite(this->portrait_background_rect->getX(), this->portrait_background_rect->getY(),
    this->portrait_background_rect->getWidth(), this->portrait_background_rect->getHeight(), this->portrait_background_rect->getSprite());

  // Draw the healthbar
  GameWindow::drawSprite(this->healthbar_empty_rect->getX(), this->healthbar_empty_rect->getY(),
    this->healthbar_empty_rect->getWidth(), this->healthbar_empty_rect->getHeight(), this->healthbar_empty_rect->getSprite());
  GameWindow::drawSprite(this->healthbar_full_rect->getX(), this->healthbar_full_rect->getY(),
    this->healthbar_full_rect->getWidth(), this->healthbar_full_rect->getHeight(), this->healthbar_full_rect->getSprite());

  // Draw the healthbar's decorative border segments
  for(int i = 0; i < HUD::HEALTHBAR_DECOR_PIECE_COUNT; ++i) {
    float segmentOffset = (i * HUD::HEALTHBAR_DECOR_SEGMENT_WIDTH) - ( i * HUD::HEALTHBAT_DECOR_PIECE_OVERLAP);
    GameWindow::drawSprite(HUD::HEALTHBAR_DECOR_SEGMENT_X + segmentOffset, HUD::HEALTHBAR_DECOR_SEGMENT_Y,
      this->healthbar_decor_segment_rect->getWidth(), this->healthbar_decor_segment_rect->getHeight(),
      this->healthbar_decor_segment_rect->getSprite());
  }

  // Draw the helathbar border's tail end
  GameWindow::drawSprite(this->healthbar_decor_tail_rect->getX(), this->healthbar_decor_tail_rect->getY(),
    this->healthbar_decor_tail_rect->getWidth(), this->healthbar_decor_tail_rect->getHeight(), this->healthbar_decor_tail_rect->getSprite());

  // Draw the ase flames
  this->portrait_rect->sprite.setTexture((player->getAse() <= 0) ?
    this->portrait_empty_tex : this->portrait_full_tex);
  for(int i = 0; i < HUD::ASEFLAME_COUNT; ++i) {
    if(i < filledSmallAseFlames)
      GameWindow::drawSprite(HUD::ASEFLAME_X + (i * (HUD::ASEFLAME_WIDTH + HUD::ASEFLAME_MARGIN)), HUD::ASEFLAME_Y,
        this->aseflame_full_rect->getWidth(), this->aseflame_full_rect->getHeight(),
        this->aseflame_full_rect->getSprite());
    else
      GameWindow::drawSprite(HUD::ASEFLAME_X + (i * (HUD::ASEFLAME_WIDTH + HUD::ASEFLAME_MARGIN)), HUD::ASEFLAME_Y,
        this->aseflame_empty_rect->getWidth(), this->aseflame_empty_rect->getHeight(),
        this->aseflame_empty_rect->getSprite());
  }

// Draw the portrait of Shango
  GameWindow::drawSprite(this->portrait_rect->getX(), this->portrait_rect->getY(),
    this->portrait_rect->getWidth(), this->portrait_rect->getHeight(), this->portrait_rect->getSprite());
}

void HUD::drawMinimap(Player *player,Hero* yemoja, Hero* oya, Hero* ogun)
{
  Vector2f minimapCoordOffset;
  Vector2f minimapCoordOffset1;
  Vector2f minimapCoordOffset2;
  Vector2f minimapCoordOffset3;


  
  if(player->getX() < 0.0F) minimapCoordOffset.setXloc(0.0F);
  else if(player->getX() > HUD::MAP_WIDTH) minimapCoordOffset.setXloc(HUD::MAP_WIDTH);
  else { 
	  minimapCoordOffset.setXloc(player->getX() / HUD::MAP_WIDTH * HUD::MINIMAP_WIDTH);

	  minimapCoordOffset1.setXloc(yemoja->getX() / HUD::MAP_WIDTH * HUD::MINIMAP_WIDTH);
	  minimapCoordOffset2.setXloc(oya->getX() / HUD::MAP_WIDTH * HUD::MINIMAP_WIDTH);
	  minimapCoordOffset3.setXloc(ogun->getX() / HUD::MAP_WIDTH * HUD::MINIMAP_WIDTH);
  }

  if(player->getY() < 0.0F) minimapCoordOffset.setYloc(0.0F);
  else if(player->getY() > HUD::MAP_HEIGHT) minimapCoordOffset.setYloc(HUD::MAP_HEIGHT);
  else { 
	  minimapCoordOffset.setYloc(player->getY() / HUD::MAP_HEIGHT * HUD::MINIMAP_HEIGHT);
  
	  minimapCoordOffset1.setYloc(yemoja->getY() / HUD::MAP_HEIGHT * HUD::MINIMAP_HEIGHT);
	  minimapCoordOffset2.setYloc(oya->getY() / HUD::MAP_HEIGHT * HUD::MINIMAP_HEIGHT);
	  minimapCoordOffset3.setYloc(ogun->getY() / HUD::MAP_HEIGHT * HUD::MINIMAP_HEIGHT);
  }

  GameWindow::drawSprite(this->minimap_rect->getX(), this->minimap_rect->getY(),
    this->minimap_rect->getWidth(), this->minimap_rect->getHeight(), this->minimap_rect->getSprite());
  GameWindow::drawSprite(this->minimap_frame_rect->getX(), this->minimap_frame_rect->getY(),
    this->minimap_frame_rect->getWidth(), this->minimap_frame_rect->getHeight(), this->minimap_frame_rect->getSprite());
  GameWindow::drawSprite(this->minimap_cursor_rect->getX() + minimapCoordOffset.getXloc(), this->minimap_cursor_rect->getY() + minimapCoordOffset.getYloc(),
    this->minimap_cursor_rect->getWidth(), this->minimap_cursor_rect->getHeight(), this->minimap_cursor_rect->getSprite());

  GameWindow::drawSprite(this->minimap_cursor_rect->getX() + minimapCoordOffset1.getXloc(), this->minimap_cursor_rect->getY() + minimapCoordOffset1.getYloc(),
	  this->minimap_cursor_rect->getWidth(), this->minimap_cursor_rect->getHeight(), this->minimap_cursor_rect->getSprite());
  GameWindow::drawSprite(this->minimap_cursor_rect->getX() + minimapCoordOffset2.getXloc(), this->minimap_cursor_rect->getY() + minimapCoordOffset2.getYloc(),
	  this->minimap_cursor_rect->getWidth(), this->minimap_cursor_rect->getHeight(), this->minimap_cursor_rect->getSprite());
  GameWindow::drawSprite(this->minimap_cursor_rect->getX() + minimapCoordOffset3.getXloc(), this->minimap_cursor_rect->getY() + minimapCoordOffset2.getYloc(),
	  this->minimap_cursor_rect->getWidth(), this->minimap_cursor_rect->getHeight(), this->minimap_cursor_rect->getSprite());
}

void HUD::drawKeybindDisplay()
{
  GameWindow::drawSprite(this->keybind_display_rect->getX(), this->keybind_display_rect->getY(),
    this->keybind_display_rect->getWidth(), this->keybind_display_rect->getHeight(), this->keybind_display_rect->getSprite());
}

void HUD::drawOri(Player* player)
{
	int ori_size;
	if(player->ori < 100){
		ori_size = player->ori;
	}
	else {
		ori_size = 100;
	}

	int x_offset = this->ori_crown_rect->getWidth() / 2 - this->ori_flame_rect->getWidth() / 2;
	int y_offset = this->ori_crown_rect->getHeight() - this->ori_flame_rect->getHeight();

	GameWindow::drawSprite(this->ori_flame_rect->getX() + (x_offset - ori_size) - 20, this->ori_flame_rect->getY() + (y_offset - ori_size * 1.5),
		this->ori_flame_rect->getWidth() + (ori_size * 2), this->ori_flame_rect->getHeight() + (ori_size * 2), 
		this->ori_flame_rect->getSprite());

		this->ori_flame_rect->get_sprite_ref()->animate();

	GameWindow::drawSprite(this->ori_crown_rect->getX() + 40 - 20, this->ori_crown_rect->getY() + 100,
		this->ori_crown_rect->getWidth() - 80, this->ori_crown_rect->getHeight() - 80, this->ori_crown_rect->getSprite());
}
