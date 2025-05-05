#ifndef MENU_H_
#define MENU_H_

#include "../utility/util.h"

struct HighScore {

    char name [50];
    int score;

};

class Menu {

    private:

        static const int MAX_HIGH_SCORES = 10;
    
        static const int MENU_MAIN = 0;
        static const int MENU_LEADERBOARD = 1;
        static const int MENU_MODE_SELECT = 2;
        static const int MENU_NAME_ENTRY = 3;
   
        static const int WIN_SCORE = 100;

        int currentMenu;

        HighScore highScores [MAX_HIGH_SCORES];
        
        int numScores;
        char playerName [50];

        bool gameStarted;
        int selectedMode;  // 0 for taxi, 1 for delivery
        

    public:

        Menu () : currentMenu (MENU_MAIN), numScores (0), selectedMode (-1), gameStarted (false) {
        
            loadHighScores ();
        
        }
        
        void DrawMenu ();
        void HandleClick (int x, int y);
        void HandleKeypress (unsigned char key);
        
        // High Scores

        void loadHighScores ();
        void saveHighScores ();
        void addNewScore (int score);

        // Getters

        bool hasGameStarted () const { return gameStarted; }
        int getSelectedMode () const { return selectedMode; }
        const char* getPlayerName () const { return playerName; }

        void checkGameStatus (int score, int remainingTime, bool & gameOver, bool & gameWon);

};

#endif