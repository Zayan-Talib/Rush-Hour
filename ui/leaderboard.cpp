#include "leaderboard.h"
#include "ui.h"

// Constructor

Leaderboard::Leaderboard (UI* ui) : numScores (0), parentUI (ui) {

    loadHighScores ();

}

// Drawing

void Leaderboard::Draw () {

    DrawString (400, 700, "HIGH SCORES", colors [RED]);
            
    for (int a = 0; a < numScores; a++) {

        string entry = string (highScores [a].name) + " - " + Num2Str (highScores [a].score);
        DrawString (400, 650 - (a * 40), entry, colors [BLACK]);
    
    }
    
    DrawString (400, 200, "Press ESC to return", colors [BLACK]);

}

// High Scores

void Leaderboard::loadHighScores () {

    ifstream file ("highscores.txt", ios::binary);
    
    if (file) {

        file.read ((char*) highScores, sizeof (HighScore) * MAX_HIGH_SCORES);
        file.read ((char*) &numScores, sizeof (int));
        
        file.close ();

    }

}

void Leaderboard::saveHighScores () {

    ofstream file ("highscores.txt", ios::binary);

    file.write ((char*) highScores, sizeof (HighScore) * MAX_HIGH_SCORES);
    file.write ((char*) &numScores, sizeof (int));
    
    file.close ();

}

void Leaderboard::addNewScore (int score) {

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
            strcpy (highScores [insertPosition].name, parentUI -> getPlayerName ());
            highScores [insertPosition].score = score;

            // If we added a new score, increase the count
            if (numScores < MAX_HIGH_SCORES) { 
                numScores++; 
            }
            
            saveHighScores ();
        
        }
    
    }

}

// User Input

void Leaderboard::PrintKeys (unsigned char key) {

 
}