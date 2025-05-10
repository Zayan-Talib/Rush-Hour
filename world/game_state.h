#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include "../utility/util.h"

class GameState {

    private:

        // Stats

        static const int WIN_SCORE = 100;

        int score;

        // Time

        static const int GAME_DURATION = 180; // 3 minutes in seconds
        int remainingTime;

        // Game Status

        bool gameOver;
        bool gameWon;

        bool gameStarted;
        
    public:

        GameState ();

        // Time

        void updateTime ();
        int getRemainingTime () const { return remainingTime; }
        bool isTimeUp () const { return remainingTime <= 0; }

        // Game Over

        bool isGameOver () const { return gameOver || isTimeUp (); }
        bool hasWon () const { return gameWon; }
        bool hasGameStarted () { return gameStarted; } 

        void startGame () { gameStarted = true; }
        void setGameOver () { gameOver = true; }
        void setGameWon () { gameWon = true; }

        bool& getGameOverRef () { return gameOver; }
        bool& getGameWonRef () { return gameWon; }
        
        void forceGameOver () { gameOver = true; }
        
        void checkGameStatus ();

        // Score

        int getScore () const { return score; }
        void addScore (int points) { score += points; }
        
};

#endif 