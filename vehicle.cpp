#include "vehicle.h"

// Helpers

int Vehicle::getCellX () const {
    
    int cx = gameBoard -> getLeft();

    for (int a = 0; a < 24; a++) {
    
        if (x >= cx && x <= cx + 30) {
            return a;
        }
    
        cx += 30;
    
    }

    return -1;

}

int Vehicle::getCellY () const {

    int cy = gameBoard -> getTop();
    
    for (int a = 0; a < 24; a++) {
    
        if (y <= cy && y >= cy - 30) {
            return a;
        }
    
        cy -= 30;
    
    }

    return -1;

}

void Vehicle::printCurrentCell () const {

    cout << "Current Cell of Car: [" << getCellY () + 1 << "][" << getCellX () + 1 << "]" << endl;

}

// Drawing

void Vehicle::DrawCar () {

    float* WheelColor = colors [BLACK];
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

void Vehicle::DrawFuelMeter () {

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

// Movement

void Vehicle::move (int dx, int dy) {

    int newX = x + dx;
    int newY = y + dy;
    
    if (canMove () && newX >= gameBoard -> getLeft () && newX <= gameBoard -> getRight () && newY >= gameBoard -> getBottom () && newY <= gameBoard -> getTop ()) {
        
        // Check collisions before moving
        checkCollisions (newX, newY);
        
        if (gameBoard -> isValidMove (newX, newY)) {
        
            x = newX;
            y = newY;
            consumeFuel ();
        
        }
    
    }

}

// Mode Switching

void Vehicle::switchMode () {

    if (gameBoard -> isModeStation (x, y)) {
    
        currentMode = (currentMode == MODE_TAXI) ? MODE_DELIVERY : MODE_TAXI;
    
    }

}

// Passengers and Packages

bool Vehicle::hasAdjacentItem (int itemType) const {
    
    // Check all 4 adjacent cells
    return gameBoard -> isPassenger (x - 30, y) ||  // Left
           gameBoard -> isPassenger (x + 30, y) ||  // Right
           gameBoard -> isPassenger (x, y + 30) ||  // Up
           gameBoard -> isPassenger (x, y - 30);    // Down

}

void Vehicle::pickupOrDropoff () {

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
            addScore (PASSENGER_SCORE);

            gameBoard -> removePassengerDestination (x, y);
        
        }
    
    }

    else {

        if (!hasPackage && hasAdjacentItem (6)) {
            
            hasPackage = true;

            pickupX = getCellX ();
            pickupY = getCellY ();

            if      (gameBoard -> isPackage (x - 30, y)) gameBoard -> removePackage (x - 30, y);
            else if (gameBoard -> isPackage (x + 30, y)) gameBoard -> removePackage (x + 30, y);
            else if (gameBoard -> isPackage (x, y + 30)) gameBoard -> removePackage (x, y + 30);
            else if (gameBoard -> isPackage (x, y - 30)) gameBoard -> removePackage (x, y - 30);
        
        }

        else if (hasPackage && gameBoard -> isPackageDestination (x, y)) {
            
            hasPackage = false;

            int fare = calculateFare (pickupX, pickupY, getCellX (), getCellY ());
            addMoney (fare);
            addScore (PACKAGE_SCORE);

            gameBoard -> removePackageDestination (x, y);

        }

    }

}

// Game Over Conditions

void Vehicle::checkGameStatus () {
    
    // Loss condition
    
    if (score < 0) {
        //gameOver = true;
    }
    
    // Win Condition

    if (score >= 100 && remainingTime > 0) {
    
        gameWon = true;
        gameOver = true;
    
    }

}

void Vehicle::updateTime () {

    if (remainingTime > 0) {
        remainingTime--;
    }

    checkGameStatus ();

}

// Score and Money

int Vehicle::calculateFare (int startX, int startY, int endX, int endY) {

    int distance = ABS (endX - startX) + ABS (endY - startY);
    
    // Base fare + distance multiplier
    if (currentMode == MODE_TAXI) {

        return PASSENGER_FARE + (distance * 2); // $2 per cell for passengers
    
    } 

    else {
    
        return PACKAGE_FARE + (distance * 3);   // $3 per cell for packages
    
    }

}

// Collisions

void Vehicle::checkCollisions (int newX, int newY) {

    if (gameBoard -> isPassenger (newX, newY)) {
        
        addScore (PERSON_COLLISION);
    
    }
    
    if (gameBoard -> GridCheck (newX, newY, 1)) {
        
        addScore (OBSTACLE_COLLISION);
    
    }
    
    if (gameBoard -> isAICar (newX, newY)) {
        
        addScore (CAR_COLLISION);
    
    }

}