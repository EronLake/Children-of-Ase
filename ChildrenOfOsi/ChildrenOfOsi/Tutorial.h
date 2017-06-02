#pragma once



#include <cstdint>

#include "Input.h"
#include "Rectangle.h"
#include "Texture.h"

struct Tutorial
{
  public:

  enum class Stage: uint8_t
  {
    GAME_START,
    INTRO01,
    INTRO02,
    DIALOGUE,
    COMBAT,
    NONE
  };

  static void init();
  static void reset();
  static void destroy();

  static Tutorial::Stage getCurrentStage() { return Tutorial::currentStage; }
  static bool isAnyStageActive() { return Tutorial::currentStage != Tutorial::Stage::NONE; }
  static bool isStageActive(Stage stage) { return Tutorial::currentStage == stage; }
  static bool isStageComplete(Stage stage);

  static void launchStage(Stage stage, Input &input, bool pause);
  static void completeStage(Input &input);
  static void drawTutorial();

  private:

  static constexpr float SCREEN_FADE_FILTER_X = 0.0F;
  static constexpr float SCREEN_FADE_FILTER_Y = 0.0F;
  static constexpr float SCREEN_FADE_FILTER_WIDTH = 960.0F;
  static constexpr float SCREEN_FADE_FILTER_HEIGHT = 540.0F;

  static constexpr float GAME_START_POPUP_X = 0.0F;
  static constexpr float GAME_START_POPUP_Y = 0.0F;
  static constexpr float GAME_START_POPUP_WIDTH = 960.0F;
  static constexpr float GAME_START_POPUP_HEIGHT = 540.0F;

  static constexpr float INTRO01_POPUP_X = 460.0F;
  static constexpr float INTRO01_POPUP_Y = 40.0F;
  static constexpr float INTRO01_POPUP_WIDTH = 500.0F;
  static constexpr float INTRO01_POPUP_HEIGHT = 500.0F;

  static constexpr float INTRO02_POPUP_X = 460.0F;
  static constexpr float INTRO02_POPUP_Y = 40.0F;
  static constexpr float INTRO02_POPUP_WIDTH = 500.0F;
  static constexpr float INTRO02_POPUP_HEIGHT = 500.0F;

  static Stage currentStage;
  static bool isPaused;

  static bool completedStageGameStart;
  static bool completedStageIntro01;
  static bool completedStageIntro02;
  static bool completedStageDialogue;
  static bool completedStageCombat;

  static Sprite *screenFadeFilterSprite;
  static Sprite *stageGameStartPopupSprite;
  static Sprite *stageIntro01PopupSprite;
  static Sprite *stageIntro02PopupSprite;
  
  static Texture *screenFaceFilterTex;
  static Texture *stageGameStartPopupTex;
  static Texture *stageIntro01PopupTex;
  static Texture *stageIntro02PopupTex;

  Tutorial() = delete;
  Tutorial(const Tutorial  &) = delete;
  Tutorial(const Tutorial &&) = delete;
  Tutorial   operator=(const Tutorial  &) = delete;
  Tutorial & operator=(const Tutorial &&) = delete;
  ~Tutorial() = delete;
};
