#include "Tutorial.h"

#include "GameState.h"

using namespace std;

Tutorial::Stage Tutorial::currentStage = Tutorial::Stage::NONE;
bool Tutorial::isPaused = false;

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
  input.current_game_state = (pause) ?
    game_state::pause_menu : game_state::in_game;

  switch(stage) {
    case Tutorial::Stage::GAME_START:
      Tutorial::handleStageGameStart();
      break;
    case Tutorial::Stage::DIALOGUE:
      Tutorial::handleStageDialogue();
      break;
    case Tutorial::Stage::COMBAT:
      Tutorial::handleStageCombat();
      break;
  }
}

/**
 * Completes the current tutorial stage, if any. If the game is paused when
 * this function is called, it will be unpaused.
 */
void Tutorial::completeStage()
{
  if(Tutorial::currentStage != Tutorial::Stage::NONE) {
    
  }
}

/**
 *
 */
void Tutorial::drawTutorial()
{

}

/**
 *
 */
void Tutorial::handleStageGameStart()
{

}

/**
 *
 */
void Tutorial::handleStageDialogue()
{

}

/**
 *
 */
void Tutorial::handleStageCombat()
{

}
