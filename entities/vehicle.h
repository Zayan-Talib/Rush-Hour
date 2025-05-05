#ifndef VEHICLE_H_
#define VEHICLE_H_

#include "../utility/util.h"
class Board;

class Vehicle {

    private:

        // Essential Parameters

        int x, y;
        Board* gameBoard;

        // Fuel

        static const int MAX_FUEL = 100;
        static const int FUEL_CONSUMPTION = 1;
        static const int REFILL_AMOUNT = 50;
        
        int currentFuel;

        // Mode Switching

        static const int MODE_TAXI = 0;
        static const int MODE_DELIVERY = 1;

        int currentMode;

        // Passengers and Packages

        int score;
        int money;

        bool hasAdjacentItem (int itemType) const;

        bool hasPassenger;
        bool hasPackage;

        // Time

        static const int GAME_DURATION = 180; // 3 minutes in seconds
        int remainingTime;

        // Game Over

        bool gameOver;
        bool gameWon;

        // Score and Money

        static const int PASSENGER_SCORE = 10;
        static const int PACKAGE_SCORE = 20;  

        static const int PASSENGER_FARE = 5;
        static const int PACKAGE_FARE = 8;

        // Pickup location tracking
        
        int pickupX;
        int pickupY;

        int calculateFare (int startX, int startY, int endX, int endY);

        // Collision

        static const int PERSON_COLLISION = -5;
        static const int OBSTACLE_COLLISION = -2;
        static const int CAR_COLLISION = -3;

  
    public:

        // Constructor
    
        Vehicle (Board* board);
        
        // Helpers

        int getX () const { return x; }
        int getY () const { return y; }
        
        int getCellX () const;
        int getCellY () const;

        void printCurrentCell () const;

        void setMode (int mode) { currentMode = mode; }
        
        // Drawing

        void DrawCar ();
        void DrawFuelMeter ();

        // Movement
        
        void move (int dx, int dy);
        void moveLeft ()  { move (-30, 0); }
        void moveRight () { move (30, 0); }
        void moveUp ()    { move (0, 30); }
        void moveDown ()  { move (0, -30); }

        // Mode Switching

        void switchMode ();
        int getCurrentMode () const { return currentMode; }

        // Fuel

        void refillFuel () { currentFuel = MIN (MAX_FUEL, currentFuel + REFILL_AMOUNT); }
        void consumeFuel () { currentFuel = MAX (0, currentFuel - FUEL_CONSUMPTION); }
        void fullFuel () { currentFuel = MAX_FUEL; }        // Cheat Code

        int getFuelLevel () const { return currentFuel; }
        bool canMove () const { return currentFuel > 0; }

        // Carrying

        void pickupOrDropoff ();

        bool isCarrying () const { return hasPassenger || hasPackage; }
        bool isCarryingPassenger () const { return hasPassenger; }
        bool isCarryingPackage () const { return hasPackage; }

        // Time

        void updateTime ();
        int getRemainingTime () const { return remainingTime; }
        bool isTimeUp () const { return remainingTime <= 0; }

        // Game Over Conditions

        bool isGameOver () const { return gameOver || isTimeUp (); }
        bool hasWon () const { return gameWon; }

        void setGameOver () { gameOver = true; }
        void setGameWon () { gameWon = true; }

        bool& getGameOverRef() { return gameOver; }
        bool& getGameWonRef() { return gameWon; }
        
        void forceGameOver () { gameOver = true; }

        // Score and Money

        int getScore () const { return score; }
        int getMoney () const { return money; }
        void addScore (int points) { score += points; }
        void addMoney (int fare) { money += fare; }

        // Collisions

        void checkCollisions (int newX, int newY);

};

#endif