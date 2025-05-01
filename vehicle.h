#ifndef VEHICLE_H_
#define VEHICLE_H_

#include "util.h"
#include "board.h"

class Vehicle {

    private:

        int x, y;

        Board* gameBoard;
    
    public:
    
        Vehicle (Board* board) : gameBoard (board) {
        
            x = board -> getLeft () + 5;
            y = board -> getTop () - 4;
        
        }
        
        void DrawCar ();
        void moveLeft ();
        void moveRight ();
        void moveUp ();
        void moveDown ();
        
        // Getters

        int getX () const { return x; }
        int getY () const { return y; }
        
        int getCellX () const;
        int getCellY () const;
        
        void printCurrentCell () const;

};

#endif