#include "vehicle.h"

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

// Movement

void Vehicle::move (int dx, int dy) {

    int newX = x + dx;
    int newY = y + dy;
    
    if (canMove () && newX >= gameBoard -> getLeft () && newX <= gameBoard -> getRight () && newY >= gameBoard -> getBottom () && newY <= gameBoard -> getTop () && gameBoard -> isValidMove (newX, newY)) {
        
        x = newX;
        y = newY;

        consumeFuel ();
        
        if (gameBoard -> isFuelStation (x, y)) {
        
            refillFuel ();
        
        }
    
    }

}

// Mode Switching

void Vehicle::switchMode () {

    if (gameBoard -> isModeStation (x, y)) {
    
        currentMode = (currentMode == MODE_TAXI) ? MODE_DELIVERY : MODE_TAXI;
    
    }

}

// Fuel

void Vehicle::consumeFuel () {

    currentFuel = MAX (0, currentFuel - FUEL_CONSUMPTION);

}

void Vehicle::refillFuel () {

    currentFuel = MIN (MAX_FUEL, currentFuel + REFILL_AMOUNT);

}

void Vehicle::DrawFuelMeter () {

    // Drawing position
    int x = 25;  // Left side of screen
    int y = 300; // Current position of your circles
    int width = 100;
    int height = 200;
    
    // Draw outer border of fuel meter
    DrawRoundRect (x, y, width, height + 10, colors[BLACK], 10);
    
    // Calculate fill height based on current fuel percentage
    float fuelPercent = currentFuel / 100.0f;
    int fillHeight = height * fuelPercent;
    
    // Choose color based on fuel level
    float* fuelColor;
    if (currentFuel > 70) {
        fuelColor = colors[GREEN];
    } 
    else if (currentFuel > 30) {
        fuelColor = colors[YELLOW];
    } 
    else {
        fuelColor = colors[RED];
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
    DrawString (x + 20, y + 225, "FULL", colors[BLACK]); 
    DrawString (x + 9, y - 35, "EMPTY", colors[BLACK]); 

}

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


// Passengers and Packages

void Vehicle::pickupOrDropoff() {
    if(currentMode == MODE_TAXI) {
        if(!hasPassenger && gameBoard->isPassenger(x, y)) {
            hasPassenger = true;
            gameBoard->removePassenger(x, y);
        }
        else if(hasPassenger && gameBoard->isPassengerDestination(x, y)) {
            hasPassenger = false;
            addScore (10);
        }
    }
    else { // Delivery mode
        if(!hasPackage && gameBoard->isPackage(x, y)) {
            hasPackage = true;
            gameBoard->removePackage(x, y);
        }
        else if(hasPackage && gameBoard->isPackageDestination(x, y)) {
            hasPackage = false;
            addScore (20);
        }
    }
}

// Time

void Vehicle::updateTime() {
    if (remainingTime > 0) {
        remainingTime--;
    }
}