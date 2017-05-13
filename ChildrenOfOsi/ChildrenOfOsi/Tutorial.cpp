#include "Tutorial.h"

#include "GameState.h"

using namespace std;

Tutorial::Stage Tutorial::currentStage = Tutorial::Stage::NONE;
bool Tutorial::isPaused = false;

bool Tutorial::completedStageGameStart = false;
bool Tutorial::completedStageDialogue = false;
bool Tutorial::completedStageCombat = false;

/**
 * Initializes the tutorial system.
 */
void Tutorial::init()
{

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
 * complete. If called with the NONE stage, this function will interpret that as
 * instructions to instead complete the current stage, if any.
 */
void Tutorial::launchStage(Stage stage, Input &input, bool pause)
{
  if(stage == Tutorial::Stage::NONE) {
    Tutorial::completeStage();
    return;
  }

  Tutorial::currentStage = stage;
  Tutorial::isPaused = pause;
  input.current_game_state = (pause) ?
    game_state::pause_menu : game_state::in_game;

  switch(stage) {
    case Tutorial::Stage::GAME_START:
      Tutorial::startStageGameStart();
      break;
    case Tutorial::Stage::DIALOGUE:
      Tutorial::startStageDialogue();
      break;
    case Tutorial::Stage::COMBAT:
      Tutorial::startStageCombat();
      break;
  }
}

/**
 * Checks whether the current stage, if any, has received the necessary input to
 * be completed.
 */
void Tutorial::updateStage(Stage stage)
{
  switch(stage) {
    case Tutorial::Stage::GAME_START:
      
      break;
    case Tutorial::Stage::DIALOGUE:
      
      break;
    case Tutorial::Stage::COMBAT:
      
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

      break;
    case Tutorial::Stage::DIALOGUE:

      break;
    case Tutorial::Stage::COMBAT:

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

}

/**
 * 
 */
void Tutorial::startStageGameStart()
{

}

/**
 * 
 */
void Tutorial::startStageDialogue()
{

}

/**
 * 
 */
void Tutorial::startStageCombat()
{

}
