#pragma once
#include "common.h"
#include "Rectangle.h"
#include "GameWindow.h"
#include "DialogueController.h"

class HUD
{
public:
	HUD();
	~HUD();
	void loadTexture();
	void setSprite();
	void drawHUD(WorldObj* obj);
	//void setTextures();
	

private:
	//kinda ugly...
	Rectangle* hud_empty;
	Rectangle* hud_ase;
	Rectangle* hud_health;
	Rectangle* hud_portrait;
	//Texture
	Texture* hud_empty_tex;
	Texture* hud_ase_tex;
	Texture* hud_health_tex;
	Texture* hud_portrait_tex;


};

