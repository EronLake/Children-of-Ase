#pragma once
#include "common.h"
#include "Rectangle.h"
#include "GameWindow.h"


class DialogueGui
{

private:
	//kinda ugly...
	Rectangle* background;
	Rectangle* swordIcon;
	Rectangle* heartIcon;
	Rectangle* faceIcon;
	Rectangle* questionIcon;
	Rectangle* dialogueBox;
	Rectangle* responseBox1;
	Rectangle* responseBox2;
	Rectangle* portrait1;
	Rectangle* portrait2;

	//Texture
	Texture* backgroundTex;
	Texture* swordTex;
	Texture* heartTex;
	Texture* faceTex;
	Texture* questionTex;
	Texture* dialogueBoxTex;
	Texture* responseBoxTex;

public:
	DialogueGui();
	~DialogueGui();
	void loadTexture();
	void setSprite();
	void drawGui();
	void setPortrait1(Sprite portrait1Sprite);
	void setPortrait2(Sprite portrait2Sprite);
};

