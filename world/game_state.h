#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include "../utility/util.h"

class GameState {

    private:

        // Stats

        int score;

        // Time

        static const int GAME_DURATION = 180; // 3 minutes in seconds
        int remainingTime;

        // Game Over

        bool gameOver;
        bool gameWon;
        
    public:

        GameState ();

        // Time

        void updateTime ();
        int getRemainingTime () const { return remainingTime; }
        bool isTimeUp () const { return remainingTime <= 0; }

        // Game Over

        bool isGameOver () const { return gameOver || isTimeUp (); }
        bool hasWon () const { return gameWon; }

        void setGameOver () { gameOver = true; }
        void setGameWon () { gameWon = true; }

        bool& getGameOverRef() { return gameOver; }
        bool& getGameWonRef() { return gameWon; }
        
        void forceGameOver () { gameOver = true; } 

        // Score

        int getScore () const { return score; }
        void addScore (int points) { score += points; }
        
};

#endif 