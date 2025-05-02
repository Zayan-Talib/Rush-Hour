#include "menu.h"

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
    
    else if(currentMenu == MENU_MODE_SELECT) {
        switch(key) {
            case '1':
                selectedMode = 0;  // Taxi
                currentMenu = MENU_NAME_ENTRY;
                break;
            case '2':
                selectedMode = 1;  // Delivery
                currentMenu = MENU_NAME_ENTRY;
                break;
            case '3':
                selectedMode = GetRandInRange(0, 2);
                currentMenu = MENU_NAME_ENTRY;
                break;
        }
    }
    else if(currentMenu == MENU_NAME_ENTRY) {
        if(key == 13) {  // Enter key
            gameStarted = true;
        }
        else if(key == 8 && strlen(playerName) > 0) {  // Backspace
            playerName[strlen(playerName)-1] = '\0';
        }
        else if(strlen(playerName) < 49) {
            playerName[strlen(playerName)] = key;
            playerName[strlen(playerName)+1] = '\0';
        }
    }
    else if(currentMenu == MENU_LEADERBOARD && key == 27) {  // ESC
        currentMenu = MENU_MAIN;
    }
}

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
    file.write ((char*)highScores, sizeof(HighScore) * MAX_HIGH_SCORES);
    file.write ((char*)&numScores, sizeof(int));
    file.close ();

}

void Menu::addNewScore(int score) {
    if(numScores < MAX_HIGH_SCORES || score > highScores[numScores-1].score) {
        int pos = numScores;
        while(pos > 0 && highScores[pos-1].score < score) {
            if(pos < MAX_HIGH_SCORES) {
                highScores[pos] = highScores[pos-1];
            }
            pos--;
        }
        
        if(pos < MAX_HIGH_SCORES) {
            strcpy(highScores[pos].name, playerName);
            highScores[pos].score = score;
            if(numScores < MAX_HIGH_SCORES) numScores++;
            saveHighScores();
        }
    }
}