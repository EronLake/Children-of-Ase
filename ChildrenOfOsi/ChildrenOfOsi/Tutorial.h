#pragma once

#include "stdafx.h"

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
  static void updateStage(Stage stage);
  static void completeStage(Input &input);
  static void drawTutorial();

  private:

  static constexpr float GAME_START_POPUP_X = 0.0F;
  static constexpr float GAME_START_POPUP_Y = 0.0F;
  static constexpr float GAME_START_POPUP_WIDTH = 960.0F;
  static constexpr float GAME_START_POPUP_HEIGHT = 540.0F;

  static Stage currentStage;
  static bool isPaused;

  static bool completedStageGameStart;
  static bool completedStageDialogue;
  static bool completedStageCombat;

  static Sprite *stageGameStartPopupSprite;
  
  static Texture *stageGameStartPopupTex;

  Tutorial() = delete;
  Tutorial(const Tutorial  &) = delete;
  Tutorial(const Tutorial &&) = delete;
  Tutorial   operator=(const Tutorial  &) = delete;
  Tutorial & operator=(const Tutorial &&) = delete;
  ~Tutorial() = delete;
};
