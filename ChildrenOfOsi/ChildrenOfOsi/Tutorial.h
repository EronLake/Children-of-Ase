#pragma once

#include "stdafx.h"

#include <cstdint>

#include "Input.h"

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

  static bool isAnyStageActive() { return Tutorial::currentStage != Tutorial::Stage::NONE; }
  static bool isStageActive(Stage stage) { return Tutorial::currentStage == stage; }
  static void launchStage(Stage stage, Input &input, bool pause);
  static void completeStage();
  static void drawTutorial();

  private:

  static Stage currentStage;
  static bool isPaused;

  Tutorial() = delete;
  Tutorial(const Tutorial  &) = delete;
  Tutorial(const Tutorial &&) = delete;
  Tutorial   operator=(const Tutorial  &) = delete;
  Tutorial & operator=(const Tutorial &&) = delete;
  ~Tutorial() = delete;

  static void handleStageGameStart();
  static void handleStageDialogue();
  static void handleStageCombat();
};
