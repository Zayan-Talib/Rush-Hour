#include "game_state.h"
#include "../ui/ui.h"

// Constructor

GameState::GameState () :

    score (START_SCORE),
    remainingTime (GAME_DURATION),
    gameOver (false),
    gameWon (false),
    gameStarted (false),
    gameUI (nullptr),
    jobsCompleted (0),
    sinceLastJob (0)

{}

// Updating

void GameState::updateTime () {

    if (remainingTime > 0) {
        remainingTime--;
    }

}

// Start Game

void GameState::startGame () {

    gameStarted = true;
    gameUI -> setCurrentMenu (UI::MENU_HUD);

    cout << "The game has started!" << endl;

}

// Game End 

void GameState::forceGameOver () {

    gameOver = true;
    checkGameStatus ();

}

void GameState::checkGameStatus () {
    
    checkJobs ();

    // Loss condition

    if (score < 0 || (gameUI -> getPlayerCar () -> getFuelLevel () <= 0)) {
    
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
    
    if (gameOver) {
    
        if (!scoreSaved) {

            gameUI -> getLeaderboard () -> addNewScore (score);   
            scoreSaved = true;

        }
        
        gameUI -> setCurrentMenu (UI::MENU_GAME_OVER);

    }

}

// Reset game state

void GameState::resetGameState () {

    gameStarted = false;
    gameOver = false;
    gameWon = false;
    score = START_SCORE;
    remainingTime = GAME_DURATION;
    jobsCompleted = 0;
    sinceLastJob = 0;

}

// Jobs Completed

void GameState::checkJobs () {

    if (sinceLastJob >= 2) {

        sinceLastJob = 0;

        gameUI -> getBoard () -> addNPCCar ();
        gameUI -> getBoard () -> increaseNPCSpeed ();

    }

}

