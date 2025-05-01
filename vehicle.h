#ifndef VEHICLE_H_
#define VEHICLE_H_

#include "util.h"
#include "board.h"

class Vehicle {

    private:

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

        bool hasPassenger;
        bool hasPackage;

        // Time

        static const int GAME_DURATION = 180; // 3 minutes in seconds
        int remainingTime;

  
    public:

        // Constructor
    
        Vehicle (Board* board) : 
        gameBoard (board), 
        x (board -> getLeft () + 5), 
        y (board -> getTop () - 4), 
        currentFuel (MAX_FUEL),
        currentMode (MODE_TAXI),
        score (0),
        hasPassenger (false),
        hasPackage (false),
        remainingTime (GAME_DURATION) {}
        

        // Getters

        int getX () const { return x; }
        int getY () const { return y; }
        
        int getCellX () const;
        int getCellY () const;

        void printCurrentCell () const;

        // Setters

        void fullFuel () { currentFuel = MAX_FUEL; }
        
        // Drawing

        void DrawCar ();
        
        // Movement
        
        void moveLeft ();
        void moveRight ();
        void moveUp ();
        void moveDown ();

        // Mode Switching

        void switchMode ();
        int getCurrentMode () const { return currentMode; }

        // Fuel

        void refillFuel ();
        void consumeFuel ();

        int getFuelLevel () const { return currentFuel; }
        bool canMove () const { return currentFuel > 0; }

        // Carrying

        void pickupOrDropoff ();
        bool isCarrying () const { return hasPassenger || hasPackage; }

        bool isCarryingPassenger () const { return hasPassenger; }
        bool isCarryingPackage () const { return hasPackage; }
        int getScore () const { return score; }
        void addScore (int points) { score += points; }

        // Time

        void updateTime ();
        int getRemainingTime () const { return remainingTime; }
        bool isTimeUp () const { return remainingTime <= 0; }


};

#endif