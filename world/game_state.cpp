#include "game_state.h"

// Constructor

GameState::GameState () :

    score (0),
    remainingTime (GAME_DURATION),
    gameOver (false),
    gameWon (false)

{}

// Game Over Conditions

void GameState::updateTime () {

    if (remainingTime > 0) {
        remainingTime--;
    }

}