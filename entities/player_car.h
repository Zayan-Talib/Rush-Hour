#ifndef PLAYER_CAR_H_
#define PLAYER_CAR_H_

#include "actor.h"

class PlayerCar : public Actor {
    
    private:

        // Coordinates

        int x;
        int y;

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

        int money;

        bool hasPassenger;
        bool hasPackage;

        // Pickup location tracking

        int pickupX;
        int pickupY;

        // Score

        static const int PASSENGER_SCORE = 10;
        static const int PACKAGE_SCORE = 20;  

        // Money

        static const int PASSENGER_FARE = 5;        // Base Fare
        static const int PACKAGE_FARE = 8;          // Base Fare

        // Collision

        static const int PERSON_COLLISION = -5;
        static const int OBSTACLE_COLLISION = -2;
        static const int CAR_COLLISION = -3;

    public:

        // Constructor

        PlayerCar (Board* board, GameState* state);

        // Vehicle

        void Draw () override;

        int getX () const { return x; }
        int getY () const { return y; }
        
        // Movement

        void Move (int dX, int dy) override;

        void moveLeft ()  { Move (-30, 0); }
        void moveRight () { Move (30, 0); }
        void moveUp ()    { Move (0, 30); }
        void moveDown ()  { Move (0, -30); }

        bool canMoveTo (int newCellX, int newCellY) override;

        void ResetPosition ();

        // Fuel

        void DrawFuelMeter ();
        void refillFuel (int refill = REFILL_AMOUNT) { currentFuel = MIN (MAX_FUEL, currentFuel + refill); }
        void consumeFuel () { currentFuel = MAX (0, currentFuel - FUEL_CONSUMPTION); }
        void fullFuel () { currentFuel = MAX_FUEL; }                 // Cheat Code

        int getFuelLevel () const { return currentFuel; }
        bool isFuelLeft () const { return currentFuel > 0; }

        // Mode Switching

        void switchMode ();
        void setMode (int mode) { currentMode = mode; }
        int getCurrentMode () const { return currentMode; }

        // Pickup and Dropoff

        bool hasAdjacentItem (int itemType) const;
        
        bool isCarrying () const { return hasPassenger || hasPackage; }
        bool isCarryingPassenger () const { return hasPassenger; }
        bool isCarryingPackage () const { return hasPackage; }

        void pickupOrDropoff ();
        
        // Money

        int getMoney () const { return money; }
        void addMoney (int fare) { money += fare; }
        int calculateFare (int startX, int startY, int endX, int endY);

        // Collision

        void checkCollisions (int newX, int newY);

};

#endif 