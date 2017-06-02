#include "stdafx.h"
#include "Tutorial.h"
#include "AssetInfo.h"
#include "GameState.h"
#include "GameWindow.h"

using namespace std;

Tutorial::Stage Tutorial::currentStage = Tutorial::Stage::NONE;
bool Tutorial::isPaused = false;

bool Tutorial::completedStageGameStart = false;
bool Tutorial::completedStageIntro01 = false;
bool Tutorial::completedStageIntro02 = false;
bool Tutorial::completedStageDialogue = false;
bool Tutorial::completedStageCombat = false;

Sprite *Tutorial::screenFadeFilterSprite = nullptr;
Sprite *Tutorial::stageGameStartPopupSprite = nullptr;
Sprite *Tutorial::stageIntro01PopupSprite = nullptr;
Sprite *Tutorial::stageIntro02PopupSprite = nullptr;
Sprite *Tutorial::stageDialoguePopupSprite = nullptr;
Sprite *Tutorial::stageCombatPopupSprite = nullptr;

Texture *Tutorial::screenFaceFilterTex = nullptr;
Texture *Tutorial::stageGameStartPopupTex = nullptr;
Texture *Tutorial::stageIntro01PopupTex = nullptr;
Texture *Tutorial::stageIntro02PopupTex = nullptr;
Texture *Tutorial::stageDialoguePopupTex = nullptr;
Texture *Tutorial::stageCombatPopupTex = nullptr;

/**
 * Initializes the tutorial system.
 */
void Tutorial::init()
{
  Tutorial::screenFadeFilterSprite = new Sprite();
  Tutorial::screenFaceFilterTex = new Texture();
  Tutorial::screenFaceFilterTex->setFile(SPRITES_PATH + "Tutorial_ScreenFadeFilter.png", 1);
  Tutorial::screenFadeFilterSprite->setTexture(Tutorial::screenFaceFilterTex);

  Tutorial::stageGameStartPopupSprite = new Sprite();
  Tutorial::stageGameStartPopupTex = new Texture();
  Tutorial::stageGameStartPopupTex->setFile(SPRITES_PATH + "Tutorial_GameStartPopup.png", 1);
  Tutorial::stageGameStartPopupSprite->setTexture(Tutorial::stageGameStartPopupTex);

  Tutorial::stageIntro01PopupSprite = new Sprite();
  Tutorial::stageIntro01PopupTex = new Texture();
  Tutorial::stageIntro01PopupTex->setFile(SPRITES_PATH + "Tutorial_Intro01Popup.png", 1);
  Tutorial::stageIntro01PopupSprite->setTexture(Tutorial::stageIntro01PopupTex);

  Tutorial::stageIntro02PopupSprite = new Sprite();
  Tutorial::stageIntro02PopupTex = new Texture();
  Tutorial::stageIntro02PopupTex->setFile(SPRITES_PATH + "Tutorial_Intro02Popup.png", 1);
  Tutorial::stageIntro02PopupSprite->setTexture(Tutorial::stageIntro02PopupTex);

  Tutorial::stageDialoguePopupSprite = new Sprite();
  Tutorial::stageDialoguePopupTex = new Texture();
  Tutorial::stageDialoguePopupTex->setFile(SPRITES_PATH + "Tutorial_DialoguePopup.png", 1);
  Tutorial::stageDialoguePopupSprite->setTexture(Tutorial::stageDialoguePopupTex);

  Tutorial::stageCombatPopupSprite = new Sprite();
  Tutorial::stageCombatPopupTex = new Texture();
}

/**
 * Resets the tutorial system. Resources are not deallocated: this function
 * merely resets all the tutorial stages.
 */
void Tutorial::reset()
{
  Tutorial::currentStage = Tutorial::Stage::NONE;
  Tutorial::isPaused = false;

  Tutorial::completedStageGameStart = false;
  Tutorial::completedStageDialogue = false;
  Tutorial::completedStageCombat = false;
}

/**
 * Deallocates all resources used by the tutorial system.
 */
void Tutorial::destroy()
{
  delete Tutorial::stageGameStartPopupSprite;
  delete Tutorial::stageIntro01PopupSprite;
  delete Tutorial::stageIntro02PopupSprite;
  delete Tutorial::stageDialoguePopupSprite;
  delete Tutorial::stageCombatPopupSprite;

  delete Tutorial::stageGameStartPopupTex;
  delete Tutorial::stageIntro01PopupTex;
  delete Tutorial::stageIntro02PopupTex;
  delete Tutorial::stageDialoguePopupTex;
  delete Tutorial::stageCombatPopupTex;
}

/**
 * Returns whether the given stage has been completed for the first time. If
 * queried with the NONE stage, this function will always return false.
 */
bool Tutorial::isStageComplete(Stage stage)
{
  switch(stage) {
    case Tutorial::Stage::GAME_START:
      return Tutorial::completedStageGameStart;
    case Tutorial::Stage::INTRO01:
      return Tutorial::completedStageIntro01;
    case Tutorial::Stage::INTRO02:
      return Tutorial::completedStageIntro02;
    case Tutorial::Stage::DIALOGUE:
      return  Tutorial::completedStageDialogue;
    case Tutorial::Stage::COMBAT:
      return Tutorial::completedStageCombat;
    default:
      return false;
  }
}

/**
 * Begins the specified tutorial stage, optionally pausing the game until it is
 * complete. If a stage is already active, this function will return without
 * changing anything. If called with the NONE stage, this function will
 * interpret that as instructions to instead complete the current stage, if any.
 */
void Tutorial::launchStage(Stage stage, Input &input, bool pause)
{
  if(Tutorial::currentStage != Tutorial::Stage::NONE)
    return;
  else if(stage == Tutorial::Stage::NONE) {
    Tutorial::completeStage(input);
    return;
  }

  Tutorial::currentStage = stage;
  Tutorial::isPaused = pause;

  switch(stage) {
    case Tutorial::Stage::GAME_START:
      input.current_game_state = game_state::main_menu;
      break;
    case Tutorial::Stage::INTRO01:
    case Tutorial::Stage::INTRO02:
    case Tutorial::Stage::DIALOGUE:
    case Tutorial::Stage::COMBAT:
      input.current_game_state = (pause) ?
        game_state::tutorial_pause : game_state::in_game;
      break;
  }
}

/**
 * Completes the current tutorial stage, if any. If the game is paused when
 * this function is called, it will be unpaused.
 */
void Tutorial::completeStage(Input &input)
{
  switch(Tutorial::currentStage) {
    case Tutorial::Stage::GAME_START:
      Tutorial::completedStageGameStart = true;
      break;
    case Tutorial::Stage::INTRO01:
      Tutorial::completedStageIntro01 = true;
      break;
    case Tutorial::Stage::INTRO02:
      Tutorial::completedStageIntro02 = true;
      break;
    case Tutorial::Stage::DIALOGUE:
      Tutorial::completedStageDialogue = true;
      break;
    case Tutorial::Stage::COMBAT:
      Tutorial::completedStageCombat = true;
      break;
  }

  Tutorial::currentStage = Tutorial::Stage::NONE;
  Tutorial::isPaused = false;
  input.current_game_state = game_state::in_game;
}

/**
 * Draws the appropriate tutorial UI elements, if active.
 */
void Tutorial::drawTutorial()
{
  switch(Tutorial::currentStage) {
    case Tutorial::Stage::GAME_START:
      GameWindow::drawSprite(Tutorial::GAME_START_POPUP_X, Tutorial::GAME_START_POPUP_Y,
        Tutorial::GAME_START_POPUP_WIDTH, Tutorial::GAME_START_POPUP_HEIGHT, *Tutorial::stageGameStartPopupSprite);
      break;
    case Tutorial::Stage::INTRO01:
      GameWindow::drawSprite(Tutorial::SCREEN_FADE_FILTER_X, Tutorial::SCREEN_FADE_FILTER_Y,
        Tutorial::SCREEN_FADE_FILTER_WIDTH, Tutorial::SCREEN_FADE_FILTER_HEIGHT, *Tutorial::screenFadeFilterSprite);
      GameWindow::drawSprite(Tutorial::INTRO01_POPUP_X, Tutorial::INTRO01_POPUP_Y,
        Tutorial::INTRO01_POPUP_WIDTH, Tutorial::INTRO01_POPUP_HEIGHT, *Tutorial::stageIntro01PopupSprite);
      break;
    case Tutorial::Stage::INTRO02:
      GameWindow::drawSprite(Tutorial::SCREEN_FADE_FILTER_X, Tutorial::SCREEN_FADE_FILTER_Y,
        Tutorial::SCREEN_FADE_FILTER_WIDTH, Tutorial::SCREEN_FADE_FILTER_HEIGHT, *Tutorial::screenFadeFilterSprite);
      GameWindow::drawSprite(Tutorial::INTRO02_POPUP_X, Tutorial::INTRO02_POPUP_Y,
        Tutorial::INTRO02_POPUP_WIDTH, Tutorial::INTRO02_POPUP_HEIGHT, *Tutorial::stageIntro02PopupSprite);
      break;
    case Tutorial::Stage::DIALOGUE:
      GameWindow::drawSprite(Tutorial::SCREEN_FADE_FILTER_X, Tutorial::SCREEN_FADE_FILTER_Y,
        Tutorial::SCREEN_FADE_FILTER_WIDTH, Tutorial::SCREEN_FADE_FILTER_HEIGHT, *Tutorial::screenFadeFilterSprite);
      GameWindow::drawSprite(Tutorial::DIALOGUE_POPUP_X, Tutorial::DIALOGUE_POPUP_Y,
        Tutorial::DIALOGUE_POPUP_WIDTH, Tutorial::DIALOGUE_POPUP_HEIGHT, *Tutorial::stageDialoguePopupSprite);
      break;
    case Tutorial::Stage::COMBAT:
      GameWindow::drawSprite(Tutorial::SCREEN_FADE_FILTER_X, Tutorial::SCREEN_FADE_FILTER_Y,
        Tutorial::SCREEN_FADE_FILTER_WIDTH, Tutorial::SCREEN_FADE_FILTER_HEIGHT, *Tutorial::screenFadeFilterSprite);
      break;
  }
}
