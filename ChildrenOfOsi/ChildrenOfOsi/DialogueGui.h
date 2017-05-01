#pragma once

#include "common.h"

#include "AssetInfo.h"
#include "DialogueController.h"
#include "GameWindow.h"
#include "Rectangle.h"

class DialogueGui
{
  private:

  static constexpr float BACKGROUND_X = 160.0F;
  static constexpr float BACKGROUND_Y = 305.0F;
  static constexpr float BACKGROUND_WIDTH = 640.0F;
  static constexpr float BACKGROUND_HEIGHT = 225.0F;

  static constexpr float HEADER_X = 355.0F;
  static constexpr float HEADER_Y = 220.0F;
  static constexpr float HEADER_WIDTH = 250.0F;
  static constexpr float HEADER_HEIGHT = 75.0F;

  static constexpr float ICON_SWORD_X = 0.0F;
  static constexpr float ICON_SWORD_Y = 0.0F;
  static constexpr float ICON_HEART_X = 0.0F;
  static constexpr float ICON_HEART_Y = 0.0F;
  static constexpr float ICON_FACE_X = 0.0F;
  static constexpr float ICON_FACE_Y = 0.0F;
  static constexpr float ICON_QUESTION_X = 0.0F;
  static constexpr float ICON_QUESTION_Y = 0.0F;
  static constexpr float ICON_WIDTH = 30.0F;
  static constexpr float ICON_HEIGHT = 30.0F;

  static constexpr float SPEAKER_LEFT_X = 0.0F;
  static constexpr float SPEAKER_LEFT_Y = 0.0F;
  static constexpr float SPEAKER_LEFT_WIDTH = 0.0F;
  static constexpr float SPEAKER_LEFT_HEIGHT = 0.0F;

  static constexpr float SPEAKER_RIGHT_X = 0.0F;
  static constexpr float SPEAKER_RIGHT_Y = 0.0F;
  static constexpr float SPEAKER_RIGHT_WIDTH = 0.0F;
  static constexpr float SPEAKER_RIGHT_HEIGHT = 0.0F;

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
  Texture *icon_heart_tex;
  Texture *icon_face_tex;
  Texture *icon_question_tex;
  Texture *speaker_left_tex;
  Texture *speaker_right_tex;

  Rectangle* background;
  Rectangle* swordIcon;
  Rectangle* heartIcon;
  Rectangle* faceIcon;
  Rectangle* questionIcon;
  Rectangle* dialogueBox;
  Rectangle* responseBox1;
  Rectangle* responseBox2;
  Rectangle* portrait1;
  Rectangle* portrait2;

  Texture* backgroundTex;
  Texture* swordTex;
  Texture* swordGlowTex;
  Texture* heartTex;
  Texture* heartGlowTex;
  Texture* faceTex;
  Texture* faceGlowTex;
  Texture* questionTex;
  Texture* questionGlowTex;
  Texture* dialogueBoxTex;
  Texture* responseBoxTex;

  glm::vec3 text_color_default;
  glm::vec3 text_color_selected;

  public:

  DialogueGui();
  ~DialogueGui();

  void loadTexture();
  void setSprite();
  void drawGui();

  void setPortrait1(Sprite portrait1Sprite);
  void setPortrait2(Sprite portrait2Sprite);

  void setSwordGlow();
  void setHeartGlow();
  void setFaceGlow();
  void setQuestionGlow();

  std::string remove_chars_from_string(string &str, char* charsToRemove);
  std::string replace_str_char(string str, const string& replace, char ch);
};
