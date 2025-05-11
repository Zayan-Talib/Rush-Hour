#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include "../utility/util.h"

class UI;

class GameState {

    private:

        UI* gameUI;

        // Stats

        static const int START_SCORE = 50;
        static const int WIN_SCORE = 100;

        int score;

        static bool scoreAdded;

        // Time

        static const int GAME_DURATION = 180; // 3 minutes in seconds
        int remainingTime;

        // Game Status

        bool gameOver;
        bool gameWon;

        bool gameStarted;
        
        // Jobs

        int jobsCompleted;
        int sinceLastJob;
        
    public:

        GameState ();

        void setUI (UI* ui) { gameUI = ui; }

        UI* getUI () { return gameUI; }

        // Time

        void updateTime ();
        int getRemainingTime () const { return remainingTime; }
        bool isTimeUp () const { return remainingTime <= 0; }

        // Game Over

        bool isGameOver () const { return gameOver || isTimeUp (); }
        bool hasWon () const { return gameWon; }
        bool hasGameStarted () const { return gameStarted; } 

        void startGame ();
        void setGameOver () { gameOver = true; }
        void setGameWon () { gameWon = true; }
        
        void forceGameOver ();
        
        void checkGameStatus ();

        // Score

        int getScore () const { return score; }
        void addScore (int points) { score += points; }

        bool isScoreNegative () const { return score <= 0; }

        // Reset game state
        
        void resetGameState ();

        // Jobs

        int getJobsCompleted () const { return jobsCompleted; }
        void increaseJobsCompleted () { jobsCompleted++; sinceLastJob++; }

        void checkJobs ();

};

#endif 