#include "leaderboard.h"
#include "ui.h"

// Constructor

Leaderboard::Leaderboard (UI* ui) : numScores (0), gameUI (ui) {

    loadHighScores ();
}

// Drawing

void Leaderboard::Draw() {
    glClearColor(0, 0, 0, 0); // White background
    glClear(GL_COLOR_BUFFER_BIT);

    const int headerHeight = 40;
    const int rowHeight = 40;
    const int rowSpacing = 10;
    int screenWidth = gameUI->getScreenWidth();
    int screenHeight = gameUI ->getScreenHeight();
    
    int tableWidth = 600; // Width of the leaderboard table
    int tableHeight = (numScores * (rowHeight + rowSpacing)) + headerHeight; // Height including rows
    int startX = (screenWidth - tableWidth) / 2; // Center horizontally
    int startY = (screenHeight - tableHeight) / 2 + 100; // Center vertically, but slightly lower

    // Draw Table Background
    DrawRectangle(startX - 10, startY - 10, tableWidth + 20, tableHeight + 20, colors[LIGHT_GRAY]);

    // Draw Header Rectangle
    DrawRectangle(startX, startY + 500, tableWidth, headerHeight, colors[BLUE]);
    
    // Draw Column Headers
    DrawString(startX + 20, startY + headerHeight / 2 - 10 + 500, "Name", colors[WHITE]);
    DrawString(startX + 300, startY + headerHeight / 2 - 10 + 500, "Score", colors[WHITE]);

// Draw the Leaderboard Entries
for (int a = 0; a < numScores; a++) {
    string entry = string(highScores[a].name) + " - " + Num2Str(highScores[a].score);

    // Calculate y-position for each row, starting from the bottom
    int y =  startY - rowHeight + headerHeight + ((numScores - a - 1) * (rowHeight + rowSpacing)); // Reverse the order

    // Draw the Name and Score inside the table
    DrawString(startX + 20, y + rowHeight / 2 - 10, highScores[a].name, colors[WHITE]);
    DrawString(startX + 300, y + rowHeight / 2 - 10, Num2Str(highScores[a].score), colors[WHITE]);
}

    // Return message for user instructions
    DrawString(startX + 200, startY - 50, "Press ESC to return", colors[WHITE]);
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
            strcpy (highScores [insertPosition].name, gameUI -> getPlayerName ());
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

    if (key == KEY_ESC) {

        gameUI -> setCurrentMenu (UI::MENU_MAIN);
    
    }
 
}