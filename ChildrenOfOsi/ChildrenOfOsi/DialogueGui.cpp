#include "stdafx.h"
#include "DialogueGui.h"
//#include "GameWindow.h"

DialogueGui::DialogueGui()
{
	//init coord of all the icons
	background = new Rectangle(Vector2f(70, 270), 820, 250);
	swordIcon = new Rectangle(Vector2f(142, 302), 50, 47);
	heartIcon = new Rectangle(Vector2f(142, 349), 50, 47);
	faceIcon = new Rectangle(Vector2f(142, 394), 50, 47);
	questionIcon = new Rectangle(Vector2f(142, 439), 50, 47);
	dialogueBox = new Rectangle(Vector2f(254, 303), 600, 80);
	responseBox1 = new Rectangle(Vector2f(280, 390), 544, 45);
	responseBox2 = new Rectangle(Vector2f(280, 440), 544, 45);
	portrait1 = new Rectangle(Vector2f(100, 70), 300, 400);
	portrait2 = new Rectangle(Vector2f(700, 70), 300, 400);
	backgroundTex = new Texture();
	swordTex = new Texture();
	swordGlowTex = new Texture();
	heartTex = new Texture();
	heartGlowTex = new Texture();
	faceTex = new Texture();
	faceGlowTex = new Texture();
	questionTex = new Texture();
	questionGlowTex = new Texture();
	dialogueBoxTex = new Texture();
	responseBoxTex = new Texture();

}


DialogueGui::~DialogueGui()
{
}

void DialogueGui::loadTexture()
{
	//setFile, load, setFrame
	// read access violation here, some sort of nullptr
	backgroundTex->setFile("DGBackground.png");
	swordTex->setFile("DGSword.png");
	swordGlowTex->setFile("DGGlowSword.png");
	heartTex->setFile("DGHeart.png");
	heartGlowTex->setFile("DGGlowHeart.png");
	faceTex->setFile("DGFace.png");
	faceGlowTex->setFile("DGGlowFace.png");
	questionTex->setFile("DGQuestion.png");
	questionGlowTex->setFile("DGGlowQuestion.png");
	dialogueBoxTex->setFile("DGDiaBox.png");
	responseBoxTex->setFile("DGResponseBox.png");


	//load the texture
	backgroundTex->load();
	swordTex->load();
	swordGlowTex->load();
	heartTex->load();
	heartGlowTex->load();
	faceTex->load();
	faceGlowTex->load();
	questionTex->load();
	questionGlowTex->load();
	dialogueBoxTex->load();
	responseBoxTex->load();

	//setframe
	backgroundTex->setFrames(1);
	swordTex->setFrames(1);
	swordGlowTex->setFrames(1);
	heartTex->setFrames(1);
	heartGlowTex->setFrames(1);
	faceTex->setFrames(1);
	faceGlowTex->setFrames(1);
	questionTex->setFrames(1);
	questionGlowTex->setFrames(1);
	dialogueBoxTex->setFrames(1);
	responseBoxTex->setFrames(1);

}

void DialogueGui::setSprite()
{
	background->sprite.setTexture(backgroundTex);
	swordIcon->sprite.setTexture(swordGlowTex);
	heartIcon->sprite.setTexture(heartTex);
	faceIcon->sprite.setTexture(faceTex);
	questionIcon->sprite.setTexture(questionTex);
	dialogueBox->sprite.setTexture(dialogueBoxTex);
	responseBox1->sprite.setTexture(responseBoxTex);
	responseBox2->sprite.setTexture(responseBoxTex);
}

void DialogueGui::setPortrait1(Sprite portrait1Sprite)
{
	portrait1->sprite = portrait1Sprite;
}

void DialogueGui::setPortrait2(Sprite portrait2Sprite)
{
	portrait2->sprite = portrait2Sprite;
}

void DialogueGui::drawGui()
{
	osi::GameWindow::drawSprite(background->getX(), background->getY(), background->getWidth(), background->getHeight(), background->sprite);
	osi::GameWindow::drawSprite(swordIcon->getX(), swordIcon->getY(), swordIcon->getWidth(), swordIcon->getHeight(), swordIcon->sprite);
	osi::GameWindow::drawSprite(heartIcon->getX(), heartIcon->getY(), heartIcon->getWidth(), heartIcon->getHeight(), heartIcon->sprite);
	osi::GameWindow::drawSprite(faceIcon->getX(), faceIcon->getY(), faceIcon->getWidth(), faceIcon->getHeight(), faceIcon->sprite);
	osi::GameWindow::drawSprite(questionIcon->getX(), questionIcon->getY(), questionIcon->getWidth(), questionIcon->getHeight(), questionIcon->sprite);
	osi::GameWindow::drawSprite(dialogueBox->getX(), dialogueBox->getY(), dialogueBox->getWidth(), dialogueBox->getHeight(), dialogueBox->sprite);
	osi::GameWindow::drawSprite(responseBox1->getX(), responseBox1->getY(), responseBox1->getWidth(), responseBox1->getHeight(), responseBox1->sprite);
	osi::GameWindow::drawSprite(responseBox2->getX(), responseBox2->getY(), responseBox2->getWidth(), responseBox2->getHeight(), responseBox2->sprite);

}
