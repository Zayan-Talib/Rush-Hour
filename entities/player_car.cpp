#include "player_car.h"
#include "../world/board.h"
#include "../world/game_state.h"

// Constructor

PlayerCar::PlayerCar (Board* board, GameState* state) :
    
    Actor (board, state), 
    x (board -> getLeft () + 5),
    y (board -> getTop () - 4),
    currentFuel (MAX_FUEL),
    currentMode (MODE_TAXI),
    hasPassenger (false),
    hasPackage (false)

{}

// Vehicle

void PlayerCar::Draw () {

    float * WheelColor = colors [BLACK];
    float * CarColor = nullptr;

    if (currentMode == MODE_TAXI) {
    
        CarColor = colors [RED];
    
    } 
    
    else {
    
        CarColor = colors [BLUE];
    
    }
    
    DrawSquare (x, y, 20, CarColor);

    int wheelSize = 5;

    DrawCircle (x + 5, y, wheelSize, WheelColor);      // Left wheel
    DrawCircle (x + 15, y, wheelSize, WheelColor);     // Right wheel

    glutPostRedisplay ();

}
       
// Movement

void PlayerCar::Move (int dx, int dy) {

    int newX = x + dx;
    int newY = y + dy;
    
    if (isFuelLeft () && newX >= gameBoard -> getLeft () && newX <= gameBoard -> getRight () && newY >= gameBoard -> getBottom () && newY <= gameBoard -> getTop ()) {
        
        // Check collisions before moving

        checkCollisions (newX, newY);
        
        if (gameBoard -> isValidMove (newX, newY)) {
        
            x = newX;
            y = newY;
            consumeFuel ();

            cellX = (gameBoard -> getTop () - y) / gameBoard -> getCellSize ();
            cellY = (x - gameBoard -> getLeft ()) / gameBoard -> getCellSize ();
        
        }
    
    }

}

bool PlayerCar::canMoveTo (int dx, int dy) {
    
    int row = (gameBoard -> getTop () - dy) / gameBoard -> getCellSize ();
    int col = (dx - gameBoard -> getLeft ()) / gameBoard -> getCellSize ();
    
    return gameBoard -> getCellValue (row, col) != 1;

}

void PlayerCar::ResetPosition () {

    x = (gameBoard -> getLeft ()) + 5;
    y = (gameBoard -> getTop ()) - 4;

    cellX = 0;
    cellY = 0;

}

// Fuel

void PlayerCar::DrawFuelMeter () {

    // Drawing position

    int x = 25;
    int y = 300;
    int width = 100;
    int height = 200;
    
    // Draw outer border of fuel meter

    DrawRoundRect (x, y, width, height + 10, colors [BLACK], 10);
    
    // Calculate fill height based on current fuel percentage

    float fuelPercent = currentFuel / 100.0f;
    int fillHeight = height * fuelPercent;
    
    // Choose color based on fuel level
 
    float* fuelColor;

    if (currentFuel > 70) {
        fuelColor = colors [GREEN];
    } 

    else if (currentFuel > 30) {
        fuelColor = colors [YELLOW];
    }

    else {
        fuelColor = colors [RED];
    }
    
    // Draw fuel level

    if (currentFuel > 4) {

        DrawRoundRect (x + 5, y + 5, width - 10, fillHeight, fuelColor, 8);

    }

    else {
    
        int lineSpacing = 1;
        
        for (int a = 0; a < currentFuel * 2; a++) {
        
            DrawLine (x + 5, y + 5 + (a * lineSpacing), x + width - 5, y + 5 + (a * lineSpacing), 5, fuelColor);
        
        }
    
    }
    
    // Draw fuel icon
 
    DrawString (x + 29, y + 220, "FULL", colors [BLACK]); 
    DrawString (x + 20, y - 25, "EMPTY", colors [BLACK]); 

}

// Mode Switching

void PlayerCar::switchMode () {

    if (gameBoard -> isModeStation (x, y)) {
    
        currentMode = (currentMode == MODE_TAXI) ? MODE_DELIVERY : MODE_TAXI;
    
    }

}

// Pickup and Dropoff

bool PlayerCar::hasAdjacentItem (int itemType) const {
    
    // Check all 4 adjacent cells

    return gameBoard -> GridCheck (x - 30, y, itemType) ||          // Left
           gameBoard -> GridCheck (x + 30, y, itemType) ||          // Right
           gameBoard -> GridCheck (x, y + 30, itemType) ||          // Up
           gameBoard -> GridCheck (x, y - 30, itemType);            // Down

}

void PlayerCar::pickupOrDropoff () {

    if (currentMode == MODE_TAXI) {
    
        if (!hasPassenger && hasAdjacentItem (4)) {
       
            hasPassenger = true;

            pickupX = getCellX ();
            pickupY = getCellY ();

            // Remove passenger from the adjacent cell
            if      (gameBoard -> isPassenger (x - 30, y)) gameBoard -> removePassenger (x - 30, y);
            else if (gameBoard -> isPassenger (x + 30, y)) gameBoard -> removePassenger (x + 30, y);
            else if (gameBoard -> isPassenger (x, y + 30)) gameBoard -> removePassenger (x, y + 30);
            else if (gameBoard -> isPassenger (x, y - 30)) gameBoard -> removePassenger (x, y - 30);
        
        }

        else if (hasPassenger && gameBoard -> isPassengerDestination (x, y)) {
        
            hasPassenger = false;

            int fare = calculateFare (pickupX, pickupY, getCellX (), getCellY ());
            addMoney (fare);
            gameState -> addScore (PASSENGER_SCORE);

            gameBoard -> removePassengerDestination (x, y);
        
        }
    
    }

    else {

        if (!hasPackage && (hasAdjacentItem (6) || gameBoard -> isPackage (x, y))) {
            
            hasPackage = true;

            pickupX = getCellX ();
            pickupY = getCellY ();

            if      (gameBoard -> isPackage (x, y))      gameBoard -> removePackage (x, y);
            else if (gameBoard -> isPackage (x - 30, y)) gameBoard -> removePackage (x - 30, y);
            else if (gameBoard -> isPackage (x + 30, y)) gameBoard -> removePackage (x + 30, y);
            else if (gameBoard -> isPackage (x, y + 30)) gameBoard -> removePackage (x, y + 30);
            else if (gameBoard -> isPackage (x, y - 30)) gameBoard -> removePackage (x, y - 30);
        
        }

        else if (hasPackage && gameBoard -> isPackageDestination (x, y)) {
            
            hasPackage = false;

            int fare = calculateFare (pickupX, pickupY, getCellX (), getCellY ());
            addMoney (fare);
            gameState -> addScore (PACKAGE_SCORE);

            gameBoard -> removePackageDestination (x, y);

        }

    }

}

// Money

int PlayerCar::calculateFare (int startX, int startY, int endX, int endY) {

    int distance = ABS (endX - startX) + ABS (endY - startY);
    
    // Base fare + distance multiplier
    
    if (currentMode == MODE_TAXI) {

        return PASSENGER_FARE + (distance * 2); // $2 per cell for passengers
    
    } 

    else {
    
        return PACKAGE_FARE + (distance * 3);   // $3 per cell for packages
    
    }

}

// Collision

void PlayerCar::checkCollisions (int newX, int newY) {

    if (gameBoard -> isPassenger (newX, newY)) {
        
        gameState -> addScore (PERSON_COLLISION);
    
    }
    
    if (gameBoard -> GridCheck (newX, newY, 1)) {
        
        gameState -> addScore (OBSTACLE_COLLISION);
    
    }
    
    if (gameBoard -> isNPCCar (newX, newY)) {
        
        gameState -> addScore (CAR_COLLISION);
    
    }

}


