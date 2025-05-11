#include "game_over_menu.h"
#include "../entities/player_car.h"
#include "../world/game_state.h"
#include "ui.h"

// Constructor

GameOverMenu::GameOverMenu (UI* ui) : gameUI(ui) {}

// Drawing

void GameOverMenu::Draw () {

	// Set Background Color
	// Range: 0 to 1

	glClearColor 
	(1, // Red 
	 1, // Green
	 1, // Blue
     0  // Alpha
    );  
	
	// R=G=B=1 -> White
	// R=G=B=0 -> Black
	// R=G=B=0.5 -> Gray

    // Draw background
    DrawRectangle(0, 0, 1020, 840, colors[WHITE]);
    
    // Game over text
    string gameOverStr;
    
    if (gameUI -> getGameState () -> hasWon ()) {
        gameOverStr = "CONGRATULATIONS! YOU WON!";
    } 
    
    else if (gameUI -> getGameState () -> isTimeUp ()) {
        gameOverStr = "TIME'S UP!";
    } 
    
    else if (gameUI -> getGameState () -> isScoreNegative ()) {

        gameOverStr = "GAME OVER - Score too low!";
    
    }

    else {

        gameOverStr = "Forced Game Over";

    }

    // Format time remaining as MM:SS
    
    int timeLeft = gameUI->getGameState()->getRemainingTime();
    int minutes = timeLeft / 60;
    int seconds = timeLeft % 60;
    string timeStr = Num2Str(minutes) + ":" + (seconds < 10 ? "0" : "") + Num2Str(seconds);
    
    // Draw final stats
    DrawString(400, 600, gameOverStr, colors[RED]);
    DrawString(400, 550, "Final Score: " + Num2Str(gameUI->getGameState()->getScore()), colors[BLACK]); 
    DrawString(400, 500, "Total Money: $" + Num2Str(gameUI->getPlayerCar()->getMoney()), colors[BLACK]);
    DrawString(400, 450, "Jobs Completed: " + Num2Str(gameUI-> getGameState () -> getJobsCompleted()), colors[BLACK]);
    DrawString(400, 400, "Time Remaining: " + timeStr, colors[BLACK]);
    DrawString(400, 350, "Final Fuel Level: " + Num2Str(gameUI -> getPlayerCar () -> getFuelPercentage ()) + "%", colors[BLACK]);
    DrawString(400, 300, "Press 'R' to restart or 'ESC' to quit", colors[BLACK]);
    
}

void GameOverMenu::PrintKeys (unsigned char key) {

    if (key == 'r' || key == 'R') {
    
        gameUI -> backToMainMenu ();
    
    }
    
    else if (key == KEY_ESC) { 
  
        exit (0);
  
    }

} 