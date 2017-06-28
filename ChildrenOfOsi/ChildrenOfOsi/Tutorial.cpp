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
bool Tutorial::completedStageDialogue01 = false;
bool Tutorial::completedStageDialogue02 = false;
bool Tutorial::completedStageDialogue03 = false;
bool Tutorial::completedStageCombat = false;

Sprite *Tutorial::screenFadeFilterSprite = nullptr;
Sprite *Tutorial::stageGameStartPopupSprite = nullptr;
Sprite *Tutorial::stageIntro01PopupSprite = nullptr;
Sprite *Tutorial::stageIntro02PopupSprite = nullptr;
Sprite *Tutorial::stageDialogue01PopupSprite = nullptr;
Sprite *Tutorial::stageDialogue02PopupSprite = nullptr;
Sprite *Tutorial::stageDialogue03PopupSprite = nullptr;
Sprite *Tutorial::stageCombatPopupSprite = nullptr;

Texture *Tutorial::screenFaceFilterTex = nullptr;
Texture *Tutorial::stageGameStartPopupTex = nullptr;
Texture *Tutorial::stageIntro01PopupTex = nullptr;
Texture *Tutorial::stageIntro02PopupTex = nullptr;
Texture *Tutorial::stageDialogue01PopupTex = nullptr;
Texture *Tutorial::stageDialogue02PopupTex = nullptr;
Texture *Tutorial::stageDialogue03PopupTex = nullptr;
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

  Tutorial::stageDialogue01PopupSprite = new Sprite();
  Tutorial::stageDialogue01PopupTex = new Texture();
  Tutorial::stageDialogue01PopupTex->setFile(SPRITES_PATH + "Tutorial_Dialogue01Popup.png", 1);
  Tutorial::stageDialogue01PopupSprite->setTexture(Tutorial::stageDialogue01PopupTex);

  Tutorial::stageDialogue02PopupSprite = new Sprite();
  Tutorial::stageDialogue02PopupTex = new Texture();
  Tutorial::stageDialogue02PopupTex->setFile(SPRITES_PATH + "Tutorial_Dialogue02Popup.png", 1);
  Tutorial::stageDialogue02PopupSprite->setTexture(Tutorial::stageDialogue02PopupTex);

  Tutorial::stageDialogue03PopupSprite = new Sprite();
  Tutorial::stageDialogue03PopupTex = new Texture();
  Tutorial::stageDialogue03PopupTex->setFile(SPRITES_PATH + "Tutorial_Dialogue03Popup.png", 1);
  Tutorial::stageDialogue03PopupSprite->setTexture(Tutorial::stageDialogue03PopupTex);

  Tutorial::stageCombatPopupSprite = new Sprite();
  Tutorial::stageCombatPopupTex = new Texture();
  Tutorial::stageCombatPopupTex->setFile(SPRITES_PATH + "Tutorial_CombatPopup.png", 1);
  Tutorial::stageCombatPopupSprite->setTexture(Tutorial::stageCombatPopupTex);
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
  Tutorial::completedStageIntro01 = false;
  Tutorial::completedStageIntro02 = false;
  Tutorial::completedStageDialogue01 = false;
  Tutorial::completedStageDialogue02 = false;
  Tutorial::completedStageDialogue03 = false;
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
  delete Tutorial::stageDialogue01PopupSprite;
  delete Tutorial::stageDialogue02PopupSprite;
  delete Tutorial::stageDialogue03PopupSprite;
  delete Tutorial::stageCombatPopupSprite;

  delete Tutorial::stageGameStartPopupTex;
  delete Tutorial::stageIntro01PopupTex;
  delete Tutorial::stageIntro02PopupTex;
  delete Tutorial::stageDialogue01PopupTex;
  delete Tutorial::stageDialogue02PopupTex;
  delete Tutorial::stageDialogue03PopupTex;
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
    case Tutorial::Stage::DIALOGUE01:
      return  Tutorial::completedStageDialogue01;
    case Tutorial::Stage::DIALOGUE02:
      return Tutorial::completedStageDialogue02;
    case Tutorial::Stage::DIALOGUE03:
      return Tutorial::completedStageDialogue03;
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
    default:
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
    case Tutorial::Stage::DIALOGUE01:
      Tutorial::completedStageDialogue01 = true;
      break;
    case Tutorial::Stage::DIALOGUE02:
      Tutorial::completedStageDialogue02 = true;
      break;
    case Tutorial::Stage::DIALOGUE03:
      Tutorial::completedStageDialogue03 = true;
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
    case Tutorial::Stage::DIALOGUE01:
      GameWindow::drawSprite(Tutorial::SCREEN_FADE_FILTER_X, Tutorial::SCREEN_FADE_FILTER_Y,
        Tutorial::SCREEN_FADE_FILTER_WIDTH, Tutorial::SCREEN_FADE_FILTER_HEIGHT, *Tutorial::screenFadeFilterSprite);
      GameWindow::drawSprite(Tutorial::DIALOGUE01_POPUP_X, Tutorial::DIALOGUE01_POPUP_Y,
        Tutorial::DIALOGUE01_POPUP_WIDTH, Tutorial::DIALOGUE01_POPUP_HEIGHT, *Tutorial::stageDialogue01PopupSprite);
      break;
    case Tutorial::Stage::DIALOGUE02:
      GameWindow::drawSprite(Tutorial::SCREEN_FADE_FILTER_X, Tutorial::SCREEN_FADE_FILTER_Y,
        Tutorial::SCREEN_FADE_FILTER_WIDTH, Tutorial::SCREEN_FADE_FILTER_HEIGHT, *Tutorial::screenFadeFilterSprite);
      GameWindow::drawSprite(Tutorial::DIALOGUE02_POPUP_X, Tutorial::DIALOGUE02_POPUP_Y,
        Tutorial::DIALOGUE02_POPUP_WIDTH, Tutorial::DIALOGUE02_POPUP_HEIGHT, *Tutorial::stageDialogue02PopupSprite);
      break;
    case Tutorial::Stage::DIALOGUE03:
      GameWindow::drawSprite(Tutorial::SCREEN_FADE_FILTER_X, Tutorial::SCREEN_FADE_FILTER_Y,
        Tutorial::SCREEN_FADE_FILTER_WIDTH, Tutorial::SCREEN_FADE_FILTER_HEIGHT, *Tutorial::screenFadeFilterSprite);
      GameWindow::drawSprite(Tutorial::DIALOGUE03_POPUP_X, Tutorial::DIALOGUE03_POPUP_Y,
        Tutorial::DIALOGUE03_POPUP_WIDTH, Tutorial::DIALOGUE03_POPUP_HEIGHT, *Tutorial::stageDialogue03PopupSprite);
      break;
    case Tutorial::Stage::COMBAT:
      GameWindow::drawSprite(Tutorial::SCREEN_FADE_FILTER_X, Tutorial::SCREEN_FADE_FILTER_Y,
        Tutorial::SCREEN_FADE_FILTER_WIDTH, Tutorial::SCREEN_FADE_FILTER_HEIGHT, *Tutorial::screenFadeFilterSprite);
      GameWindow::drawSprite(Tutorial::COMBAT_POPUP_X, Tutorial::COMBAT_POPUP_Y,
        Tutorial::COMBAT_POPUP_WIDTH, Tutorial::COMBAT_POPUP_HEIGHT, *Tutorial::stageCombatPopupSprite);
      break;
  }
}
