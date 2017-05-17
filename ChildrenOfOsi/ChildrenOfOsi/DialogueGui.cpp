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
  this->speaker_left_sprite = nullptr;
  this->speaker_right_sprite = nullptr;

 // this->shango_sprite = new Sprite();
  //this->yemoja_sprite = new Sprite();
  //this->oya_sprite = new Sprite();
  //this->oshosi_sprite = new Sprite();
  //this->ogun_sprite = new Sprite();

  this->shango_tex = new Texture();
  this->yemoja_tex = new Texture();
  this->oya_tex = new Texture();
  this->ogun_tex = new Texture();
  this->oshosi_tex = new Texture();

  //this->shango_sprite->setTexture(shango_tex);
  //this->yemoja_sprite->setTexture(yemoja_tex);
  //this->oya_sprite->setTexture(oya_tex);
  //this->oshosi_sprite->setTexture(oshosi_tex);
  //this->ogun_sprite->setTexture(ogun_tex);



  text_color_default = glm::vec3(0, 0, 0);
  text_color_selected = glm::vec3(50, 0, 0);
  text_color_unselectable = glm::vec3(50,50,50);
  DialogueController::scroll_control = 0;
}


DialogueGui::~DialogueGui()
{
  delete this->background_rect;
  delete this->header_rect;
  delete this->icon_sword_rect;
  delete this->icon_heart_rect;
  delete this->icon_face_rect;
  delete this->icon_question_rect;
  delete this->speaker_left_rect;
  delete this->speaker_right_rect;

  delete this->background_tex;
  delete this->header_tex;
  delete this->icon_sword_glow_tex;
  delete this->icon_sword_tex;
  delete this->icon_heart_tex;
  delete this->icon_heart_glow_tex;
  delete this->icon_face_tex;
  delete this->icon_face_glow_tex;
  delete this->icon_question_tex;
  delete this->icon_question_glow_tex;

  delete this->shango_tex;
  delete this->yemoja_tex;
  delete this->oya_tex;
  delete this->oshosi_tex;
  delete this->ogun_tex;

}

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

  this->yemoja_tex->setFile(SPRITES_PATH + "Dialogue_portrait_yemoja_1.png", 1);
  this->shango_tex->setFile(SPRITES_PATH + "Dialogue_portrait_yemoja_1.png", 1);
  this->oya_tex->setFile(SPRITES_PATH + "Dialogue_portrait_oya.png", 1);
}

void DialogueGui::setSprite()
{
  this->background_rect->sprite.setTexture(this->background_tex);
  this->header_rect->sprite.setTexture(this->header_tex);
  //this->shango_sprite->setTexture(this->shango_tex);
  this->setSwordGlow();
}

/**
 * Sets the current topic filter selection to the sword icon.
 */
void DialogueGui::setSwordGlow()
{
  this->icon_sword_rect->sprite.setTexture(this->icon_sword_glow_tex);
  this->icon_heart_rect->sprite.setTexture(this->icon_heart_tex);
  this->icon_face_rect->sprite.setTexture(this->icon_face_tex);
  this->icon_question_rect->sprite.setTexture(this->icon_question_tex);
}

/**
 * Sets the current topic filter selection to the heart icon.
 */
void DialogueGui::setHeartGlow()
{
  this->icon_sword_rect->sprite.setTexture(this->icon_sword_tex);
  this->icon_heart_rect->sprite.setTexture(this->icon_heart_glow_tex);
  this->icon_face_rect->sprite.setTexture(this->icon_face_tex);
  this->icon_question_rect->sprite.setTexture(this->icon_question_tex);
}

/**
 * Sets the current topic filter selection to the face icon.
 */
void DialogueGui::setFaceGlow()
{
  this->icon_sword_rect->sprite.setTexture(this->icon_sword_tex);
  this->icon_heart_rect->sprite.setTexture(this->icon_heart_tex);
  this->icon_face_rect->sprite.setTexture(this->icon_face_glow_tex);
  this->icon_question_rect->sprite.setTexture(this->icon_question_tex);
}

/**
 * Sets the current topic filter selection to the question mark icon.
 */
void DialogueGui::setQuestionGlow()
{
  this->icon_sword_rect->sprite.setTexture(this->icon_sword_tex);
  this->icon_heart_rect->sprite.setTexture(this->icon_heart_tex);
  this->icon_face_rect->sprite.setTexture(this->icon_face_tex);
  this->icon_question_rect->sprite.setTexture(this->icon_question_glow_tex);
}

/**
 * Sets the sprite for the left-side speaker portrait to that specified.
 *
 * Param speakerSprite: The new sprite to be used
 */
void DialogueGui::setLeftSpeaker(Sprite *speakerSprite)
{
  this->speaker_left_sprite = speakerSprite;
}

/**
 * Sets the sprite for the right-side speaker portrait to that specified.
 *
 * Param speakerSprite: The new sprite to be used
 */
void DialogueGui::setRightSpeaker(Sprite *speakerSprite)
{
  this->speaker_right_sprite = speakerSprite;
}

/**
 * Draws all elements of the dialogue GUI.
 */
void DialogueGui::drawGui()
{
  set_character_portrait_tex();

  //Draws character portraits
  GameWindow::drawSprite(this->speaker_left_rect->getX(), this->speaker_left_rect->getY(),
	  this->speaker_left_rect->getWidth(), this->speaker_left_rect->getHeight(),
	  this->speaker_left_rect->getSprite());

  GameWindow::drawSprite(this->speaker_right_rect->getX(), this->speaker_right_rect->getY(),
	  this->speaker_right_rect->getWidth(), this->speaker_right_rect->getHeight(),
	  this->speaker_right_rect->getSprite());

  // Draw the dialogue background and icon header
  GameWindow::drawSprite(this->header_rect->getX(), this->header_rect->getY(),
    this->header_rect->getWidth(), this->header_rect->getHeight(), this->header_rect->getSprite());
  GameWindow::drawSprite(this->background_rect->getX(), this->background_rect->getY(),
    this->background_rect->getWidth(), this->background_rect->getHeight(), this->background_rect->getSprite());

  // Draw the four topic grouping icons
  GameWindow::drawSprite(this->icon_sword_rect->getX(), this->icon_sword_rect->getY(),
    this->icon_sword_rect->getWidth(), this->icon_sword_rect->getHeight(), this->icon_sword_rect->getSprite());
  GameWindow::drawSprite(this->icon_heart_rect->getX(), this->icon_heart_rect->getY(),
    this->icon_heart_rect->getWidth(), this->icon_heart_rect->getHeight(), this->icon_heart_rect->getSprite());
  GameWindow::drawSprite(this->icon_face_rect->getX(), this->icon_face_rect->getY(),
    this->icon_face_rect->getWidth(), this->icon_face_rect->getHeight(), this->icon_face_rect->getSprite());
  GameWindow::drawSprite(this->icon_question_rect->getX(), this->icon_question_rect->getY(),
    this->icon_question_rect->getWidth(), this->icon_question_rect->getHeight(), this->icon_question_rect->getSprite());


  
  this->drawGuiText();
}

/**
 * A helper function to handle drawing of the text of the dialogue UI.
 */
void DialogueGui::drawGuiText()
{
  GameWindow::createText(DialogueController::getMessage(),
    DialogueGui::MESSAGE_X, DialogueGui::MESSAGE_Y,
    DialogueGui::MESSAGE_WIDTH, DialogueGui::MESSAGE_HEIGHT,
    text_color_default);

  switch(DialogueController::getState()) {
    case 1:
      for(int i = 0; i <= 4; i++) {
        if(((CheckClass::isHero(DialogueController::getOther())) ?
          DialogueController::getOptions() : DialogueController::get_soldier_options()).size()
          <= (DialogueController::scroll_control + i)) break;

        std::string option_str = replace_str_char(((CheckClass::isHero(DialogueController::getOther())) ?
          DialogueController::getOptions() : DialogueController::get_soldier_options())[DialogueController::scroll_control + i][1], "_", ' ');
        if(option_str.find("Advise To", 0) != string::npos || option_str.find("Ask About", 0) != string::npos)
          option_str += (" " + ((CheckClass::isHero(DialogueController::getOther())) ?
            DialogueController::getOptions() : DialogueController::get_soldier_options())[DialogueController::scroll_control + i][3]);

		//sets options to color signifying unselectability if player does not meet requirements
		glm::vec3 avail_color = text_color_default;
		if ((CheckClass::isHero(DialogueController::getOther()))) {
			std::string is_selectable;
			is_selectable = DialogueController::getOptions()[DialogueController::scroll_control + i][4];
			if (is_selectable == "0")
				avail_color = text_color_unselectable;
		}

        GameWindow::createText(option_str,
          DialogueGui::OPTIONS_X, DialogueGui::OPTIONS_Y + (DialogueGui::LINE_SPACING * i),
          DialogueGui::OPTIONS_WIDTH, DialogueGui::OPTIONS_HEIGHT,
          (DialogueController::getSelect() == i) ? this->text_color_selected : avail_color);
      }

      break;
    case 2:
      for(int i = 0; i <= 4; ++i) {
        if(DialogueController::getReplyOptions().size() <= (DialogueController::scroll_control + i))
          break;

        std::string option_str = replace_str_char(DialogueController::getReplyOptions()[DialogueController::scroll_control + i][1], "_", ' ');
        if(option_str.find("Take Advice", 0) != string::npos || option_str.find("Tell About", 0) != string::npos)
          option_str += (" " + DialogueController::getReplyOptions()[DialogueController::scroll_control + i][3]);

        GameWindow::createText(option_str,
          DialogueGui::OPTIONS_X, DialogueGui::OPTIONS_Y + (DialogueGui::LINE_SPACING * i),
          DialogueGui::OPTIONS_WIDTH, DialogueGui::OPTIONS_HEIGHT,
          (DialogueController::getSelect() == i) ? this->text_color_selected : text_color_default);
      }

      break;
    case 5:
      GameWindow::createText("Next",
        DialogueGui::OPTIONS_X, DialogueGui::OPTIONS_Y + (DialogueGui::LINE_SPACING * 1),
        DialogueGui::OPTIONS_WIDTH, DialogueGui::OPTIONS_HEIGHT,
        text_color_selected);
      break;
    case 6:
      GameWindow::createText("Next",
        DialogueGui::OPTIONS_X, DialogueGui::OPTIONS_Y + (DialogueGui::LINE_SPACING * 1),
        DialogueGui::OPTIONS_WIDTH, DialogueGui::OPTIONS_HEIGHT,
        text_color_selected);
      break;
    case 7:
      GameWindow::createText("Exit",
        DialogueGui::OPTIONS_X, DialogueGui::OPTIONS_Y + (DialogueGui::LINE_SPACING * 1),
        DialogueGui::OPTIONS_WIDTH, DialogueGui::OPTIONS_HEIGHT,
        text_color_selected);
      break;
    case 8:
      GameWindow::createText("Next",
        DialogueGui::OPTIONS_X, DialogueGui::OPTIONS_Y + (DialogueGui::LINE_SPACING * 1),
        DialogueGui::OPTIONS_WIDTH, DialogueGui::OPTIONS_HEIGHT,
        text_color_selected);
      break;
    case 9:
      GameWindow::createText("Exit",
        DialogueGui::OPTIONS_X, DialogueGui::OPTIONS_Y + (DialogueGui::LINE_SPACING * 1),
        DialogueGui::OPTIONS_WIDTH, DialogueGui::OPTIONS_HEIGHT,
        text_color_selected);
      break;
    case 10:
      GameWindow::createText("Next",
        DialogueGui::OPTIONS_X, DialogueGui::OPTIONS_Y + (DialogueGui::LINE_SPACING * 1),
        DialogueGui::OPTIONS_WIDTH, DialogueGui::OPTIONS_HEIGHT,
        text_color_selected);
      break;
	case 11:
		GameWindow::createText("Next",
			DialogueGui::OPTIONS_X, DialogueGui::OPTIONS_Y + (DialogueGui::LINE_SPACING * 1),
			DialogueGui::OPTIONS_WIDTH, DialogueGui::OPTIONS_HEIGHT,
			text_color_selected);
		break;
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

/*Sets the textures for the speaker left and right rect sprites
to the appropriate ones based on who is engaging in dialogue*/
void DialogueGui::set_character_portrait_tex() {
	if (DialogueController::started_conv == false) {
		this->speaker_left_rect->sprite.setTexture(this->shango_tex);
		Hero* temp_hero = CheckClass::isHero(DialogueController::getOther());
		if (temp_hero) {
			if (DialogueController::getOther()->getName() == "Yemoja") {
				this->speaker_right_rect->sprite.setTexture(this->yemoja_tex);
			}
			else if (DialogueController::getOther()->getName() == "Oya") {
				this->speaker_right_rect->sprite.setTexture(this->oya_tex);
			}
		}
		else if (DialogueController::quited_gui == false)
			this->speaker_right_rect->sprite.setTexture(this->icon_question_tex);

		DialogueController::started_conv = true;
		if (DialogueController::quited_gui == true) {
			DialogueController::started_conv = false;
			DialogueController::quited_gui = false;
		}
	}
}
