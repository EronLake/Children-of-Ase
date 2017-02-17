#pragma once
#include "common.h"
#include "Rectangle.h"

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
};

