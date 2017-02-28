#pragma once
#include "common.h"
#include "Rectangle.h"
#include "GameWindow.h"
#include "DialogueController.h"


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
	Texture* swordGlowTex;
	Texture* heartTex;
	Texture* heartGlowTex;
	Texture* faceTex;
	Texture* faceGlowTex;
	Texture* questionTex;
	Texture* questionGlowTex;
	Texture* dialogueBoxTex;
	Texture* responseBoxTex;

	//strings
	std::string dialogueStr = "";
	std::string responseStr1 = "";
	std::string responseStr2 = "";

public:
	DialogueGui();
	~DialogueGui();
	void loadTexture();
	void setSprite();
	void drawGui();
	void setPortrait1(Sprite portrait1Sprite);
	void setPortrait2(Sprite portrait2Sprite);
	void setSwordGlow();
	void setHeartGlow();
	void setFaceGlow();
	void setQuestionGlow();
	void updateText();
	
};

