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

  static void init();
  static void reset();
  static void destroy();

  static bool isAnyStageActive() { return Tutorial::currentStage != Tutorial::Stage::NONE; }
  static bool isStageActive(Stage stage) { return Tutorial::currentStage == stage; }
  static bool isStageComplete(Stage stage);

  static void launchStage(Stage stage, Input &input, bool pause);
  static void updateStage(Stage stage);
  static void completeStage(Input &input);
  static void drawTutorial();

  private:

  static Stage currentStage;
  static bool isPaused;

  static bool completedStageGameStart;
  static bool completedStageDialogue;
  static bool completedStageCombat;

  Tutorial() = delete;
  Tutorial(const Tutorial  &) = delete;
  Tutorial(const Tutorial &&) = delete;
  Tutorial   operator=(const Tutorial  &) = delete;
  Tutorial & operator=(const Tutorial &&) = delete;
  ~Tutorial() = delete;

  static void startStageGameStart();
  static void startStageDialogue();
  static void startStageCombat();
};
