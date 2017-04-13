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
	DialogueController::set_scroll_control(0);

}


DialogueGui::~DialogueGui()
{
}

void DialogueGui::loadTexture()
{
	//setFile, load, setFrame
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
	GameWindow::drawSprite(background->getX(), background->getY(), background->getWidth(), background->getHeight(), background->sprite);
	GameWindow::drawSprite(swordIcon->getX(), swordIcon->getY(), swordIcon->getWidth(), swordIcon->getHeight(), swordIcon->sprite);
	GameWindow::drawSprite(heartIcon->getX(), heartIcon->getY(), heartIcon->getWidth(), heartIcon->getHeight(), heartIcon->sprite);
	GameWindow::drawSprite(faceIcon->getX(), faceIcon->getY(), faceIcon->getWidth(), faceIcon->getHeight(), faceIcon->sprite);
	GameWindow::drawSprite(questionIcon->getX(), questionIcon->getY(), questionIcon->getWidth(), questionIcon->getHeight(), questionIcon->sprite);
	GameWindow::drawSprite(dialogueBox->getX(), dialogueBox->getY(), dialogueBox->getWidth(), dialogueBox->getHeight(), dialogueBox->sprite);
	GameWindow::drawSprite(responseBox1->getX(), responseBox1->getY(), responseBox1->getWidth(), responseBox1->getHeight(), responseBox1->sprite);
  // GameWindow::drawSprite(responseBox2->getX(), responseBox2->getY(), responseBox2->getWidth(), responseBox2->getHeight(), responseBox2->sprite);
	std::string message = DialogueController::getMessage();
	int j = 0;
	GameWindow::createText(message, 266, 303, 500, 80, black);
	std::vector<std::string> options;
	if (DialogueController::getState() == 1) {
		options = DialogueController::getOptions();
		if (options.size() <= 4)
			j = options.size();
		else
			j = 4;
		for (int i = 0; i <= 4; i++) {
			if ( options.size() <= (DialogueController::scroll_control + i))
				break;
			if (DialogueController::getSelect() == i) {
				GameWindow::createText(replace_str_char(options[DialogueController::scroll_control + i], "_", ' '), 292, 390 + (18 * i), 544, 45, red);
			}
			else {
				GameWindow::createText(replace_str_char(options[DialogueController::scroll_control + i], "_", ' '), 292, 390 + (18 * i), 544, 45, black);
			}

		}
	}
	if (DialogueController::getState() == 2) {
		options = DialogueController::getReplyOptions();
		//DialogueController::scroll_control = 0;
		if (options.size() <= DialogueController::scroll_control)
			j = options.size();
		else
			j = 4;
		for (int i = 0; i <= 4; i++) {
			if (options.size() <= (DialogueController::scroll_control + i))
				break;
			if (DialogueController::getSelect() == i) {
			GameWindow::createText(replace_str_char(options[DialogueController::scroll_control + i], "_",' '), 292, 390 + (18 * i), 544, 45, red);
			}
			else {
				GameWindow::createText(replace_str_char(options[DialogueController::scroll_control + i], "_", ' '), 292, 390 + (18 * i), 544, 45, black);
			}

		}
	}
}

std::string DialogueGui::remove_chars_from_string(string &str, char* charsToRemove) {
	for (unsigned int i = 0; i < strlen(charsToRemove); ++i) {
		str.erase(remove(str.begin(), str.end(), charsToRemove[i]), str.end());
	}
	return str;
}

std::string DialogueGui::replace_str_char(string str, const string& replace, char ch) {

	// set our locator equal to the first appearance of any character in replace
	size_t found = str.find_first_of(replace);

	while (found != string::npos) { // While our position in the sting is in range.
		str[found] = ch; // Change the character at position.
		found = str.find_first_of(replace, found + 1); // Relocate again.
	}

	return str; // return our new string.
}
