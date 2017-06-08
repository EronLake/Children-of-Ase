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

  this->shango_tex = new Texture();
  this->yemoja_tex = new Texture();
  this->oya_tex = new Texture();
  this->ogun_tex = new Texture();
  this->oshosi_tex = new Texture();

  text_color_default = glm::vec3(0, 0, 0);
  text_color_selected = glm::vec3(50, 0, 0);
  text_color_unselectable = glm::vec3(50,50,50);
  text_color_hide = glm::vec4(0, 0, 0, 0);
  text_color_feedback = glm::vec4(0, 50, 0, 1);
  text_color_neg = glm::vec4(0, 50, 50, 1);
  feed_col;
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

  this->shango_tex->setFile(SPRITES_PATH + "Dialogue_PortraitShango.png", 1);
  this->yemoja_tex->setFile(SPRITES_PATH + "Dialogue_PortraitYemoja.png", 1);
  this->oya_tex->setFile(SPRITES_PATH + "Dialogue_PortraitOya.png", 1);
  this->oshosi_tex->setFile(SPRITES_PATH + "Dialogue_PortraitOgun.png", 1); // Placeholder until we have an Oshosi portrait
  this->ogun_tex->setFile(SPRITES_PATH + "Dialogue_PortraitOgun.png", 1);
}

/**
 * Initializes the sprites of the dialogue GUI.
 */
void DialogueGui::setSprite()
{
  this->background_rect->sprite.setTexture(this->background_tex);
  this->header_rect->sprite.setTexture(this->header_tex);
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

  // Draw character portraits
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
  
  // Draw all of the text
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
        /*if(((CheckClass::isHero(DialogueController::getOther())) ?
          DialogueController::getOptions() : DialogueController::get_soldier_options()).size()
          <= (DialogueController::scroll_control + i)) break;*/
	      if (CheckClass::isHero(DialogueController::getOther())){
		      if(DialogueController::getOptions().size() <= (DialogueController::scroll_control + i))
			    break;
		  }
		  else{
		      Soldier* sol = dynamic_cast<Soldier*>(DialogueController::getOther());
			  if(sol){
			      if(DialogueController::get_soldier_options().size() <= (DialogueController::scroll_control + i))
				      break;
		      }   
			  else { //babalawo case
				  if (DialogueController::get_babalawo_options().size() <= (DialogueController::scroll_control + i))
					  break;
			  }
		  }

		  std::string option_str = "";
		  if(CheckClass::isHero(DialogueController::getOther()))
		     option_str = replace_str_char(DialogueController::getOptions()[DialogueController::scroll_control + i][1], "_", ' ');
		  else{
		     Soldier* s = dynamic_cast<Soldier*>(DialogueController::getOther());
		     if(s)
			     option_str = replace_str_char(DialogueController::get_soldier_options()[DialogueController::scroll_control + i][1], "_", ' ');
			 else//babalawo case
			     option_str = replace_str_char(DialogueController::get_babalawo_options()[DialogueController::scroll_control + i][1], "_", ' ');    
			     
		  }

        /*std::string option_str = replace_str_char(((CheckClass::isHero(DialogueController::getOther())) ?
          DialogueController::getOptions() : DialogueController::get_soldier_options())[DialogueController::scroll_control + i][1], "_", ' ');*/
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

		if (option_str.find("Bribe") != string::npos)
			option_str = "Offer Gift";

		if (option_str.find("Grovel") != string::npos)
			option_str = "Offer Praise";

		if (option_str.find("Ask To Spar") != string::npos)
			option_str = "Request Friendly Spar";

		if (option_str.find("Ask To Duel") != string::npos)
			option_str = "Challenge To Duel";

        GameWindow::createText(option_str,
          DialogueGui::OPTIONS_X, DialogueGui::OPTIONS_Y + (DialogueGui::LINE_SPACING * i),
          DialogueGui::OPTIONS_WIDTH, DialogueGui::OPTIONS_HEIGHT,
          (DialogueController::getSelect() == i) ? this->text_color_selected : avail_color);

		
      }
	  GameWindow::createText("Press 'Q' to Quit",
		  400.50F, 475.50F,
		  DialogueGui::OPTIONS_WIDTH, DialogueGui::OPTIONS_HEIGHT,
		  text_color_default);
	  if (DialogueController::show_advice_feedback)
		  advise_feedback();
	  else
	      show_vis_feedback_2();
	  
      break;
    case 2:
      for(int i = 0; i <= 4; ++i) {
        if(DialogueController::getReplyOptions().size() <= (DialogueController::scroll_control + i))
          break;

        std::string option_str = replace_str_char(DialogueController::getReplyOptions()[DialogueController::scroll_control + i][1], "_", ' ');
        if(option_str.find("Take Advice", 0) != string::npos || option_str.find("Tell About", 0) != string::npos)
          option_str += (" " + DialogueController::getReplyOptions()[DialogueController::scroll_control + i][3]);

		if (option_str.find("Accept Plea") != string::npos)
			option_str = "Thank";
		if (option_str.find("Accept Bribe") != string::npos)
			option_str = "Accept Gift";

        GameWindow::createText(option_str,
          DialogueGui::OPTIONS_X, DialogueGui::OPTIONS_Y + (DialogueGui::LINE_SPACING * i),
          DialogueGui::OPTIONS_WIDTH, DialogueGui::OPTIONS_HEIGHT,
          (DialogueController::getSelect() == i) ? this->text_color_selected : text_color_default);
      }
	  show_vis_feedback();
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

	  show_vis_feedback();
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
	case 12:
		GameWindow::createText("Next",
			DialogueGui::OPTIONS_X, DialogueGui::OPTIONS_Y + (DialogueGui::LINE_SPACING * 1),
			DialogueGui::OPTIONS_WIDTH, DialogueGui::OPTIONS_HEIGHT,
			text_color_selected);

		GameWindow::createText("+ strength",
			530.50F, 475.50F,
			DialogueGui::OPTIONS_WIDTH, DialogueGui::OPTIONS_HEIGHT,
			glm::vec4(0, 50, 0, 1));
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
      if(DialogueController::getOther()->getName() == "Yemoja")
        this->speaker_right_rect->sprite.setTexture(this->yemoja_tex);
      else if(DialogueController::getOther()->getName() == "Oya")
        this->speaker_right_rect->sprite.setTexture(this->oya_tex);
      else if(DialogueController::getOther()->getName() == "Oshosi")
        this->speaker_right_rect->sprite.setTexture(this->ogun_tex);
      else if(DialogueController::getOther()->getName() == "Ogun")
        this->speaker_right_rect->sprite.setTexture(this->ogun_tex);
		}
		else if (DialogueController::quited_gui == false)
			this->speaker_right_rect->sprite.setTexture(this->icon_question_tex);

		DialogueController::started_conv = true;
		if (DialogueController::quited_gui == true) {
			DialogueController::started_conv = false;
			DialogueController::quited_gui = false;
			this->setSwordGlow();
		}
	}
}

/*displays visual feedback*/
void DialogueGui::show_vis_feedback() {
	std::pair<bool,std::string> p_conv_pt = DialogueController::vis_feedback;
	std::string aff = "";
	std::string notoriety = "";
	std::string strength = "";

	if (p_conv_pt.first) {
		vector<std::shared_ptr<Postcondition>> tmp_succ_post;
		std::string cpoint = p_conv_pt.second;
		auto it_2 = Containers::conv_point_table.find(p_conv_pt.second);
		p_conv_pt.second.append("_1");//append Shango
		auto it = Containers::action_table.find(p_conv_pt.second);
	    if (it_2 != Containers::conv_point_table.end())
		    tmp_succ_post = Containers::conv_point_table[cpoint]->doer_succ_postconds;
		else if (it != Containers::action_table.end())	
			tmp_succ_post = Containers::action_table[p_conv_pt.second]->doer_succ_postconds;
		
		for (int i = 0; i < tmp_succ_post.size(); ++i) {
			int type = tmp_succ_post[i]->get_rel_type();
			//Postcondition* pos = tmp_succ_post[i].get();
			float util = tmp_succ_post[i]->get_utility(DialogueController::player, DialogueController::player);
			if (type == 6) {//strength
				strength = "+ Strength";
			}
		    else if (type == 7) {//affinity
				aff = "+ Affinity";
			}
			else if (type == 8) {//notoriety
				notoriety = "+ Notoriety";
			}

			else if (type == 9) {//strength
				strength = "- Strength";
			}

			else if (type == 10) {//affinity
								  //if ((util * -1) > 0)
				aff = "- Affinity";
			}

			else if (type == 11) {//notoriety
				notoriety = "- Notoriety";
			}
		}
	}
	else {
		vector<std::shared_ptr<Postcondition>> tmp_fail_post;
		std::string cpoint = p_conv_pt.second;
		auto it_2 = Containers::conv_point_table.find(p_conv_pt.second);
		p_conv_pt.second.append("_1");//append Shango
		auto it = Containers::action_table.find(p_conv_pt.second);
		if (it_2 != Containers::conv_point_table.end())
		    tmp_fail_post = Containers::conv_point_table[cpoint]->doer_fail_postconds;
		else if (it != Containers::action_table.end())
			tmp_fail_post = Containers::action_table[p_conv_pt.second]->doer_fail_postconds;

		for (int i = 0; i < tmp_fail_post.size(); ++i) {
			int type = tmp_fail_post[i]->get_rel_type();
			//Postcondition* pos = tmp_fail_post[i].get();
			float util = tmp_fail_post[i]->get_utility(DialogueController::player, DialogueController::player);
			if (type == 6) {//strength
				strength = "+ Strength";
			}
		    else if (type == 7) {//affinity
					aff = "+ Affinity";
			}
			else if (type == 8) {//notoriety
					notoriety = "+ Notoriety";
			}

			else if (type == 9) {//strength
					strength = "- Strength";
			}

			else if (type == 10) {//affinity
				//if ((util * -1) > 0)
					aff = "- Affinity";
			}

			else if (type == 11) {//notoriety
					notoriety = "- Notoriety";
			}
		}

	}
	if (DialogueController::feedback_timer > 0) {
		if(aff.find('+') != string::npos)
			feed_col = glm::vec4(0, 50, 0, 1);
		else 
			feed_col = glm::vec4(0, 50, 50, 1);
		GameWindow::createText(aff,
			530.50F, 425.50F,
			DialogueGui::OPTIONS_WIDTH, DialogueGui::OPTIONS_HEIGHT,
			feed_col);

		if (notoriety.find('+') != string::npos)
			feed_col = glm::vec4(0, 50, 0, 1);
		else
			feed_col = glm::vec4(0, 50, 50, 1);
		GameWindow::createText(notoriety,
			530.50F, 450.50F,
			DialogueGui::OPTIONS_WIDTH, DialogueGui::OPTIONS_HEIGHT,
			feed_col);

		if (strength.find('+') != string::npos)
			feed_col = glm::vec4(0, 50, 0, 1);
		else
			feed_col = glm::vec4(0, 50, 50, 1);
		GameWindow::createText(strength,
			530.50F, 475.50F,
			DialogueGui::OPTIONS_WIDTH, DialogueGui::OPTIONS_HEIGHT,
			feed_col);
			--DialogueController::feedback_timer;
	}
	else {
		GameWindow::createText("",
			450.50F, 475.50F,
			DialogueGui::OPTIONS_WIDTH, DialogueGui::OPTIONS_HEIGHT,
			text_color_hide);

		GameWindow::createText("",
			450.50F, 475.50F,
			DialogueGui::OPTIONS_WIDTH, DialogueGui::OPTIONS_HEIGHT,
			text_color_hide);

		GameWindow::createText("",
			450.50F, 475.50F,
			DialogueGui::OPTIONS_WIDTH, DialogueGui::OPTIONS_HEIGHT,
			text_color_hide);
	}
}

/*displays visual feedback*/
void DialogueGui::show_vis_feedback_2() {
	std::pair<bool, std::string> p_conv_pt = DialogueController::vis_feedback;
	std::string aff = "";
	std::string notoriety = "";
	std::string strength = "";

	if (p_conv_pt.first) {
		vector<std::shared_ptr<Postcondition>> tmp_succ_post;
		std::string cpoint = p_conv_pt.second;
		auto it_2 = Containers::conv_point_table.find(p_conv_pt.second);
		p_conv_pt.second.append("_1");//append Shango
		auto it = Containers::action_table.find(p_conv_pt.second);
	    if (it_2 != Containers::conv_point_table.end())
		    tmp_succ_post = Containers::conv_point_table[cpoint]->doer_succ_postconds;
		else if (it != Containers::action_table.end())
			tmp_succ_post = Containers::action_table[p_conv_pt.second]->doer_succ_postconds;
		
		for (int i = 0; i < tmp_succ_post.size(); ++i) {
			int type = tmp_succ_post[i]->get_rel_type();
			//Postcondition* pos = tmp_succ_post[i].get();
			float util = tmp_succ_post[i]->get_utility(DialogueController::player, DialogueController::player);
			if (type == 6) {//strength
				strength = "+ Strength";
			}
			else if (type == 7) {//affinity
				aff = "+ Affinity";
			}
			else if (type == 8) {//notoriety
				notoriety = "+ Notoriety";
			}

			else if (type == 9) {//strength
				strength = "- Strength";
			}

			else if (type == 10) {//affinity
								  //if ((util * -1) > 0)
				aff = "- Affinity";
			}

			else if (type == 11) {//notoriety
				notoriety = "- Notoriety";
			}
		}
	}
	else {
		vector<std::shared_ptr<Postcondition>> tmp_fail_post;
		std::string cpoint = p_conv_pt.second;
		auto it_2 = Containers::conv_point_table.find(p_conv_pt.second);
		p_conv_pt.second.append("_1");//append Shango
		auto it = Containers::action_table.find(p_conv_pt.second);
		if (it_2 != Containers::conv_point_table.end())
			tmp_fail_post = Containers::conv_point_table[cpoint]->doer_fail_postconds;
		else if (it != Containers::action_table.end())
			tmp_fail_post = Containers::action_table[p_conv_pt.second]->doer_fail_postconds;
		for (int i = 0; i < tmp_fail_post.size(); ++i) {
			int type = tmp_fail_post[i]->get_rel_type();
			//Postcondition* pos = tmp_fail_post[i].get();
			float util = tmp_fail_post[i]->get_utility(DialogueController::player, DialogueController::player);
			if (type == 6) {//strength
				strength = "+ Strength";
			}
			else if (type == 7) {//affinity
				aff = "+ Affinity";
			}
			else if (type == 8) {//notoriety
				notoriety = "+ Notoriety";
			}

			else if (type == 9) {//strength
				strength = "- Strength";
			}

			else if (type == 10) {//affinity
								  //if ((util * -1) > 0)
				aff = "- Affinity";
			}

			else if (type == 11) {//notoriety
				notoriety = "- Notoriety";
			}
		}

	}
	if (DialogueController::feedback_timer_2 > 0) {
		if (aff.find('+') != string::npos)
			feed_col = glm::vec4(0, 50, 0, 1);
		else
			feed_col = glm::vec4(0, 50, 50, 1);
		GameWindow::createText(aff,
			530.50F, 425.50F,
			DialogueGui::OPTIONS_WIDTH, DialogueGui::OPTIONS_HEIGHT,
			feed_col);

		if (notoriety.find('+') != string::npos)
			feed_col = glm::vec4(0, 50, 0, 1);
		else
			feed_col = glm::vec4(0, 50, 50, 1);
		GameWindow::createText(notoriety,
			530.50F, 450.50F,
			DialogueGui::OPTIONS_WIDTH, DialogueGui::OPTIONS_HEIGHT,
			feed_col);

		if (strength.find('+') != string::npos)
			feed_col = glm::vec4(0, 50, 0, 1);
		else
			feed_col = glm::vec4(0, 50, 50, 1);
		GameWindow::createText(strength,
			530.50F, 475.50F,
			DialogueGui::OPTIONS_WIDTH, DialogueGui::OPTIONS_HEIGHT,
			feed_col);
		--DialogueController::feedback_timer_2;
	}
	else {
		GameWindow::createText("",
			450.50F, 475.50F,
			DialogueGui::OPTIONS_WIDTH, DialogueGui::OPTIONS_HEIGHT,
			text_color_hide);

		GameWindow::createText("",
			450.50F, 475.50F,
			DialogueGui::OPTIONS_WIDTH, DialogueGui::OPTIONS_HEIGHT,
			text_color_hide);

		GameWindow::createText("",
			450.50F, 475.50F,
			DialogueGui::OPTIONS_WIDTH, DialogueGui::OPTIONS_HEIGHT,
			text_color_hide);
	}
}

void DialogueGui::advise_feedback() {
	std::string aff = "";
	std::string notoriety = "";
	std::string strength = "";
	//if failed advice
	if (DialogueController::show_advice_feedback == 1) {
		aff = "";
		notoriety = "- Notoriety";
		strength = "";
	}
	//if success advice
	if (DialogueController::show_advice_feedback == 2) {
		aff = "+ Affinity";
		notoriety = "+ Notoriety";
		strength = "+ Strength";
	}
	if (DialogueController::feedback_timer > 0 && DialogueController::getState() == 1) {
		if (aff.find('+') != string::npos)
			feed_col = glm::vec4(0, 50, 0, 1);
		else
			feed_col = glm::vec4(0, 50, 50, 1);
		GameWindow::createText(aff,
			530.50F, 425.50F,
			DialogueGui::OPTIONS_WIDTH, DialogueGui::OPTIONS_HEIGHT,
			feed_col);

		if (notoriety.find('+') != string::npos)
			feed_col = glm::vec4(0, 50, 0, 1);
		else
			feed_col = glm::vec4(0, 50, 50, 1);
		GameWindow::createText(notoriety,
			530.50F, 450.50F,
			DialogueGui::OPTIONS_WIDTH, DialogueGui::OPTIONS_HEIGHT,
			feed_col);

		if (strength.find('+') != string::npos)
			feed_col = glm::vec4(0, 50, 0, 1);
		else
			feed_col = glm::vec4(0, 50, 50, 1);
		GameWindow::createText(strength,
			530.50F, 475.50F,
			DialogueGui::OPTIONS_WIDTH, DialogueGui::OPTIONS_HEIGHT,
			feed_col);

		--DialogueController::feedback_timer;
	}
	else {
		GameWindow::createText("",
			450.50F, 475.50F,
			DialogueGui::OPTIONS_WIDTH, DialogueGui::OPTIONS_HEIGHT,
			text_color_hide);

		GameWindow::createText("",
			450.50F, 475.50F,
			DialogueGui::OPTIONS_WIDTH, DialogueGui::OPTIONS_HEIGHT,
			text_color_hide);

		GameWindow::createText("",
			450.50F, 475.50F,
			DialogueGui::OPTIONS_WIDTH, DialogueGui::OPTIONS_HEIGHT,
			text_color_hide);

		DialogueController::show_advice_feedback = 0;
	}

}
