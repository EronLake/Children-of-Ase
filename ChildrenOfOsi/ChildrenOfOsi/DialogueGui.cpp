#include "stdafx.h"
#include "DialogueGui.h"
#include "GameWindow.h"

DialogueGui::DialogueGui()
{
	//init coord of all the icons
	background = new Rectangle(Vector2f(70, 270), 600, 200);
	//swordIcon = new Rectangle(Vector2f(142, 302), 960, 540);
	backgroundTex = new Texture();
	//swordTex = new Texture();
	//heartTex = new Texture();
	//faceTex = new Texture();
	//questionTex = new Texture();
	//dialogueBoxTex = new Texture();
	//responseBoxTex = new Texture();
}


DialogueGui::~DialogueGui()
{
}

void DialogueGui::loadTexture()
{
	//setFile, load, setFrame
	// read access violation here, some sort of nullptr
	backgroundTex->setFile("DialogueGuiBackground.png");
	//swordTex->setFile("DialogueGuiSword.png");
	//heartTex->setFile("DialogueGuiHeart.png");
	//faceTex->setFile("DialogueGuiFace.png");
	//questionTex->setFile("DialogueGuiQuestion.png");
	//dialogueBoxTex->setFile("DialogueGuiDiaBox.png");
	//responseBoxTex->setFile("DialogueGuiResponseBox.png");


	//load the texture
	backgroundTex->load();
	//swordTex->load();
	//heartTex->load();
	//faceTex->load();
	//questionTex->load();
	//dialogueBoxTex->load();
	//responseBoxTex->load();

	//setframe
	backgroundTex->setFrames(1);
	//swordTex->setFrames(1);
	//heartTex->setFrames(1);
	//faceTex->setFrames(1);
	//questionTex->setFrames(1);
	//dialogueBoxTex->setFrames(1);
	//responseBoxTex->setFrames(1);
	
}

void DialogueGui::setSprite()
{
	background->sprite.setTexture(backgroundTex);
	//swordIcon->sprite.setTexture(swordTex);
	//heartIcon->sprite.setTexture(heartTex);
	//faceIcon->sprite.setTexture(faceTex);
	//questionIcon->sprite.setTexture(questionTex);
	//dialogueBox->sprite.setTexture(dialogueBoxTex);
	//responseBox1->sprite.setTexture(responseBoxTex);
	//responseBox2->sprite.setTexture(responseBoxTex);
}

void DialogueGui::drawGui()
{
	osi::GameWindow::drawSprite(background->getX(), background->getY(), background->getWidth(), background->getHeight(), background->sprite);
}
