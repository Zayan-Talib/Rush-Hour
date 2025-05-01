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
    
    public:

        // Constructor
    
        Vehicle (Board* board) : gameBoard (board), x (board -> getLeft () + 5), y (board -> getTop () - 4), currentFuel (MAX_FUEL) {}
        
        // Drawing

        void DrawCar ();
        
        // Movement
        
        void moveLeft ();
        void moveRight ();
        void moveUp ();
        void moveDown ();

        // Fuel

        void refillFuel ();
        void consumeFuel ();

        int getFuelLevel () const { return currentFuel; }
        bool canMove () const { return currentFuel > 0; }

        // Getters

        int getX () const { return x; }
        int getY () const { return y; }
        
        int getCellX () const;
        int getCellY () const;

        void printCurrentCell () const;

        // Setters

        void fullFuel () { currentFuel = MAX_FUEL; }

};

#endif