#pragma once

#include "common.h"

#include "AssetInfo.h"
#include "DialogueController.h"
#include "GameWindow.h"
#include "Rectangle.h"

class DialogueGui
{
  private:

  static constexpr float BACKGROUND_X = 10.0F;
  static constexpr float BACKGROUND_Y = 316.0F;
  static constexpr float BACKGROUND_WIDTH = 940.0F;
  static constexpr float BACKGROUND_HEIGHT = 220.0F;

  static constexpr float HEADER_X = 17.5F;
  static constexpr float HEADER_Y = 257.5F;
  static constexpr float HEADER_WIDTH = 250.0F;
  static constexpr float HEADER_HEIGHT = 75.0F;

  static constexpr float ICON_SWORD_X = 60.0F;
  static constexpr float ICON_SWORD_Y = 280.0F;
  static constexpr float ICON_HEART_X = 105.0F;
  static constexpr float ICON_HEART_Y = 280.0F;
  static constexpr float ICON_FACE_X = 150.0F;
  static constexpr float ICON_FACE_Y = 280.0F;
  static constexpr float ICON_QUESTION_X = 195.0F;
  static constexpr float ICON_QUESTION_Y = 280.0F;
  static constexpr float ICON_WIDTH = 30.0F;
  static constexpr float ICON_HEIGHT = 30.0F;

  static constexpr float MESSAGE_X = 32.5F;
  static constexpr float MESSAGE_Y = 343.5F;
  static constexpr float MESSAGE_WIDTH = 895.0F;
  static constexpr float MESSAGE_HEIGHT = -1.0F;

  static constexpr float OPTIONS_X = 52.5F;
  static constexpr float OPTIONS_Y = 420.0F;
  static constexpr float OPTIONS_WIDTH = 575.0F;
  static constexpr float OPTIONS_HEIGHT = -1.0F;

  static constexpr int LINE_SPACING = 18;

  static constexpr float SPEAKER_LEFT_X = 15.0F;
  static constexpr float SPEAKER_LEFT_Y = 20.0F;
  static constexpr float SPEAKER_LEFT_WIDTH = 300.0F;
  static constexpr float SPEAKER_LEFT_HEIGHT = 300.0F;

  static constexpr float SPEAKER_RIGHT_X = 645.0F;
  static constexpr float SPEAKER_RIGHT_Y = 20.0F;
  static constexpr float SPEAKER_RIGHT_WIDTH = 300.0F;
  static constexpr float SPEAKER_RIGHT_HEIGHT = 300.0F;

  Rectangle *background_rect;
  Rectangle *header_rect;
  Rectangle *icon_sword_rect;
  Rectangle *icon_heart_rect;
  Rectangle *icon_face_rect;
  Rectangle *icon_question_rect;
  Rectangle *speaker_left_rect;
  Rectangle *speaker_right_rect;

  Texture *background_tex;
  Texture *header_tex;
  Texture *icon_sword_tex;
  Texture *icon_sword_glow_tex;
  Texture *icon_heart_tex;
  Texture *icon_heart_glow_tex;
  Texture *icon_face_tex;
  Texture *icon_face_glow_tex;
  Texture *icon_question_tex;
  Texture *icon_question_glow_tex;
  Sprite *speaker_left_sprite;
  Sprite *speaker_right_sprite;

  Rectangle* dialogueBox;//remove
  Rectangle* responseBox1;//remove
  Rectangle* responseBox2;//remove

  Texture* dialogueBoxTex;//remove
  Texture* responseBoxTex;//remove

  glm::vec3 text_color_default;
  glm::vec3 text_color_selected;
  glm::vec3 text_color_unselectable;

  void drawGuiText();

  public:

  DialogueGui();
  ~DialogueGui();

  void loadTexture();
  void setSprite();
  void drawGui();
  void set_character_portrait_tex();

  void setLeftSpeaker(Sprite *speakerTexture);
  void setRightSpeaker(Sprite *speakerTexture);

  void setSwordGlow();
  void setHeartGlow();
  void setFaceGlow();
  void setQuestionGlow();

  std::string remove_chars_from_string(string &str, char* charsToRemove);
  std::string replace_str_char(string str, const string& replace, char ch);

  //character portrait textures
  Texture* shango_tex;
  Texture* yemoja_tex;
  Texture* oya_tex;
  Texture* ogun_tex;
  Texture* oshosi_tex;
};
