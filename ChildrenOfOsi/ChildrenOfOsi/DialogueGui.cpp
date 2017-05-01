#include "stdafx.h"
#include "DialogueGui.h"

DialogueGui::DialogueGui()
{
  this->background_rect = new Rectangle({DialogueGui::BACKGROUND_X, DialogueGui::BACKGROUND_Y}, DialogueGui::BACKGROUND_WIDTH, DialogueGui::BACKGROUND_HEIGHT);
  this->header_rect = new Rectangle({DialogueGui::HEADER_X, DialogueGui::HEADER_Y}, DialogueGui::HEADER_WIDTH, DialogueGui::HEADER_HEIGHT);
  this->icon_sword_rect = new Rectangle({DialogueGui::ICON_SWORD_X, DialogueGui::ICON_SWORD_Y}, DialogueGui::ICON_WIDTH, DialogueGui::ICON_HEIGHT);
  this->icon_heart_rect = new Rectangle({DialogueGui::ICON_HEART_X, DialogueGui::ICON_HEART_Y}, DialogueGui::ICON_WIDTH, DialogueGui::ICON_HEIGHT);
  this->icon_face_rect = new Rectangle({DialogueGui::ICON_FACE_X, DialogueGui::ICON_FACE_Y}, DialogueGui::ICON_WIDTH, DialogueGui::ICON_HEIGHT);
  this->icon_question_rect = new Rectangle({DialogueGui::ICON_QUESTION_X, DialogueGui::ICON_QUESTION_Y}, DialogueGui::ICON_WIDTH, DialogueGui::ICON_HEIGHT);
  this->speaker_left_rect = new Rectangle({DialogueGui::SPEAKER_LEFT_X, DialogueGui::SPEAKER_LEFT_Y}, DialogueGui::SPEAKER_LEFT_WIDTH, DialogueGui::SPEAKER_LEFT_HEIGHT);
  this->speaker_right_rect = new Rectangle({DialogueGui::SPEAKER_RIGHT_X, DialogueGui::SPEAKER_RIGHT_Y}, DialogueGui::SPEAKER_RIGHT_WIDTH, DialogueGui::SPEAKER_RIGHT_HEIGHT);

  this->background_tex = new Texture();
  this->header_tex = new Texture();

  this->icon_sword_tex = new Texture();
  this->icon_sword_glow_tex = new Texture();
  this->icon_heart_tex = new Texture();
  this->icon_heart_glow_tex = new Texture();
  this->icon_face_tex = new Texture();
  this->icon_face_glow_tex = new Texture();
  this->icon_question_tex = new Texture();
  this->icon_question_glow_tex = new Texture();

  this->speaker_left_tex = new Texture();
  this->speaker_right_tex = new Texture();

  /*background = new Rectangle(Vector2f(70, 270), 820, 250);
  swordIcon = new Rectangle(Vector2f(142, 302), 50, 47);
  heartIcon = new Rectangle(Vector2f(142, 349), 50, 47);
  faceIcon = new Rectangle(Vector2f(142, 394), 50, 47);
  questionIcon = new Rectangle(Vector2f(142, 439), 50, 47);
  dialogueBox = new Rectangle(Vector2f(254, 303), 600, 80);
  responseBox1 = new Rectangle(Vector2f(280, 390), 544, 90);
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
  responseBoxTex = new Texture();*/

  text_color_default = glm::vec3(0, 0, 0);
  text_color_selected = glm::vec3(50, 0, 0);
  DialogueController::scroll_control = 0;
}


DialogueGui::~DialogueGui() {}

void DialogueGui::loadTexture()
{
  this->background_tex->setFile(SPRITES_PATH + "Dialogue_Background.png", 1);
  this->header_tex->setFile(SPRITES_PATH + "Dialogue_Header.png", 1);

  this->icon_sword_tex->setFile(SPRITES_PATH + "Dialogue_IconSword.png", 1);
  this->icon_sword_glow_tex->setFile(SPRITES_PATH + "Dialogue_IconSword_Glow.png", 1);
  this->icon_heart_tex->setFile(SPRITES_PATH + "Dialogue_IconHeart.png", 1);
  this->icon_heart_glow_tex->setFile(SPRITES_PATH + "Dialogue_IconHeart_Glow.png", 1);
  this->icon_face_tex->setFile(SPRITES_PATH + "Dialogue_IconFace.png", 1);
  this->icon_face_glow_tex->setFile(SPRITES_PATH + "Dialogue_IconFace_Glow.png", 1);
  this->icon_question_tex->setFile(SPRITES_PATH + "Dialogue_IconQuestion.png", 1);
  this->icon_question_glow_tex->setFile(SPRITES_PATH + "Dialogue_IconQuestion_Glow.png", 1);

  /*backgroundTex->setFile("DGBackground.png", 1);
  swordTex->setFile("DGSword.png", 1);
  swordGlowTex->setFile("DGGlowSword.png", 1);
  heartTex->setFile("DGHeart.png", 1);
  heartGlowTex->setFile("DGGlowHeart.png", 1);
  faceTex->setFile("DGFace.png", 1);
  faceGlowTex->setFile("DGGlowFace.png", 1);
  questionTex->setFile("DGQuestion.png", 1);
  questionGlowTex->setFile("DGGlowQuestion.png", 1);
  dialogueBoxTex->setFile("DGDiaBox.png", 1);
  responseBoxTex->setFile("DGResponseBox.png", 1);*/
}

void DialogueGui::setSprite()
{
  this->background_rect->sprite.setTexture(this->background_tex);
  this->header_rect->sprite.setTexture(this->header_tex);
  this->setSwordGlow();

  /*background->sprite.setTexture(backgroundTex);
  swordIcon->sprite.setTexture(swordGlowTex);
  heartIcon->sprite.setTexture(heartTex);
  faceIcon->sprite.setTexture(faceTex);
  questionIcon->sprite.setTexture(questionTex);
  dialogueBox->sprite.setTexture(dialogueBoxTex);
  responseBox1->sprite.setTexture(responseBoxTex);*/
}

void DialogueGui::setSwordGlow()
{
  this->icon_sword_rect->sprite.setTexture(this->icon_sword_glow_tex);
  this->icon_heart_rect->sprite.setTexture(this->icon_heart_tex);
  this->icon_face_rect->sprite.setTexture(this->icon_face_tex);
  this->icon_question_rect->sprite.setTexture(this->icon_question_tex);
}

void DialogueGui::setHeartGlow()
{
  this->icon_sword_rect->sprite.setTexture(this->icon_sword_tex);
  this->icon_heart_rect->sprite.setTexture(this->icon_heart_glow_tex);
  this->icon_face_rect->sprite.setTexture(this->icon_face_tex);
  this->icon_question_rect->sprite.setTexture(this->icon_question_tex);
}

void DialogueGui::setFaceGlow()
{
  this->icon_sword_rect->sprite.setTexture(this->icon_sword_tex);
  this->icon_heart_rect->sprite.setTexture(this->icon_heart_tex);
  this->icon_face_rect->sprite.setTexture(this->icon_face_glow_tex);
  this->icon_question_rect->sprite.setTexture(this->icon_question_tex);
}

void DialogueGui::setQuestionGlow()
{
  this->icon_sword_rect->sprite.setTexture(this->icon_sword_tex);
  this->icon_heart_rect->sprite.setTexture(this->icon_heart_tex);
  this->icon_face_rect->sprite.setTexture(this->icon_face_tex);
  this->icon_question_rect->sprite.setTexture(this->icon_question_glow_tex);
}

void DialogueGui::setLeftSpeaker(Texture *speakerTexture)
{
  this->speaker_left_tex = speakerTexture;
}

void DialogueGui::setRightSpeaker(Texture *speakerTexture)
{
  this->speaker_right_tex = speakerTexture;
}

void DialogueGui::drawGui()
{
  // Draw the dialogue background and icon header
  GameWindow::drawSprite(this->background_rect->getX(), this->background_rect->getY(),
    this->background_rect->getWidth(), this->background_rect->getHeight(), this->background_rect->getSprite());
  GameWindow::drawSprite(this->header_rect->getX(), this->header_rect->getY(),
    this->header_rect->getWidth(), this->header_rect->getHeight(), this->header_rect->getSprite());
  
  // Draw the four topic grouping icons
  GameWindow::drawSprite(this->icon_sword_rect->getX(), this->icon_sword_rect->getY(),
    this->icon_sword_rect->getWidth(), this->icon_sword_rect->getHeight(), this->icon_sword_rect->getSprite());
  GameWindow::drawSprite(this->icon_heart_rect->getX(), this->icon_heart_rect->getY(),
    this->icon_heart_rect->getWidth(), this->icon_heart_rect->getHeight(), this->icon_heart_rect->getSprite());
  GameWindow::drawSprite(this->icon_face_rect->getX(), this->icon_face_rect->getY(),
    this->icon_face_rect->getWidth(), this->icon_face_rect->getHeight(), this->icon_face_rect->getSprite());
  GameWindow::drawSprite(this->icon_question_rect->getX(), this->icon_question_rect->getY(),
    this->icon_question_rect->getWidth(), this->icon_question_rect->getHeight(), this->icon_question_rect->getSprite());

  /*GameWindow::drawSprite(background->getX(), background->getY(), background->getWidth(), background->getHeight(), background->sprite);
  GameWindow::drawSprite(swordIcon->getX(), swordIcon->getY(), swordIcon->getWidth(), swordIcon->getHeight(), swordIcon->sprite);
  GameWindow::drawSprite(heartIcon->getX(), heartIcon->getY(), heartIcon->getWidth(), heartIcon->getHeight(), heartIcon->sprite);
  GameWindow::drawSprite(faceIcon->getX(), faceIcon->getY(), faceIcon->getWidth(), faceIcon->getHeight(), faceIcon->sprite);
  GameWindow::drawSprite(questionIcon->getX(), questionIcon->getY(), questionIcon->getWidth(), questionIcon->getHeight(), questionIcon->sprite);
  GameWindow::drawSprite(dialogueBox->getX(), dialogueBox->getY(), dialogueBox->getWidth(), dialogueBox->getHeight(), dialogueBox->sprite);
  GameWindow::drawSprite(responseBox1->getX(), responseBox1->getY(), responseBox1->getWidth(), responseBox1->getHeight(), responseBox1->sprite);*/

  std::string message = DialogueController::getMessage();
  GameWindow::createText(message, 266, 303, 500, 80, text_color_default);
  std::vector<std::vector<std::string>> options;

  if(DialogueController::getState() == 1) {
    options = DialogueController::getOptions();

    for(int i = 0; i <= 4; i++) {
      if(options.size() <= (DialogueController::scroll_control + i))
        break;
      std::string option_str = replace_str_char(options[DialogueController::scroll_control + i][1], "_", ' ');
      if(option_str.find("Advise To", 0) != string::npos || option_str.find("Ask About", 0) != string::npos)
        option_str += (" " + options[DialogueController::scroll_control + i][3]);
      if(DialogueController::getSelect() == i) {
        GameWindow::createText(option_str, 292, 390 + (18 * i), 544, 45, text_color_selected);
      }
      else {
        GameWindow::createText(option_str, 292, 390 + (18 * i), 544, 45, text_color_default);
      }

    }
  }
  if(DialogueController::getState() == 2) {
    options = DialogueController::getReplyOptions();

    for(int i = 0; i <= 4; i++) {
      if(options.size() <= (DialogueController::scroll_control + i))
        break;
      std::string option_str = replace_str_char(options[DialogueController::scroll_control + i][1], "_", ' ');
      if(option_str.find("Take Advice", 0) != string::npos || option_str.find("Tell About", 0) != string::npos) {
        option_str += (" " + options[DialogueController::scroll_control + i][3]);
      }
      if(DialogueController::getSelect() == i) {
        GameWindow::createText(option_str, 292, 390 + (18 * i), 544, 45, text_color_selected);
      }
      else {
        GameWindow::createText(option_str, 292, 390 + (18 * i), 544, 45, text_color_default);
      }

    }
  }
  if(DialogueController::getState() == 5) {
    GameWindow::createText("Next", 292, 390 + (18 * 1), 544, 45, text_color_selected);
  }
  if(DialogueController::getState() == 6) {
    GameWindow::createText("Next", 292, 390 + (18 * 1), 544, 45, text_color_selected);
  }
  if(DialogueController::getState() == 7) {
    GameWindow::createText("Exit", 292, 390 + (18 * 1), 544, 45, text_color_selected);
  }
  if(DialogueController::getState() == 8) {
    GameWindow::createText("Next", 292, 390 + (18 * 1), 544, 45, text_color_selected);
  }
  if(DialogueController::getState() == 9) {
    GameWindow::createText("Exit", 292, 390 + (18 * 1), 544, 45, text_color_selected);
  }
  if(DialogueController::getState() == 10) {
    GameWindow::createText("Next", 292, 390 + (18 * 1), 544, 45, text_color_selected);
  }
}

/*Removes all appearances of a specified char(charsToRemove) from a
specified string(str)*/
std::string DialogueGui::remove_chars_from_string(string &str, char* charsToRemove)
{
  for(unsigned int i = 0; i < strlen(charsToRemove); ++i) {
    str.erase(remove(str.begin(), str.end(), charsToRemove[i]), str.end());
  }
  return str;
}

/*Replaces all appearances of a specified string(replace) with a
specified char(ch)*/
std::string DialogueGui::replace_str_char(string str, const string& replace, char ch)
{

// set our locator equal to the first appearance of any character in replace
  size_t found = str.find_first_of(replace);

  while(found != string::npos) { // While our position in the sting is in range.
    str[found] = ch; // Change the character at position.
    found = str.find_first_of(replace, found + 1); // Relocate again.
  }

  return str; // return our new string.
}
