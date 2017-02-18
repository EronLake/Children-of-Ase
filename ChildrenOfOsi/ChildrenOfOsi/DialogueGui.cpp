#include "stdafx.h"
#include "DialogueGui.h"


DialogueGui::DialogueGui()
{
	//init coord of all the icons
	background = new Rectangle(Vector2f(70, 270), 960, 540);
	//swordIcon = new Rectangle(Vector2f(142, 302), 960, 540);
}


DialogueGui::~DialogueGui()
{
}

void DialogueGui::loadTexture()
{
	//setFile, load, setFrame
	backgroundTex->setFile("DialogueGuiBackground");
	swordTex->setFile("DialogueGuiSword");
	heartTex->setFile("DialogueGuiHeart");
	faceTex->setFile("DialogueGuiFace");
	questionTex->setFile("DialogueGuiQuestion");
	dialogueBoxTex->setFile("DialogueGuiDiaBox");
	responseBoxTex->setFile("DialogueGuiResponseBox");

	//load the texture
	backgroundTex->load();
	swordTex->load();
	heartTex->load();
	faceTex->load();
	questionTex->load();
	dialogueBoxTex->load();
	responseBoxTex->load();

	//setframe
	backgroundTex->setFrames(1);
	swordTex->setFrames(1);
	heartTex->setFrames(1);
	faceTex->setFrames(1);
	questionTex->setFrames(1);
	dialogueBoxTex->setFrames(1);
	responseBoxTex->setFrames(1);
	
}

void DialogueGui::setSprite()
{
	background->sprite.setTexture(backgroundTex);
	swordIcon->sprite.setTexture(swordTex);
	heartIcon->sprite.setTexture(heartTex);
	faceIcon->sprite.setTexture(faceTex);
	questionIcon->sprite.setTexture(questionTex);
	dialogueBox->sprite.setTexture(dialogueBoxTex);
	responseBox1->sprite.setTexture(responseBoxTex);
	responseBox2->sprite.setTexture(responseBoxTex);
}

void DialogueGui::drawGui()
{
	//osi::GameWindow::drawSprite(loc.getXloc() - _x, loc.getYloc() - _y, width, height, sprite);
}
