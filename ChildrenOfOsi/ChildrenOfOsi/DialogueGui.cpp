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
	responseBox1 = new Rectangle(Vector2f(280, 390), 544, 90);
	//responseBox2 = new Rectangle(Vector2f(280, 440), 544, 45);
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
	black = glm::vec3(0, 0, 0);
	red = glm::vec3(50, 0, 0);

}


DialogueGui::~DialogueGui()
{
}

void DialogueGui::loadTexture()
{
	//setFile, load, setFrame
	// read access violation here, some sort of nullptr
	backgroundTex->setFile("DGBackground.png",1);
	swordTex->setFile("DGSword.png",1);
	swordGlowTex->setFile("DGGlowSword.png", 1);
	heartTex->setFile("DGHeart.png", 1);
	heartGlowTex->setFile("DGGlowHeart.png", 1);
	faceTex->setFile("DGFace.png", 1);
	faceGlowTex->setFile("DGGlowFace.png", 1);
	questionTex->setFile("DGQuestion.png", 1);
	questionGlowTex->setFile("DGGlowQuestion.png", 1);
	dialogueBoxTex->setFile("DGDiaBox.png", 1);
	responseBoxTex->setFile("DGResponseBox.png", 1);
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
	//responseBox2->sprite.setTexture(responseBoxTex);
}

void DialogueGui::setPortrait1(Sprite portrait1Sprite)
{
	portrait1->sprite = portrait1Sprite;
}

void DialogueGui::setPortrait2(Sprite portrait2Sprite)
{
	portrait2->sprite = portrait2Sprite;
}

void DialogueGui::setSwordGlow()
{
	heartIcon->sprite.setTexture(heartTex);
	faceIcon->sprite.setTexture(faceTex);
	questionIcon->sprite.setTexture(questionTex);
	swordIcon->sprite.setTexture(swordGlowTex);
}

void DialogueGui::setHeartGlow()
{
	swordIcon->sprite.setTexture(swordTex);
	faceIcon->sprite.setTexture(faceTex);
	questionIcon->sprite.setTexture(questionTex);
	heartIcon->sprite.setTexture(heartGlowTex);
}

void DialogueGui::setFaceGlow()
{
	heartIcon->sprite.setTexture(heartTex);
	swordIcon->sprite.setTexture(swordTex);
	questionIcon->sprite.setTexture(questionTex);
	faceIcon->sprite.setTexture(faceGlowTex);
}

void DialogueGui::setQuestionGlow()
{
	heartIcon->sprite.setTexture(heartTex);
	faceIcon->sprite.setTexture(faceTex);
	swordIcon->sprite.setTexture(swordTex);
	questionIcon->sprite.setTexture(questionGlowTex);
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
//	osi::GameWindow::drawSprite(responseBox2->getX(), responseBox2->getY(), responseBox2->getWidth(), responseBox2->getHeight(), responseBox2->sprite);
	std::string message = DialogueController::getMessage();
	//	////std:://cout << "Message: " << m << std::endl;
	osi::GameWindow::createText(message, 266, 303, 600, 80, black);
	std::vector<std::string> options;
	if (DialogueController::getState() == 1) {
		options = DialogueController::getOptions();
		for (int i = 0; i < options.size(); i++) {
			if (DialogueController::getSelect() == i) {
				osi::GameWindow::createText(options[i], 292, 390 + (18 * i), 544, 45, red);
			}
			else {
				osi::GameWindow::createText(options[i], 292, 390 + (18 * i), 544, 45, black);
			}
			//	////std:://cout << i << ": " << show[i] << std::endl;
		}
	}
	if (DialogueController::getState() == 2) {
		options = DialogueController::getReplyOptions();
		for (int i = 0; i < options.size(); i++) {
			if (DialogueController::getSelect() == i) {
				osi::GameWindow::createText(options[i], 292, 390 + (18 * i), 544, 45, red);
			}
			else {
				osi::GameWindow::createText(options[i], 292, 390 + (18 * i), 544, 45, black);
			}
			//	////std:://cout << i<<": "<<show[i] << std::endl;
		}
	}
}
