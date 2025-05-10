#include "game_state.h"

// Constructor

GameState::GameState () :

    score (50),
    remainingTime (GAME_DURATION),
    gameOver (false),
    gameWon (false),
    gameStarted (false)

{}

// Updating

void GameState::updateTime () {

    if (remainingTime > 0) {
        remainingTime--;
    }

}

// Game End 

void GameState::checkGameStatus () {
    
    // Loss condition

    if (score < 0) {
    
        gameOver = true;
    
    }
    
    // Win condition
    
    if (score >= WIN_SCORE && remainingTime > 0) {
    
        gameWon = true;
        gameOver = true;
    
    }
    
    // Time up condition

    if (remainingTime <= 0) {
    
        gameOver = true;
    
    }
    
    // Save score if game just ended
    
    static bool scoreSaved = false;
    
    if(gameOver && !scoreSaved) {
    
        addScore (score);
        scoreSaved = true;
    
    }

}