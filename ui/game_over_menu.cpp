#include "game_over_menu.h"
#include "../entities/player_car.h"
#include "../world/game_state.h"
#include "ui.h"

// Constructor

GameOverMenu::GameOverMenu (UI* ui) : 

    gameUI (ui),
    numButtons (3) {

        const int buttonWidth = 200;
        const int buttonHeight = 50;
        const int spacing = 20;
        
        int screenWidth = gameUI->getScreenWidth();
        int screenHeight = gameUI->getScreenHeight();
        
        // Y position near bottom (adjust as needed)
        int bottomY = 150;
        
        // Horizontal pair (Restart and Quit)
        int centerX = screenWidth / 2;
        int restartX = centerX - buttonWidth - spacing / 2;
        int quitX = centerX + spacing / 2;
        int horizontalY = bottomY;
        
        // Leaderboard centered below
        int leaderboardX = centerX - buttonWidth / 2;
        int leaderboardY = horizontalY - buttonHeight - spacing;
        
        // Button labels
        string labels[] = {"Restart - 'R'", "Quit - 'ESC'", "Leaderboard"};
        
        // Create buttons
        buttons[0] = new Button(restartX, horizontalY, buttonWidth, buttonHeight, labels[0], colors[BLUE], colors[GREEN], colors[WHITE], 10);
        buttons[1] = new Button(quitX, horizontalY, buttonWidth, buttonHeight, labels[1], colors[BLUE], colors[GREEN], colors[WHITE], 10);
        buttons[2] = new Button(leaderboardX, leaderboardY, buttonWidth, buttonHeight, labels[2], colors[BLUE], colors[GREEN], colors[WHITE], 10);
    
}

// Drawing

void GameOverMenu::Draw () {

	// Set Background Color
	// Range: 0 to 1

	glClearColor 
	(0, // Red 
	 0, // Green
	 0, // Blue
     0  // Alpha
    );  
	
	// R=G=B=1 -> White
	// R=G=B=0 -> Black
	// R=G=B=0.5 -> Gray

    // // Draw background
    // DrawRectangle (0, 0, 1020, 840, colors[WHITE]);
    
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

    else if (gameUI -> getPlayerCar () -> getFuelLevel () <= 0) {

        gameOverStr = "GAME OVER - You Ran out of Fuel!";
    
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
    DrawString(440, 700, gameOverStr, colors[RED]);
    DrawString(450, 550, "Final Score: " + Num2Str(gameUI->getGameState()->getScore()), colors[SILVER]); 
    DrawString(450, 500, "Total Money: $" + Num2Str(gameUI->getPlayerCar()->getMoney()), colors[GREEN]);
    DrawString(440, 450, "Jobs Completed: " + Num2Str(gameUI-> getGameState () -> getJobsCompleted()), colors[WHITE]);
    DrawString(440, 400, "Time Remaining: " + timeStr, colors[GOLDEN_ROD]);
    DrawString(440, 350, "Final Fuel Amount: " + Num2Str(gameUI -> getPlayerCar () -> getFuelLevel ()), colors[BLUE]);
    //DrawString(400, 300, "Press 'R' to restart or 'ESC' to quit", colors[BLACK]);

    for (int a = 0; a < numButtons; a++) {

        buttons [a] -> Draw ();

    }
    
}

void GameOverMenu::PrintKeys (unsigned char key) {

    if (key == 'r' || key == 'R') {
    
        gameUI -> backToMainMenu ();
    
    }
    
    else if (key == KEY_ESC) { 
  
        exit (0);
  
    }

} 

void GameOverMenu::MouseMove (int x, int y) {

    for (int a = 0; a < numButtons; a++) {

        buttons [a] -> MouseMove (x, y);

    }

}

void GameOverMenu::MouseClick (int button, int state, int x, int y) {

    for (int a = 0; a < numButtons; a++) {

        buttons [a] -> MouseClick (button, state, x, y);
        
        if (buttons [a] -> getPressed ()) {

            buttons [a] -> setPressed (false);

            switch (a) {
            
                case 0:
            
                    gameUI -> backToMainMenu ();
                    break;
        
                case 1:
        
                    exit (0);
                    break;
                
                case 2:
            
                    gameUI -> setCurrentMenu (UI::MENU_LEADERBOARD);
                    break;
        
                default:
                
                    break;
            
            }

        }

    }


}