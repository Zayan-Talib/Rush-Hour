#include "menu.h"

// Drawing

void Menu::DrawMenu () {

    switch (currentMenu) {
        
        case MENU_MAIN:
        
            DrawString (400, 600, "RUSH HOUR", colors [RED]);
            DrawString (400, 500, "1. Play Game", colors [BLACK]);
            DrawString (400, 450, "2. View Leaderboard", colors [BLACK]);
            DrawString (400, 400, "3. Exit", colors [BLACK]);
            
            break;
            
        case MENU_LEADERBOARD:

            DrawString (400, 700, "HIGH SCORES", colors [RED]);
            
            for (int a = 0; a < numScores; a++) {

                string entry = string (highScores [a].name) + " - " + Num2Str (highScores [a].score);
                DrawString (400, 650 - (a * 40), entry, colors [BLACK]);
            
            }
            
            DrawString (400, 200, "Press ESC to return", colors [BLACK]);
            
            break;
            
        case MENU_MODE_SELECT:

            DrawString (400, 600, "SELECT MODE", colors [RED]);
            DrawString (400, 500, "1. Taxi Driver", colors [BLACK]);
            DrawString (400, 450, "2. Delivery Driver", colors [BLACK]);
            DrawString (400, 400, "3. Random", colors [BLACK]);
        
            break;
            
        case MENU_NAME_ENTRY:

            DrawString (400, 600, "ENTER YOUR NAME:", colors [RED]);
            DrawString (400, 500, string (playerName) + "_", colors [BLACK]);
            DrawString (400, 400, "Press ENTER when done", colors [BLACK]);

            break;

        }

}

// Entering

void Menu::HandleKeypress (unsigned char key) {
    
    if (currentMenu == MENU_MAIN) {
    
        switch (key) {
            
            case '1':
        
                currentMenu = MENU_MODE_SELECT;
                break;

            case '2':

                currentMenu = MENU_LEADERBOARD;
                break;
            
            case '3':
        
                exit (0);
                break;
        
            default:
                break;
        
        }
    
    }
    
    else if (currentMenu == MENU_MODE_SELECT) {
        
        switch (key) {
            
            case '1':
            
                selectedMode = 0;  // Taxi
                currentMenu = MENU_NAME_ENTRY;
                break;
            
            case '2':
            
                selectedMode = 1;  // Delivery
                currentMenu = MENU_NAME_ENTRY;
                break;
            
            case '3':
    
                selectedMode = GetRandInRange (0, 2);
                currentMenu = MENU_NAME_ENTRY;
                break;
        
        }
    
    }

    else if (currentMenu == MENU_NAME_ENTRY) {
        
        if (key == KEY_ENTER) {
        
            gameStarted = true;
        
        }

        else if (key == KEY_BACKSPACE && strlen (playerName) > 0) {
        
            playerName [strlen (playerName) - 1] = '\0';
        
        }

        else if (strlen (playerName) < 49) {
    
            playerName [strlen (playerName)] = key;
            playerName [strlen (playerName) + 1] = '\0';
    
        }
    
    }

    else if (currentMenu == MENU_LEADERBOARD && key == KEY_ESC) {

        currentMenu = MENU_MAIN;

    }

}

// High Scores

void Menu::loadHighScores () {

    ifstream file ("highscores.txt", ios::binary);
    
    if (file) {

        file.read ((char*) highScores, sizeof (HighScore) * MAX_HIGH_SCORES);
        file.read ((char*) &numScores, sizeof (int));
        
        file.close ();

    }

}

void Menu::saveHighScores () {

    ofstream file ("highscores.txt", ios::binary);

    file.write ((char*) highScores, sizeof (HighScore) * MAX_HIGH_SCORES);
    file.write ((char*) &numScores, sizeof (int));
    
    file.close ();

}

void Menu::addNewScore (int score) {

    // Writing a lot of comments because this logic is a bit tricky

    // Only add score if:
    // 1. We haven't reached maximum high scores yet, OR
    // 2. This score is better than the lowest existing score
    
    bool canAddScore = (numScores < MAX_HIGH_SCORES) || (score > highScores[numScores - 1].score);

    if (canAddScore) {
       
        // Important: Lower scores have a greater index in the array

        // Start from the bottom of the list
        int insertPosition = numScores;

        while (insertPosition > 0) {
       
            int comparePosition = insertPosition - 1;
            bool scoreIsBetter = score > highScores [comparePosition].score;

            if (!scoreIsBetter) {

                break; // It's at the right spot
            
            }

            // Shift the lower score down if we haven't hit the size limit
            if (insertPosition < MAX_HIGH_SCORES) {

                highScores [insertPosition] = highScores [comparePosition];
            
            }            
            
            insertPosition--;
        
        }
        
        if (insertPosition < MAX_HIGH_SCORES) {
        
            // Insert the new score
            strcpy (highScores [insertPosition].name, playerName);
            highScores [insertPosition].score = score;

            // If we added a new score, increase the count
            if (numScores < MAX_HIGH_SCORES) { 
                numScores++; 
            }
            
            saveHighScores ();
        
        }
    
    }

}

// Game Over

void Menu::checkGameStatus(int score, int remainingTime, bool& gameOver, bool& gameWon) {
    // Loss condition
    if(score < 0) {
        //gameOver = true;
    }
    
    // Win condition
    if(score >= WIN_SCORE && remainingTime > 0) {
        gameWon = true;
        gameOver = true;
    }
    
    // Time up condition
    if(remainingTime <= 0) {
        gameOver = true;
    }
    
    // Save score if game just ended
    static bool scoreSaved = false;
    if(gameOver && !scoreSaved) {
        addNewScore(score);
        scoreSaved = true;
    }
}