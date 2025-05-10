#ifndef LEADERBOARD_H_
#define LEADERBOARD_H_

#include "ui_element.h"

class UI;

struct HighScore {

    char name [50];
    int score;

};

class Leaderboard : public UIElement {

    private:

        UI* parentUI;

        // High Scores

        static const int MAX_HIGH_SCORES = 10;
        HighScore highScores [MAX_HIGH_SCORES];
        int numScores;


    public:

        // Constructor

        Leaderboard (UI* ui);

        // Main Methods

        void Draw () override;
        void PrintKeys (char unsigned key) override;

        // High Scores

        void loadHighScores ();
        void saveHighScores ();
        void addNewScore (int score);


    
};

#endif

